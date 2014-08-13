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
        userInfo = { "id", "userName", "full name", "profile pic" };
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
