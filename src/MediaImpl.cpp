#include "MediaImpl.h"

using namespace Instagram;

MediaImpl::MediaImpl(const std::string& link, const std::string& caption) :
    mLink(link), 
    mCaption(caption)
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
