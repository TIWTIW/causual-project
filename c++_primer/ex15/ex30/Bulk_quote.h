#ifndef _BQH
#define _BQH

#include "Disc_quote.h"

class Bulk_quote : public Disc_quote
{
public:
    Bulk_quote() = default;
    Bulk_quote( const std::string&, double, std::size_t, double );
    double net_price( std::size_t ) const override;
    void debug() const override;

    Bulk_quote *clone() const & override { return new Bulk_quote( *this ); }
    Bulk_quote *clone() && override { return new Bulk_quote( std::move( *this ) ); }
};

#endif
