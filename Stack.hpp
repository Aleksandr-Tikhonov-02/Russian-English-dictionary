#ifndef _STACK_
#define _STACK_

template <class T>
class Stack
{
public:
	virtual ~Stack() = default;

	virtual void push(const T& e) = 0;
	virtual T pop() = 0;
	virtual T& top() const = 0;

	virtual bool isEmpty() = 0;
};

#endif
