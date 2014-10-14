#include "MediaDataImpl.h"

using namespace Instagram;

MediaDataImpl::MediaDataImpl(const MediaDataInfo& info) : mInfo(info)
{
}

int MediaDataImpl::getWidth() const
{
    return 0;
}

int MediaDataImpl::getHeight() const
{
    return 0;
}

std::string MediaDataImpl::getUrl() const
{
    return std::string();
}
