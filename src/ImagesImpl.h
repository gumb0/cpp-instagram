#ifndef CPP_INSTAGRAM_IMPL_IMAGES_IMPL_H
#define CPP_INSTAGRAM_IMPL_IMAGES_IMPL_H

#include "Images.h"
#include "MediaInfo.h"

namespace Instagram
{
    class ImagesImpl : public Images
    {
    public:
        explicit ImagesImpl(const ImageInfo& imageInfo);

        virtual MediaDataPtr getLowResolution() const;
        virtual MediaDataPtr getStandardResolution() const;
        virtual MediaDataPtr getThumbnail() const;

    private:
        const ImageInfo mImageInfo;
        const MediaDataPtr mLowResolution;
        const MediaDataPtr mStandardResolution;
        const MediaDataPtr mThumbnail;
    };

    ImagesPtr CreateImagesImpl(ImageInfoPtr imageInfo);
}

#endif
