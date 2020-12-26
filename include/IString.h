#ifndef _I_STRING_H_
#define _I_STRING_H_

#include <string>

namespace ds
{
    class IString
    {
    public:
        virtual std::string toString(void) = 0;
    };

} // namespace ds


#endif // !_I_STRING_H_