#pragma once
template<typename T>
class CStack
{
public:
	CStack();
	~CStack();
private:
	void Release();
public:
	void push(const T& value);
	void pop();
	T& top();
	bool empty() const;
	int size();

private:
	T* arr;
	int cnt;
	int capacity;
};



template<typename T>
inline CStack<T>::CStack()
{
	cnt = 0;
	capacity = 0;
	arr = nullptr;
}

template<typename T>
inline CStack<T>::~CStack()
{
	Release();
}

template<typename T>
void CStack<T>::Release()
{
	if (arr)
	{
		delete[] arr;
		arr = nullptr;
	}
}

template<typename T>
inline void CStack<T>::push(const T& value)
{
	if (!arr)
	{
		++cnt;
		capacity = 1;
		arr = new T[1];
		arr[cnt - 1] = value;
	}
	else
	{
		if (capacity <= cnt)
		{
			capacity *= 2;
			T* temp = new T[capacity];
			for (int i = 0; i < cnt; i++) temp[i] = arr[i];
			delete[] arr;
			arr = temp;
		}
		arr[cnt] = value;
		cnt++;
	}
}

template<typename T>
void CStack<T>::pop()
{
	if (cnt > 0) cnt--;
}

template<typename T>
inline T& CStack<T>::top()
{
	if (cnt > 0) return arr[cnt - 1];
}

template<typename T>
inline int CStack<T>::size()
{
	return cnt;
}

template<typename T>
inline bool CStack<T>::empty() const
{
	return cnt == 0;
}