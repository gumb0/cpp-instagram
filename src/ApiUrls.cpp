#include "ApiUrls.h"
#include "UrlBuilder.h"

#include <boost/format.hpp>

using namespace Instagram;

namespace
{
    const std::string BASE_URL = "https://api.instagram.com/v1/";
    
    const std::string GET_USER_BY_ID = "users/%1%";
    const std::string GET_FEED = "users/self/feed";
    const std::string GET_POPULAR_MEDIAS = "media/popular";

    const std::string COUNT_PARAM = "count";
    const std::string MIN_ID_PARAM = "min_id";
    const std::string MAX_ID_PARAM = "max_id";

    const std::string CLIENT_ID_PARAM = "client_id";
    const std::string ACCESS_TOKEN_PARAM = "access_token";
}

ApiUrls::ApiUrls(const std::string& accessParamKey, const std::string& accessParamValue) : 
    mAccessParamKey(accessParamKey), 
    mAccessParamValue(accessParamValue)
{
}

std::string ApiUrls::getUserById(const std::string& id) const
{
    const std::string path = boost::str(boost::format(GET_USER_BY_ID) % id);
    return getPathWithAccessParam(path).getResult();
}

UrlBuilder ApiUrls::getPathWithAccessParam(const std::string& path) const
{
    UrlBuilder urlBuilder(BASE_URL, path);
    urlBuilder.addParam(mAccessParamKey, mAccessParamValue);

    return urlBuilder;
}

std::string ApiUrls::getFeed(int count, const std::string& minId, const std::string& maxId) const
{
    UrlBuilder urlBuilder(getPathWithAccessParam(GET_FEED));
    
    if (count)
        urlBuilder.addParam(COUNT_PARAM, count);
    if (!minId.empty())
        urlBuilder.addParam(MIN_ID_PARAM, minId);
    if (!maxId.empty())
        urlBuilder.addParam(MAX_ID_PARAM, maxId);

    return urlBuilder.getResult();
}

std::string ApiUrls::getPopularMedias() const
{
    return getPathWithAccessParam(GET_POPULAR_MEDIAS).getResult();
}

ApiUrlsPtr Instagram::CreateNonauthenticatedApiUrls(const std::string& clientId)
{
    return ApiUrlsPtr(new ApiUrls(CLIENT_ID_PARAM, clientId));
}

ApiUrlsPtr Instagram::CreateAuthenticatedApiUrls(const std::string& accessToken)
{
    return ApiUrlsPtr(new ApiUrls(ACCESS_TOKEN_PARAM, accessToken));
}
