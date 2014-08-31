#ifndef CPP_INSTAGRAM_NONCOPYABLE_H
#define CPP_INSTAGRAM_NONCOPYABLE_H

namespace Instagram
{
    class NonCopyable
    {
    protected:
        NonCopyable() {}
        virtual ~NonCopyable() {}

    private:
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
    };
}

#endif