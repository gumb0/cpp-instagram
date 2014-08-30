#include "CurlApiImpl.h"
#include "CurlInitializer.h"
#include "ExceptionHelpers.h"

using namespace Instagram;

namespace
{
    // Initializing will be called during global variables initialization
    CurlInitializer curlInitializer(CurlApiPtr(new CurlApiImpl));
}

CurlInitializer::CurlInitializer(CurlApiPtr curlApi) : mCurlApi(curlApi)
{
    if (mCurlApi->curl_global_init(CURL_GLOBAL_ALL))
        Throw(CURL_GLOBAL_INIT_FAILED);
}

CurlInitializer::~CurlInitializer()
{
    mCurlApi->curl_global_cleanup();
}
