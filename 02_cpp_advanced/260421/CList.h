#pragma once
template<typename T>
class CList
{
public:
	CList();
	~CList();

private:
	struct Node
	{
		Node* prev;
		T value;
		Node* next;
	};
	Node* head;
	Node* tail;
	int cnt;
public:
	void push_back(const T& value);
	void push_front(const T& value);

	void pop_back();
	void pop_front();

	bool empty() const;
	int size() const;

	void insert(Node* pos, const T& value);
	void erase(Node* pos);

public:
	class iterator
	{
	private:
		Node* ptr;

	public:
		iterator(Node* p = nullptr): ptr(p) {}

		T& operator*() 
		{
			return ptr->value;	
		}

		iterator& operator++()
		{
			ptr = ptr->next;
			return *this;
		}

		bool operator!=(const iterator& other)
		{
			return ptr != other.ptr;
		}
	};

	iterator begin()
	{
		return iterator(head);
	}

	iterator end()
	{
		return iterator(nullptr);
	}
};

template<typename T>
inline CList<T>::CList()
{
	cnt = 0;
	head = nullptr;
	tail = nullptr;
}

template<typename T>
inline CList<T>::~CList()
{
	Node* temp;
	while (head)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

template<typename T>
void CList<T>::push_back(const T& value)
{
	if (cnt == 0)
	{
		head = new Node{nullptr,value,nullptr};
		tail = head;
		cnt++;
	}
	else
	{
		Node* temp = new Node{ tail ,value, nullptr };
		tail->next = temp;
		tail = temp;
		cnt++;
	}
}

template<typename T>
void CList<T>::push_front(const T& value)
{
	if (cnt == 0)
	{
		head = new Node{ nullptr,value,nullptr };
		tail = head;
		cnt++;
	}
	else
	{
		Node* temp = new Node{ nullptr ,value, head };
		head->prev = temp;
		head = temp;
		cnt++;
	}
}

template<typename T>
void CList<T>::pop_back()
{
	if (cnt == 0)
	{
		return;
	}
	else if (cnt == 1)
	{
		delete tail;
		head = nullptr;
		tail = nullptr;
		cnt--;
	}
	else
	{	
		Node* temp = tail;
		tail = temp->prev;
		tail->next = nullptr;
		delete temp;
		cnt--;
	}
}

template<typename T>
void CList<T>::pop_front()
{
	if (cnt == 0)
	{
		return;
	}
	else if (cnt == 1)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
		cnt--;
	}
	else
	{
		Node* temp = head;
		head = temp->next;
		head->prev = nullptr;
		delete temp;
		cnt--;
	}
}


template<typename T>
void CList<T>::insert(Node* pos, const T& value)
{
	if (!pos) //리스트 맨 뒤에 insert로 요소 추가하는 경우
	{
		push_back(value);
	}
	else if (!pos->prev)//리스트 맨 앞에 insert로 요소 추가하는 경우
	{
		push_front(value);
	}
	else
	{
		Node* temp = new Node{ pos->prev,value,pos };
		pos->prev->next = temp;
		pos->prev = temp;
		cnt++;
	}
}

template<typename T>
void CList<T>::erase(Node* pos)
{
	if (!pos) return;
	if (!pos->next) //마지막 요소 삭제
	{
		pop_back();
	}
	else if (!pos->prev) //첫 번째 요소 삭제
	{
		pop_front();
	}
	else
	{
		pos->prev->next = pos->next;
		pos->next->prev = pos->prev;
		delete pos;
		cnt--;
	}
}

