#ifndef CPP_INSTAGRAM_IMPL_USER_INFO_H
#define CPP_INSTAGRAM_IMPL_USER_INFO_H

#include <string>

namespace Instagram
{
    struct UserInfo
    {
        std::string mId;
        std::string mUsername;
        std::string mFullName;
        std::string mProfilePicture;
        std::string mBio;
    };
}

#endif
