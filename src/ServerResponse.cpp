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
    userInfo.mId = getId();
    userInfo.mUsername = getUsername();
    userInfo.mFullName = getFullName();
    userInfo.mProfilePicture = getProfilePicture();

    return userInfo;
}

std::string ServerResponse::getId() const
{
    const Json::Value id = mData[JSON_KEY_ID];
    if (id.isNull())
        Throw(USER_JSON_DOESNT_HAVE_ID);

    return id.asString();
}

std::string ServerResponse::getUsername() const
{
    const Json::Value username = mData[JSON_KEY_USERNAME];
    if (username.isNull())
        Throw(USER_JSON_DOESNT_HAVE_USERNAME);

    return username.asString();
}

std::string ServerResponse::getFullName() const
{
    const Json::Value fullName = mData[JSON_KEY_FULL_NAME];
    if (fullName.isNull())
        Throw(USER_JSON_DOESNT_HAVE_FULL_NAME);

    return fullName.asString();
}

// TODO dry
std::string ServerResponse::getProfilePicture() const
{
    const Json::Value profilePicture = mData[JSON_KEY_PROFILE_PICTURE];
    if (profilePicture.isNull())
        Throw(USER_JSON_DOESNT_HAVE_FULL_NAME);

    return profilePicture.asString();
}
