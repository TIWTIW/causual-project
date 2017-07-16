#ifndef _BUBBLE_H
#define _BUBBLE_H

#include <vector>
#include <climits>

//swap function
void swap( int &, int & );


//sort function
int bubble_sort( std::vector<int> & );
int select_sort( std::vector<int> & );
int insert_sort( std::vector<int> & );
int merge_sort( std::vector<int> &, std::vector<int>::size_type, std::vector<int>::size_type );
int count_sort( std::vector<int> & );
int quick_sort( std::vector<int> &, int, int );

#endif
