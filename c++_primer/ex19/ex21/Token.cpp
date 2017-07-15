#include "Token.h"

using namespace std;

Token &Token::operator=( int i )
{
    if( tok == STR )
        sval.~string();

    ival = i;
    tok = INT;
    return *this;
}

Token &Token::operator=( char c )
{
    if( tok == STR )
        sval.~string();

    cval = c;
    tok = CHAR;
    return *this;
}

Token &Token::operator=( double d )
{
    if( tok == STR )
        sval.~string();

    dval = d;
    tok = DBL;
    return *this;
}

Token &Token::operator=( const string &s )
{
    if( tok == STR )
        sval = s;
    else
        new( &sval ) string( s );

    tok = STR;
    return *this;
}

void Token::copyUnion( const Token &t )
{
    switch( t.tok )
    {
        case Token::INT: ival = t.ival; break;
        case Token::CHAR: cval = t.cval; break;
        case Token::DBL: dval = t.dval; break;
        case Token::STR: new( &sval ) string( t.sval ); break;
    }
}

Token &Token::operator=( const Token &t )
{
    if( tok == STR && t.tok != STR )
        sval.~string();
    if( tok == STR && t.tok == STR )
        sval = t.sval;
    else
        copyUnion( t );

    tok = t.tok;
    return *this;
}

Token::~Token()
{
    if( tok == STR )
        sval.~string();
}
