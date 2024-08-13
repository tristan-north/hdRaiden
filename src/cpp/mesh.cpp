//
// Copyright 2020 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "mesh.h"

#include <iostream>

PXR_NAMESPACE_OPEN_SCOPE

HdRdnMesh::HdRdnMesh(SdfPath const& id)
    : HdMesh(id)
{
}

HdDirtyBits
HdRdnMesh::GetInitialDirtyBitsMask() const
{
    return HdChangeTracker::Clean
        | HdChangeTracker::DirtyTransform;
}

HdDirtyBits
HdRdnMesh::_PropagateDirtyBits(HdDirtyBits bits) const
{
    return bits;
}

void 
HdRdnMesh::_InitRepr(TfToken const &reprToken, HdDirtyBits *dirtyBits)
{

}

void
HdRdnMesh::Sync(HdSceneDelegate *sceneDelegate,
                   HdRenderParam   *renderParam,
                   HdDirtyBits     *dirtyBits,
                   TfToken const   &reprToken)
{
    std::cout << "* (multithreaded) Sync HdRdnMesh id=" << GetId() << std::endl;
}

PXR_NAMESPACE_CLOSE_SCOPE
