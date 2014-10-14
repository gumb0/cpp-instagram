#include "Exception.h"
#include "ImagesImpl.h"
#include "MediaDataImpl.h"
#include "MediaImpl.h"
#include "VideosImpl.h"

#include <gmock/gmock.h>
#include <memory>

using namespace Instagram;
using namespace testing;

namespace
{
    ImageInfoPtr CreateImageInfo()
    {
        ImageInfoPtr imageInfo(new ImageInfo);
        imageInfo->mLowResolution.reset(new MediaDataInfo);
        imageInfo->mStandardResolution.reset(new MediaDataInfo);
        imageInfo->mThumbnail.reset(new MediaDataInfo);
        
        return imageInfo;
    }

    VideoInfoPtr CreateVideoInfo()
    {
        VideoInfoPtr videoInfo(new VideoInfo);
        videoInfo->mLowResolution.reset(new MediaDataInfo);
        videoInfo->mStandardResolution.reset(new MediaDataInfo);
        videoInfo->mLowBandwidth.reset(new MediaDataInfo);

        return videoInfo;
    }
}

class MediaTest : public Test
{
    virtual void SetUp()
    {
        mediaInfo = { "id", "link", "caption", "creation time", MediaType::Image, "filter" };
        mediaInfo.mTags = std::vector<std::string>{ "tag1", "tag2" };
        mediaInfo.mImageInfo = CreateImageInfo();

        media = CreateMediaImpl(mediaInfo);
    }

protected:
    MediaInfo mediaInfo;
    MediaPtr media;
};

TEST_F(MediaTest, getsLink)
{
    ASSERT_THAT(media->getLink(), StrEq(mediaInfo.mLink));
}

TEST_F(MediaTest, getsCaption)
{
    ASSERT_THAT(media->getCaption(), StrEq(mediaInfo.mCaption));
}

TEST_F(MediaTest, getsCreationTime)
{
    ASSERT_THAT(media->getCreatedTime(), StrEq(mediaInfo.mCreatedTime));
}

TEST_F(MediaTest, getsType)
{
    ASSERT_THAT(media->getType(), Eq(mediaInfo.mType));
}

TEST_F(MediaTest, getsFilter)
{
    ASSERT_THAT(media->getFilter(), StrEq(mediaInfo.mFilter));
}

TEST_F(MediaTest, getsId)
{
    ASSERT_THAT(media->getId(), StrEq(mediaInfo.mId));
}

TEST_F(MediaTest, getsTags)
{
    ASSERT_THAT(media->getTags(), ElementsAreArray(mediaInfo.mTags));
}

class ImageMediaTest : public Test
{
    virtual void SetUp()
    {
        MediaInfo mediaInfo;
        mediaInfo.mType = MediaType::Image;
        mediaInfo.mImageInfo = CreateImageInfo();

        media = CreateMediaImpl(mediaInfo);
    }

protected:
    MediaPtr media;
};


TEST_F(ImageMediaTest, getsImages)
{
    ASSERT_THAT(media->getImages(), NotNull());
}

TEST_F(ImageMediaTest, GettingVideosThrows)
{
    ASSERT_THROW(media->getVideos(), Instagram::Exception);
}

class ImagesTest : public Test
{
    virtual void SetUp()
    {
        images = CreateImagesImpl(CreateImageInfo());
    }

protected:
    ImagesPtr images;
};

TEST_F(ImagesTest, getsLowResolutionImage)
{
    ASSERT_THAT(images->getLowResolution(), NotNull());
}

TEST_F(ImagesTest, getsStandardResolutionImage)
{
    ASSERT_THAT(images->getStandardResolution(), NotNull());
}

TEST_F(ImagesTest, getsThumbnail)
{
    ASSERT_THAT(images->getThumbnail(), NotNull());
}


class MediaDataTest : public Test
{
    virtual void SetUp()
    {
        info.reset(new MediaDataInfo);
        info->mWidth = 640;
        info->mHeight = 480;
        info->mUrl = "url";
        
        mediaData = CreateMediaDataImpl(info);
    }

protected:
    MediaDataInfoPtr info;
    MediaDataPtr mediaData;
};

TEST_F(MediaDataTest, getsWidth)
{
    ASSERT_THAT(mediaData->getWidth(), Eq(info->mWidth));
}

TEST_F(MediaDataTest, getsHeight)
{
    ASSERT_THAT(mediaData->getHeight(), Eq(info->mHeight));
}

TEST_F(MediaDataTest, getsUrl)
{
    ASSERT_THAT(mediaData->getUrl(), StrEq(info->mUrl));
}


class VideoMediaTest : public Test
{
    virtual void SetUp()
    {
        MediaInfo mediaInfo;
        mediaInfo.mType = MediaType::Video;
        mediaInfo.mImageInfo = CreateImageInfo();
        mediaInfo.mVideoInfo = CreateVideoInfo();;

        media = CreateMediaImpl(mediaInfo);
    }

protected:
    MediaPtr media;
};

TEST_F(VideoMediaTest, getsImages)
{
    ASSERT_THAT(media->getImages(), NotNull());
}

TEST_F(VideoMediaTest, getsVideos)
{
    ASSERT_THAT(media->getVideos(), NotNull());
}

class VideosTest : public Test
{
    virtual void SetUp()
    {
        videos = CreateVideosImpl(CreateVideoInfo());
    }

protected:
    VideosPtr videos;
};

TEST_F(VideosTest, getsLowBandwidthideo)
{
    ASSERT_THAT(videos->getLowBandwidth(), NotNull());
}

TEST_F(VideosTest, getsLowResolutionVideo)
{
    ASSERT_THAT(videos->getLowResolution(), NotNull());
}

TEST_F(VideosTest, getsStandardResolutionVideo)
{
    ASSERT_THAT(videos->getStandardResolution(), NotNull());
}
