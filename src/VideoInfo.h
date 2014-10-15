#ifndef CPP_INSTAGRAM_IMPL_VIDEO_INFO_H
#define CPP_INSTAGRAM_IMPL_VIDEO_INFO_H

#include "MediaDataInfo.h"

namespace Instagram
{
    struct VideoInfo
    {
        MediaDataInfoPtr mLowBandwidth;
        MediaDataInfoPtr mLowResolution;
        MediaDataInfoPtr mStandardResolution;
    };

    typedef std::shared_ptr<VideoInfo> VideoInfoPtr;
}

#endif
