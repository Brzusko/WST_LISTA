#include "List.h"
#include <iostream>

template<typename T>
List<T>::~List()
{
	Flush();
}

template<typename T>
T List<T>::Remove(T value)
{
	auto helper = SearchNode(value);
	if (helper != nullptr) {
		if (helper->prevNode == nullptr) {
			auto newNode = helper->currentNode->next;
			auto valToRet = *helper->currentNode->value;
			delete head;
			head = new Node();
			head = newNode;
			size--;
			return valToRet;
		}
		else {
			if (helper->currentNode->next == nullptr) {
				back = helper->prevNode;
				auto valToRet = *helper->currentNode->value;
				delete helper->currentNode->value;
				delete helper->currentNode;
				size--;
				return valToRet;
			}
			else {

				auto newNode = helper->currentNode->next;
				helper->prevNode->next = newNode;
				auto valToRet = *helper->currentNode->value;
				delete helper->currentNode->value;
				delete helper->currentNode;
				size--;
				return valToRet;
			}
		}
	}
	return T();
}

template<typename T>
void List<T>::Add(T value)
{
	switch(size){
	case 0:
	{
		head = new Node();
		head->value = new T(value);
		head->next = nullptr;
		size++;
		break;
	}
	case 1:
	{
		auto newNode = new Node();
		newNode->value = new T(value);
		newNode->next = nullptr;

		head->next = newNode;
		back = newNode;
		size++;
		break;
	}
	default:
	{
		auto newNode = new Node();
		newNode->value = new T(value);
		newNode->next = nullptr;

		auto helper = back;
		back = newNode;
		helper->next = back;
		size++;
		break;
	}
	}
}

template<typename T>
void List<T>::Flush() {
	if (size == 0)
		return;

	auto helper = head;
	for (int i = 0; i < size; i++) {
		if (helper->next == nullptr) {
			delete helper->next;
			delete helper->value;
			delete helper;
			size--;
			break;
		}

		auto nextNode = helper->next;
		delete helper->value;
		
		helper = nextNode;
		size--;
	}
	delete head;
	delete back;

	head = nullptr;
	back = nullptr;
	size--;
}

template<typename T>
int List<T>::Size()
{
	return size;
}

template<typename T>
T* List<T>::Search(T value)
{
	if (size == 0)
		return nullptr;
	
	auto helper = head;
	for (int i = 0; i < size; i++) {
		if (*helper->value == value) {
			return helper->value;
		}
		else {
			if (helper->next == nullptr) {
				return nullptr;
			}

			helper = helper->next;
		}
	}
}

template<typename T>
void List<T>::Print()
{
	if (size == 0)
		std::cout << "Lista jest pusta :/" << std::endl;
	auto helper = head;
	int pos = 0;
	for (int i = 0; i < size; i++) {
		if (helper == nullptr)
			break;
		std::cout << "Pozycja elementu w liscie: " << i << " , wartosc elementu: " << *helper->value << std::endl;
		helper = helper->next;
	}
}

template<typename T>
void List<T>::AddAt(T valueToAdd, T valueWhereToAdd)
{

	auto helper = SearchNode(valueWhereToAdd);
	if (!helper || !helper->currentNode->next) {
		Add(valueToAdd);
		return;
	}

	auto newNode = new Node();
	newNode->value = new T(valueToAdd);
	newNode->next = helper->currentNode;

	if (!helper->prevNode)
		head = newNode;
	else {
		helper->prevNode->next = newNode;
	}

	size++;

}

template<typename T>
auto List<T>::SearchNode(T value) -> NodeToRemove*
{
	if (size == 0)
		return nullptr;
	
	if (*head->value == value) {
		auto nodeToRemove = new NodeToRemove();
		nodeToRemove->currentNode = head;
		nodeToRemove->prevNode = nullptr;
		return nodeToRemove;
	}

	auto helper = new NodeToRemove();
	helper->currentNode = head->next;
	helper->prevNode = head;
	for (int i = 0; i < size - 1; i++) {
		if (*helper->currentNode->value == value)
			return helper;
		else {
			auto buffer = helper->currentNode->next;
			helper->prevNode = helper->currentNode;
			helper->currentNode = buffer;
		}
	}
	delete helper;
	return nullptr;
}

template class List<int>;
template class List<float>;
template class List<std::string>;
template class List<double>;
template class List<bool>;
template class List<char>;

