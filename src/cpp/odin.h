#ifndef ODIN_H
#define ODIN_H

#include "pxr/imaging/garch/glApi.h"

extern "C" {   

void odin_init();
void odin_cleanup();
void odin_render(void* buffer_data, int width, int height);
void odin_clear();


// OpenGL functions
void gl_funcptr_setup();
void odin_glClearColor(void (*func_ptr)(float, float, float, float));
void odin_glClear(void (*func_ptr)(GLbitfield));

    // glGenFramebuffers(1, &framebuffer);
    // glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // // Create a texture to render to
    // GLuint texture;
    // glGenTextures(1, &texture);
    // glBindTexture(GL_TEXTURE_2D, texture);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    // if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    //     fprintf(stderr, "Framebuffer is not complete\n");
    // }

    // // Set the color to clear with
    // glClearColor(1.0f, 0.5f, 0.25f, 1.0f);
    // odin_gltest_clearColor(glClearColor);
    // glClear(GL_COLOR_BUFFER_BIT);

    // // Read the pixels from the framebuffer
    // unsigned char pixels[WIDTH * HEIGHT * 4];
    // glReadPixels(0, 0, WIDTH, HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    // // Print the pixel values
    // for (int y = 0; y < HEIGHT; y++) {
    //     for (int x = 0; x < WIDTH; x++) {
    //         int index = (y * WIDTH + x) * 4;
    //         printf("Pixel (%d, %d): R=%d G=%d B=%d A=%d\n", x, y, pixels[index], pixels[index + 1], pixels[index + 2], pixels[index + 3]);
    //     }
    // }

    // // Cleanup
    // glDeleteTextures(1, &texture);
    // glDeleteFramebuffers(1, &framebuffer);

}

#endif // ODIN_H