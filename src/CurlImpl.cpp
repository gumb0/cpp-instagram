#include "CurlImpl.h"
#include "ExceptionHelpers.h"

using namespace Instagram;
using namespace std::placeholders;

namespace
{
#ifdef _WIN32
	const char* SSL_CERTIFICATE_PATH = "ca-bundle.crt";
#else
	const char* SSL_CERTIFICATE_PATH = "/etc/ssl/certs/ca-certificates.crt";
#endif
}

CurlImpl::CurlImpl(CurlApiPtr curlApi, StdioApiPtr stdio) :
    mCurlApi(curlApi),
    mStdio(stdio),
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

void CurlImpl::download(const std::string& url, const std::string& localPath)
{
    setUrl(url);
    setGetMethod();

    std::shared_ptr<FILE> file(mStdio->openFileForWrite(localPath), std::bind(&StdioApi::closeFile, mStdio, _1));
    if (!file)
        Throw(FILE_OPEN_FOR_WRITE_FAILED, localPath);

    FileWriteFunction fileWriteFunction = std::bind(&StdioApi::writeToFile, mStdio, _1, _2, _3, file.get());
    setFileReceiveCallback(fileWriteFunction);

    perform();
}

void CurlImpl::setFileReceiveCallback(FileWriteFunction& fileWriteFunction)
{
    if (CURLcode result = mCurlApi->curl_easy_setopt_func(mHandle, CURLOPT_WRITEFUNCTION, onFileDataReceived))
        ThrowCurl(CURL_SETTING_WRITE_FUNCTION_FAILED, result);

    if (CURLcode result = mCurlApi->curl_easy_setopt_ptr(mHandle, CURLOPT_WRITEDATA, &fileWriteFunction))
        ThrowCurl(CURL_SETTING_WRITE_DATA_FAILED, result);
}

size_t CurlImpl::onFileDataReceived(char* buffer, size_t size, size_t nmemb, void* context)
{
    const FileWriteFunction* fileWriteFunction = static_cast<FileWriteFunction*>(context);
    return (*fileWriteFunction)(buffer, size, nmemb);
}
