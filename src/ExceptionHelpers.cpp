#include "ExceptionHelpers.h"

#include <unordered_map>

using namespace Instagram;

namespace
{
    const std::pair<ErrorCode, const char*> CODE_MESSAGE_PAIRS[] = 
    { 
        { CURL_GLOBAL_INIT_FAILED, "curl_global_init() failed." },
        { CURL_EASY_INIT_FAILED, "curl_easy_init() failed." },
        { CURL_SETTING_URL_FAILED, "Setting URL to curl failed." },
        { CURL_SETTING_GET_METHOD_FAILED, "Setting GET method to curl failed." },
        { CURL_SETTING_SSL_CERTIFICATE_PATH_FAILED, "Setting path to SSL certificate bundle failed." },
        { CURL_SETTING_WRITE_FUNCTION_FAILED, "Setting write function callback to curl failed." },
        { CURL_SETTING_WRITE_DATA_FAILED, "Setting data paramter for write function callback failed." },
        { CURL_PERFORM_FAILED, "Perform call of curl failed." },
        { RESPONSE_JSON_PARSE_FAILED, "Invalid JSON data for user." },
        { RESPONSE_CONTAINS_SERVER_ERROR, "Server returned error: " },
        { USER_JSON_KEY_NOT_FOUND, "Key not found in JSON data: " },
    };

    const int CODE_MESSAGE_PAIRS_SIZE = sizeof(CODE_MESSAGE_PAIRS) / sizeof(CODE_MESSAGE_PAIRS[0]);
    const std::unordered_map<ErrorCode, const char*> ERROR_MESSAGE_MAP(CODE_MESSAGE_PAIRS, CODE_MESSAGE_PAIRS + CODE_MESSAGE_PAIRS_SIZE);

    const char* CURL_ERROR_CODE = " CURL error code: ";

    std::string GetMessageFromMap(ErrorCode error)
    {
        std::unordered_map<ErrorCode, const char*>::const_iterator it = ERROR_MESSAGE_MAP.find(error);
        return (it != ERROR_MESSAGE_MAP.end() ? it->second : std::string());
    }
}


std::string Instagram::GetErrorMessage(ErrorCode error, const std::string& additionalMessage)
{
    return GetMessageFromMap(error) + additionalMessage;
}

std::string Instagram::GetCurlErrorMessage(ErrorCode error, CURLcode curlError)
{
    return GetMessageFromMap(error) + CURL_ERROR_CODE + std::to_string(curlError);
}
