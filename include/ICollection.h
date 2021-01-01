#ifndef _I_COLLECTION_
#define _I_COLLECTION_

namespace ds
{
    template<typename T>
    class ICollection
    {
    public:
        virtual T* toArray(void) const = 0;
    };

} // namespace ds


#endif // !_I_COLLECTION_