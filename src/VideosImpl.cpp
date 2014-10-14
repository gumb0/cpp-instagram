#include "MediaDataImpl.h"
#include "VideosImpl.h"

#include <assert.h>

using namespace Instagram;

VideosImpl::VideosImpl(const VideoInfo& videoInfo) : 
    mVideoInfo(videoInfo),
    mLowBandwidth(CreateMediaDataImpl(videoInfo.mLowBandwidth)),
    mLowResolution(CreateMediaDataImpl(videoInfo.mLowResolution)),
    mStandardResolution(CreateMediaDataImpl(videoInfo.mStandardResolution))
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

VideosPtr Instagram::CreateVideosImpl(VideoInfoPtr videoInfo)
{
    assert(videoInfo);

    return VideosPtr(new VideosImpl(*videoInfo));
}
