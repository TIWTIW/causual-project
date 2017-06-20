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

class QueryResult;
class TextQuery
{
public:
    using line_no = std::vector<std::string>::size_type;
    TextQuery( std::ifstream & );
    QueryResult query( const std::string & ) const;
private:
    StrBlob file;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

#endif
