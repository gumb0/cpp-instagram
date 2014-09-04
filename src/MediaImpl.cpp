#include "MediaImpl.h"

using namespace Instagram;

MediaImpl::MediaImpl(const std::string& link) : mLink(link)
{
}

std::string MediaImpl::getLink() const
{
    return mLink;
}
