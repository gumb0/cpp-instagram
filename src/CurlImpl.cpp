#include "CurlImpl.h"
#include "ExceptionHelpers.h"

using namespace Instagram;

namespace
{
    const char* SSL_CERTIFICATE_PATH = "ca-bundle.crt";
}

CurlImpl::CurlImpl(CurlApiPtr curlApi) : 
    mCurlApi(curlApi),
    mHandle(mCurlApi->curl_easy_init())
{
    if (!mHandle)
        Throw(CURL_EASY_INIT_FAILED);
}

CurlImpl::~CurlImpl()
{
    mCurlApi->curl_easy_cleanup(mHandle);
}

std::string CurlImpl::get(const std::string& url)
{
    setUrl(url);
    setGetMethod();
    setSslCertificatePath();

    std::string result;
    setReceiveCallback(result);

    perform();

    return result;
}

void CurlImpl::setUrl(const std::string& url)
{
    if (CURLcode result = mCurlApi->curl_easy_setopt_string(mHandle, CURLOPT_URL, url.c_str()))
        ThrowCurl(CURL_SETTING_URL_FAILED, result);
}

void CurlImpl::setGetMethod()
{
    if (CURLcode result = mCurlApi->curl_easy_setopt_long(mHandle, CURLOPT_HTTPGET, 1))
        ThrowCurl(CURL_SETTING_GET_METHOD_FAILED, result);
}

void CurlImpl::setSslCertificatePath()
{
    if (CURLcode result = mCurlApi->curl_easy_setopt_string(mHandle, CURLOPT_CAINFO, SSL_CERTIFICATE_PATH))
        ThrowCurl(CURL_SETTING_SSL_CERTIFICATE_PATH_FAILED, result);
}

void CurlImpl::setReceiveCallback(std::string& outResult)
{
    if (CURLcode result = mCurlApi->curl_easy_setopt_func(mHandle, CURLOPT_WRITEFUNCTION, onDataReceived))
        ThrowCurl(CURL_SETTING_WRITE_FUNCTION_FAILED, result);

    if (CURLcode result = mCurlApi->curl_easy_setopt_ptr(mHandle, CURLOPT_WRITEDATA, &outResult))
        ThrowCurl(CURL_SETTING_WRITE_DATA_FAILED, result);
}

size_t CurlImpl::onDataReceived(char* buffer, size_t size, size_t nmemb, void* context)
{
    std::string* s = static_cast<std::string*>(context);
    s->append(buffer, nmemb * size);

    return nmemb * size;
}

void CurlImpl::perform()
{
    if (CURLcode result = mCurlApi->curl_easy_perform(mHandle))
        ThrowCurl(CURL_PERFORM_FAILED, result);
}
