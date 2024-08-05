//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "rendererPlugin.h"
#include "renderDelegate.h"

#include "pxr/imaging/hd/rendererPluginRegistry.h"

#include <iostream>

PXR_NAMESPACE_OPEN_SCOPE

// Register the plugin with the renderer plugin system.
TF_REGISTRY_FUNCTION(TfType)
{
    HdRendererPluginRegistry::Define<HdRdnRendererPlugin>();
}

HdRenderDelegate*
HdRdnRendererPlugin::CreateRenderDelegate()
{
    std::cout << "CreateRenderDelegate()" << std::endl;
    return new HdRdnRenderDelegate();
}

HdRenderDelegate*
HdRdnRendererPlugin::CreateRenderDelegate(
    HdRenderSettingsMap const& settingsMap)
{
    std::cout << "CreateRenderDelegate()" << std::endl;
    return new HdRdnRenderDelegate(settingsMap);
}

void
HdRdnRendererPlugin::DeleteRenderDelegate(HdRenderDelegate *renderDelegate)
{
    delete renderDelegate;
}

bool 
HdRdnRendererPlugin::IsSupported(bool /* gpuEnabled */) const
{
    // Nothing more to check for now, we assume if the plugin loads correctly
    // it is supported.
    return true;
}

PXR_NAMESPACE_CLOSE_SCOPE
