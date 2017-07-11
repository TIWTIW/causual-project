#ifndef _TEXTQUERY_H
#define _TEXTQUERY_H

#include <iostream>
#include "QueryResult.h"
#include <string>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <memory>
#include <sstream>
#include "DebugDelete.h"

class QueryResult;
class TextQuery
{
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery( std::ifstream &, DebugDelete );
    QueryResult query( const std::string & ) const;
private:
    std::shared_ptr<std::vector<std::string>> file;
    std::map<std::string,
        std::shared_ptr<std::set<line_no>>> wm;
};

#endif
