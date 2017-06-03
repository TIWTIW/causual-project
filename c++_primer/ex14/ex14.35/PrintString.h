#ifndef _PS_H
#define _PS_H

#include <iostream>
#include <string>
#include <fstream>

class PrintString
{
public:
    PrintString( std::istream & i = std::cin ) : is( i ) {  }
    std::string operator()(  ) { std::string s;is >> s; return s; }
private:
    std::istream & is;
};

#endif
