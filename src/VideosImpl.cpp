#include "MediaDataImpl.h"
#include "VideosImpl.h"

#include <assert.h>

using namespace Instagram;

VideosImpl::VideosImpl(CurlPtr curl, const VideoInfo& videoInfo) :
    mVideoInfo(videoInfo),
    mLowBandwidth(CreateMediaDataImpl(curl, videoInfo.mLowBandwidth)),
    mLowResolution(CreateMediaDataImpl(curl, videoInfo.mLowResolution)),
    mStandardResolution(CreateMediaDataImpl(curl, videoInfo.mStandardResolution))
{
}

MediaDataPtr VideosImpl::getLowBandwidth() const
{
    return mLowBandwidth;
}

MediaDataPtr VideosImpl::getLowResolution() const
{
    return mLowResolution;
}

MediaDataPtr VideosImpl::getStandardResolution() const
{
    return mStandardResolution;
}

VideosPtr Instagram::CreateVideosImpl(CurlPtr curl, VideoInfoPtr videoInfo)
{
    assert(videoInfo);

    return VideosPtr(new VideosImpl(curl, *videoInfo));
}
