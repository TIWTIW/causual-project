#ifndef FOLDERS_H
#define FOLDERS_H

#include <iostream>
#include <set>

class Message;
class Folder
{
public:
    
    void addMsg( Message* );
    void remMsg( Message* );
private:
    std::set<Message*> messages;

};

#endif
