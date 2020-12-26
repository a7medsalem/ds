#include "exception.h"


ds::exception::exception(std::string const &message) 
    : msg_(message) { }


char const* ds::exception::what() const noexcept 
{ 
    return msg_.c_str(); 
}


ds::negativeIndexNotAllowedException::negativeIndexNotAllowedException()
    : ds::exception::exception("NEGATIVE_INDEX_NOT_ALLOWED_EXCEPTION") { }


ds::outOfRangeException::outOfRangeException()
    : ds::exception::exception("OUT_OF_RANGE_EXCEPTION") { }

ds::emptyCollectionException::emptyCollectionException()
    : ds::exception::exception("COLLECTION_HAS_NOT_ELEMENTS") { }