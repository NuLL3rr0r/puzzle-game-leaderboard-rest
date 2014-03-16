#ifndef XML_EXCEPTION_HPP
#define XML_EXCEPTION_HPP


#include <string>
#include "exception.hpp"

namespace NowruzPuzzle {
    class XMLException;
}

class NowruzPuzzle::XMLException : public NowruzPuzzle::Exception
{
public:
    explicit XMLException(const std::string &message);
    explicit XMLException(const std::wstring &message);

public:
    virtual const wchar_t *What() const;
};


#endif /* XML_EXCEPTION_HPP */

