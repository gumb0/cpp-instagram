#ifndef CPP_INSTAGRAM_MEDIA_H
#define CPP_INSTAGRAM_MEDIA_H

#include "Images.h"
#include "Location.h"
#include "NonCopyable.h"
#include "Videos.h"

#include <memory>
#include <string>
#include <vector>

namespace Instagram
{
    enum class MediaType
    {
        Image,
        Video
    };

    class Media : NonCopyable
    {
    public:
        virtual std::string getId() const = 0;
        virtual std::string getLink() const = 0;
        virtual std::string getCaption() const = 0;
        virtual std::string getCreatedTime() const = 0;
        virtual MediaType getType() const = 0;
        virtual std::string getFilter() const = 0;
        virtual std::string getUserId() const = 0;
        virtual std::vector<std::string> getTags() const = 0;
        virtual ImagesPtr getImages() const = 0;
        // throws if trying to get video of media with type != MediaType::Video
        virtual VideosPtr getVideos() const = 0;
        // returns null pointer if location is not set
        virtual LocationPtr getLocation() const = 0;
    };

    typedef std::shared_ptr<Media> MediaPtr;
    typedef std::vector<MediaPtr> MediaList;
}

#endif