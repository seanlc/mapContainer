#include <iostream>
#include <iterator>
#include <algorithm>
#include <utility>
using namespace std;

template
< typename Key, typename Value >
class MapArray
{
private:
	struct ListNode
	{
		pair<Key, Value > info;
		ListNode * next;
		ListNode * last;
		ListNode( pair<Key,Value> p,  ListNode * newNext, ListNode * newLast )
		:info ( p ), next ( newNext ), last (newLast)
		{
		}
		static ListNode * copy( ListNode * L )
		{
			if ( L == nullptr )
				return nullptr;
			ListNode * first = new ListNode( L->info, nullptr, nullptr );
			ListNode * temp = first;
			ListNode * trav;
			for ( trav = L->next; trav != nullptr; temp = temp->next )
			{
				temp->next = new ListNode( trav->info, nullptr, nullptr );
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
		static ListNode * lastN ( ListNode * L )
		{
			if ( L == nullptr )
				return nullptr;
			ListNode * p;
			for ( p = L; p->next != nullptr; p = p->next)
			{}
			return p;
		} 
	};
	ListNode * buf;
public:
	struct iterator
	{
		typedef std::random_access_iterator_tag iterator_category;
		typedef iterator self_type;
		typedef pair<Key, Value> value_type;
		typedef pair<Key, Value>& reference;
		typedef pair<Key, Value>* pointer;
		typedef ptrdiff_t difference_type;
	private:
		ListNode * ibuf;
	public:
		iterator( ListNode * p)
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
		self_type operator--()
		{ 
			return *this;
		}
		self_type operator--( int postfix )
		{
			self_type oldVal = *this;
/*			self_type p = begin();
			while( p->next != ibuf)
				p = p->next;
			ibuf = p;*/
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
		typedef std::random_access_iterator_tag iterator_category;
		typedef const_iterator self_type;
		typedef pair<Key, Value> value_type;
		typedef pair<Key, Value>& reference;
		typedef pair<Key, Value>* pointer;
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
		self_type operator--()
		{
	/*		self_type p = begin();
			while ( p->next != buf)
				p = p->next;
			buf = p;
	*/		return *this;
		}
		self_type operator--( int postfix )
		{
			self_type oldVal = *this;
	/*		self_type p = begin();
			while ( p->next != buf)
				p = p->next;
			buf = p;
	*/		return oldVal;	
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
	
	MapArray()
	: buf ( nullptr )
	{
		
	}
	MapArray( const MapArray &s)
	{
		buf = ListNode::copy( s.buf );
	}
	~MapArray()
	{
		ListNode::deleteList( buf );
	}
	int size()
	{
		return ListNode::length( buf );
	}
	void insert(pair<Key, Value> s)
	{
		ListNode * newNode = new ListNode( s, nullptr, nullptr);
		ListNode * prev = nullptr;
		ListNode * loc = buf;
		while ( loc &&  s.first >= loc->info.first ) 
		{
			prev = loc;
			loc = loc->next;
		}
		if ( prev == nullptr )
		{
			newNode->next = buf;
			if ( buf != nullptr )
				buf->last = newNode;
			buf = newNode;
		}
		else
		{
			newNode->next = loc;
			if ( loc != nullptr )
				loc->last = newNode;
			newNode->last = prev;
			prev->next = newNode;
		}
		
	} 	
	pair<Key, Value>& operator[](Key k)
	{
		ListNode * p;
		for (ListNode * p = buf; p != nullptr; p=p->next )
		{
			if ( p->info.first == k )
				break;
		}
		return p->info;
			
	}
	pair<Key, Value>& operator[](Key k) const
	{
		ListNode * p;
		for ( ListNode * p = buf; p != nullptr; p = p->next )
		{
			if ( p->info.first = k)
				break;
		}
		return p->info;
	}
	iterator begin()
	{
		return iterator(buf);
	}
	iterator end()
	{
		return iterator( nullptr );
	}
	iterator prevNode( iterator p )
	{
		ListNode * d = buf;
		while( d->next != p.ibuf )
			d = d->next;
		return iterator(d); 
	}
	const_iterator begin() const
	{
		return const_iterator( buf );
	}
	const_iterator end() const
	{
		return const_iterator( nullptr );
	}
	iterator find( Key f )
	{
		ListNode * p;
		for ( p = buf; p != nullptr; p = p->next )
		{
			if ( p->info.first == f)
				return iterator(p);	
		}
		return iterator(nullptr);
	}
	void increment(Key K )
	{
		ListNode * p = buf;
		while( p->info.first != K)
			p=p->next;
		p->info.second = p->info.second + 1; 
		
	} 
};
