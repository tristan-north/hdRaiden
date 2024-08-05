//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "renderDelegate.h"
#include "mesh.h"
#include "renderPass.h"
#include "renderBuffer.h"

#include <iostream>

PXR_NAMESPACE_OPEN_SCOPE

const TfTokenVector HdRdnRenderDelegate::SUPPORTED_RPRIM_TYPES =
{
    HdPrimTypeTokens->mesh,
};

const TfTokenVector HdRdnRenderDelegate::SUPPORTED_SPRIM_TYPES =
{
    HdPrimTypeTokens->camera,
};

const TfTokenVector HdRdnRenderDelegate::SUPPORTED_BPRIM_TYPES =
{
    HdPrimTypeTokens->renderBuffer,
};

HdRdnRenderDelegate::HdRdnRenderDelegate()
    : HdRenderDelegate()
{
    _Initialize();
}

HdRdnRenderDelegate::HdRdnRenderDelegate(
    HdRenderSettingsMap const& settingsMap)
    : HdRenderDelegate(settingsMap)
{
    _Initialize();
}

void
HdRdnRenderDelegate::_Initialize()
{
    std::cout << "Creating Rdn RenderDelegate" << std::endl;
    _resourceRegistry = std::make_shared<HdResourceRegistry>();
}

HdRdnRenderDelegate::~HdRdnRenderDelegate()
{
    _resourceRegistry.reset();
    std::cout << "Destroying Rdn RenderDelegate" << std::endl;
}

TfTokenVector const&
HdRdnRenderDelegate::GetSupportedRprimTypes() const
{
    return SUPPORTED_RPRIM_TYPES;
}

TfTokenVector const&
HdRdnRenderDelegate::GetSupportedSprimTypes() const
{
    return SUPPORTED_SPRIM_TYPES;
}

TfTokenVector const&
HdRdnRenderDelegate::GetSupportedBprimTypes() const
{
    return SUPPORTED_BPRIM_TYPES;
}

HdResourceRegistrySharedPtr
HdRdnRenderDelegate::GetResourceRegistry() const
{
    return _resourceRegistry;
}

void 
HdRdnRenderDelegate::CommitResources(HdChangeTracker *tracker)
{
}

HdRenderPassSharedPtr 
HdRdnRenderDelegate::CreateRenderPass(
    HdRenderIndex *index,
    HdRprimCollection const& collection)
{
    std::cout << "Create RenderPass with Collection=" 
        << collection.GetName() << std::endl; 

    return HdRenderPassSharedPtr(new HdRdnRenderPass(index, collection, this));  
}

HdRprim *
HdRdnRenderDelegate::CreateRprim(TfToken const& typeId,
                                    SdfPath const& rprimId)
{
    std::cout << "Create Rdn Rprim type=" << typeId.GetText() 
        << " id=" << rprimId 
        << std::endl;

    if (typeId == HdPrimTypeTokens->mesh) {
        return new HdRdnMesh(rprimId);
    } else {
        TF_CODING_ERROR("Unknown Rprim type=%s id=%s", 
            typeId.GetText(), 
            rprimId.GetText());
    }
    return nullptr;
}

void
HdRdnRenderDelegate::DestroyRprim(HdRprim *rPrim)
{
    std::cout << "Destroy Rdn Rprim id=" << rPrim->GetId() << std::endl;
    delete rPrim;
}

HdSprim *
HdRdnRenderDelegate::CreateSprim(TfToken const& typeId,
                                    SdfPath const& sprimId)
{
    std::cout << "CreateSprim() NOT IMPLEMENTED. Being asked to create " << typeId.GetText() << std::endl;
    return nullptr;
}

HdSprim *
HdRdnRenderDelegate::CreateFallbackSprim(TfToken const& typeId)
{
    std::cout << "CreateFallbackSprim() NOT IMPLEMENTED. Being asked to create " << typeId.GetText() << std::endl;
    return nullptr;
}

void
HdRdnRenderDelegate::DestroySprim(HdSprim *sPrim)
{
    std::cout << "DestroySprim NOT IMPLEMENTED" << std::endl;
}

HdBprim *
HdRdnRenderDelegate::CreateBprim(TfToken const& typeId, SdfPath const& bprimId)
{
    std::cout << "Create Rdn Bprim type=" << typeId.GetText() 
        << " id=" << bprimId 
        << std::endl;

    if (typeId == HdPrimTypeTokens->renderBuffer) {
        return new HdRdnRenderBuffer(bprimId);
    } else {
        TF_CODING_ERROR("Unknown Bprim type=%s id=%s", 
            typeId.GetText(), 
            bprimId.GetText());
    }
    return nullptr;
}

HdBprim *
HdRdnRenderDelegate::CreateFallbackBprim(TfToken const& typeId)
{
    if (typeId == HdPrimTypeTokens->renderBuffer) {
        return new HdRdnRenderBuffer(SdfPath::EmptyPath());
    } else {
        TF_CODING_ERROR("Unknown Bprim Type %s", typeId.GetText());
    }
    return nullptr;
}

void
HdRdnRenderDelegate::DestroyBprim(HdBprim *bPrim)
{
    std::cout << "Destroy Rdn Bprim id=" << bPrim->GetId() << std::endl;
    delete bPrim;
}

HdInstancer *
HdRdnRenderDelegate::CreateInstancer(
    HdSceneDelegate *delegate,
    SdfPath const& id)
{
    TF_CODING_ERROR("Creating Instancer not supported id=%s", 
        id.GetText());
    return nullptr;
}

void 
HdRdnRenderDelegate::DestroyInstancer(HdInstancer *instancer)
{
    TF_CODING_ERROR("Destroy instancer not supported");
}

HdRenderParam *
HdRdnRenderDelegate::GetRenderParam() const
{
    return nullptr;
}

HdAovDescriptor
HdRdnRenderDelegate::GetDefaultAovDescriptor(TfToken const& name) const
{
    if (name == HdAovTokens->color)
    {
        return HdAovDescriptor(HdFormatFloat16Vec4, false, VtValue(GfVec4f(0.0f)));
    }
    else if (name == HdAovTokens->depth)
    {
        return HdAovDescriptor(HdFormatFloat32, false, VtValue(1.0f));
    }

    return HdAovDescriptor(HdFormatInvalid, false, VtValue());
}

PXR_NAMESPACE_CLOSE_SCOPE
