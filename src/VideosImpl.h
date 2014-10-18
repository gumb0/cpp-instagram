#ifndef CPP_INSTAGRAM_IMPL_VIDEOS_IMPL_H
#define CPP_INSTAGRAM_IMPL_VIDEOS_IMPL_H

#include "Curl.h"
#include "VideoInfo.h"
#include "Videos.h"

namespace Instagram
{
    class VideosImpl : public Videos
    {
    public:
        VideosImpl(CurlPtr curl, const VideoInfo& videoInfos);

        virtual MediaDataPtr getLowBandwidth() const;
        virtual MediaDataPtr getLowResolution() const;
        virtual MediaDataPtr getStandardResolution() const;

    private:
        const VideoInfo mVideoInfo;
        const MediaDataPtr mLowBandwidth;
        const MediaDataPtr mLowResolution;
        const MediaDataPtr mStandardResolution;
    };

    VideosPtr CreateVideosImpl(CurlPtr curl, VideoInfoPtr videoInfo);
}

#endif
