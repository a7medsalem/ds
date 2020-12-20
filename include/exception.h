#ifndef _EXCEPTION_H
#define _EXCEPTION_H

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
}


#endif // !_EXCEPTION_H