#include "Folders.h"

using namespace std;

void Folder::addMsg( Message *m )
{
    messages.insert( m );
}

void Folder::remMsg( Message *m )
{
    messages.erase( m );
}
