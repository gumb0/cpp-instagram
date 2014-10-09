#include "ExceptionHelpers.h"
#include "MediaImpl.h"
#include "ServerResponse.h"

#include <algorithm>

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
    const char* JSON_KEY_LINK = "link";
    const char* JSON_KEY_CAPTION = "caption";
    const char* JSON_KEY_TEXT = "text";
    const char* JSON_KEY_CREATED_TIME = "created_time";
    const char* JSON_KEY_TYPE = "type";
    const char* JSON_KEY_FILTER = "filter";

    const char* MEDIA_TYPE_IMAGE = "image";
    const char* MEDIA_TYPE_VIDEO = "video";

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

    const Json::Value& getSubvalue(const Json::Value& value, const char* key)
    {
        const Json::Value& subvalue = value[key];
        if (subvalue.isNull())
            Throw(USER_JSON_KEY_NOT_FOUND, key);

        return subvalue;
    }

    const Json::Value& getOptionalSubvalue(const Json::Value& value, const char* key)
    {
        return value[key];
    }

    void checkResponseCode(const Json::Value& root)
    {
        const Json::Value& meta = getSubvalue(root, JSON_KEY_META);

        const Json::Value& code = getSubvalue(meta, JSON_KEY_CODE);

        if (code.asInt() != RESPONSE_CODE_OK)
            Throw(RESPONSE_CONTAINS_SERVER_ERROR, meta.toStyledString());
    }

    const Json::Value& getDataFromJsonRoot(const Json::Value& root)
    {
        return getSubvalue(root, JSON_KEY_DATA);
    }

    Json::Value getData(const std::string& jsonData)
    {
        Json::Value jsonRoot = getRoot(jsonData);
        checkResponseCode(jsonRoot);

        return getDataFromJsonRoot(jsonRoot);
    }

    std::string getCaptionSubvalue(const Json::Value& value)
    {
        const Json::Value& captionValue = getOptionalSubvalue(value, JSON_KEY_CAPTION);
        return captionValue.empty() ? std::string() : getSubvalue(captionValue, JSON_KEY_TEXT).asString();
    }

    MediaType stringToMediaType(const std::string& type)
    {
        MediaType mediaType;
        if (type == MEDIA_TYPE_IMAGE)
            mediaType = MediaType::Image;
        else if (type == MEDIA_TYPE_VIDEO)
            mediaType = MediaType::Video;
        else
            Throw(UNKNOWN_MEDIA_TYPE);
    
        return mediaType;
    }

    MediaType getMediaTypeSubvalue(const Json::Value& value)
    {
        const std::string type = getSubvalue(value, JSON_KEY_TYPE).asString();
        return stringToMediaType(type);
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

const Json::Value& ServerResponse::getValue(const char* key) const
{
    return getSubvalue(mData, key);
}

UserCounts ServerResponse::parseCounts() const
{
    const Json::Value& counts = getValue(JSON_KEY_COUNTS);

    UserCounts res;
    res.mMedia = getSubvalue(counts, JSON_KEY_MEDIA).asUInt();
    res.mFollows = getSubvalue(counts, JSON_KEY_FOLLOWS).asUInt();
    res.mFollowedBy = getSubvalue(counts, JSON_KEY_FOLLOWED_BY).asUInt();

    return res;
}

std::vector<MediaInfo> ServerResponse::parseFeed() const
{
    std::vector<MediaInfo> feed;
    std::transform(mData.begin(), mData.end(), std::back_inserter(feed), parseMedia);
    return feed;
}

MediaInfo ServerResponse::parseMedia(const Json::Value& value)
{
    MediaInfo mediaInfo;
    mediaInfo.mLink = getSubvalue(value, JSON_KEY_LINK).asString();
    mediaInfo.mCaption = getCaptionSubvalue(value);
    mediaInfo.mCreatedTime = getSubvalue(value, JSON_KEY_CREATED_TIME).asString();
    mediaInfo.mType = getMediaTypeSubvalue(value);
    mediaInfo.mFilter = getSubvalue(value, JSON_KEY_FILTER).asString();

    return mediaInfo;
}
