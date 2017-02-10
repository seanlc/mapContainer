#include <iostream>
#include <iterator>
#include <algorithm>

using namespace std;

template
< typename Type >
class SetList
{
private:
	struct ListNode
	{
		Type info;
		ListNode * next;
		ListNode( Type data, ListNode * newNext )
		:info ( data), next ( newNext )
		{
		}
		static ListNode * copy( ListNode * L )
		{
			if ( L == nullptr )
				return nullptr;
			ListNode * first = new ListNode( L->info, nullptr );
			ListNode * temp = first;
			ListNode * trav;
			for ( trav = L->next; trav != nullptr; temp = temp->next )
			{
				temp->next = new ListNode( trav->info, nullptr );
				trav = trav->next;
			}
			return first;
		} 
		static void deleteList( ListNode * L )
		{
			ListNode * cur = L;
			ListNode * next;
			while( cur != nullptr )
			{
				next = cur->next;
				delete cur;
				cur = next;
			}
			L = nullptr;
		}
		static int length( ListNode * L )
		{
			int len = 0;
			for ( ListNode * p = L; p != nullptr; p = p->next )
				len++;
			return len;
		} 
	};
	ListNode * buf;
public:
	struct iterator
	{
		typedef std::forward_iterator_tag iterator_category;
		typedef iterator self_type;
		typedef Type value_type;
		typedef Type& reference;
		typedef Type* pointer;
		typedef ptrdiff_t difference_type;
	private:
		ListNode * ibuf;
	public:
		iterator( ListNode * p )
		: ibuf ( p )
		{}
		self_type operator++()
		{
			ibuf = ibuf -> next;
			return *this;
		}
		self_type operator++(int postfix)
		{
			self_type oldVal = *this;
			ibuf = ibuf->next;
			return oldVal;
		}
		reference operator*()
		{
			return ibuf->info;
		}
		pointer operator->()
		{
			return &(ibuf->info);
		}
		bool operator==( const self_type & rhs) const
		{
			return ibuf == rhs.ibuf;
		}
		bool operator!=( const self_type & rhs) const
		{
			return ibuf != rhs.ibuf;
		}
	};
	struct const_iterator
	{
		typedef std::forward_iterator_tag iterator_category;
		typedef const_iterator self_type;
		typedef Type value_type;
		typedef Type& reference;
		typedef Type* pointer;
		typedef ptrdiff_t difference_type;
	private:
		ListNode * buf;
	public:
		const_iterator( ListNode * p )
		: buf ( p )
		{
		}
		self_type operator++()
		{
			buf = buf -> next;
			return *this;
		}
		self_type operator++( int postfix )
		{
			self_type oldVal = *this;
			buf = buf -> next;
			return oldVal;
		}
		const reference operator*()
		{
			return buf->info;
		}
		const pointer operator->()
		{
			return &(buf->info);
		}
		bool operator==( const self_type & rhs ) const
		{
			return buf == rhs.buf;
		}
		bool operator!=( const self_type & rhs ) const
		{
			return buf != rhs.buf;
		}
	};
	
	SetList()
	: buf ( nullptr )
	{
		
	}
	SetList( const SetList &s)
	{
		buf = ListNode::copy( s.buf );
	}
	~SetList()
	{
		ListNode::deleteList( buf );
	}
	int size()
	{
		return ListNode::length( buf );
	}
	void insert( Type s )
	{
		ListNode * newNode = new ListNode( s, nullptr);
		ListNode * p = buf;
		if ( p != nullptr )
		{
			while ( p->next != nullptr)
				p = p->next;
			p->next = newNode;
		}
		else
		{
			buf = newNode;
		} 
	}
	iterator begin()
	{
		return iterator(buf);
	}
	iterator end()
	{
		return iterator( nullptr );
	}
	const_iterator begin() const
	{
		return const_iterator( buf );
	}
	const_iterator end() const
	{
		return const_iterator( nullptr );
	}
	iterator find( Type f )
	{
		ListNode * p;
		for ( p = buf; p != nullptr; p = p->next )
		{
			if ( p -> info == f)
				return iterator(p);	
		}
		return iterator(nullptr);
	} 
};
