#ifndef LOADINGEXCEPTION_H
#define LOADINGEXCEPTION_H

#include <stdexcept>
#include <string>

class LoadingException : public std::exception
{
    public:
        
        LoadingException(const std::string& msg = "");
        virtual ~LoadingException() throw();
        
        virtual const char* what() const throw();

    protected:
    
        std::string myMessage;
};

#endif // LOADINGEXCEPTION_H 