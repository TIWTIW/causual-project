#ifndef _PERSON_H
#define _PERSON_H

#include <string>
#include <iostream>

class Person
{
friend std::istream &read( std::istream &, Person & );
friend std::ostream &print( std::ostream &, const Person & );

public:
    Person() = default;
    Person( std::string s_name, std::string s_address ) : 
            name( s_name ), address( s_address ) { }

private:
    std::string name;
    std::string address;

public:
    std::string get_name() const { return name; }
    std::string get_address() const { return address; }

};

std::istream &read( std::istream&, Person& );
std::ostream &print( std::ostream&, const Person& );

#endif
