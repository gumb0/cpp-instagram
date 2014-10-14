#ifndef CPP_INSTAGRAM_VIDEOS_H
#define CPP_INSTAGRAM_VIDEOS_H

#include "NonCopyable.h"

#include <memory>

namespace Instagram
{
    class Videos : NonCopyable
    {
    public:
    };

    typedef std::shared_ptr<Videos> VideosPtr;
}

#endif