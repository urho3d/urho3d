// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#include "tb_bitmap_fragment.h"
#include "tb_renderer.h"
#include "tb_system.h"

namespace tb {

int TBGetNearestPowerOfTwo(int val)
{
	int i;
	for(i = 31; i >= 0; i--)
		if ((val - 1) & (1<<i))
			break;
	return (1<<(i + 1));
}

// == TBSpaceAllocator ======================================================================================

bool TBSpaceAllocator::HasSpace(int needed_w) const
{
	if (needed_w > m_available_space)
		return false;
	if (IsAllAvailable())
		return true;
	for (Space *fs = m_free_space_list.GetFirst(); fs; fs = fs->GetNext())
	{
		if (needed_w <= fs->width)
			return true;
	}
	return false;
}

TBSpaceAllocator::Space *TBSpaceAllocator::AllocSpace(int needed_w)
{
	if (Space *available_space = GetSmallestAvailableSpace(needed_w))
	{
		if (Space *new_space = new Space)
		{
			new_space->x = available_space->x;
			new_space->width = needed_w;
			m_used_space_list.AddLast(new_space);

			// Consume the used space from the available space
			available_space->x += needed_w;
			available_space->width -= needed_w;
			m_available_space -= needed_w;

			// Remove it if empty
			if (!available_space->width)
				m_free_space_list.Delete(available_space);
			return new_space;
		}
	}
	return nullptr;
}

TBSpaceAllocator::Space *TBSpaceAllocator::GetSmallestAvailableSpace(int needed_w)
{
	assert(needed_w > 0);

	// Add free space covering all available space if empty.
	if (!m_free_space_list.HasLinks() && IsAllAvailable())
	{
		if (Space *fs = new Space)
		{
			fs->x = 0;
			fs->width = m_available_space;
			m_free_space_list.AddLast(fs);
		}
	}

	// Check for the smallest space where we fit
	Space *best_fs = nullptr;
	for (Space *fs = m_free_space_list.GetFirst(); fs; fs = fs->GetNext())
	{
		if (needed_w == fs->width)
			return fs; // It can't be better than a perfect match!
		if (needed_w < fs->width)
			if (!best_fs || fs->width < best_fs->width)
				best_fs = fs;
	}
	return best_fs;
}

void TBSpaceAllocator::FreeSpace(Space *space)
{
	m_used_space_list.Remove(space);
	m_available_space += space->width;

	// Find where in m_free_space_list we should insert the space,
	// or which existing space we can extend.
	Space *preceeding = nullptr;
	Space *succeeding = nullptr;
	for (Space *fs = m_free_space_list.GetFirst(); fs; fs = fs->GetNext())
	{
		if (fs->x < space->x)
			preceeding = fs;
		if (fs->x > space->x)
		{
			succeeding = fs;
			break;
		}
	}
	if (preceeding && preceeding->x + preceeding->width == space->x)
	{
		preceeding->width += space->width;
		delete space;
	}
	else if (succeeding && succeeding->x == space->x + space->width)
	{
		succeeding->x -= space->width;
		succeeding->width += space->width;
		delete space;
	}
	else
	{
		if (preceeding)
			m_free_space_list.AddAfter(space, preceeding);
		else if (succeeding)
			m_free_space_list.AddBefore(space, succeeding);
		else
		{
			assert(!m_free_space_list.HasLinks());
			m_free_space_list.AddLast(space);
		}
	}
	// Merge free spaces
	Space *fs = m_free_space_list.GetFirst();
	while (fs)
	{
		Space *next_fs = fs->GetNext();
		if (!next_fs)
			break;
		if (fs->x + fs->width == next_fs->x)
		{
			fs->width += next_fs->width;
			m_free_space_list.Delete(next_fs);
			continue;
		}
		fs = next_fs;
	}

#ifdef TB_RUNTIME_DEBUG_INFO
	// Check that free space is in order
	Space *tmp = m_free_space_list.GetFirst();
	int x = 0;
	while (tmp)
	{
		assert(tmp->x >= x);
		x = tmp->x + tmp->width;
		tmp = tmp->GetNext();
	}
#endif // TB_RUNTIME_DEBUG_INFO
}

// == TBBitmapFragmentMap ===================================================================================

TBBitmapFragmentMap::TBBitmapFragmentMap()
	: m_bitmap_w(0)
	, m_bitmap_h(0)
	, m_bitmap_data(nullptr)
	, m_bitmap(nullptr)
	, m_need_update(false)
	, m_allocated_pixels(0)
{
}

bool TBBitmapFragmentMap::Init(int bitmap_w, int bitmap_h)
{
	m_bitmap_data = new uint32[bitmap_w * bitmap_h];
	m_bitmap_w = bitmap_w;
	m_bitmap_h = bitmap_h;
#ifdef TB_RUNTIME_DEBUG_INFO
	if (m_bitmap_data)
		memset(m_bitmap_data, 0x88, bitmap_w * bitmap_h * sizeof(uint32));
#endif
	return m_bitmap_data ? true : false;
}

TBBitmapFragmentMap::~TBBitmapFragmentMap()
{
	delete m_bitmap;
	delete [] m_bitmap_data;
}

TBBitmapFragment *TBBitmapFragmentMap::CreateNewFragment(int frag_w, int frag_h, int data_stride, uint32 *frag_data, bool add_border)
{
	// Finding available space works like this:
	// The map size is sliced up horizontally in rows (initially just one row covering
	// the entire map). When adding a new fragment, put it in the row with smallest height.
	// If the smallest row is empty, it may slice the row to make a even smaller row.

	// When a image is stretched up to a larger size, the filtering will read
	// pixels closest (but outside) of the src_rect. When we pack images together
	// those pixels would be read from neighbour images, so we must add border space
	// around each image to avoid artifacts. We must also fill in that border with
	// the "clamp" of the image itself so we don't get any filtering artifacts at all.
	// Allways add border except when we're using the entire map for one fragment.
	int border = 0;
	int needed_w = frag_w;
	int needed_h = frag_h;
	if (add_border)
	{
		if (needed_w != m_bitmap_w || needed_h != m_bitmap_h)
		{
			border = 1;
			needed_w += 2;
			needed_h += 2;
		}
	}

	// Snap the fragments to a certain granularity. This could maybe ease the stress
	// on the space allocator when allocating & deallocating lots of small fragments.
	// I'm not sure there is any performance issue though and it would be better to
	// optimize the algorithm instead (so disabled it for now).
	//const int granularity = 8;
	//needed_w = (needed_w + granularity - 1) / granularity * granularity;
	//needed_h = (needed_h + granularity - 1) / granularity * granularity;

	if (!m_rows.GetNumItems())
	{
		// Create a row covering the entire bitmap.
		TBFragmentSpaceAllocator *row;
		if (!m_rows.GrowIfNeeded() || !(row = new TBFragmentSpaceAllocator(0, m_bitmap_w, m_bitmap_h)))
			return nullptr;
		m_rows.Add(row);
	}
	// Get the smallest row where we fit
	int best_row_index = -1;
	TBFragmentSpaceAllocator *best_row = nullptr;
	for (int i = 0; i < m_rows.GetNumItems(); i++)
	{
		TBFragmentSpaceAllocator *row = m_rows[i];
		if (!best_row || row->height < best_row->height)
		{
			// This is the best row so far, if we fit
			if (needed_h <= row->height && row->HasSpace(needed_w))
			{
				best_row = row;
				best_row_index = i;
				if (needed_h == row->height)
					break; // We can't find a smaller line, so we're done
			}
		}
	}
	// Return if we're full
	if (!best_row)
		return nullptr;
	// If the row is unused, create a smaller row to only consume needed height for fragment
	if (best_row->IsAllAvailable() && needed_h < best_row->height)
	{
		TBFragmentSpaceAllocator *row;
		if (!m_rows.GrowIfNeeded() || !(row = new TBFragmentSpaceAllocator(best_row->y + needed_h, m_bitmap_w, best_row->height - needed_h)))
			return nullptr;
		// Keep the rows sorted from top to bottom
		m_rows.Add(row, best_row_index + 1);
		best_row->height = needed_h;
	}
	// Allocate the fragment and copy the fragment data into the map data.
	if (TBFragmentSpaceAllocator::Space *space = best_row->AllocSpace(needed_w))
	{
		if (TBBitmapFragment *frag = new TBBitmapFragment)
		{
			frag->m_map = this;
			frag->m_row = best_row;
			frag->m_space = space;
			frag->m_rect.Set(space->x + border, best_row->y + border, frag_w, frag_h);
			frag->m_row_height = best_row->height;
			frag->m_batch_id = 0xffffffff;
			CopyData(frag, data_stride, frag_data, border);
			m_need_update = true;
			m_allocated_pixels += frag->m_space->width * frag->m_row->height;
			return frag;
		}
		else
			best_row->FreeSpace(space);
	}
	return nullptr;
}

void TBBitmapFragmentMap::FreeFragmentSpace(TBBitmapFragment *frag)
{
	if (!frag)
		return;
	assert(frag->m_map == this);

#ifdef TB_RUNTIME_DEBUG_INFO
	// Debug code to clear the area in debug builds so it's easier to
	// see & debug the allocation & deallocation of fragments in maps.
	if (uint32 *data32 = new uint32[frag->m_space->width * frag->m_row->height])
	{
		static int c = 0;
		memset(data32, (c++) * 32, sizeof(uint32) * frag->m_space->width * frag->m_row->height);
		CopyData(frag, frag->m_space->width, data32, false);
		m_need_update = true;
		delete [] data32;
	}
#endif // TB_RUNTIME_DEBUG_INFO

	m_allocated_pixels -= frag->m_space->width * frag->m_row->height;
	frag->m_row->FreeSpace(frag->m_space);
	frag->m_space = nullptr;
	frag->m_row_height = 0;

	// If the row is now empty, merge empty rows so larger fragments
	// have a chance of allocating the space.
	if (frag->m_row->IsAllAvailable())
	{
		for (int i = 0; i < m_rows.GetNumItems() - 1; i++)
		{
			assert(i >= 0);
			assert(i < m_rows.GetNumItems() - 1);
			TBFragmentSpaceAllocator *row = m_rows.Get(i);
			TBFragmentSpaceAllocator *next_row = m_rows.Get(i + 1);
			if (row->IsAllAvailable() && next_row->IsAllAvailable())
			{
				row->height += next_row->height;
				m_rows.Delete(i + 1);
				i--;
			}
		}
	}
}

void TBBitmapFragmentMap::CopyData(TBBitmapFragment *frag, int data_stride, uint32 *frag_data, int border)
{
	// Copy the bitmap data
	uint32 *dst = m_bitmap_data + frag->m_rect.x + frag->m_rect.y * m_bitmap_w;
	uint32 *src = frag_data;
	for (int i = 0; i < frag->m_rect.h; i++)
	{
		memcpy(dst, src, frag->m_rect.w * sizeof(uint32));
		dst += m_bitmap_w;
		src += data_stride;
	}
	// Copy the bitmap data to the border around the fragment
	if (border)
	{
		TBRect rect = frag->m_rect.Expand(border, border);
		// Copy vertical edges
		dst = m_bitmap_data + rect.x + (rect.y + 1) * m_bitmap_w;
		src = frag_data;
		for (int i = 0; i < frag->m_rect.h; i++)
		{
			dst[0] = src[0] & 0x00ffffff;
			dst[rect.w - 1] = src[frag->m_rect.w - 1] & 0x00ffffff;
			dst += m_bitmap_w;
			src += data_stride;
		}
		// Copy horizontal edges
		dst = m_bitmap_data + rect.x + 1 + rect.y * m_bitmap_w;
		src = frag_data;
		for (int i = 0; i < frag->m_rect.w; i++)
			dst[i] = src[i] & 0x00ffffff;
		dst = m_bitmap_data + rect.x + 1 + (rect.y + rect.h - 1) * m_bitmap_w;
		src = frag_data + (frag->m_rect.h - 1) * data_stride;
		for (int i = 0; i < frag->m_rect.w; i++)
			dst[i] = src[i] & 0x00ffffff;
	}
}

TBBitmap *TBBitmapFragmentMap::GetBitmap(TB_VALIDATE_TYPE validate_type)
{
	if (m_bitmap && validate_type == TB_VALIDATE_FIRST_TIME)
		return m_bitmap;
	ValidateBitmap();
	return m_bitmap;
}

bool TBBitmapFragmentMap::ValidateBitmap()
{
	if (m_need_update)
	{
		if (m_bitmap)
			m_bitmap->SetData(m_bitmap_data);
		else
			m_bitmap = g_renderer->CreateBitmap(m_bitmap_w, m_bitmap_h, m_bitmap_data);
		m_need_update = false;
	}
	return m_bitmap ? true : false;
}

void TBBitmapFragmentMap::DeleteBitmap()
{
	delete m_bitmap;
	m_bitmap = nullptr;
	m_need_update = true;
}

// == TBBitmapFragmentManager =============================================================================

TBBitmapFragmentManager::TBBitmapFragmentManager()
	: m_num_maps_limit(0)
	, m_add_border(false)
	, m_default_map_w(512)
	, m_default_map_h(512)
{
}

TBBitmapFragmentManager::~TBBitmapFragmentManager()
{
	Clear();
}

TBBitmapFragment *TBBitmapFragmentManager::GetFragmentFromFile(const char *filename, bool dedicated_map)
{
	TBID id(filename);

	// If we already have a fragment for this filename, return that
	TBBitmapFragment *frag = m_fragments.Get(id);
	if (frag)
		return frag;

	// Load the file
	TBImageLoader *img = TBImageLoader::CreateFromFile(filename);
	if (!img)
		return nullptr;

	frag = CreateNewFragment(id, dedicated_map, img->Width(), img->Height(), img->Width(), img->Data());
	delete img;
	return frag;
}

TBBitmapFragment *TBBitmapFragmentManager::CreateNewFragment(const TBID &id, bool dedicated_map,
															 int data_w, int data_h, int data_stride,
															 uint32 *data)
{
	assert(!GetFragment(id));

	TBBitmapFragment *frag = nullptr;

	// Create a fragment in any of the fragment maps. Doing it in the reverse order
	// would be faster since it's most likely to succeed, but we want to maximize
	// the amount of fragments per map, so do it in the creation order.
	if (!dedicated_map)
	{
		for (int i = 0; i < m_fragment_maps.GetNumItems(); i++)
		{
			if ((frag = m_fragment_maps[i]->CreateNewFragment(data_w, data_h, data_stride, data, m_add_border)))
				break;
		}
	}
	// If we couldn't create the fragment in any map, create a new map where we know it will fit.
	bool allow_another_map = (m_num_maps_limit == 0 || m_fragment_maps.GetNumItems() < m_num_maps_limit);
	if (!frag && allow_another_map && m_fragment_maps.GrowIfNeeded())
	{
		int po2w = TBGetNearestPowerOfTwo(MAX(data_w, m_default_map_w));
		int po2h = TBGetNearestPowerOfTwo(MAX(data_h, m_default_map_h));
		if (dedicated_map)
		{
			po2w = TBGetNearestPowerOfTwo(data_w);
			po2h = TBGetNearestPowerOfTwo(data_h);
		}
		TBBitmapFragmentMap *fm = new TBBitmapFragmentMap();
		if (fm && fm->Init(po2w, po2h))
		{
			m_fragment_maps.Add(fm);
			frag = fm->CreateNewFragment(data_w, data_h, data_stride, data, m_add_border);
		}
		else
			delete fm;
	}
	// Finally, add the new fragment to the hash.
	if (frag && m_fragments.Add(id, frag))
	{
		frag->m_id = id;
		return frag;
	}
	delete frag;
	return nullptr;
}

void TBBitmapFragmentManager::FreeFragment(TBBitmapFragment *frag)
{
	if (frag)
	{
		g_renderer->FlushBitmapFragment(frag);

		TBBitmapFragmentMap *map = frag->m_map;
		frag->m_map->FreeFragmentSpace(frag);
		m_fragments.Delete(frag->m_id);

		// If the map is now empty, delete it.
		if (map->m_allocated_pixels == 0)
			m_fragment_maps.Delete(m_fragment_maps.Find(map));
	}
}

TBBitmapFragment *TBBitmapFragmentManager::GetFragment(const TBID &id) const
{
	return m_fragments.Get(id);
}

void TBBitmapFragmentManager::Clear()
{
	m_fragment_maps.DeleteAll();
	m_fragments.DeleteAll();
}

bool TBBitmapFragmentManager::ValidateBitmaps()
{
	bool success = true;
	for (int i = 0; i < m_fragment_maps.GetNumItems(); i++)
		if (!m_fragment_maps[i]->ValidateBitmap())
			success = false;
	return success;
}

void TBBitmapFragmentManager::DeleteBitmaps()
{
	for (int i = 0; i < m_fragment_maps.GetNumItems(); i++)
		m_fragment_maps[i]->DeleteBitmap();
}

void TBBitmapFragmentManager::SetNumMapsLimit(int num_maps_limit)
{
	m_num_maps_limit = num_maps_limit;
}

void TBBitmapFragmentManager::SetDefaultMapSize(int w, int h)
{
	assert(TBGetNearestPowerOfTwo(w) == w);
	assert(TBGetNearestPowerOfTwo(h) == h);
	m_default_map_w = w;
	m_default_map_h = h;
}

int TBBitmapFragmentManager::GetUseRatio() const
{
	int used = 0;
	int total = 0;
	for (int i = 0; i < m_fragment_maps.GetNumItems(); i++)
	{
		used += m_fragment_maps[i]->m_allocated_pixels;
		total += m_fragment_maps[i]->m_bitmap_w * m_fragment_maps[i]->m_bitmap_h;
	}
	return total ? (used * 100) / total : 0;
}

#ifdef TB_RUNTIME_DEBUG_INFO
void TBBitmapFragmentManager::Debug()
{
	int x = 0;
	for (int i = 0; i < m_fragment_maps.GetNumItems(); i++)
	{
		TBBitmapFragmentMap *fm = m_fragment_maps[i];
		if (TBBitmap *bitmap = fm->GetBitmap())
			g_renderer->DrawBitmap(TBRect(x, 0, fm->m_bitmap_w, fm->m_bitmap_h), TBRect(0, 0, fm->m_bitmap_w, fm->m_bitmap_h), bitmap);
		x += fm->m_bitmap_w + 5;
	}
}
#endif // TB_RUNTIME_DEBUG_INFO

}; // namespace tb
