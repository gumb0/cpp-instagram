#include "ImagesImpl.h"
#include "MediaDataImpl.h"

#include <assert.h>

using namespace Instagram;

ImagesImpl::ImagesImpl(const ImageInfo& imageInfo) : 
    mImageInfo(imageInfo), 
    mLowResolution(new MediaDataImpl(*imageInfo.mLowResolution)),
    mStandardResolution(new MediaDataImpl(*imageInfo.mStandardResolution)),
    mThumbnail(new MediaDataImpl(*imageInfo.mThumbnail))
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
