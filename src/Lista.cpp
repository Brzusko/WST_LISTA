

#include <iostream>
#include "List.h"

int main()
{
	List<int> list;
	list.Add(1);
	list.Add(2);
	list.Add(3);
	list.Add(7);
	list.Add(5);
	list.AddAt(30, 5);
	std::cout << "List elements: " << list.Size() << std::endl;
	auto searchVal = list.Search(2);
	std::cout << "Search val: " << *searchVal << std::endl;
	auto removedValue = list.Remove(1);
	list.Remove(3);
	list.Remove(5);
	std::cout << "List elements: " << list.Size() << std::endl;
	list.Print();
	list.Flush();
}

