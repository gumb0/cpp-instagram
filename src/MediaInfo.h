#ifndef CPP_INSTAGRAM_IMPL_MEDIA_INFO_H
#define CPP_INSTAGRAM_IMPL_MEDIA_INFO_H

#include "Media.h"

#include <string>
#include <vector>

namespace Instagram
{
    struct MediaData
    {
        int mWidth;
        int mHeight;
        std::string mUrl;
    };

    typedef std::shared_ptr<MediaData> MediaDataPtr;

    struct ImageInfo
    {
        MediaDataPtr mLowResolution;
        MediaDataPtr mStandardResolution;
        MediaDataPtr mThumbnail;
    };

    typedef std::shared_ptr<ImageInfo> ImageInfoPtr;

    struct VideoInfo
    {
        MediaDataPtr mLowBandwidth;
        MediaDataPtr mLowResolution;
        MediaDataPtr mStandardResolution;
    };

    typedef std::shared_ptr<VideoInfo> VideoInfoPtr;

    struct MediaInfo
    {
        std::string mId;
        std::string mLink;
        std::string mCaption;
        std::string mCreatedTime;
        MediaType mType;
        std::string mFilter;
        std::vector<std::string> mTags;
        ImageInfoPtr mImageInfo;
        VideoInfoPtr mVideoInfo;
    };
}

#endif
