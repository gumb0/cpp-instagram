/*
 * Tag.h
 *
 *  Created on: Nov 7, 2014
 *      Author: romeo
 */

#ifndef TAG_H_
#define TAG_H_

#include "NonCopyable.h"

#include <memory>
#include <string>

namespace Instagram
{
    class Tag : NonCopyable
    {
    public:
        virtual std::string getMediaCount() const = 0;
        virtual std::string getName() const = 0;
    };

    typedef std::shared_ptr<Tag> TagPtr;
    typedef std::vector<TagPtr> TagList;
}

#endif /* TAG_H_ */
