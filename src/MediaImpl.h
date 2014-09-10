#ifndef CPP_INSTAGRAM_IMPL_MEDIA_IMPL_H
#define CPP_INSTAGRAM_IMPL_MEDIA_IMPL_H

#include "Media.h"

namespace Instagram
{
    class MediaImpl : public Media
    {
    public:
        MediaImpl(const std::string& link, const std::string& caption);

        virtual std::string getLink() const;
        virtual std::string getCaption() const;

    private:
        const std::string mLink;
        const std::string mCaption;
    };
}

#endif
