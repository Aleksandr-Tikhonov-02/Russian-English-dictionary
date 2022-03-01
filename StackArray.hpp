#ifndef _STACK_ARRAY_
#define _STACK_ARRAY_
#include "Stack.hpp"
#include <exception>
#include <string>

class StackOverflow : public std::exception
{
public:
	StackOverflow(const char* reason = "StackOverflow") : std::exception(reason)
	{}
};

class StackUnderflow : public std::exception
{
public:
	StackUnderflow(const char* reason = "StackUnderflow") : std::exception(reason)
	{}
};

class WrongStackSize : public std::exception
{
public:
	WrongStackSize(const char* reason = "WrongStackSize") : std::exception(reason)
	{}
};
template <class T>
class StackArray : public Stack<T>
{
public:
	explicit StackArray(size_t size);
	StackArray(const StackArray<T>& src) = delete;
	StackArray(StackArray<T>&& src) noexcept;
	StackArray& operator=(const StackArray<T>& src) = delete;
	StackArray& operator=(StackArray<T>&& src) noexcept;
	~StackArray() override;

	void push(const T& e) override;
	T pop() override;
	T& top() const override;

	bool isEmpty() override;
private:
	T* array_;
	size_t top_;
	size_t size_;
	void swap(StackArray<T>& src);
};
template<class T>
StackArray<T>::StackArray(size_t size) :
	size_(size),
	top_(0)
{
	try
	{
		array_ = new T[size_ + 1];
	}
	catch (...)
	{
		throw WrongStackSize();
	}
}
template<class T>
StackArray<T>::StackArray(StackArray<T>&& src) noexcept
{
	swap(src);
}
template<class T>
StackArray<T>& StackArray<T>::operator=(StackArray<T>&& src) noexcept
{
	if (this != &src)
	{
		swap(src);
	}
	return *this;

}
template<class T>
StackArray<T>::~StackArray()
{
	delete[] array_;
}
template<class T>
void StackArray<T>::push(const T& e)
{
	if (top_ == size_)
	{
		throw StackOverflow();
	}
	array_[++top_] = e;
}
template<class T>
T StackArray<T>::pop()
{
	if (top_ == 0) {
		throw StackUnderflow();
	}
	return array_[top_--];
}
template<class T>
T& StackArray<T>::top() const
{
	return array_[top_];
}
template<class T>
bool StackArray<T>::isEmpty()
{
	if (top_ == 0)
	{
		return true;
	}
	return false;
}
template<class T>
void StackArray<T>::swap(StackArray<T>& src)
{
	std::swap(array_, src.array_);
	std::swap(top_, src.top_);
	std::swap(size_, src.size_);
}

#endif
