#include <iostream>

using namespace std;

template <typename Object>
class List
{
private:
    struct Node
    {
        Object data;
        Node *prev;
        Node *next;

        Node( const Object & d = Object{  }, Node * p = nullptr,
                                             Node * n = nullptr )
        :data{ d }, prev{ p }, next{ n } {  }

        Node( const Object && d, Node * p = nullptr, Node * n = nullptr )
        :data{ move( d ) }, prev{ p }, next{ n } {  }
    };

public:
    /**********const_iterator类定义*************/
    class const_iterator
    {
    public:
        const_iterator(  ) : current{ nullptr }
        {  }
        const Object & operator* (  ) const
        { return retrive(  ); }
        const_iterator & operator++ (  )
        {
            current = current -> next;
            return *this;
        }
        const_iterator operator++( int )
        {
            const_iterator old = *this;
            ++( *this );
            return old;
        }

        bool operator== ( const const_iterator & rhs ) const
        { return current == rhs.current; }
        bool operator!= ( const const_iterator & rhs ) const
        { return current != rhs.current; }

    protected:
        Node *current;
        Object & retrive(  ) const
        { return current->data; }

        const_iterator( Node *p ) : current{ p }
            {  }
    friend class List<Object>;
    };

    /**************iterator类定义*****************/
    class iterator : public const_iterator
    {
    public:
        iterator(  )
        {  }

        Object & operator* ()
        { return const_iterator::retrive(  ); }
        const Object & operator* (  ) const
        { return const_iterator::operator*(  ); }

        iterator & operator++ (  )
        {
            this->current = this->current->next;
            return *this;
        }

        iterator operator++ ( int )
        {
            iterator old = *this;
            ++( *this );
            return old;
        };

        iterator & operator-- (  )
        {
            this->current = this->current->prev;
            return *this;
        }

        iterator operator-- ( int )
        {
            iterator old = *this;
            --( *this );
            return old;
        }

    protected:
        iterator( Node *p ) : const_iterator{ p }
        {  };

    friend class List<Object>;
    };

public:
    /*****普通构造函数********/
    List()
    { init(  ); }
    /*****拷贝构造函数*******/
    List( const List & rhs )
    {
        init(  );
        for( auto & x : rhs )
            push_back( x );
    }
    /****析构函数***********/
    ~List()
    {
        clear(  );
        delete head;
        delete tail;
    }
    /*****重载=运算符*****/
    List & operator= ( const List & rhs )
    {
        List copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    /******移动构造函数****/
    List( List && rhs ) : theSize{ rhs.theSize }, head{ rhs.head }, tail( rhs.tail )
    {
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }

    /*****移动=重载****/
    List & operator= ( List && rhs )
    {
        std::swap( theSize, rhs.theSize );
        std::swap( head, rhs.head );
        std::swap( tail, rhs.tail );

        return *this;
    }

    /***返回开始和结束迭代器************/
    iterator begin()
    { return { head->next }; }
    const_iterator begin() const
    { return { head->next }; }
    iterator end()
    { return { tail }; }
    const_iterator end() const
    { return { tail }; }

    int size(  ) const
    {return theSize;  }
    bool empty(  ) const
    { return size(  ) == 0; }

    void clear(  )
    {
        while( !empty(  ) )
            pop_front(  );
    }

    Object & front(  )
    {
        return *begin(  );
    }
    const Object & front(  ) const
    { return *begin(  ); }
    Object & back(  )
    { return *--end(); }
    const Object & back(  ) const
    { return *--end(  ); }
    void push_front( const Object & x )
    { insert( begin(  ), x ); }
    void push_back( const Object & x )
    { insert( end(  ), x ); }
    void pop_front(  )
    { erase( begin(  ) ); }
    void pop_back(  )
    { erase( --end(  ) ); }

    /*****插入  精华所在******/
    iterator insert( iterator itr, const Object & x )
    {
        Node *p = itr.current;
        theSize++;
        return { p->prev = p->prev->next = new Node{ x, p->prev, p } };
    }

    iterator erase( iterator itr )
    {
        Node *p = itr.current;
        iterator retVal{ p->next };
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        theSize--;

        return retVal;
    }

    /*****只用链交换数据********/
    void Swap( iterator itr )
    {
        Node *p = itr.current;
        --itr;
        Node *p_before = (itr).current;
        ++itr;
        Node *p_next = (++itr).current;
        ++itr;
        Node *p_next_next = itr.current;

        p->next = p_next_next;
        p->prev = p_before;

        p_before->next = p_next;

        p_next->prev = p_before;
        p_next->next = p;

        p_next_next->prev = p_next;
    }

private:
    int theSize;
    Node *head;
    Node *tail;

    void init(  )
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
 };

int main(  )
{
    List<int> list;

    list.push_back( 1 );
    list.push_back( 2 );
    list.push_back( 3 );
    list.push_back( 4 );
    list.push_back( 6 );
    list.push_back( 8 );

    auto iterator = list.begin();
    ++iterator;
    ++iterator;

    list.Swap( iterator );

    for( auto & a : list )
        cout << a << endl;
}


