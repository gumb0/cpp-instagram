#ifndef CPP_INSTAGRAM_IMPL_MEDIA_IMPL_H
#define CPP_INSTAGRAM_IMPL_MEDIA_IMPL_H

#include "Media.h"
#include "MediaInfo.h"

namespace Instagram
{
    class MediaImpl : public Media
    {
    public:
        explicit MediaImpl(const MediaInfo& mediaInfo);

        virtual std::string getId() const;
        virtual std::string getLink() const;
        virtual std::string getCaption() const;
        virtual std::string getCreatedTime() const;
        virtual MediaType getType() const;
        virtual std::string getFilter() const;
        virtual std::vector<std::string> getTags() const;
        virtual ImagesPtr getImages() const;
        virtual VideosPtr getVideos() const;

    private:
        const MediaInfo mInfo;
        const ImagesPtr mImages;
        const VideosPtr mVideos;
    };

    MediaPtr CreateMedia(const MediaInfo& mediaInfo);
}

#endif
