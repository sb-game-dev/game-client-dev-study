#pragma once
template<typename T>
class CQueue
{
public:
	CQueue();
	~CQueue();
private:
	void Release();
public:
	void push(const T& value);
	void pop();
	T& front();
	bool empty() const;
	int size();

private:
	T* arr;
	int cnt;
	int capacity;
};



template<typename T>
inline CQueue<T>::CQueue()
{
	cnt = 0;
	capacity = 0;
	arr = nullptr;
}

template<typename T>
inline CQueue<T>::~CQueue()
{
	Release();
}

template<typename T>
void CQueue<T>::Release()
{
	if (arr)
	{
		delete[] arr;
		arr = nullptr;
	}
}

template<typename T>
inline void CQueue<T>::push(const T& value)
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
void CQueue<T>::pop()
{
	if (cnt > 0)
	{
		cnt--;
		for (int i = 0; i < cnt - 1; i++)
		{
			arr[i] = arr[i + 1];
		}
	}
}

template<typename T>
inline T& CQueue<T>::front()
{
	if (cnt > 0) return arr[0];
}

template<typename T>
inline int CQueue<T>::size()
{
	return cnt;
}

template<typename T>
inline bool CQueue<T>::empty() const
{
	return cnt == 0;
}
