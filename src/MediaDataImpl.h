#ifndef CPP_INSTAGRAM_IMPL_MEDIA_DATA_IMPL_H
#define CPP_INSTAGRAM_IMPL_MEDIA_DATA_IMPL_H

#include "Curl.h"
#include "MediaData.h"
#include "MediaDataInfo.h"

namespace Instagram
{
    class MediaDataImpl : public MediaData
    {
    public:
        MediaDataImpl(CurlPtr curl, const MediaDataInfo& mediaDataInfo);

        virtual int getWidth() const;
        virtual int getHeight() const;
        virtual std::string getUrl() const;
        virtual void download(const std::string& localPath) const;

    private:
        CurlPtr mCurl;
        const MediaDataInfo mInfo;
    };

    MediaDataPtr CreateMediaDataImpl(CurlPtr curl, MediaDataInfoPtr info);
}

#endif
