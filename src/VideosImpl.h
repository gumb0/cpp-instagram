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

        virtual MediaDataPtr getLowBandwidth() const;
        virtual MediaDataPtr getLowResolution() const;
        virtual MediaDataPtr getStandardResolution() const;

    private:
        const VideoInfo mVideoInfo;
        const MediaDataPtr mLowBandwidth;
        const MediaDataPtr mLowResolution;
        const MediaDataPtr mStandardResolution;
    };

    VideosPtr CreateVideosImpl(VideoInfoPtr videoInfo);
}

#endif
