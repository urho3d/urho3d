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

#include "SDL_libgl2D.h"

/*
 * Our static global variable used for Depth values since we cannot
 * disable depth testing in the DS hardware This value is incremented
 * for every draw call. */
v16 g_depth;
int gCurrentTexture;

/*
 * !!! PRIVATE !!!  Set orthographic projection at 1:1 correspondence
 * to screen coords glOrtho expects f32 values but if we use the
 * standard f32 values, we need to rescale either every vert or the
 * modelview matrix by the same amount to make it work.  That's gonna
 * give us lots of overflows and headaches.  So we "scale down" and
 * use an all integer value.
 */
void SetOrtho(void)		
{
	glMatrixMode(GL_PROJECTION); // set matrixmode to projection
	glLoadIdentity();			   // reset
	glOrthof32(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1 << 12, 1 << 12);  // downscale projection matrix
}

/*
 * Initializes GL in 2D mode Also initializes GL in 3d mode so that we
 * could combine 2D and 3D later Almost a direct copy from the DS
 * example files
 */
void glScreen2D(void)
{
	// initialize gl
	glInit();
	
	// enable textures
	glEnable(GL_TEXTURE_2D);
	
	// enable antialiasing
	glEnable(GL_ANTIALIAS);
		
	// setup the rear plane
	glClearColor(0, 0, 0, 31); // BG must be opaque for AA to work
	glClearPolyID(63); // BG must have a unique polygon ID for AA to work
	
	glClearDepth(GL_MAX_DEPTH);

	// this should work the same as the normal gl call
	glViewport(0,0,255,191);

	// any floating point gl call is being converted to fixed prior to being implemented
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 256.0 / 192.0, 1, 200);

	gluLookAt(	0.0, 0.0, 1.0,		//camera possition 
				0.0, 0.0, 0.0,		//look at
				0.0, 1.0, 0.0);		//up

	glMaterialf(GL_AMBIENT, RGB15(31,31,31));
	glMaterialf(GL_DIFFUSE, RGB15(31,31,31));
	glMaterialf(GL_SPECULAR, BIT(15) | RGB15(31,31,31));
	glMaterialf(GL_EMISSION, RGB15(31,31,31));

	// ds uses a table for shinyness..this generates a half-ass one
	glMaterialShinyness();

	// not a real gl function and will likely change
	glPolyFmt(POLY_ALPHA(31) | POLY_CULL_BACK);
}

/*
 * Sets up OpenGL for 2d rendering Call this before drawing any of
 * GL2D's drawing or sprite functions.
 */
void glBegin2D(void)
{
	// save 3d perpective projection matrix
	glMatrixMode(GL_PROJECTION);   
    glPushMatrix();
	
	// save 3d modelview matrix for safety
	glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
	
	
	// what?!! No glDisable(GL_DEPTH_TEST)?!!!!!!
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_ANTIALIAS);	// disable AA
	glDisable(GL_OUTLINE);	// disable edge-marking

	glColor(0x7FFF);			// max color
	
	glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE);  // no culling

	SetOrtho();
	
	glMatrixMode(GL_TEXTURE);	// reset texture matrix just in case we did some funky stuff with it
	glLoadIdentity();
	
	glMatrixMode(GL_MODELVIEW); // reset modelview matrix. No need to scale up by << 12
	glLoadIdentity();

	gCurrentTexture = 0;		// set current texture to 0 
	g_depth = 0; // set depth to 0. We need this var since we cannot disable depth testing
}

/*
 * Issue this after drawing 2d so that we don't mess the matrix stack.
 * The complement of glBegin2D.
 */
void glEnd2D(void)
{
	// restore 3d matrices and set current matrix to modelview
	glMatrixMode(GL_PROJECTION);    
    glPopMatrix(1);
	glMatrixMode(GL_MODELVIEW);
    glPopMatrix(1);
}

/*
 * Draws a pixel
 * Parameters:
 *   x,y 	-> First coordinate of the line 
 *   color 	-> RGB15/ARGB16 color 
 */
void glPutPixel(int x, int y, int color)
{
	glBindTexture(0, 0);
	glColor(color);
	glBegin(GL_TRIANGLES);
		gxVertex3i(x, y, g_depth);
		gxVertex2i(x, y);
		gxVertex2i(x, y);
	glEnd();
	glColor(0x7FFF);
	g_depth++;
	gCurrentTexture = 0;
}

/*
 * Draws a line
 * Parameters:
 *   x1,y1 	-> First coordinate of the line 
 *   x2,y2 	-> Second coordinate of the line 
 *   color 	-> RGB15/ARGB16 color
 */
void glLine(int x1, int y1, int x2, int y2, int color)
{
	x2++;
	y2++;
	
	glBindTexture(0, 0);
	glColor(color);
	glBegin(GL_TRIANGLES);
		gxVertex3i(x1, y1, g_depth);
		gxVertex2i(x2, y2);
		gxVertex2i(x2, y2);
	glEnd();
	glColor(0x7FFF);
	g_depth++;
	gCurrentTexture = 0;
}

/*
 * Draws a Filled Box
 * Parameters:
 *   x1,y1 	-> Top-left corner of the box 
 *   x2,y2 	-> Bottom-Right corner of the box 
 *   color 	-> RGB15/ARGB16 color 
*/
void glBoxFilled(int x1, int y1, int x2, int y2, int color)
{
	x2++;
	y2++;
	
	glBindTexture(0, 0);
	glColor(color);
	glBegin(GL_QUADS);
		gxVertex3i(x1, y1, g_depth); // use 3i for first vertex so that we increment HW depth
		gxVertex2i(x1, y2); // no need for 3 vertices as 2i would share last depth call
		gxVertex2i(x2, y2);
		gxVertex2i(x2, y1);
	glEnd();
	glColor(0x7FFF);
	g_depth++;
	gCurrentTexture = 0;
}

/*
 *
 * Create a tile.
 * Very rigid and prone to human error.
 *
 * Parameters:
 *   *sprite 		 -> pointer to a glImage
 *   texture_width   -> width/height of the texture;
 *   texture_height  ->  valid sizes are enumerated in GL_TEXTURE_TYPE_ENUM (see glTexImage2d)
 *   sprite_width
 *   sprite_height   -> width/height of the picture in the texture.
 *   type 		     -> The format of the texture (see glTexImage2d)
 *   param 		     -> parameters for the texture (see glTexImage2d)
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
			   const uint8          *texture)
{
	int textureID;

	glGenTextures(1, &textureID);
	glBindTexture(0, textureID);
	glTexImage2D(0, 0, type, texture_width, texture_height, 0, param, texture);
	glColorTableEXT(0, 0, pallette_width, 0, 0, palette);

	sprite->width 			= sprite_width;
	sprite->height 			= sprite_height;
	sprite->textureID 		= textureID;
	
	return textureID;
}

/*
 * I made this since the scale wrappers are either the vectorized mode
 * or does not permit you to scale only the axis you want to
 * scale. Needed for sprite scaling.
 */
static inline void gxScalef32(s32 x, s32 y, s32 z)
{
	MATRIX_SCALE = x;
	MATRIX_SCALE = y;
	MATRIX_SCALE = z;
}

/*
 * I this made for future naming conflicts.
 */
static inline void gxTranslate3f32(int32 x, int32 y, int32 z) 
{
	MATRIX_TRANSLATE = x;
	MATRIX_TRANSLATE = y;
	MATRIX_TRANSLATE = z;
}

/*
 * Draws an axis exclusive scaled sprite
 * Parameters:
 *   x 			-> x position of the sprite
 *   y 			-> y position of the sprite
 *   scaleX   	-> 20.12 FP X axis scale value (1 << 12 is normal)
 *   scaleY   	-> 20.12 FP Y axis scale value (1 << 12 is normal)
 *   flipmode 	-> mode for flipping (see GL_FLIP_MODE enum)
 *   *spr 		-> pointer to a glImage
 */
void glSpriteScaleXY(int x, int y, s32 scaleX, s32 scaleY, int flipmode, const glImage *spr)
{
	const int x1 = 0;
	const int y1 = 0;
	const int x2 = spr->width;
	const int y2 = spr->height;
	const int u1 = ((flipmode & GL_FLIP_H) ? spr->width-1  : 0);
 	const int u2 = ((flipmode & GL_FLIP_H) ? 0 : spr->width-1);
	const int v1 = ((flipmode & GL_FLIP_V) ? spr->height-1 : 0);
	const int v2 = ((flipmode & GL_FLIP_V) ? 0 : spr->height-1);
 
    if (spr->textureID != gCurrentTexture)
    {
        glBindTexture(GL_TEXTURE_2D, spr->textureID);
        gCurrentTexture = spr->textureID;
    }

	glPushMatrix();

		gxTranslate3f32(x, y, 0);
		gxScalef32(scaleX, scaleY, 1 << 12);

		glBegin(GL_QUADS);
			
			gxTexcoord2i(u1, v1); gxVertex3i(x1, y1, g_depth);	
			gxTexcoord2i(u1, v2); gxVertex2i(x1, y2);
			gxTexcoord2i(u2, v2); gxVertex2i(x2, y2);
			gxTexcoord2i(u2, v1); gxVertex2i(x2, y1);
			
		glEnd();
	
	glPopMatrix(1);
	g_depth++;
}

#endif /* SDL_VIDEO_RENDER_NDS */
