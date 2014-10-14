#ifndef CPP_INSTAGRAM_IMPL_VIDEOS_IMPL_H
#define CPP_INSTAGRAM_IMPL_VIDEOS_IMPL_H

#include "Images.h"
#include "MediaInfo.h"

namespace Instagram
{
    class VideosImpl : public Videos
    {
    public:
        explicit VideosImpl(const VideoInfo& videoInfos);


    private:
        const VideoInfo mVideoInfo;
    };
}

#endif
