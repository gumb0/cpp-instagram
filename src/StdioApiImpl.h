#ifndef CPP_INSTAGRAM_IMPL_STDIO_API_IMPL_H
#define CPP_INSTAGRAM_IMPL_STDIO_API_IMPL_H

#include "StdioApi.h"

namespace Instagram
{

    // The virtual interface wrapper over stdio.h functions, it is needed to mock stdio calls in unit tests
    class StdioApiImpl : public StdioApi
    {
    public:
        virtual FILE* openFileForWrite(const std::string& path);

        virtual size_t writeToFile(const void* buffer, size_t size, size_t count, FILE* file);

        virtual void closeFile(FILE* file);
    };

}

#endif