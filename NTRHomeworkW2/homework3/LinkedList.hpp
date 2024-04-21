#pragma once

#include <memory>

template<typename T>
struct Node
{
	T m_value;
	Node<T>* m_next;

	explicit Node(T val, Node<T>* next = nullptr)
		: m_value(val)
		, m_next(next)
	{}
	~Node() = default;
};

template <typename T>
class List
{
public:
	List();
	~List() noexcept;

	List(const List& list);
	List& operator=(const List& list);
	List(List&& list) noexcept;
	List& operator=(List&& list) noexcept;

	void add(const T& val);
	void addFront(const T& val);
	void pop();
	void popFront();
	void clear();

	inline bool empty() const { return m_size == 0; }
	inline size_t size() const { return m_size; }

private:
	Node<T>* m_start = nullptr;
	Node<T>* m_end = nullptr;

	size_t m_size = 0;
};

template<typename T>
List<T>::List()
	: m_start(nullptr)
	, m_end(nullptr)
	, m_size(0)
{}

template<typename T>
List<T>::~List() noexcept
{
	clear();
}

template<typename T>
List<T>::List(const List<T>& list)
	: m_size(list.m_size)
{
	if (!list.empty())
	{
		auto foreignNode = list.m_start;
		auto curr = new Node(foreignNode->m_value);
		for (size_t iNode = 0; iNode < m_size; iNode++)
		{
			foreignNode = foreignNode->m_next;

			if (m_start == nullptr)
			{
				m_start = curr;
			}
			curr->m_next = new Node(foreignNode->m_value);
			curr = curr->m_next;
		}

		m_end = curr;
	}
}

template<typename T>
List<T>& List<T>::operator=(const List<T>& list)
{
	if (this == &list)
	{
		return *this;
	}
	else if (list.empty())
	{
		clear();
	}
	else if (m_start == nullptr)
	{
		auto foreignNode = list.m_start;
		auto curr = new Node(foreignNode->m_value);
		m_start = curr;
		for (size_t iNode = 0; iNode < list.m_size - 1; iNode++)
		{
			foreignNode = foreignNode->m_next;

			if (m_start == nullptr)
			{
				m_start = curr;
			}
			curr->m_next = new Node(foreignNode->m_value);
			curr = curr->m_next;
		}

		m_end = curr;
	}
	else
	{
		auto curr = m_start;
		auto foreign = list.m_start;

		while (curr->m_next != nullptr && foreign->m_next != nullptr)
		{
			curr->m_value = foreign->m_value;
			curr = curr->m_next;
			foreign = foreign->m_next;
		}
		curr->m_value = foreign->m_value;
		foreign = foreign->m_next;

		if (m_size < list.m_size)
		{
			while (m_size < list.m_size)
			{
				add(foreign->m_value);
				foreign = foreign->m_next;
			}
		}
		else if (m_size > list.m_size)
		{
			while (m_size > list.m_size)
			{
				pop();
			}
		}
	}

	return *this;
}

template<typename T>
List<T>::List(List<T>&& list) noexcept
	: m_start(list.m_start)
	, m_end(list.m_end)
	, m_size(list.m_size)
{
	list.m_start = nullptr;
	list.m_end = nullptr;
	list.m_size = 0;
}

template<typename T>
List<T>& List<T>::operator=(List<T>&& list) noexcept
{
	clear();

	m_start = list.m_start;
	m_end = list.m_end;
	m_size = list.m_size;

	list.m_start = nullptr;
	list.m_end = nullptr;
	list.m_size = 0;

	return *this;
}


template<typename T>
void List<T>::add(const T& val)
{
	if (m_start == nullptr)
	{
		m_start = new Node(val);
		m_end = m_start;
		m_size++;
		return;
	}

	m_end->m_next = new Node(val);
	m_end = m_end->m_next;
	m_size++;
}

template<typename T>
void List<T>::addFront(const T& val)
{
	if (m_start == nullptr)
	{
		m_start = new Node(val);
		m_end = m_start;
		m_size++;
		return;
	}

	auto temp = new Node(val, m_start);
	m_start = temp;
	m_size++;
}

template<typename T>
void List<T>::clear()
{
	if (m_start == nullptr)
	{
		return;
	}

	while (m_start != m_end)
	{
		auto temp = m_start->m_next;
		delete m_start;
		m_start = temp;
	}
	delete m_start;

	m_start = nullptr;
	m_end = nullptr;
	m_size = 0;
}

template <typename T>
void List<T>::popFront()
{
	if (m_start == nullptr)
	{
		return;
	}

	if (m_size == 1)
	{
		delete m_start;
		m_start = nullptr;
		m_end = nullptr;
		m_size--;
		return;
	}

	auto temp = m_start->m_next;
	delete m_start;
	m_start = temp;
	m_size--;
}

template <typename T>
void List<T>::pop()
{
	if (m_start == m_end)
	{
		delete m_start;
		m_start = nullptr;
		m_end = nullptr;
		m_size = 0;
		return;
	}
	
	auto curr = m_start;
	for (size_t iNode = 0; iNode < m_size - 2; iNode++)
	{
		curr = curr->m_next;
	}
	delete curr->m_next;

	m_end = curr;
	m_end->m_next = nullptr;
	m_size--;
}
