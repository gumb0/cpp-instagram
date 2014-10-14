#ifndef CPP_INSTAGRAM_IMAGES_H
#define CPP_INSTAGRAM_IMAGES_H

#include "NonCopyable.h"

#include <memory>

namespace Instagram
{
    class Images : NonCopyable
    {
    public:
    };

    typedef std::shared_ptr<Images> ImagesPtr;
}

#endif