#ifndef CPP_INSTAGRAM_IMPL_MEDIA_DATA_INFO_H
#define CPP_INSTAGRAM_IMPL_MEDIA_DATA_INFO_H

#include <memory>
#include <string>

namespace Instagram
{
    struct MediaDataInfo
    {
        int mWidth;
        int mHeight;
        std::string mUrl;
    };

    typedef std::shared_ptr<MediaDataInfo> MediaDataInfoPtr;
}

#endif
