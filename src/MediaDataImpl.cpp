#include "MediaDataImpl.h"

#include <assert.h>

using namespace Instagram;

MediaDataImpl::MediaDataImpl(const MediaDataInfo& info) : mInfo(info)
{
}

int MediaDataImpl::getWidth() const
{
    return mInfo.mWidth;
}

int MediaDataImpl::getHeight() const
{
    return mInfo.mHeight;
}

std::string MediaDataImpl::getUrl() const
{
    return mInfo.mUrl;
}

MediaDataPtr Instagram::CreateMediaDataImpl(MediaDataInfoPtr info)
{
    assert(info);

    return MediaDataPtr(new MediaDataImpl(*info));
}