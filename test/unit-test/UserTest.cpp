#include "Exception.h"
#include "MockCurl.h"
#include "UserImpl.h"

#include <gmock/gmock.h>
#include <memory>

using namespace Instagram;
using namespace testing;

class UserTest : public Test
{
    virtual void SetUp()
    {
        curl.reset(new MockCurl);

        userInfo = { "id", "userName", "full name", "profile pic", "bio", "website", { 1, 2, 3 } };
        user = CreateUserImpl(curl, userInfo);
    }

protected:
    std::shared_ptr<MockCurl> curl;
    UserInfo userInfo;
    UserPtr user;
};

TEST_F(UserTest, getsId)
{
    ASSERT_THAT(user->getId(), StrEq(userInfo.mId));
}

TEST_F(UserTest, getsUsername)
{
    ASSERT_THAT(user->getUsername(), StrEq(userInfo.mUsername));
}

TEST_F(UserTest, getsFullName)
{
    ASSERT_THAT(user->getFullName(), StrEq(userInfo.mFullName));
}

TEST_F(UserTest, getsProfilePictureUrl)
{
    ASSERT_THAT(user->getProfilePictureUrl(), StrEq(userInfo.mProfilePicture));
}

TEST_F(UserTest, downloadsProfilePicture)
{
    const std::string localPath = "path";
    EXPECT_CALL(*curl, download(StrEq(userInfo.mProfilePicture), StrEq(localPath)));

    user->downloadProfilePicture(localPath);
}

TEST_F(UserTest, getsBio)
{
    ASSERT_THAT(user->getBio(), StrEq(userInfo.mBio));
}

TEST_F(UserTest, getsWebsite)
{
    ASSERT_THAT(user->getWebsite(), StrEq(userInfo.mWebsite));
}

TEST_F(UserTest, getMediaCount)
{
    ASSERT_THAT(user->getMediaCount(), Eq(userInfo.mCounts.mMedia));
}

TEST_F(UserTest, getFollowsCount)
{
    ASSERT_THAT(user->getFollowsCount(), Eq(userInfo.mCounts.mFollows));
}

TEST_F(UserTest, getFollowedByCount)
{
    ASSERT_THAT(user->getFollowedByCount(), Eq(userInfo.mCounts.mFollowedBy));
}
