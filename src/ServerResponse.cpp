#include "ExceptionHelpers.h"
#include "ServerResponse.h"

using namespace Instagram;

namespace
{
    const char* JSON_KEY_META = "meta";
    const char* JSON_KEY_CODE = "code";
    const char* JSON_KEY_DATA = "data";
    const char* JSON_KEY_ID = "id";
    const char* JSON_KEY_USERNAME = "username";
    const char* JSON_KEY_FULL_NAME = "full_name";
    const char* JSON_KEY_PROFILE_PICTURE = "profile_picture";
    const char* JSON_KEY_BIO = "bio";
    const char* JSON_KEY_WEBSITE = "website";
    const char* JSON_KEY_COUNTS = "counts";
    const char* JSON_KEY_MEDIA = "media";
    const char* JSON_KEY_FOLLOWS = "follows";
    const char* JSON_KEY_FOLLOWED_BY = "followed_by";

    const Json::Int RESPONSE_CODE_OK = 200;
}

namespace
{
    Json::Value getRoot(const std::string& jsonData)
    {
        Json::Reader jsonReader;
        Json::Value root;
        if (!jsonReader.parse(jsonData, root))
            Throw(RESPONSE_JSON_PARSE_FAILED);

        return root;
    }

    Json::Value getSubvalue(const Json::Value& value, const char* key)
    {
        const Json::Value subvalue = value[key];
        if (subvalue.isNull())
            Throw(USER_JSON_KEY_NOT_FOUND, key);

        return subvalue;
    }

    void checkResponseCode(const Json::Value& root)
    {
        const Json::Value meta = getSubvalue(root, JSON_KEY_META);

        const Json::Value code = getSubvalue(meta, JSON_KEY_CODE);

        if (code.asInt() != RESPONSE_CODE_OK)
            Throw(RESPONSE_CONTAINS_SERVER_ERROR, meta.toStyledString());
    }

    Json::Value getDataFromJsonRoot(const Json::Value& root)
    {
        return getSubvalue(root, JSON_KEY_DATA);
    }

    Json::Value getData(const std::string& jsonData)
    {
        Json::Value jsonRoot = getRoot(jsonData);
        checkResponseCode(jsonRoot);

        return getDataFromJsonRoot(jsonRoot);
    }
}

ServerResponse::ServerResponse(const std::string& response) : mData(getData(response))
{
}

UserInfo ServerResponse::parseUser() const
{
    UserInfo userInfo;
    userInfo.mId = getStringValue(JSON_KEY_ID);
    userInfo.mUsername = getStringValue(JSON_KEY_USERNAME);
    userInfo.mFullName = getStringValue(JSON_KEY_FULL_NAME);
    userInfo.mProfilePicture = getStringValue(JSON_KEY_PROFILE_PICTURE);
    userInfo.mBio = getStringValue(JSON_KEY_BIO);
    userInfo.mWebsite = getStringValue(JSON_KEY_WEBSITE);
    userInfo.mCounts = parseCounts();

    return userInfo;
}

std::string ServerResponse::getStringValue(const char* key) const
{
    return getValue(key).asString();
}

Json::Value ServerResponse::getValue(const char* key) const
{
    return getSubvalue(mData, key);
}

UserCounts ServerResponse::parseCounts() const
{
    const Json::Value counts = getValue(JSON_KEY_COUNTS);

    UserCounts res;
    res.mMedia = getSubvalue(counts, JSON_KEY_MEDIA).asUInt();
    res.mFollows = getSubvalue(counts, JSON_KEY_FOLLOWS).asUInt();
    res.mFollowedBy = getSubvalue(counts, JSON_KEY_FOLLOWED_BY).asUInt();

    return res;
}
