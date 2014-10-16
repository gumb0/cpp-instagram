#ifndef CPP_INSTAGRAM_IMPL_LOCATION_IMPL_H
#define CPP_INSTAGRAM_IMPL_LOCATION_IMPL_H

#include "Location.h"
#include "LocationInfo.h"

namespace Instagram
{
    class LocationImpl : public Location
    {
    public:
        explicit LocationImpl(const LocationInfo& locationInfo);

        virtual std::string getId() const;
        virtual double getLatitude() const;
        virtual double getLongitude() const;
        virtual std::string getName() const;

    private:
        const LocationInfo mInfo;
    };

    LocationPtr CreateLocationImpl(LocationInfoPtr info);
}

#endif
