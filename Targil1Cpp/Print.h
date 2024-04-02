#ifndef __PRINT_H
#define __PRINT_H

#include <iostream>

template <class T>
class Print
{
public:
	void operator()(const T& pObj) { std::cout << *pObj << std::endl; }
};

#endif // __PRINT_H
