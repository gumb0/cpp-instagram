#include "ImagesImpl.h"
#include "MediaDataImpl.h"

#include <assert.h>

using namespace Instagram;

ImagesImpl::ImagesImpl(const ImageInfo& imageInfo) : 
    mImageInfo(imageInfo), 
    mLowResolution(CreateMediaDataImpl(imageInfo.mLowResolution)),
    mStandardResolution(CreateMediaDataImpl(imageInfo.mStandardResolution)),
    mThumbnail(CreateMediaDataImpl(imageInfo.mThumbnail))
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

ImagesPtr Instagram::CreateImagesImpl(ImageInfoPtr imageInfo)
{
    assert(imageInfo);

    return ImagesPtr(new ImagesImpl(*imageInfo));
}
