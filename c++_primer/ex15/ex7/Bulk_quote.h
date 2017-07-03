#ifndef _BQH
#define _BQH

#include "Disc_quote.h"

class Bulk_quote : public Disc_quote
{
public:
    Bulk_quote() = default;
    Bulk_quote( const std::string&, double, std::size_t, double );
    double net_price( std::size_t ) const override;

};

#endif
