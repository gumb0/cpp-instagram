#ifndef CPP_INSTAGRAM_IMPL_LOCATION_INFO_H
#define CPP_INSTAGRAM_IMPL_LOCATION_INFO_H

#include <memory>
#include <string>

namespace Instagram
{
    struct LocationInfo
    {
        std::string mId;
        double mLatitude;
        double mLongitude;
        std::string mName;
    };

    typedef std::shared_ptr<LocationInfo> LocationInfoPtr;
}

#endif
