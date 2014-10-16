#ifndef CPP_INSTAGRAM_IMPL_MEDIA_INFO_H
#define CPP_INSTAGRAM_IMPL_MEDIA_INFO_H

#include "ImageInfo.h"
#include "LocationInfo.h"
#include "VideoInfo.h"

#include <vector>

namespace Instagram
{
    struct MediaInfo
    {
        std::string mId;
        std::string mLink;
        std::string mCaption;
        std::string mCreatedTime;
        MediaType mType;
        std::string mFilter;
        std::string mUserId;
        std::vector<std::string> mTags;
        ImageInfoPtr mImageInfo;
        VideoInfoPtr mVideoInfo;
        LocationInfoPtr mLocationInfo;
    };
}

#endif
