#include "Client.h"
#include "User.h"

#include <gmock/gmock.h>

using namespace Instagram;
using namespace testing;

class ClientTest : public Test
{
protected:
    virtual void SetUp()
    {
        // TODO init with constructor
        client.init("client-id");
    }

    Client client;
};

TEST_F(ClientTest, DISABLED_FindsUserById)
{
    const std::string id = "1574083";

    User user = client.findUserById(id);
    ASSERT_THAT(user.getId(), StrEq(id));
}
