#ifndef CPP_INSTAGRAM_MEDIA_H
#define CPP_INSTAGRAM_MEDIA_H

#include "NonCopyable.h"

#include <memory>
#include <string>
#include <vector>

namespace Instagram
{

    class Media : NonCopyable
    {
    public:
        virtual std::string getLink() const = 0;
    };

    typedef std::shared_ptr<Media> MediaPtr;
    typedef std::vector<MediaPtr> Feed;
}

#endif