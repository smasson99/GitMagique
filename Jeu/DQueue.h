#pragma once
// <sberube>
#ifndef _D_QUEUE_H_

// DECLARATIONS
template <class T>
class DQueue
{
	//DQueue(const DQueue&) = delete;

	//Representation
	T *data;
	size_t sz;
	size_t cap;
	size_t head;

public:

	//deque(const deque&); // A FAIRE
	//void clear();// A FAIRE
	//void resize(size_t); // A FAIRE

	//Constructeur et affectateur
	DQueue();
	~DQueue();

	//Opérateurs
	DQueue& operator=(const DQueue<T>& other);
	T& operator[](const size_t index);

	//Accesseur
	T& front();
	T& back();
	const T& Front() const;
	const T& Back() const;

	//Capacite
	bool Empty() const;
	size_t Size() const;
	void Reserve();

	//Fonction generatrice
	void PushFront(const T& value);
	void PushBack(const T& value);
	void PopFront();
	void PopBack();

	// échange
	void Swap(DQueue& other) noexcept;
};

//DEFINITIONS
template<class T>
inline DQueue<T>::DQueue()
{
	cap = data->GetSize()
	sz = 0;
	head = 0;
}

template<class T>
inline DQueue<T>::~DQueue()
{
	delete data;
	data = nullptr;
}

template<class T>
inline DQueue<T> & DQueue<T>::operator=(const DQueue<T> &other)
{
	while (sz < other.sz)
	{
		Reserve();
	}
	for (size_t i = 0; i < other.sz; i++)
	{
		data[i] = other.data[i];
	}
	head = 0;
	sz = other.sz;
}

template<class T>
T& DQueue<T>::operator[](const size_t index)
{
	return data[(head + index) % cap];
}

template<class T>
inline T & DQueue<T>::front()
{
	// Il n'y a pas de front si la file est vide. Attention à l'utilisation.
	return data[head];
}

template<class T>
inline T & DQueue<T>::back()
{
	// Il n'y a pas de back si la file est vide. Attention à l'utilisation.
	return data[(head + sz - 1) % cap];
}

template<class T>
inline const T & DQueue<T>::Front() const
{
	// Il n'y a pas de front si la file est vide. Attention à l'utilisation.
	return data[head];
}

template<class T>
inline const T & DQueue<T>::Back() const
{
	// Il n'y a pas de back si la file est vide. Attention à l'utilisation.
	return data[(head + sz - 1) % cap];
}

template<class T>
inline bool DQueue<T>::Empty() const
{
	// Si le size est de 0, c'est qu'il est vide.
	return sz == 0;
}

template<class T>
inline size_t DQueue<T>::Size() const
{
	// On retourne la taille de la file.
	return sz;
}

template<class T>
inline void DQueue<T>::Reserve()
{
	T *tab[cap+1 * 2];
	tab = data;
	data& = tab&;
	tab = nullptr;
}

template<class T>
inline void DQueue<T>::PushFront(const T & value)
{
	if (sz == cap)
	{
		Reserve();
	}

	if (head == 0)
	{
		head = cap - 1;
		data[head] = value;
	}
	else
	{
		head--;
		data[head] = value;
	}
	sz++;
}

template<class T>
inline void DQueue<T>::PushBack(const T & value)
{
	if (sz == cap)
	{
		Reserve();
	}

	data[(head + sz) % cap] = value;
	sz++;
}

template<class T>
inline void DQueue<T>::PopFront()
{
	head = (head + 1) % cap;
	sz--;
}

template<class T>
inline void DQueue<T>::PopBack()
{

	sz--;
}

template<class T>
inline void DQueue<T>::Swap(DQueue & other) noexcept
{
	T tempData* = data;
	size_t tempSz = sz;
	size_t tempCap = cap;
	int tempHead = head;

	data = other.data;
	sz = other.sz;
	cap = other.cap;
	head = other.head;

	other.data = tempData;
	other.sz = tempSz;
	other.cap = tempCap;
	other.head = tempHead;
}

#endif // !_D_QUEUE_H_

// </sberube>