#ifndef CPP_INSTAGRAM_VIDEOS_H
#define CPP_INSTAGRAM_VIDEOS_H

#include "NonCopyable.h"

#include <memory>

namespace Instagram
{
    class Videos : NonCopyable
    {
    public:
        virtual MediaDataPtr getLowBandwidth() const = 0;
        virtual MediaDataPtr getLowResolution() const = 0;
        virtual MediaDataPtr getStandardResolution() const = 0;
    };

    typedef std::shared_ptr<Videos> VideosPtr;
}

#endif