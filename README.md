cpp-instagram
=============

C++ client library for Instagram REST API.

Only some of the APIs are supported now.

Has been built with MS Visual Studio Express 2013 (see solution and project files in msvc directory), but contains no platform dependencies and should be easily portable.


requirements
-------

* boost/format http://www.boost.org/doc/libs/1_55_0/libs/format/
* libcurl http://curl.haxx.se/libcurl/
* jsoncpp https://github.com/open-source-parsers/jsoncpp
* Google Mock for tests https://code.google.com/p/googlemock

sample code
----
``` cpp
#include "cpp-instagram/AuthenticatedClient.h"
#include "cpp-instagram/Exception.h"

using namespace Instagram;

void downloadPopularImages()
{
    try
    {
        AuthenticatedClientPtr client = CreateAuthenticatedClient(userToken);

        MediaList medias = client->getPopularMedias();

        for (MediaPtr media : medias)
        {
            const std::string id = media->getId();
            media->getImages()->getStandardResolution()->download(id + ".jpg");
        }
    }
    catch (const Exception& e)
    {
        std::cerr << e.GetMessage() << std::endl;
    }
}
  
```
