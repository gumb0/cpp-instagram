#ifndef CPP_INSTAGRAM_IMPL_STDIO_API_H
#define CPP_INSTAGRAM_IMPL_STDIO_API_H

#include "NonCopyable.h"

#include <memory>
#include <string>

namespace Instagram
{

    // The virtual interface wrapper over stdio.h functions, it is needed to mock stdio calls in unit tests
    class StdioApi : NonCopyable
    {
    public:
        virtual FILE* openFileForWrite(const std::string& path) = 0;
        virtual size_t writeToFile(const void* buffer, size_t size, size_t count, FILE* file) = 0;
        virtual void closeFile(FILE* file) = 0;
    };

    typedef std::shared_ptr<StdioApi> StdioApiPtr;

}

#endif