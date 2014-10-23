#ifndef CPP_INSTAGRAM_IMPL_SERVER_RESPONSE_H
#define CPP_INSTAGRAM_IMPL_SERVER_RESPONSE_H

#include "AuthenticatedClient.h" // for Feed
#include "NonCopyable.h"
#include "MediaInfo.h"
#include "UserInfo.h"

#include <json/json.h>

namespace Instagram
{
    class ServerResponse : NonCopyable
    {
    public:
        explicit ServerResponse(const std::string& response);

        UserInfo parseUser() const;
        std::vector<MediaInfo> parseMediaList() const;

    private:
        static MediaInfo parseMedia(const Json::Value& value);
            
        std::string getStringValue(const char* key) const;
        const Json::Value& getValue(const char* key) const;
        UserCounts parseCounts(const Json::Value& value) const;

    private:
        const Json::Value mData;
    };
}

#endif
