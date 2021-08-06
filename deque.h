#pragma once
#ifndef DEQUE_H
#define DEQUE_H
#include<string>
#include<iostream>
using namespace std;
template <typename T>
class deque
{
private:
	struct node
	{
		T value;
		node* next;
		node* previous;
	};
	node* header,
		* trailer;
public:
	class iterator
	{
	public:
		bool operator==(const iterator& that);
		bool  operator!=(const iterator& that);
		iterator& operator++()
		{
			this->v = this->v->next;
			return *this;
		}
		iterator& operator--()
		{
			this->v = this->v->previous;
			return *this;
		}
		T& operator*();
		~iterator()
		{}
		friend class deque;
	private:
		node* v;
		iterator(node* u);
	};

	deque()
	{
		this->header = new node;
		this->trailer = new node;
		this->header->next = this->trailer;
		this->trailer->previous = this->header;
		this->header->previous = this->trailer->next = NULL;
	}
	bool empty()
	{
		return this->header->next == this->trailer;
	}
	void insertfront(const T& e)
	{
		node* newnode = new node{ e };
		this->header->next->previous = newnode;
		newnode->next = this->header->next;
		this->header->next = newnode;
		newnode->previous = this->header;
	}
	void insertback(const T& e)
	{
		node* newnode = new node{ e };
		this->trailer->previous->next = newnode;
		newnode->previous = this->trailer->previous;
		newnode->next = this->trailer;
		this->trailer->previous = newnode;
	}
	void erasefront() throw(const char*)
	{
		if (empty())
			throw"removeFront of empty deque";
		this->header->next = this->header->next->next;
		delete this->header->next->previous;
		this->header->next->previous = this->header;
	}
	void eraseback() throw(const char*)
	{
		if (empty())
			throw"removeBack of empty deque";
		this->trailer->previous = this->trailer->previous->previous;
		delete this->trailer->previous->next;
		this->trailer->previous->next = this->trailer;
	}
	void print()  throw(const char*)
	{
		if (empty())
			throw"removeBack of empty deque";
		node* traverse = this->header->next;
		while (traverse != trailer)
		{
			cout << traverse->value << endl;
			traverse = traverse->next;
		}
	}
	const T& front()
	{
		return this->header->next->value;
	}
	~deque()
	{
		if (!empty())
		{
			node* traverse = this->header->next;
			while (traverse != trailer)
			{
				node* temp = traverse;
				traverse = traverse->next;
				delete temp;
			}
		}
	}
	iterator begin() const
	{
		return iterator(header->next);
	}
	iterator end() const
	{
		return iterator(trailer);
	}
};
template<typename T>
bool deque<T>::iterator::operator==(const iterator& that)
{
	return this->v == that.v;
}
template<typename T>
bool deque<T>::iterator::operator!=(const iterator& that)
{
	return this->v != that.v;
}
template<typename T>
T& deque<T>::iterator::operator*()
{
	return this->v->value;
}
template<typename T>
deque<T>::iterator::iterator(node* u) :v(u)
{}
#endif // !DEQUE_H