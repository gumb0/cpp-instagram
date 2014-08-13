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

    void checkResponseCode(const Json::Value& root)
    {
        const Json::Value meta = root[JSON_KEY_META];
        if (meta.isNull())
            Throw(RESPONSE_JSON_DOESNT_HAVE_META);

        const Json::Value code = meta[JSON_KEY_CODE];
        if (code.isNull())
            Throw(RESPONSE_JSON_DOESNT_HAVE_CODE);

        if (code.asInt() != RESPONSE_CODE_OK)
            Throw(RESPONSE_CONTAINS_SERVER_ERROR, meta.toStyledString());

    }

    Json::Value getDataFromJsonRoot(const Json::Value& root)
    {
        const Json::Value data = root[JSON_KEY_DATA];
        if (data.isNull())
            Throw(USER_JSON_DOESNT_HAVE_DATA);

        return data;
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

    return userInfo;
}

std::string ServerResponse::getStringValue(const char* key) const
{
    const Json::Value value = mData[key];
    if (value.isNull())
        Throw(USER_JSON_KEY_NOT_FOUND, key);

    return value.asString();
}
