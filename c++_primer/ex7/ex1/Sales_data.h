#ifndef _SALES_DATA
#define _SALES_DATA

#include <string>

struct Sales_data
{
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

#endif
