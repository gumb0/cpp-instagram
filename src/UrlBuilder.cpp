#include "UrlBuilder.h"

using namespace Instagram;

namespace
{
    const char PATH_QUERY_SEPARATOR = '?';
    const char KEY_VALUE_SEPARATOR = '=';
    const char PARAM_SEPARATOR = '&';
}

UrlBuilder::UrlBuilder(const std::string& baseUrl, const std::string& path) :
    mPath(baseUrl + path)
{

}

void UrlBuilder::addParam(const std::string& key, const std::string& value)
{
    if (!mQuery.empty())
        mQuery += PARAM_SEPARATOR;

    mQuery += key;
    mQuery += KEY_VALUE_SEPARATOR;
    mQuery += value;
}

void UrlBuilder::addParam(const std::string& key, const int value)
{
    addParam(key, std::to_string(value));
}


std::string UrlBuilder::getResult() const
{
    return mQuery.empty() ? mPath : mPath + PATH_QUERY_SEPARATOR + mQuery;
}
