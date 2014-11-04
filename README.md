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

sample app invocation
----
```
  ./cpp-instagram --token <your_CLIENT_ID>
```
