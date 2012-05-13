/*
 * Note: The Nintendo DS port to SDL uses excerpts from the libGL2D,
 * with permission of the original author. The following is mostly his
 * code/comments.
 *
 *
 *	Easy GL2D
 *
 *	Relminator 2010 
 *	Richard Eric M. Lope BSN RN
 *
 *	http://rel.betterwebber.com
 *
 *	A very small and simple DS rendering lib using the 3d core to render 2D stuff
 */
#include "SDL_config.h"

#if SDL_VIDEO_RENDER_NDS

#include <nds/arm9/videoGL.h>

/* LibGL extension(s) */
static inline void gxTexcoord2i(t16 u, t16 v)
{
	GFX_TEX_COORD = (v << 20) | ((u << 4) & 0xFFFF);
}

static inline void gxVertex3i(v16 x, v16 y, v16 z)
{
	GFX_VERTEX16 = (y << 16) | (x & 0xFFFF);
	GFX_VERTEX16 = ((uint32)(uint16)z);
}

static inline void gxVertex2i(v16 x, v16 y)
{
	GFX_VERTEX_XY = (y << 16) | (x & 0xFFFF);	
}

/*
 * Enums selecting flipping mode.
 *
 *	These enums are bits for flipping the sprites.
 *	You can "|" (or) GL_FLIP_V and GL_FLIP_H to flip 
 *	both ways.
 */
typedef enum
{
	GL_FLIP_NONE 	= (1 << 0), /* No flipping */
	GL_FLIP_V 		= (1 << 1), /* Sprite is rendered vertically flipped */
	GL_FLIP_H 		= (1 << 2), /* Sprite is rendered horizontally flipped */
} GL_FLIP_MODE;

/* Struct for out GL-Based Images. */
typedef struct 
{
	int		width;		/* Width of the Sprite */      			
	int 	height;		/* Height of the Sprite */	
	int		textureID;  /* Texture handle (used in glDeleteTextures())
						   The texture handle in VRAM (returned by glGenTextures())
						   ie. This references the actual texture stored in VRAM. */
} glImage;

extern v16 g_depth;
extern int gCurrentTexture;

/*
 * Draws an Axis Exclusive Scaled Sprite
 * Parameters:
 *   x X position of the sprite.
 *   y Y position of the sprite.
 *   scaleX 20.12 fixed-point X-Axis scale value (1 << 12 is normal).
 *   scaleY 20.12 fixed-point Y-Axis scale value (1 << 12 is normal).
 *   flipmode mode for flipping (see GL_FLIP_MODE enum).
 *   *spr pointer to a glImage. 
*/
void glSpriteScaleXY(int x, int y, s32 scaleX, s32 scaleY, int flipmode, const glImage *spr);

/* Initializes our Tileset (like glInitSpriteset()) but without the use of Texture Packer auto-generated files.
 * Can only be used when tiles in a tilset are of the same dimensions.
 * Parameters:
 *   *sprite Pointer to an array of glImage.
 *   tile_wid Width of each tile in the texture.
 *   tile_hei Height of each tile in the texture.
 *   bmp_wid Width of of the texture or tileset.
 *   bmp_hei height of of the texture or tileset.
 *   type The format of the texture (see glTexImage2d()).
 *   sizeX The horizontal size of the texture; valid sizes are enumerated in GL_TEXTURE_TYPE_ENUM (see glTexImage2d()).
 *   sizeY The vertical size of the texture; valid sizes are enumerated in GL_TEXTURE_TYPE_ENUM (see glTexImage2d()).
 *   param parameters for the texture (see glTexImage2d()). 
 *   pallette_width Length of the palette. Valid values are <b>4, 16, 32, 256</b> (if <b>0</b>, then palette is removed from currently bound texture). 
 *   *palette Pointer to the palette data to load (if NULL, then palette is removed from currently bound texture).
 *   *texture Pointer to the texture data to load.
*/
int glLoadTile(glImage              *sprite,
			   int                  texture_width,
			   int                  texture_height,
			   int                  sprite_width,
			   int                  sprite_height,
			   GL_TEXTURE_TYPE_ENUM type,
			   int 	                param,
			   int					pallette_width,
			   const u16			*palette,
			   const uint8          *texture);

/* Initializes GL in 2D mode */
void glScreen2D(void);

/* 
 * Sets up OpenGL for 2d rendering. 
 *
 * Call this before drawing any of GL2D's drawing or sprite functions.
 */
void glBegin2D(void);

/*
 * Issue this after drawing 2d so that we don't mess the matrix stack.
 *
 * The complement of glBegin2D().
 */
void glEnd2D(void);

/*
 * Draws a Pixel
 *   x X position of the pixel.
 *   y Y position of the pixel.
 *   color RGB15/ARGB16 color.
 */
void glPutPixel(int x, int y, int color);

/*
 * Draws a Line
 *   x1,y1 Top-Left coordinate of the line.
 *   x2,y2 Bottom-Right coordinate of the line.
 *   color RGB15/ARGB16 color.
 */
void glLine(int x1, int y1, int x2, int y2, int color);

/* 
 * Draws a Box
 *   x1,y1 Top-Left coordinate of the box.
 *   x2,y2 Bottom-Right coordinate of the box.
 *   color RGB15/ARGB16 color.
*/
void glBox(int x1, int y1, int x2, int y2, int color);

/*
 * Draws a Filled Box
 *   x1,y1 Top-Left coordinate of the box.
 *   x2,y2 Bottom-Right coordinate of the box.
 *   color RGB15/ARGB16 color.
 */
void glBoxFilled(int x1, int y1, int x2, int y2, int color);

#endif /* SDL_VIDEO_RENDER_NDS */
