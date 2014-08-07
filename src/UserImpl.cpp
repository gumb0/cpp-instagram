#include "UserImpl.h"
#include "ExceptionHelpers.h"

#include <json/json.h>

using namespace Instagram;

namespace
{
    const char* JSON_KEY_META = "meta";
    const char* JSON_KEY_CODE = "code";
    const char* JSON_KEY_DATA = "data";
    const char* JSON_KEY_ID = "id";

    const Json::Int RESPONSE_CODE_OK = 200;
}

// TODO initialize with UserInfo struct instead, move json parser to another class
UserImpl::UserImpl(const std::string& jsonData)
{
    Json::Reader jsonReader;
    Json::Value jsonRoot;
    if (!jsonReader.parse(jsonData, jsonRoot))
        Throw(RESPONSE_JSON_PARSE_FAILED);

    const Json::Value meta = jsonRoot[JSON_KEY_META];
    if (meta.isNull())
        Throw(RESPONSE_JSON_DOESNT_HAVE_META);

    const Json::Value code = meta[JSON_KEY_CODE];
    if (code.isNull())
        Throw(RESPONSE_JSON_DOESNT_HAVE_CODE);

    if (code.asInt() != RESPONSE_CODE_OK)
        Throw(RESPONSE_CONTAINS_SERVER_ERROR, meta.toStyledString());

    const Json::Value data = jsonRoot[JSON_KEY_DATA];
    if (data.isNull())
        Throw(USER_JSON_DOESNT_HAVE_DATA);

    const Json::Value id = data[JSON_KEY_ID];
    if (id.isNull())
        Throw(USER_JSON_DOESNT_HAVE_ID);

    mId = id.asString();
}

std::string UserImpl::getId() const
{
    return mId;
}
