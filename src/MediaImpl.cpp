#include "ExceptionHelpers.h"
#include "ImagesImpl.h"
#include "MediaImpl.h"
#include "VideosImpl.h"

using namespace Instagram;

MediaImpl::MediaImpl(const MediaInfo& mediaInfo) : 
    mInfo(mediaInfo), 
    mImages(new ImagesImpl(*mediaInfo.mImageInfo)),
    mVideos(mediaInfo.mType == MediaType::Video ? new VideosImpl(*mediaInfo.mVideoInfo) : nullptr)
{
}

std::string MediaImpl::getId() const
{
    return mInfo.mId;
}

std::string MediaImpl::getLink() const
{
    return mInfo.mLink;
}

std::string MediaImpl::getCaption() const
{
    return mInfo.mCaption;
}

std::string MediaImpl::getCreatedTime() const
{
    return mInfo.mCreatedTime;
}

MediaType MediaImpl::getType() const
{
    return mInfo.mType;
}

std::string MediaImpl::getFilter() const
{
    return mInfo.mFilter;
}

std::vector<std::string> MediaImpl::getTags() const
{
    return mInfo.mTags;
}

ImagesPtr MediaImpl::getImages() const
{
    return mImages;
}

VideosPtr MediaImpl::getVideos() const
{
    if (mInfo.mType != MediaType::Video)
        Throw(GET_VIDEOS_FROM_NOT_VIDEO_MEDIA);

    return mVideos;
}

MediaPtr Instagram::CreateMedia(const MediaInfo& mediaInfo)
{
    return MediaPtr(new MediaImpl(mediaInfo));
}
