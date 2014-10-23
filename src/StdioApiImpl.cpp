#include "StdioApiImpl.h"

using namespace Instagram;

namespace
{
    const static char* OPEN_MODE_WRITE_BINARY = "wb";
}

FILE* StdioApiImpl::openFileForWrite(const std::string& path)
{
    return fopen(path.c_str(), OPEN_MODE_WRITE_BINARY);
}

size_t StdioApiImpl::writeToFile(const void* buffer, size_t size, size_t count, FILE* file)
{
    return fwrite(buffer, size, count, file);
}

void StdioApiImpl::closeFile(FILE* file)
{
    fclose(file);
}
