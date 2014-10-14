#ifndef CPP_INSTAGRAM_IMPL_IMAGES_IMPL_H
#define CPP_INSTAGRAM_IMPL_IMAGES_IMPL_H

#include "Images.h"
#include "MediaInfo.h"

namespace Instagram
{
    class ImagesImpl : public Images
    {
    public:
        explicit ImagesImpl(const ImageInfo& imageInfos);


    private:
        const ImageInfo mImageInfo;
    };
}

#endif
