#include "Client.h"

#include <gmock/gmock.h>
#include <memory>

using namespace Instagram;
using namespace testing;

class UserTest : public Test
{
    virtual void SetUp()
    {
//        userInfo = { "id", "userName", "full name", "profile pic", "bio", "website", { 1, 2, 3 } };
//        user.reset(new UserImpl(userInfo));
    }

protected:
};

TEST_F(UserTest, getsId)
{
    ClientPtr client = CreateClient("d7b1086490044ada88da482a87b073f3");
}

