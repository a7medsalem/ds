#ifndef _I_COMPARER_
#define _I_COMPARER_

#include "global.h"

namespace ds
{
    template<typename T>
    class IComparer
    {
    public:
        virtual BYTE compare(T, T) const = 0;
        IComparer<T>& operator=(const IComparer<T>&) const;
    };

} // namespace ds

template<typename T>
ds::IComparer<T>& ds::IComparer<T>::operator=(const IComparer<T>& comparer) const
{
    return compare;
}

#endif // !_I_COMPARER_