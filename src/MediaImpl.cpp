#include "MediaImpl.h"

using namespace Instagram;

MediaImpl::MediaImpl(const std::string& link, const std::string& caption, const std::string& createdTime) :
    mLink(link), 
    mCaption(caption),
    mCreatedTime(createdTime)
{
}

std::string MediaImpl::getLink() const
{
    return mLink;
}

std::string MediaImpl::getCaption() const
{
    return mCaption;
}

std::string MediaImpl::getCreatedTime() const
{
    return mCreatedTime;
}
