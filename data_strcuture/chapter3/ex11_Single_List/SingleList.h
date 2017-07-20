#include <algorithm>
#include <iostream>

template <typename Object>
class SingleList
{
public:
    SingleList(){ init(); }
    ~SingleList()
    {
        Node *p = head;
        while( p != nullptr )
        {
            delete p;
            p = p->next;
        }
    }
    
    int size() { return theSize; }
    void print() 
    { 
        Node *p = head;
        while( p->next != nullptr ) 
        {
            std::cout << p->next->val << " ";
            p = p->next;
        }
        std::cout << std::endl;
    }

    bool contain( const Object &x )
    {
        Node *p = head;
        while( p->next != nullptr )
        {
            if( p->next->val == x )
                return true;
            p = p->next;
        }
        return false;
    }

    void push_or_pop( const Object &x )
    {
        if( contain( x ) )
        {
            Node *p = head;
            while( p->next != nullptr )
            {
                if( p->next->val == x )
                    break;
                p = p->next;
            }
            
            Node *del = p->next;
            p->next = p->next->next;
            
            delete del;
            theSize--;
            return ;
        }

        Node *p = new Node{ x };
        Node *h = head;
        while( h->next != nullptr )
            h = h->next;

        h->next = p;
        theSize++;
        if( x < h->val )
            sort();
    }

    //ex12 sort mantain list
    void sort()
    {
        Node *p = head->next, *p_before = head;
        while( p->next != nullptr )
        {
            p_before = p_before->next;
            p = p->next;
        }
        Node *p2 = head->next, *p2_before = head;
        while( p->val > p2->val && p2 != nullptr )
        {
            p2 = p2->next;
            p2_before = p2_before->next;
        }

        if( p == p2 )
            return;

        p_before->next = p->next;
        p2_before->next = p;
        p->next = p2;

    }
private:
    struct Node
    {   
        Object val;
        Node *next;

        Node( const Object &x = Object{}, Node *p = nullptr ) : val( x ), next( p ) {}
    };
    int theSize;
    Node *head;
    void init()
    {
        theSize = 0;
        head = new Node;
    }
};
