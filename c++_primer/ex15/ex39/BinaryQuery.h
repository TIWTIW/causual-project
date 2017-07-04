#ifndef BQUERY_H
#define BQUERY_H

#include "Query.h"

class BinaryQuery : public Query_base
{
protected:
    BinaryQuery( const Query &l, const Query &r, std::string s ) : lhs( l ), rhs( r ), opSym( s ) { std::cout << "BinaryQuery Construct!" << std::endl; }

    std::string rep() const override { return "(" + lhs.rep() +  "" + opSym + " " + rhs.rep() + ")" ;}

    Query lhs, rhs;
    std::string opSym;

};

class AndQuery : public BinaryQuery
{
    friend Query operator&( const Query&, const Query& );
    AndQuery( const Query &left, const Query &right ) : BinaryQuery( left, right, "&" ) { std::cout << "AndQuery Construct!" << std::endl; }
    QueryResult eval( const TextQuery& ) const override; 
}; 

inline Query operator&( const Query &lhs, const Query &rhs )
{
    return std::shared_ptr<Query_base>( new AndQuery( lhs, rhs ) );
}

class OrQuery : public BinaryQuery
{
    friend Query operator|( const Query&, const Query& );
    OrQuery( const Query &left, const Query &right ) : BinaryQuery( left, right, "|" ) { std::cout << "OrQuery Construct!" << std::endl; }
    QueryResult eval( const TextQuery& ) const override; 
}; 

inline Query operator|( const Query &lhs, const Query &rhs )
{
    return std::shared_ptr<Query_base>( new OrQuery( lhs, rhs ) );
}

#endif
