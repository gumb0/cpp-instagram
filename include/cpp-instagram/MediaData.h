#ifndef CPP_INSTAGRAM_MEDIA_DATA_H
#define CPP_INSTAGRAM_MEDIA_DATA_H

#include "NonCopyable.h"

#include <memory>
#include <string>

namespace Instagram
{
    class MediaData : NonCopyable
    {
    public:
        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;
        virtual std::string getUrl() const = 0;
    };

    typedef std::shared_ptr<MediaData> MediaDataPtr;
}

#endif