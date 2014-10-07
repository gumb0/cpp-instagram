#ifndef CPP_INSTAGRAM_IMPL_API_URLS_H
#define CPP_INSTAGRAM_IMPL_API_URLS_H

#include "NonCopyable.h"

#include <memory>
#include <string>

namespace Instagram
{
    class UrlBuilder;

    class ApiUrls : NonCopyable
    {
    public:
        // initialized with either client_id param or access_token param
        ApiUrls(const std::string& accessParamKey, const std::string& accessParamValue);

        std::string getUserById(const std::string& id) const;
        
        std::string getFeed(int count, int minId, int maxId) const;

    private:
        UrlBuilder getPathWithAccessParam(const std::string& path) const;

    private:
        const std::string mAccessParamKey;
        const std::string mAccessParamValue;
    };

    typedef std::shared_ptr<ApiUrls> ApiUrlsPtr;

    ApiUrlsPtr CreateNonauthenticatedApiUrls(const std::string& clientId);
    ApiUrlsPtr CreateAuthenticatedApiUrls(const std::string& accessToken);
}

#endif
