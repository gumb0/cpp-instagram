#include "UserImpl.h"
#include "ExceptionHelpers.h"

#include <json/json.h>

using namespace Instagram;

UserImpl::UserImpl(const std::string& jsonData)
{
    Json::Reader jsonReader;
    Json::Value jsonValue;
    bool res = jsonReader.parse(jsonData, jsonValue);

    // TODO handle errors
    mId = jsonValue["data"]["id"].asString();
        
}

std::string UserImpl::getId() const
{
    return mId;
}
