/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2011 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGLDrawable.h>
#import "SDL_uikitopenglview.h"

@interface SDL_uikitopenglview (privateMethods)

- (BOOL) createFramebuffer;
- (void) destroyFramebuffer;

@end


@implementation SDL_uikitopenglview

@synthesize context;

+ (Class)layerClass {
    return [CAEAGLLayer class];
}

- (id)initWithFrame:(CGRect)frame \
      retainBacking:(BOOL)retained \
      rBits:(int)rBits \
      gBits:(int)gBits \
      bBits:(int)bBits \
      aBits:(int)aBits \
      depthBits:(int)depthBits \
      majorVersion:(int)majorVersion \
{
    NSString *colorFormat=nil;
    BOOL useDepthBuffer;
    
    if (rBits == 8 && gBits == 8 && bBits == 8) {
        /* if user specifically requests rbg888 or some color format higher than 16bpp */
        colorFormat = kEAGLColorFormatRGBA8;
    }
    else {
        /* default case (faster) */
        colorFormat = kEAGLColorFormatRGB565;
    }
    
    depthBufferFormat = 0;

    if (depthBits == 24) {
        useDepthBuffer = YES;
        depthBufferFormat = GL_DEPTH_COMPONENT24_OES;
    }
    else if (depthBits == 0) {
        useDepthBuffer = NO;
    }
    else {
        /* default case when depth buffer is not disabled */
        /* 
           strange, even when we use this, we seem to get a 24 bit depth buffer on iPhone.
           perhaps that's the only depth format iPhone actually supports
        */
        useDepthBuffer = YES;
        depthBufferFormat = GL_DEPTH_COMPONENT16_OES;
    }
    
    if ((self = [super initWithFrame:frame])) {
        // Get the layer
        CAEAGLLayer *eaglLayer = (CAEAGLLayer *)self.layer;
        
        eaglLayer.opaque = YES;
        eaglLayer.drawableProperties = [NSDictionary dictionaryWithObjectsAndKeys:
                                        [NSNumber numberWithBool: retained], kEAGLDrawablePropertyRetainedBacking, colorFormat, kEAGLDrawablePropertyColorFormat, nil];
        
        if (majorVersion > 1) {
            context = [[EAGLContext alloc] initWithAPI: kEAGLRenderingAPIOpenGLES2];
        } else {
            context = [[EAGLContext alloc] initWithAPI: kEAGLRenderingAPIOpenGLES1];
        }
        if (!context || ![EAGLContext setCurrentContext:context]) {
            [self release];
            return nil;
        }
        
        /* create the buffers */
        glGenFramebuffersOES(1, &viewFramebuffer);
        glGenRenderbuffersOES(1, &viewRenderbuffer);
        
        glBindFramebufferOES(GL_FRAMEBUFFER_OES, viewFramebuffer);
        glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
        [context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:(CAEAGLLayer*)self.layer];
        glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, viewRenderbuffer);
        
        glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth);
        glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight);

        if (useDepthBuffer) {
            glGenRenderbuffersOES(1, &depthRenderbuffer);
            glBindRenderbufferOES(GL_RENDERBUFFER_OES, depthRenderbuffer);
            glRenderbufferStorageOES(GL_RENDERBUFFER_OES, depthBufferFormat, backingWidth, backingHeight);
            glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, depthRenderbuffer);
        }
            
        if(glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES) != GL_FRAMEBUFFER_COMPLETE_OES) {
            return NO;
        }
        /* end create buffers */

        // !!! FIXME: use the screen this is on!
        /* Use the main screen scale (for retina display support) */
        if ([[UIScreen mainScreen] respondsToSelector:@selector(scale)])
            self.contentScaleFactor = [UIScreen mainScreen].scale;

        self.autoresizingMask = 0;  // don't allow autoresize, since we need to do some magic in -(void)updateFrame.
    }
    return self;
}

- (void)updateFrame {
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, viewFramebuffer);
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, 0);
    glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, 0);
    glDeleteRenderbuffersOES(1, &viewRenderbuffer);

    glGenRenderbuffersOES(1, &viewRenderbuffer);
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
    [context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:(CAEAGLLayer*)self.layer];
    glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, viewRenderbuffer);  

    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth);
    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight);

    if (depthRenderbuffer != 0) {
        glBindRenderbufferOES(GL_RENDERBUFFER_OES, depthRenderbuffer);
        glRenderbufferStorageOES(GL_RENDERBUFFER_OES, depthBufferFormat, backingWidth, backingHeight);
    }
    
    // !!! FIXME: use the screen this is on!
    /* Use the main screen scale (for retina display support) */
    if ([[UIScreen mainScreen] respondsToSelector:@selector(scale)])
        self.contentScaleFactor = [UIScreen mainScreen].scale;
}

- (void)setCurrentContext {
    [EAGLContext setCurrentContext:context];
}


- (void)swapBuffers {
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, viewRenderbuffer);
    [context presentRenderbuffer:GL_RENDERBUFFER_OES];
}


- (void)layoutSubviews {
    [EAGLContext setCurrentContext:context];
}

- (void)destroyFramebuffer {
    glDeleteFramebuffersOES(1, &viewFramebuffer);
    viewFramebuffer = 0;
    glDeleteRenderbuffersOES(1, &viewRenderbuffer);
    viewRenderbuffer = 0;
    
    if (depthRenderbuffer) {
        glDeleteRenderbuffersOES(1, &depthRenderbuffer);
        depthRenderbuffer = 0;
    }
}


- (void)dealloc {
    [self destroyFramebuffer];
    if ([EAGLContext currentContext] == context) {
        [EAGLContext setCurrentContext:nil];
    }
    [context release];    
    [super dealloc];
}

@end

/* vi: set ts=4 sw=4 expandtab: */
