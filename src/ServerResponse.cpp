#include "ExceptionHelpers.h"
#include "MediaImpl.h"
#include "ServerResponse.h"

#include <algorithm>
#include <functional>

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
    const char* JSON_KEY_TAGS = "tags";
    const char* JSON_KEY_IMAGES = "images";
    const char* JSON_KEY_VIDEOS = "videos";
    const char* JSON_KEY_LOW_RESOLUTION = "low_resolution";
    const char* JSON_KEY_STANDARD_RESOLUTION = "standard_resolution";
    const char* JSON_KEY_LOW_BANDWIDTH = "low_bandwidth";
    const char* JSON_KEY_THUMBNAIL = "thumbnail";
    const char* JSON_KEY_WIDTH = "width";
    const char* JSON_KEY_HEIGHT = "height";
    const char* JSON_KEY_URL = "url";
    const char* JSON_KEY_LOCATION = "location";
    const char* JSON_KEY_LATITUDE = "latitude";
    const char* JSON_KEY_LONGITUDE = "longitude";
    const char* JSON_KEY_NAME = "name";
    const char* JSON_KEY_USER = "user";

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

    std::string parseCaption(const Json::Value& value)
    {
        return value.empty() ? std::string() : getSubvalue(value, JSON_KEY_TEXT).asString();
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

    MediaType parseMediaType(const Json::Value& value)
    {
        return stringToMediaType(value.asString());
    }

    std::vector<std::string> parseTags(const Json::Value& value)
    {
        std::vector<std::string> tags;
        std::transform(value.begin(), value.end(), std::back_inserter(tags), std::mem_fun_ref(&Json::Value::asString));
        return tags;
    }

    MediaDataInfoPtr parseMediaData(const Json::Value& value)
    {
        MediaDataInfoPtr mediaData(new MediaDataInfo);
        mediaData->mWidth = getSubvalue(value, JSON_KEY_WIDTH).asInt();
        mediaData->mHeight = getSubvalue(value, JSON_KEY_HEIGHT).asInt();
        mediaData->mUrl = getSubvalue(value, JSON_KEY_URL).asString();
        return mediaData;
    }

    MediaDataInfoPtr parseMediaDataSubvalue(const Json::Value& value, const char* key)
    {
        return parseMediaData(getSubvalue(value, key));
    }

    ImageInfoPtr parseImages(const Json::Value& value)
    {
        ImageInfoPtr imageInfos(new ImageInfo);
        imageInfos->mLowResolution = parseMediaDataSubvalue(value, JSON_KEY_LOW_RESOLUTION);
        imageInfos->mStandardResolution = parseMediaDataSubvalue(value, JSON_KEY_STANDARD_RESOLUTION);
        imageInfos->mThumbnail = parseMediaDataSubvalue(value, JSON_KEY_THUMBNAIL);
        return imageInfos;
    }

    VideoInfoPtr parseVideos(const Json::Value& value)
    {
        VideoInfoPtr videoInfo(new VideoInfo);
        videoInfo->mLowBandwidth = parseMediaDataSubvalue(value, JSON_KEY_LOW_BANDWIDTH);
        videoInfo->mLowResolution = parseMediaDataSubvalue(value, JSON_KEY_LOW_RESOLUTION);
        videoInfo->mStandardResolution = parseMediaDataSubvalue(value, JSON_KEY_STANDARD_RESOLUTION);
        return videoInfo;
    }

    std::string parseOptionalStringSubvalue(const Json::Value& value, const char* key)
    {
        const Json::Value& subvalue = getOptionalSubvalue(value, key);

        return subvalue.empty() ? std::string() : subvalue.asString();
    }
 
    LocationInfoPtr parseLocation(const Json::Value& value)
    {
        if (value.empty())
            return LocationInfoPtr();

        LocationInfoPtr locationInfo(new LocationInfo);
        locationInfo->mId = parseOptionalStringSubvalue(value, JSON_KEY_ID);
        locationInfo->mLatitude = getSubvalue(value, JSON_KEY_LATITUDE).asDouble();
        locationInfo->mLongitude = getSubvalue(value, JSON_KEY_LONGITUDE).asDouble();
        locationInfo->mName = parseOptionalStringSubvalue(value, JSON_KEY_NAME);
        return locationInfo;
    }

    std::string parseMediaUser(const Json::Value& value)
    {
        return getSubvalue(value, JSON_KEY_ID).asString();
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
    userInfo.mCounts = parseCounts(getValue(JSON_KEY_COUNTS));

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

UserCounts ServerResponse::parseCounts(const Json::Value& value) const
{
    UserCounts res;
    res.mMedia = getSubvalue(value, JSON_KEY_MEDIA).asUInt();
    res.mFollows = getSubvalue(value, JSON_KEY_FOLLOWS).asUInt();
    res.mFollowedBy = getSubvalue(value, JSON_KEY_FOLLOWED_BY).asUInt();

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
    mediaInfo.mId = getSubvalue(value, JSON_KEY_ID).asString();
    mediaInfo.mLink = getSubvalue(value, JSON_KEY_LINK).asString();
    mediaInfo.mCaption = parseCaption(getOptionalSubvalue(value, JSON_KEY_CAPTION));
    mediaInfo.mCreatedTime = getSubvalue(value, JSON_KEY_CREATED_TIME).asString();
    mediaInfo.mType = parseMediaType(getSubvalue(value, JSON_KEY_TYPE));
    mediaInfo.mFilter = getSubvalue(value, JSON_KEY_FILTER).asString();
    mediaInfo.mTags = parseTags(getSubvalue(value, JSON_KEY_TAGS));
    mediaInfo.mImageInfo = parseImages(getSubvalue(value, JSON_KEY_IMAGES));
    if (mediaInfo.mType == MediaType::Video)
        mediaInfo.mVideoInfo = parseVideos(getSubvalue(value, JSON_KEY_VIDEOS));
    mediaInfo.mLocationInfo = parseLocation(getOptionalSubvalue(value, JSON_KEY_LOCATION));
    mediaInfo.mUserId = parseMediaUser(getSubvalue(value, JSON_KEY_USER));

    return mediaInfo;
}
