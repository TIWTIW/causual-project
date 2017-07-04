#ifndef _DQ_H
#define _DQ_H

#include "Quote.h"

class Disc_quote : public Quote
{
public:
    Disc_quote() = default;
    Disc_quote( const std::string & book, double price,
                std::size_t qty, double disc ) :
                Quote( book, price ),
                quantity( qty ), discount( disc ) {  }
    double net_price( std::size_t ) const override = 0;
    void debug() const override {}
protected:
    std::size_t quantity = 0;
    double discount = 0.0;
};
#endif
