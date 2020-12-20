#include "exception.h"


ds::exception::exception(std::string const &message) 
    : msg_(message) { }


char const* ds::exception::what() const noexcept 
{ 
    return msg_.c_str(); 
}


ds::negativeIndexNotAllowedException::negativeIndexNotAllowedException()
    : ds::exception::exception("OUT_OF_RANGE_EXCEPTION") { }