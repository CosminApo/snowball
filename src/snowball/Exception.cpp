#include "Exception.h"
#include <GL/glew.h>
#include <iostream>

namespace snowball
{
    Exception::Exception(const std::string& message)
    {
        this->message = message; // Store the output message locally.
    }

    Exception::~Exception() throw() { }

    const char* Exception::what() const throw()
    {
        return message.c_str(); // Return the stored message.
    }

}
