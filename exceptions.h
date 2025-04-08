#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include "worddictionary.h"
#include <exception>
#include <numeric>
#include <string>
#include <sstream>

namespace sator
{
    class exception:public std::exception
    {
    protected:
        std::string msg;
    public:
        exception(){}

        const char *what() const noexcept override
        {
            return msg.c_str();
        }
    };

    class InvalidStrException:public sator::exception
    {
    public:
        InvalidStrException(const std::string & invalidStr,const int line){
            std::stringstream ss=std::stringstream();
            ss<<"Invalid word given : "<<invalidStr<<" at line "<<line<<" (only letters accepted)";
            msg=ss.str();
        }
    };

    class InvalidPathException:public sator::exception
    {
    public:
        InvalidPathException(const std::string & path){
            std::stringstream ss=std::stringstream();
            ss<<"No input file found at given path ("<<path<<")";
            msg=ss.str();
        }
    };

    class EmptyFileException:public sator::exception
    {
    public:
        EmptyFileException(const std::string &path,const int wordLenght){
            std::stringstream ss=std::stringstream();
            ss<<"No word found in input file ("<<path<<") that matches constraints of wordlenght : "<<wordLenght;
            msg=ss.str();
        }
    };

    class GeneratedPalindromeIsInvalid:public sator::exception
    {
    public:
        GeneratedPalindromeIsInvalid(int * pallindrom,int lenght){
            std::stringstream ss=std::stringstream();
            std::string palindrom="";
            for(int i=0;i<lenght;i++)
            {
                palindrom.append(WordDictionary::Get(pallindrom[i]));
                palindrom.append(" ");
            }
            ss<<"Generated palindrome is invalid : "<<palindrom<<" something needs to be fixed..";
            msg=ss.str();
        }
    };
}


#endif // EXCEPTIONS_H
