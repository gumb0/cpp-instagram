#ifndef CPP_INSTAGRAM_IMPL_CURL_IMPL_H
#define CPP_INSTAGRAM_IMPL_CURL_IMPL_H

#include "Curl.h"
#include "CurlApi.h"
#include "StdioApi.h"

namespace Instagram
{
    class CurlImpl : public Curl
    {
    public:
        CurlImpl(CurlApiPtr curlApi, StdioApiPtr stdio);
        virtual ~CurlImpl();

        // perform GET request and return response, throw in case of error
        virtual std::string get(const std::string& url);

        // perform GET request and save response to file with localPath, throw in case of error
        virtual void download(const std::string& url, const std::string& localPath);

    private:
        static size_t onDataReceived(char* buffer, size_t size, size_t nmemb, void* context);

        void setUrl(const std::string& url);
        void setGetMethod();
        void setSslCertificatePath();

        void setReceiveCallback(std::string& outResult);
        void setFileReceiveCallback(std::shared_ptr<FILE> file);

        void perform();

    private:
        CurlApiPtr mCurlApi;
        StdioApiPtr mStdio;
        CURL* mHandle;
    };

}

#endif
