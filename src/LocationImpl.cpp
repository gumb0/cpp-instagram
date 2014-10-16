#include "LocationImpl.h"

#include <assert.h>

using namespace Instagram;

LocationImpl::LocationImpl(const LocationInfo& info) : mInfo(info)
{
}

std::string LocationImpl::getId() const
{
    return mInfo.mId;
}

double LocationImpl::getLatitude() const
{
    return mInfo.mLatitude;
}

double LocationImpl::getLongitude() const
{
    return mInfo.mLongitude;
}

std::string LocationImpl::getName() const
{
    return mInfo.mName;
}

LocationPtr Instagram::CreateLocationImpl(LocationInfoPtr info)
{
    assert(info);

    return LocationPtr(new LocationImpl(*info));
}