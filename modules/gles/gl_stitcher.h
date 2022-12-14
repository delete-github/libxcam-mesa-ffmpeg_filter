/*
 * gl_stitcher.h - GL stitcher class
 *
 *  Copyright (c) 2018 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Yinhang Liu <yinhangx.liu@intel.com>
 */

#ifndef XCAM_GL_STITCHER_H
#define XCAM_GL_STITCHER_H

#include <interface/stitcher.h>
#include <gles/gles_std.h>
#include <gles/gl_image_handler.h>

namespace XCam {

namespace GLStitcherPriv {
class StitcherImpl;
};

class GLStitcher
    : public GLImageHandler
    , public Stitcher
{
    friend class GLStitcherPriv::StitcherImpl;

public:
    struct StitcherParam
        : ImageHandler::Parameters
    {
        SmartPtr<VideoBuffer> in_bufs[XCAM_STITCH_MAX_CAMERAS];
        SmartPtr<VideoBuffer> in_dmabufs[XCAM_STITCH_MAX_CAMERAS];
        SmartPtr<VideoBuffer> out_dmabuf;
        bool enable_dmabuf;

        StitcherParam ()
            : Parameters (NULL, NULL)
        {
            enable_dmabuf = false;
        }
    };

public:
    explicit GLStitcher (const char *name = "GLStitcher");
    ~GLStitcher ();

    virtual XCamReturn terminate ();

protected:
    virtual XCamReturn stitch_buffers (const VideoBufferList &in_bufs, SmartPtr<VideoBuffer> &out_buf);

    virtual XCamReturn configure_resource (const SmartPtr<Parameters> &param);
    virtual XCamReturn start_work (const SmartPtr<Parameters> &param);

private:
    SmartPtr<GLStitcherPriv::StitcherImpl>    _impl;
};

}

#endif // XCAM_GL_STITCHER_H
