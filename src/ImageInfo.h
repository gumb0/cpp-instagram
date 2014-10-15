#ifndef CPP_INSTAGRAM_IMPL_IMAGE_INFO_H
#define CPP_INSTAGRAM_IMPL_IMAGE_INFO_H

#include "MediaDataInfo.h"

namespace Instagram
{
    struct ImageInfo
    {
        MediaDataInfoPtr mLowResolution;
        MediaDataInfoPtr mStandardResolution;
        MediaDataInfoPtr mThumbnail;
    };

    typedef std::shared_ptr<ImageInfo> ImageInfoPtr;

}

#endif
