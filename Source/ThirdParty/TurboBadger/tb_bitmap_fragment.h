// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_BITMAP_FRAGMENT_H
#define TB_BITMAP_FRAGMENT_H

#include "tb_core.h"
#include "tb_geometry.h"
#include "tb_hashtable.h"
#include "tb_list.h"
#include "tb_id.h"
#include "tb_linklist.h"

namespace tb {

class TBBitmapFragment;
class TBBitmap;

/** Return the nearest power of two from val.
	F.ex 110 -> 128, 256->256, 257->512 etc. */
int TBGetNearestPowerOfTwo(int val);

/** TBImageloader is a class used to load skin images. It can be implemented
	in any way the system wants, but the system has to provide a image loader
	capable of handling all image formats used in the skin. */
class TBImageLoader
{
public:
	/** Static method used to create an image loader. The system must implement this
		function and create an implementation of the TBImageLoader interface. */
	static TBImageLoader *CreateFromFile(const char *filename);

	virtual ~TBImageLoader() {}

	/** Return the width of the loaded bitmap. */
	virtual int Width() = 0;

	/** Return the height of the loaded bitmap. */
	virtual int Height() = 0;

	/** Return the data of the loaded bitmap.
		This data should always be in 32bit RGBA format. */
	virtual uint32 *Data() = 0;
};

/** Allocator of space out of a given available space. */
class TBSpaceAllocator
{
public:
	/** A chunk of space */
	class Space : public TBLinkOf<Space>
	{
	public:
		int x, width;
	};

	TBSpaceAllocator(int available_space)
		: m_available_space(available_space) { }

	/** Return true if no allocations are currently live using this allocator. */
	bool IsAllAvailable() const { return !m_used_space_list.HasLinks(); }

	/** Return true if the given width is currently available. */
	bool HasSpace(int needed_w) const;

	/** Allocate the given space and return the Space, or nullptr on error. */
	Space *AllocSpace(int needed_w);

	/** Free the given space so it is available for new allocations. */
	void FreeSpace(Space *space);
private:
	Space *GetSmallestAvailableSpace(int needed_w);
	int m_available_space;
	TBLinkListAutoDeleteOf<Space> m_free_space_list;
	TBLinkListAutoDeleteOf<Space> m_used_space_list;
};

/** Allocates space for TBBitmapFragment in a row (used in TBBitmapFragmentMap). */
class TBFragmentSpaceAllocator : public TBSpaceAllocator
{
public:
	TBFragmentSpaceAllocator(int y, int width, int height)
		: TBSpaceAllocator(width), y(y), height(height) {}

	int y, height;
};

/** Specify when the bitmap should be validated when calling TBBitmapFragmentMap::GetBitmap. */
enum TB_VALIDATE_TYPE {

	/** Always validate the bitmap (The bitmap is updated if needed) */
	TB_VALIDATE_ALWAYS,

	/** Only validate if the bitmap does not yet exist (Make sure there is
		a valid bitmap pointer, but the data is not necessarily updated) */
	TB_VALIDATE_FIRST_TIME
};

/** TBBitmapFragmentMap is used to pack multiple bitmaps into a single TBBitmap.
	When initialized (in a size suitable for a TBBitmap) is also creates a software buffer
	that will make up the TBBitmap when all fragments have been added. */
class TBBitmapFragmentMap
{
public:
	TBBitmapFragmentMap();
	~TBBitmapFragmentMap();

	/** Initialize the map with the given size. The size should be a power of two since
		it will be used to create a TBBitmap (texture memory). */
	bool Init(int bitmap_w, int bitmap_h);

	/** Create a new fragment with the given size and data in this map.
		Returns nullptr if there is not enough room in this map or on any other fail. */
	TBBitmapFragment *CreateNewFragment(int frag_w, int frag_h, int data_stride, uint32 *frag_data, bool add_border);

	/** Free up the space used by the given fragment, so that other fragments can take its place. */
	void FreeFragmentSpace(TBBitmapFragment *frag);

	/** Return the bitmap for this map.
		By default, the bitmap is validated if needed before returning (See TB_VALIDATE_TYPE) */
	TBBitmap *GetBitmap(TB_VALIDATE_TYPE validate_type = TB_VALIDATE_ALWAYS);
private:
	friend class TBBitmapFragmentManager;
	bool ValidateBitmap();
	void DeleteBitmap();
	void CopyData(TBBitmapFragment *frag, int data_stride, uint32 *frag_data, int border);
	TBListAutoDeleteOf<TBFragmentSpaceAllocator> m_rows;
	int m_bitmap_w, m_bitmap_h;
	uint32 *m_bitmap_data;
	TBBitmap *m_bitmap;
	bool m_need_update;
	int m_allocated_pixels;
};

/** TBBitmapFragment represents a sub part of a TBBitmap.
	It's owned by TBBitmapFragmentManager which pack multiple
	TBBitmapFragment within TBBitmaps to reduce texture switching. */
class TBBitmapFragment
{
public:
	/** Return the width of the bitmap fragment. */
	int Width() const { return m_rect.w; }

	/** Return the height of the bitmap fragment. */
	int Height() const { return m_rect.h; }

	/** Return the bitmap for this fragment.
		By default, the bitmap is validated if needed before returning (See TB_VALIDATE_TYPE) */
	TBBitmap *GetBitmap(TB_VALIDATE_TYPE validate_type = TB_VALIDATE_ALWAYS) { return m_map->GetBitmap(validate_type); }

	/** Return the height allocated to this fragment. This may be larger than Height() depending
		of the internal allocation of fragments in a map. It should rarely be used. */
	int GetAllocatedHeight() const { return m_row_height; }
public:
	TBBitmapFragmentMap *m_map;
	TBRect m_rect;
	TBFragmentSpaceAllocator *m_row;
	TBFragmentSpaceAllocator::Space *m_space;
	TBID m_id;
	int m_row_height;

	/** This uint32 is reserved for batching renderer backends. It's not used
		internally, but always initialized to 0xffffffff for all new fragments. */
	uint32 m_batch_id;
};

/** TBBitmapFragmentManager manages loading bitmaps of arbitrary size,
	pack as many of them into as few TBBitmap as possible.

	It also makes sure that only one instance of each file is loaded,
	so f.ex loading "foo.png" many times still load and allocate one
	TBBitmapFragment. */
class TBBitmapFragmentManager
{
public:
	TBBitmapFragmentManager();
	~TBBitmapFragmentManager();

	/** Set to true if a 1px border should be added to new fragments so stretched
		drawing won't get filtering artifacts at the edges (default is disabled). */
	void SetAddBorder(bool add_border) { m_add_border = add_border; }
	bool GetAddBorder() const { return m_add_border; }

	/** Get the fragment with the given image filename. If it's not already loaded,
		it will be loaded into a new fragment with the filename as id.
		returns nullptr on fail. */
	TBBitmapFragment *GetFragmentFromFile(const char *filename, bool dedicated_map);

	/** Get the fragment with the given id, or nullptr if it doesn't exist. */
	TBBitmapFragment *GetFragment(const TBID &id) const;

	/** Create a new fragment from the given data.
		@param id The id that should be used to identify the fragment.
		@param dedicated_map if true, it will get a dedicated map.
		@param data_w the width of the data.
		@param data_h the height of the data.
		@param data_stride the number of pixels in a row of the input data.
		@param data pointer to the data in BGRA32 format. */
	TBBitmapFragment *CreateNewFragment(const TBID &id, bool dedicated_map,
										int data_w, int data_h, int data_stride,
										uint32 *data);

	/** Delete the given fragment and free the space it used in its map,
		so that other fragments can take its place. */
	void FreeFragment(TBBitmapFragment *frag);

	/** Clear all loaded bitmaps and all created bitmap fragments and maps.
		After this call, do not keep any pointers to any TBBitmapFragment created
		by this fragment manager. */
	void Clear();

	/** Validate bitmaps on fragment maps that has changed. */
	bool ValidateBitmaps();

	/** Delete all bitmaps in all fragment maps in this manager.
		The bitmaps will be recreated automatically when needed, or when
		calling ValidateBitmaps. You do not need to call this, except when
		the context is lost and all bitmaps must be forgotten. */
	void DeleteBitmaps();

	/** Get number of fragment maps that is currently used. */
	int GetNumMaps() const { return m_fragment_maps.GetNumItems(); }

	/** Set the number of maps (TBBitmaps) this manager should be allowed to create.
		If a new fragment can't fit into any existing bitmap and the limit is reached,
		the fragment creation will fail. Set to 0 for unlimited (default). */
	void SetNumMapsLimit(int num_maps_limit);

	/** Set the default size of new fragment maps. These must be power of two. */
	void SetDefaultMapSize(int w, int h);

	/** Get the amount (in percent) of space that is currently occupied by all maps
		in this fragment manager. */
	int GetUseRatio() const;
#ifdef TB_RUNTIME_DEBUG_INFO
	/** Render the maps on screen, to analyze fragment positioning. */
	void Debug();
#endif
private:
	TBListOf<TBBitmapFragmentMap> m_fragment_maps;
	TBHashTableOf<TBBitmapFragment> m_fragments;
	int m_num_maps_limit;
	bool m_add_border;
	int m_default_map_w;
	int m_default_map_h;
};

}; // namespace tb

#endif // TB_BITMAP_FRAGMENT_H
