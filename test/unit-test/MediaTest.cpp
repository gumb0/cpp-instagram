#include "Exception.h"
#include "ImagesImpl.h"
#include "MediaImpl.h"

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
}

class MediaTest : public Test
{
    virtual void SetUp()
    {
        mediaInfo = { "id", "link", "caption", "creation time", MediaType::Image, "filter" };
        mediaInfo.mTags = std::vector<std::string>{ "tag1", "tag2" };
        mediaInfo.mImageInfo = CreateImageInfo();

        media = CreateMedia(mediaInfo);
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

        media = CreateMedia(mediaInfo);
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

// TODO test MediaData

class VideoMediaTest : public Test
{
    virtual void SetUp()
    {
        MediaInfo mediaInfo;
        mediaInfo.mType = MediaType::Video;
        mediaInfo.mImageInfo = CreateImageInfo();
        mediaInfo.mVideoInfo.reset(new VideoInfo);

        media = CreateMedia(mediaInfo);
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

// TODO VideosTest