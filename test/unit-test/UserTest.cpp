#include "Exception.h"
#include "UserImpl.h"

#include <gmock/gmock.h>
#include <memory>

using namespace Instagram;
using namespace testing;

class UserTest : public Test
{
    virtual void SetUp()
    {
        userInfo = { "id", "userName", "full name", "profile pic", "bio", "website", { 1, 2, 3 } };
        user.reset(new UserImpl(userInfo));
    }

protected:
    UserInfo userInfo;
    std::unique_ptr<User> user;
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

TEST_F(UserTest, getsProfilePicture)
{
    ASSERT_THAT(user->getProfilePicture(), StrEq(userInfo.mProfilePicture));
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
