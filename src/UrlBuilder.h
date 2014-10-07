#ifndef CPP_INSTAGRAM_IMPL_URL_BUILDER_H
#define CPP_INSTAGRAM_IMPL_URL_BUILDER_H

#include <string>

namespace Instagram
{
    class UrlBuilder
    {
    public:
        UrlBuilder(const std::string& baseUrl, const std::string& path);

        void addParam(const std::string& key, const std::string& value);
        void addParam(const std::string& key, const int value);

        std::string getResult() const;

    private:
        std::string appendAccessParam(const std::string& url) const;

    private:
        std::string mPath;
        std::string mQuery;
    };
}

#endif
