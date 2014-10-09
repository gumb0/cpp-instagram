#include "MediaImpl.h"

#include <gmock/gmock.h>
#include <memory>

using namespace Instagram;
using namespace testing;

class MediaTest : public Test
{
    virtual void SetUp()
    {
        mediaInfo = { "link", "caption", "creation time", MediaType::Image };
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
    ASSERT_THAT(media->getType(), Eq(MediaType::Image));
}
