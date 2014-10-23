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
        
        // 0 passed to count makes it ignored
        // empty string passed to minId/maxId makes them ignored
        std::string getFeed(int count, const std::string& minId, const std::string& maxId) const;

        std::string getPopularMedias() const;

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
