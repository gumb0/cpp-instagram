#ifndef CPP_INSTAGRAM_IMAGES_H
#define CPP_INSTAGRAM_IMAGES_H

#include "MediaData.h"
#include "NonCopyable.h"

#include <memory>

namespace Instagram
{
    class Images : NonCopyable
    {
    public:
        virtual MediaDataPtr getLowResolution() const = 0;
        virtual MediaDataPtr getStandardResolution() const = 0;
        virtual MediaDataPtr getThumbnail() const = 0;
    };

    typedef std::shared_ptr<Images> ImagesPtr;
}

#endif