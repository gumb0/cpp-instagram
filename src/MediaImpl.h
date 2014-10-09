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

    private:
        const MediaInfo mInfo;
    };

    MediaPtr CreateMedia(const MediaInfo& mediaInfo);
}

#endif
