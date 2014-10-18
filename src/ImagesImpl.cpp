#include "ImagesImpl.h"
#include "MediaDataImpl.h"

#include <assert.h>

using namespace Instagram;

ImagesImpl::ImagesImpl(CurlPtr curl, const ImageInfo& imageInfo) :
    mImageInfo(imageInfo), 
    mLowResolution(CreateMediaDataImpl(curl, imageInfo.mLowResolution)),
    mStandardResolution(CreateMediaDataImpl(curl, imageInfo.mStandardResolution)),
    mThumbnail(CreateMediaDataImpl(curl, imageInfo.mThumbnail))
{
}

MediaDataPtr ImagesImpl::getLowResolution() const
{
    return mLowResolution;
}

MediaDataPtr ImagesImpl::getStandardResolution() const
{
    return mStandardResolution;
}

MediaDataPtr ImagesImpl::getThumbnail() const
{
    return mThumbnail;
}

ImagesPtr Instagram::CreateImagesImpl(CurlPtr curl, ImageInfoPtr imageInfo)
{
    assert(imageInfo);

    return ImagesPtr(new ImagesImpl(curl, *imageInfo));
}
