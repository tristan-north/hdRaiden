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

void
HdRdnRenderPass::_Execute(HdRenderPassStateSharedPtr const& renderPassState,
                             TfTokenVector const &renderTags)
{
    std::cout << "=> Execute RenderPass: Rendering!" << std::endl;
    from_odin();

    HdRenderPassAovBindingVector aovBindings = renderPassState->GetAovBindings();
    if(aovBindings.empty()) {
        std::cout << "No AOV Bindings." << std::endl;
        return;
    }

    for(int i=0; i<aovBindings.size(); i++ ) {
        
        if(aovBindings[i].aovName == HdAovTokens->color) {
            HdRdnRenderBuffer *rb = static_cast<HdRdnRenderBuffer*>(aovBindings[i].renderBuffer);
        
            rb->Map();
            rb->Clear();
            rb->Unmap();
            rb->SetConverged(true);
            std::cout << "Cleared color buffer." << std::endl;
        }
        else if(aovBindings[i].aovName == HdAovTokens->depth) {
            HdRdnRenderBuffer *rb = static_cast<HdRdnRenderBuffer*>(aovBindings[i].renderBuffer);
        
            rb->Map();
            rb->Clear();
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
