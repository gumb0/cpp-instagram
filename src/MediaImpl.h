#ifndef CPP_INSTAGRAM_IMPL_MEDIA_IMPL_H
#define CPP_INSTAGRAM_IMPL_MEDIA_IMPL_H

#include "Media.h"

namespace Instagram
{
    class MediaImpl : public Media
    {
    public:
        explicit MediaImpl(const std::string& link);

        virtual std::string getLink() const;

    private:
        const std::string mLink;
    };
}

#endif
