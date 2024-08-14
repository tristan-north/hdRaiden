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
#ifndef PXR_IMAGING_PLUGIN_HD_RDN_RENDER_BUFFER_H
#define PXR_IMAGING_PLUGIN_HD_RDN_RENDER_BUFFER_H

#include "pxr/pxr.h"
#include "pxr/imaging/hd/renderBuffer.h"

PXR_NAMESPACE_OPEN_SCOPE

class HdRdnRenderBuffer : public HdRenderBuffer
{
public:
    HdRdnRenderBuffer(SdfPath const& id);
    ~HdRdnRenderBuffer() override;

    /// Get allocation information from the scene delegate.
    /// Note: Embree overrides this only to stop the render thread before
    /// potential re-allocation.
    ///   \param sceneDelegate The scene delegate backing this render buffer.
    ///   \param renderParam   The renderer-global render param.
    ///   \param dirtyBits     The invalidation state for this render buffer.
    void Sync(HdSceneDelegate *sceneDelegate,
              HdRenderParam *renderParam,
              HdDirtyBits *dirtyBits) override;

    /// Deallocate before deletion.
    ///   \param renderParam   The renderer-global render param.
    /// Note: Embree overrides this only to stop the render thread before
    /// potential deallocation.
    void Finalize(HdRenderParam *renderParam) override;

    /// Allocate a new buffer with the given dimensions and format.
    ///   \param dimensions   Width, height, and depth of the desired buffer.
    ///                       (Only depth==1 is supported).
    ///   \param format       The format of the desired buffer, taken from the
    ///                       HdFormat enum.
    ///   \param multisampled Whether the buffer is multisampled.
    ///   \return             True if the buffer was successfully allocated,
    ///                       false with a warning otherwise.
    bool Allocate(GfVec3i const& dimensions,
                  HdFormat format,
                  bool multiSampled) override;

    void Clear(float r, float g, float b);
    void ClearDepth();

    /// Accessor for buffer width.
    ///   \return The width of the currently allocated buffer.
    unsigned int GetWidth() const override { return _width; }

    /// Accessor for buffer height.
    ///   \return The height of the currently allocated buffer.
    unsigned int GetHeight() const override { return _height; }

    /// Accessor for buffer depth.
    ///   \return The depth of the currently allocated buffer.
    unsigned int GetDepth() const override { return 1; }

    /// Accessor for buffer format.
    ///   \return The format of the currently allocated buffer.
    HdFormat GetFormat() const override { return _format; }

    /*
        This appears unused by Hydra. While we do multisample, we don't do it
        using Hydra's definition so it probably makes more sense to return
        false here, in case it is ever used somewhere.
    */
    virtual bool IsMultiSampled() const override { return false; }


    /// Map the buffer for reading/writing. The control flow should be Map(),
    /// before any I/O, followed by memory access, followed by Unmap() when
    /// done.
    ///   \return The address of the buffer.
    void* Map() override {
        _mappers++;
        return _buffer.data();
    }

    /// Unmap the buffer.
    void Unmap() override {
        _mappers--;
    }

    /// Return whether any clients have this buffer mapped currently.
    ///   \return True if the buffer is currently mapped by someone.
    bool IsMapped() const override {
        return _mappers.load() != 0;
    }

    /// Is the buffer converged?
    ///   \return True if the buffer is converged (not currently being
    ///           rendered to).
    bool IsConverged() const override {
        return _converged.load();
    }

    /// Set the convergence.
    ///   \param cv Whether the buffer should be marked converged or not.
    void SetConverged(bool cv) {
        _converged.store(cv);
    }

    /// Resolve the sample buffer into final values.
    void Resolve() override;

private:
    // Release any allocated resources.
    void _Deallocate() override;

    // Buffer width.
    unsigned int _width;
    // Buffer height.
    unsigned int _height;
    // Buffer format.
    HdFormat _format;

    // The resolved output buffer.
    std::vector<uint8_t> _buffer;

    // The number of callers mapping this buffer.
    std::atomic<int> _mappers;
    // Whether the buffer has been marked as converged.
    std::atomic<bool> _converged;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif // PXR_IMAGING_PLUGIN_HD_RDN_RENDER_BUFFER_H