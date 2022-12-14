/*
 * feature_match.cpp - optical flow feature match
 *
 *  Copyright (c) 2016-2017 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Wind Yuan <feng.yuan@intel.com>
 * Author: Yinhang Liu <yinhangx.liu@intel.com>
 */

#include "feature_match.h"

#define XCAM_FM_DEBUG 0

namespace XCam {

FeatureMatch::FeatureMatch ()
    : _x_offset (0.0f)
    , _y_offset (0.0f)
    , _mean_offset (0.0f)
    , _mean_offset_y (0.0f)
    , _valid_count (0)
    , _fm_idx (-1)
    , _frame_num (0)
{
}

void
FeatureMatch::set_fm_index (int idx)
{
    _fm_idx = idx;
}

void
FeatureMatch::set_config (const FMConfig &config)
{
    _config = config;
}

void
FeatureMatch::set_crop_rect (const Rect &left_rect, const Rect &right_rect)
{
    _left_rect = left_rect;
    _right_rect = right_rect;
}

void
FeatureMatch::get_crop_rect (Rect &left_rect, Rect &right_rect)
{
    left_rect = _left_rect;
    right_rect = _right_rect;
}

void
FeatureMatch::reset_offsets ()
{
    _x_offset = 0.0f;
    _y_offset = 0.0f;
    _mean_offset = 0.0f;
    _mean_offset_y = 0.0f;
}

float
FeatureMatch::get_current_left_offset_x ()
{
    return _x_offset;
}

float
FeatureMatch::get_current_left_offset_y ()
{
    return _y_offset;
}

void
FeatureMatch::set_dst_width (int width)
{
    XCAM_UNUSED (width);

    XCAM_LOG_ERROR ("dst width is not supported");
    XCAM_ASSERT (false);
}

void
FeatureMatch::enable_adjust_crop_area ()
{
    XCAM_LOG_ERROR ("adjust crop area is not supported");
    XCAM_ASSERT (false);
}

bool
FeatureMatch::get_mean_offset (
    const std::vector<float> &offsets, float sum, int &count, float &mean_offset)
{
    if (count < _config.min_corners || count <= 0)
        return false;

    mean_offset = sum / count;

#if XCAM_FM_DEBUG
    XCAM_LOG_INFO (
        "FeatureMatch(idx:%d): X-axis mean offset:%.2f, pre_mean_offset:%.2f (%d times, count:%d)",
        _fm_idx, mean_offset, 0.0f, 0, count);
#endif

    bool ret = true;
    float delta = 20.0f;//mean_offset;
    float pre_mean_offset = mean_offset;
    for (int try_times = 1; try_times < 4; ++try_times) {
        int recur_count = 0;
        sum = 0.0f;

        for (size_t i = 0; i < offsets.size (); ++i) {
            if (fabs (offsets[i] - mean_offset) >= _config.recur_offset_error)
                continue;
            sum += offsets[i];
            ++recur_count;
        }

        if (recur_count < _config.min_corners || recur_count <= 0) {
            ret = false;
            break;
        }

        mean_offset = sum / recur_count;
#if XCAM_FM_DEBUG
        XCAM_LOG_INFO (
            "FeatureMatch(idx:%d): X-axis mean_offset:%.2f, pre_mean_offset:%.2f (%d times, count:%d)",
            _fm_idx, mean_offset, pre_mean_offset, try_times, recur_count);
#endif

        if (mean_offset == pre_mean_offset && recur_count == count)
            return true;

        if (fabs (mean_offset - pre_mean_offset) > fabs (delta) * 1.2f) {
            ret = false;
            break;
        }

        delta = mean_offset - pre_mean_offset;
        pre_mean_offset = mean_offset;
        count = recur_count;
    }

    return ret;
}

void
FeatureMatch::get_correspondence (std::vector<PointFloat2> &points_left, std::vector<PointFloat2> &points_right)
{
    XCAM_UNUSED (points_left);
    XCAM_UNUSED (points_right);

    XCAM_LOG_ERROR ("get correspondence is not supported");
    XCAM_ASSERT (false);

}

}
