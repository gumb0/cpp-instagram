#ifndef CPP_INSTAGRAM_LOCATION_H
#define CPP_INSTAGRAM_LOCATION_H

#include "NonCopyable.h"

#include <memory>
#include <string>

namespace Instagram
{
    class Location : NonCopyable
    {
    public:
        virtual std::string getId() const = 0;
        virtual double getLatitude() const = 0;
        virtual double getLongitude() const = 0;
        virtual std::string getName() const = 0;
    };

    typedef std::shared_ptr<Location> LocationPtr;
}

#endif