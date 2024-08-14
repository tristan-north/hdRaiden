//
// Copyright 2018 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#include "renderBuffer.h"
#include "pxr/base/gf/half.h"
#include "pxr/base/gf/vec3i.h"

#include <iostream>

PXR_NAMESPACE_OPEN_SCOPE

HdRdnRenderBuffer::HdRdnRenderBuffer(SdfPath const& id)
    : HdRenderBuffer(id)
    , _width(0)
    , _height(0)
    , _format(HdFormatInvalid)
    , _buffer()
    , _mappers(0)
    , _converged(false)
{
}

HdRdnRenderBuffer::~HdRdnRenderBuffer() = default;

/*virtual*/
void
HdRdnRenderBuffer::Sync(HdSceneDelegate *sceneDelegate,
                           HdRenderParam *renderParam,
                           HdDirtyBits *dirtyBits)
{
    std::cout << "HdRdnRenderBuffer::Sync()" << std::endl;
    if (*dirtyBits & DirtyDescription) {
        // Should stop the render here.
        //static_cast<HdEmbreeRenderParam*>(renderParam)->AcquireSceneForEdit();
        std::cout << "HdRdnRenderBuffer::Sync() Dirty TODO" << std::endl;
    }

    HdRenderBuffer::Sync(sceneDelegate, renderParam, dirtyBits);
}

/*virtual*/
void
HdRdnRenderBuffer::Finalize(HdRenderParam *renderParam)
{
    // Embree has the background thread write directly into render buffers,
    // so we need to stop the render thread before removing them.
    //static_cast<HdEmbreeRenderParam*>(renderParam)->AcquireSceneForEdit();
    std::cout << "HdRdnRenderBuffer::Finalize() TODO" << std::endl;

    HdRenderBuffer::Finalize(renderParam);
}

/*virtual*/
void
HdRdnRenderBuffer::_Deallocate()
{
    // If the buffer is mapped while we're doing this, there's not a great
    // recovery path...
    TF_VERIFY(!IsMapped());

    _width = 0;
    _height = 0;
    _format = HdFormatInvalid;
    _buffer.resize(0);

    _mappers.store(0);
    _converged.store(false);
}


/*virtual*/
bool
HdRdnRenderBuffer::Allocate(GfVec3i const& dimensions,
                               HdFormat format,
                               bool multiSampled)
{
    _Deallocate();

    if (dimensions[2] != 1) {
        TF_WARN("Render buffer allocated with dims <%d, %d, %d> and"
                " format %s; depth must be 1!",
                dimensions[0], dimensions[1], dimensions[2],
                TfEnum::GetName(format).c_str());
        return false;
    }

    _width = dimensions[0];
    _height = dimensions[1];
    _format = format;
    _buffer.resize(_width * _height * HdDataSizeOfFormat(format));

    std::cout << "Allocated Buffer  " << _width << "x" << _height 
    << "format: " << TfEnum::GetName(format).c_str() << std::endl;

    return true;
}

void
HdRdnRenderBuffer::Clear(float r, float g, float b)
{
    size_t formatDataSize = HdDataSizeOfFormat(_format);

    if(_format == HdFormatFloat16Vec4) {
        for (size_t i = 0; i < _width * _height; ++i) {
            uint16_t *dst = reinterpret_cast<uint16_t*>(&_buffer[i*formatDataSize]);

            dst[0] = GfHalf(r).bits();
            dst[1] = GfHalf(g).bits();
            dst[2] = GfHalf(b).bits();
            dst[3] = GfHalf(1.0f).bits();
        }
    }

}

void
HdRdnRenderBuffer::ClearDepth()
{
    size_t formatDataSize = HdDataSizeOfFormat(_format);

    if(_format == HdFormatFloat32) {
        for (size_t i = 0; i < _width * _height; ++i) {
            float *dst = reinterpret_cast<float*>(&_buffer[i*formatDataSize]);

            dst[0] = 0.1f;
        }
    }

}

/*virtual*/
void
HdRdnRenderBuffer::Resolve()
{
}

PXR_NAMESPACE_CLOSE_SCOPE