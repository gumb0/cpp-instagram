#ifndef CPP_INSTAGRAM_IMPL_MEDIA_INFO_H
#define CPP_INSTAGRAM_IMPL_MEDIA_INFO_H

#include "Media.h"

#include <string>
#include <vector>

namespace Instagram
{
    struct ImageInfo
    {
        int mWidth;
        int mHeight;
        std::string mUrl;
    };

    typedef std::shared_ptr<ImageInfo> ImageInfoPtr;

    struct ImageInfos
    {
        ImageInfoPtr mLowResolution;
        ImageInfoPtr mStandardResolution;
        ImageInfoPtr mThumbnail;
    };

    typedef std::shared_ptr<ImageInfos> ImageInfosPtr;

    struct MediaInfo
    {
        std::string mId;
        std::string mLink;
        std::string mCaption;
        std::string mCreatedTime;
        MediaType mType;
        std::string mFilter;
        std::vector<std::string> mTags;
        ImageInfosPtr mImageInfos;
    };
}

#endif
