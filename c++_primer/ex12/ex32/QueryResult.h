#ifndef _QUERYRESULT_H
#define _QUERYRESULT_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <memory>
#include "StrBlob.h"

class QueryResult
{
friend std::ostream & print( std::ostream&, const QueryResult& );
public:
    using line_no = std::vector<std::string>::size_type;
    QueryResult( std::string s, std::shared_ptr<std::set<line_no>> p, StrBlob f ) :
        sought( s ), lines( p ), file( f ) {  }
private:
    std::string sought;
    std::shared_ptr<std::set<line_no>> lines;
    StrBlob file;
};

#endif
