#include "Exception.h"
#include "UserImpl.h"

#include <gmock/gmock.h>
#include <memory>

using namespace Instagram;
using namespace testing;

class UserTest : public Test
{
protected:
    const std::string json = R"({"meta":{"code":200},"data":{"username":"snoopdogg","bio":"I smoked out the whitehouse !","website":"http://bit.ly/1onGzhG","profile_picture":"http://images.ak.instagram.com/profiles/profile_1574083_75sq_1381898834.jpg", "full_name":"snoopdogg", "counts" : {"media":7453, "followed_by" : 3370805, "follows" : 698}, "id" : "1574083"}})";
};

TEST_F(UserTest, ParsesId)
{
    UserImpl user(json);

    ASSERT_THAT(user.getId(), StrEq("1574083"));
}

TEST_F(UserTest, ParsesUsername)
{
    UserImpl user(json);

    ASSERT_THAT(user.getUsername(), StrEq("snoopdogg"));
}

TEST(UserSadPathTest, ThrowsIfJsonParseFails)
{
    const std::string json = "{meta";
    std::unique_ptr<User> user;

    ASSERT_THROW(user.reset(new UserImpl(json)), Instagram::Exception);
}

TEST(UserSadPathTest, ThrowsIfJsonHasNoData)
{
    const std::string json = R"({"meta":{"code":200}})";
    std::unique_ptr<User> user;

    ASSERT_THROW(user.reset(new UserImpl(json)), Instagram::Exception);
}

TEST(UserSadPathTest, ThrowsIfJsonHasNoId)
{
    const std::string json = R"({"meta":{"code":200},"data":{"username":"snoopdogg"}})";
    std::unique_ptr<User> user;

    ASSERT_THROW(user.reset(new UserImpl(json)), Instagram::Exception);
}

TEST(UserSadPathTest, ThrowsIfResponseIsError)
{
    const std::string json = R"({"meta":{"error_type": "APINotAllowedError", "code": 400, "error_message": "you cannot view this resource"}})";
    std::unique_ptr<User> user;

    ASSERT_THROW(user.reset(new UserImpl(json)), Instagram::Exception);
}

TEST(UserSadPathTest, ThrowsIfJsonHasNoUsername)
{
    const std::string json = R"({"meta":{"code":200},"data":{"id" : "1574083"}})";
    std::unique_ptr<User> user;

    ASSERT_THROW(user.reset(new UserImpl(json)), Instagram::Exception);
}
