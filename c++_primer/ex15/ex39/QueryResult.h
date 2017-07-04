#ifndef _QUERYRESULT_H
#define _QUERYRESULT_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <memory>

class QueryResult
{
friend std::ostream & print( std::ostream&, const QueryResult& );
public:
    using line_no = std::vector<std::string>::size_type;
    QueryResult( std::string s,
                 std::shared_ptr<std::set<line_no>> p,
                 std::shared_ptr<std::vector<std::string>> f ) :
        sought( s ), lines( p ), file( f) {  }
    std::set<line_no>::iterator begin() { return lines->begin(); }
    std::set<line_no>::iterator end()  { return lines->end(); }
    std::shared_ptr<std::vector<std::string>> get_file() { return std::make_shared<std::vector<std::string>>( *file ); }
    
private:
    std::string sought;
    std::shared_ptr<std::set<line_no>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};

#endif
