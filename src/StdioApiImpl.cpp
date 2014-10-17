#include "ExceptionHelpers.h"
#include "StdioApiImpl.h"

using namespace Instagram;

namespace
{
    const static char* OPEN_MODE_WRITE_BINARY = "wb";
}

FILE* StdioApiImpl::openFileForWrite(const std::string& path)
{
    FILE* f = fopen(path.c_str(), OPEN_MODE_WRITE_BINARY);
    if (!f)
        Throw(FILE_OPEN_FOR_WRITE_FAILED, path);

    return f;
}

void StdioApiImpl::closeFile(FILE* file)
{
    fclose(file);
}
