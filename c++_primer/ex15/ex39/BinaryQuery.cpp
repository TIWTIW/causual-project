#include "BinaryQuery.h"
#include <algorithm>

using namespace std;

QueryResult OrQuery::eval( const TextQuery &text ) const
{
    auto right = rhs.eval( text ), left = lhs.eval( text );

    auto ret_lines = make_shared<set<line_no>>( left.begin(), left.end() );

    ret_lines->insert( right.begin(), right.end() );

    return QueryResult( rep(), ret_lines, left.get_file() );
}

QueryResult AndQuery::eval( const TextQuery &text ) const
{
    auto right = rhs.eval( text ), left = lhs.eval( text );

    auto ret_lines = make_shared<set<line_no>>( left.begin(), left.end() );

    set_intersection( left.begin(), left.end(), right.begin(), right.end(), inserter( *ret_lines, ret_lines->begin() ) );

    return QueryResult( rep(), ret_lines, left.get_file() );
}
