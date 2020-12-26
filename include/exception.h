#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <string>
#include <exception>

namespace ds
{
    class exception : public std::exception 
    {
    private:
        std::string msg_;
    public:
        exception(std::string const &message);
        virtual char const *what() const noexcept;
    };



    class negativeIndexNotAllowedException : public ds::exception
    {
    public:
        negativeIndexNotAllowedException();
    };

    class outOfRangeException : public ds::exception
    {
    public:
        outOfRangeException();
    };

    class emptyCollectionException : public ds::exception
    {
    public:
        emptyCollectionException();
    };
}


#endif // !_EXCEPTION_H_