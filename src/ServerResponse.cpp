#include "ExceptionHelpers.h"
#include "ServerResponse.h"

#include <json/json.h>

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

    std::string getId(const Json::Value& data)
    {
        const Json::Value id = data[JSON_KEY_ID];
        if (id.isNull())
            Throw(USER_JSON_DOESNT_HAVE_ID);

        return id.asString();
    }

    std::string getUsername(const Json::Value& data)
    {
        const Json::Value username = data[JSON_KEY_USERNAME];
        if (username.isNull())
            Throw(USER_JSON_DOESNT_HAVE_USERNAME);
        
        return username.asString();
    }

    std::string getFullName(const Json::Value& data)
    {
        const Json::Value fullName = data[JSON_KEY_FULL_NAME];
        if (fullName.isNull())
            Throw(USER_JSON_DOESNT_HAVE_FULL_NAME);

        return fullName.asString();
    }

    // TODO dry
    std::string getProfilePicture(const Json::Value& data)
    {
        const Json::Value profilePicture = data[JSON_KEY_PROFILE_PICTURE];
        if (profilePicture.isNull())
            Throw(USER_JSON_DOESNT_HAVE_FULL_NAME);

        return profilePicture.asString();
    }

    UserInfo parseUserInfo(const Json::Value& data)
    {
        UserInfo userInfo;
        userInfo.mId = getId(data);
        userInfo.mUsername = getUsername(data);
        userInfo.mFullName = getFullName(data);
        userInfo.mProfilePicture = getProfilePicture(data);

        return userInfo;
    }
}

UserInfo ServerResponse::parseUser(const std::string& jsonData)
{
    const Json::Value data = getData(jsonData);

    return parseUserInfo(data);
}
