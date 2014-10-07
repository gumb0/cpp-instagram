#include "ClientImpl.h"
#include "MockCurl.h"
#include "User.h"

#include <gmock/gmock.h>
#include <memory>

using namespace Instagram;
using namespace testing;

class ClientTest : public Test
{
protected:
    virtual void SetUp()
    {
        curl.reset(new MockCurl);

        client.reset(new ClientImpl(curl, CreateNonauthenticatedApiUrls(clientId)));
    }

    std::shared_ptr<MockCurl> curl;
    std::unique_ptr<Client> client;
    const std::string clientId = "client-id";
};

TEST_F(ClientTest, FindsUserById)
{
    const std::string id = "1574083";

    const std::string request = std::string("https://api.instagram.com/v1/users/") + id + "?client_id=" + clientId;
    std::string response = "{\"meta\":{\"code\":200},\"data\":{\"username\":\"snoopdogg\",\"bio\":\"I smoked out the whitehouse !\",\"website\":\"http://bit.ly/1onGzhG\",\"profile_picture\":\"http://images.ak.instagram.com/profiles/profile_1574083_75sq_1381898834.jpg\", \"full_name\":\"snoopdogg\", \"counts\" : {\"media\":7453, \"followed_by\" : 3370805, \"follows\" : 698}, \"id\" : \"1574083\"}}";
    EXPECT_CALL(*curl, get(StrEq(request))).WillOnce(Return(response));

    UserPtr user = client->findUserById(id);
    ASSERT_THAT(user->getId(), StrEq(id));
}
