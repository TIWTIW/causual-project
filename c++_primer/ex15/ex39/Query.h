#ifndef QUERY_H
#define QUERY_H

#include "TextQuery.h"
#include "Query_base.h"

class Query
{
    friend Query operator~( const Query& );
    friend Query operator|( const Query&, const Query& );
    friend Query operator&( const Query&, const Query& );
public:
    QueryResult eval( const TextQuery &t ) const { return q->eval( t ); }
    std::string rep() const { return q->rep(); }
    Query( const std::string &s );

private:
    Query( std::shared_ptr<Query_base> query ) : q( query ) { std::cout << "Shared_ptr Query Construct!" << std::endl; }
    std::shared_ptr<Query_base> q;
};

class WordQuery : public Query_base
{
    friend class Query;
    WordQuery( const std::string &s ) : query_word( s ) { std::cout << "WordQuery Construct!" << std::endl; }
    QueryResult eval( const TextQuery &t ) const override { return t.query( query_word ); }
    std::string rep() const override { return query_word; }
    std::string query_word;
};

class NotQuery : public Query_base
{
    friend Query operator~( const Query& );
    NotQuery( const Query &q ) : query( q ) { std::cout << "NotQuery Construct!" << std::endl; }
    std::string rep() const override { return "~" + query.rep() + ")"; }
    QueryResult eval( const TextQuery& ) const override; 
    Query query;
};

inline Query operator~( const Query &operand )
{
    return std::shared_ptr<Query_base>( new NotQuery( operand ) );
}

inline Query::Query( const std::string &s ) : q( new WordQuery( s ) ) 
{
    std::cout << "Query construct!" << std::endl; 
}


#endif
