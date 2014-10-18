#include "MediaDataImpl.h"

#include <assert.h>

using namespace Instagram;

MediaDataImpl::MediaDataImpl(CurlPtr curl, const MediaDataInfo& info) : 
    mCurl(curl),
    mInfo(info)
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

void MediaDataImpl::download(const std::string& localPath) const
{
    mCurl->download(mInfo.mUrl, localPath);
}

MediaDataPtr Instagram::CreateMediaDataImpl(CurlPtr curl, MediaDataInfoPtr info)
{
    assert(info);

    return MediaDataPtr(new MediaDataImpl(curl, *info));
}