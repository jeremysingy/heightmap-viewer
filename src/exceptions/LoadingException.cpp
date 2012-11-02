#include <exceptions/LoadingException.h>

LoadingException::LoadingException(const std::string& msg) :
myMessage(msg)
{

}

LoadingException::~LoadingException() throw()
{

}

const char* LoadingException::what() const throw()
{
    return myMessage.c_str();
}