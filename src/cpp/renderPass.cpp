//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "odin.h"
#include "renderDelegate.h"
#include "renderPass.h"
#include "pxr/imaging/hd/renderPassState.h"
#include "pxr/usd/usdRender/tokens.h"
#include "pxr/imaging/garch/glApi.h"

#include <pxr/imaging/hgi/hgi.h>
#include <pxr/imaging/hgi/types.h>

#include <iostream>

PXR_NAMESPACE_OPEN_SCOPE

HdRdnRenderPass::HdRdnRenderPass(HdRenderIndex *index, HdRprimCollection const &collection, 
                                    HdRdnRenderDelegate *renderDelegate) 
                                    : HdRenderPass(index, collection)
                                    , _renderDelegate(renderDelegate)
{
}

HdRdnRenderPass::~HdRdnRenderPass()
{
    std::cout << "Destroying renderPass" << std::endl;
}

bool
HdRdnRenderPass::IsConverged() const
{
    return true;
}

void openGLTest() {
    const int WIDTH = 4;
    const int HEIGHT = 4;

    // Create a framebuffer
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    // Create a texture to render to
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        fprintf(stderr, "Framebuffer is not complete\n");
    }

    // Set the color to clear with
    // glClearColor(1.0f, 0.5f, 0.25f, 1.0f);
    // odin_gltest_clearColor(glClearColor);
    // glClear(GL_COLOR_BUFFER_BIT);
    odin_clear();

    // Read the pixels from the framebuffer
    unsigned char pixels[WIDTH * HEIGHT * 4];
    glReadPixels(0, 0, WIDTH, HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    // Print the pixel values
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int index = (y * WIDTH + x) * 4;
            printf("Pixel (%d, %d): R=%d G=%d B=%d A=%d\n", x, y, pixels[index], pixels[index + 1], pixels[index + 2], pixels[index + 3]);
        }
    }

    // Cleanup
    glDeleteTextures(1, &texture);
    glDeleteFramebuffers(1, &framebuffer);
}

void
HdRdnRenderPass::_Execute(HdRenderPassStateSharedPtr const& renderPassState,
                             TfTokenVector const &renderTags)
{
    std::cout << "=> Execute RenderPass: Rendering!" << std::endl;

    HdRenderPassAovBindingVector aovBindings = renderPassState->GetAovBindings();
    if(aovBindings.empty()) {
        std::cout << "No AOV Bindings." << std::endl;
        return;
    }

    for(int i=0; i<aovBindings.size(); i++ ) {
        
        if(aovBindings[i].aovName == HdAovTokens->color) {
            HdRdnRenderBuffer *rb = static_cast<HdRdnRenderBuffer*>(aovBindings[i].renderBuffer);

            rb->Map();
           // rb->Clear(.2f, .1f, .1f);
            odin_render(rb->data(), rb->GetWidth(), rb->GetHeight());
            rb->Unmap();
            rb->SetConverged(true);
            openGLTest();
            std::cout << "Cleared color buffer." << std::endl;
        }
        else if(aovBindings[i].aovName == HdAovTokens->depth) {
            HdRdnRenderBuffer *rb = static_cast<HdRdnRenderBuffer*>(aovBindings[i].renderBuffer);
        
            rb->Map();
            rb->ClearDepth();
            rb->Unmap();
            rb->SetConverged(true);
            std::cout << "Cleared depth buffer." << std::endl;
        }
        else {
            std::cout << "Ignoring buffer: " << aovBindings[i].aovName.GetString() << std::endl;
        }
    }
    
}


PXR_NAMESPACE_CLOSE_SCOPE
