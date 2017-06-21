/*****Message*****
 * C++ Primer:chapter13.4
 * an interesting example
 * Name:zft
 * Time:2017.6.21
 * *****************/

#ifndef _MESSAGE_H
#define _MESSAGE_H

#include <iostream>
#include <set>
#include <string>
#include "Folders.h"

class Message
{
    friend class Folder;
public:
    explicit Message( const std::string &str = "" ) : contents( str ) { }
    Message( const Message& );
    Message& operator=( const Message& );
    ~Message();
    void save( Folder& );
    void remove( Folder& );
    void add_folder( Folder* );
    void remove_folder( Folder* );
private:
    std::string contents;
    std::set<Folder*> folders;
    void add_to_Folders( const Message& );
    void remove_from_Folders();
};


#endif
