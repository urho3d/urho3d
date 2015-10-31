// ================================================================================
// ==      This file is a part of Turbo Badger. (C) 2011-2014, Emil Segerås      ==
// ==                     See tb_core.h for more information.                    ==
// ================================================================================

#ifndef TB_IMAGE_MANAGER_H
#define TB_IMAGE_MANAGER_H

#include "tb_core.h"

#ifdef TB_IMAGE

#include "tb_linklist.h"
#include "tb_hashtable.h"
#include "tb_bitmap_fragment.h"
#include "tb_renderer.h"

namespace tb {

class TBImageManager;

/** TBImageRep is the internal contents of a TBImage. Owned by reference counting from TBImage. */

class TBImageRep
{
	friend class TBImageManager;
	friend class TBImage;

	TBImageRep(TBImageManager *image_manager, TBBitmapFragment *fragment, uint32 hash_key);

	void IncRef();
	void DecRef();

	int ref_count;
	uint32 hash_key;
	TBImageManager *image_manager;
	TBBitmapFragment *fragment;
};

/** TBImage is a reference counting object representing a image loaded by TBImageManager.
	As long as there are TBImage objects for a certain image, it will be kept loaded in memory.
	It may be empty if the image has not yet been set, or if the TBImageManager is destroyed
	when the image is still alive.
*/

class TBImage
{
public:
	TBImage() : m_image_rep(nullptr) {}
	TBImage(TBImageRep *rep);
	TBImage(const TBImage &image);
	~TBImage();

	/** Return true if this image is empty. */
	bool IsEmpty() const;

	/** Return the width of this image, or 0 if empty. */
	int Width() const;

	/** Return the height of this image, or 0 if empty. */
	int Height() const;

	/** Return the bitmap fragment for this image, or nullptr if empty. */
	TBBitmapFragment *GetBitmap() const;

	const TBImage& operator = (const TBImage &image) { SetImageRep(image.m_image_rep); return *this; }
	bool operator == (const TBImage &image) const { return m_image_rep == image.m_image_rep; }
	bool operator != (const TBImage &image) const { return m_image_rep != image.m_image_rep; }
private:
	void SetImageRep(TBImageRep *image_rep);
	TBImageRep *m_image_rep;
};

/** TBImageManager loads images returned as TBImage objects.

	It internally use a TBBitmapFragmentManager that create fragment maps for loaded images,
	and keeping track of which images are loaded so they are not loaded several times.

	Images are forgotten when there are no longer any TBImage objects for a given file.
*/

class TBImageManager : private TBRendererListener
{
public:
	TBImageManager();
	~TBImageManager();

	/** Return a image object for the given filename.
		If it fails, the returned TBImage object will be empty. */
	TBImage GetImage(const char *filename);

#ifdef TB_RUNTIME_DEBUG_INFO
	/** Render the skin bitmaps on screen, to analyze fragment positioning. */
	void Debug() { m_frag_manager.Debug(); }
#endif

	// Implementing TBRendererListener
	virtual void OnContextLost();
	virtual void OnContextRestored();
private:
	TBBitmapFragmentManager m_frag_manager;
	TBHashTableOf<TBImageRep> m_image_rep_hash;

	friend class TBImageRep;
	void RemoveImageRep(TBImageRep *image_rep);
};

/** The global TBImageManager. */
extern TBImageManager *g_image_manager;

}; // namespace tb

#endif // TB_IMAGE
#endif // TB_IMAGE_MANAGER_H
