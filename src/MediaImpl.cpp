#include "MediaImpl.h"

using namespace Instagram;

MediaImpl::MediaImpl(const MediaInfo& mediaInfo) : mInfo(mediaInfo)
{
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

MediaPtr Instagram::CreateMedia(const MediaInfo& mediaInfo)
{
    return MediaPtr(new MediaImpl(mediaInfo));
}
