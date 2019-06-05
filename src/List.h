#pragma once


template<typename T>
class List
{
public:
	List<T>() : head{ nullptr }, back{ nullptr } {};
	~List();
public:
	T Remove(T value); // Metoda, ktora wyszukuje element i go usuwa z listy
	void Add(T value); // Metoda, ktora dodaje element na koniec listy
	void Flush(); // Metoda, ktora czysci cala liste
	int Size(); // Getter, ktory zwraca liczbe elementow w liscie
	T* Search(T value); // Metoda, ktora wyszukuje element w liscie
	void Print(); // Wyswietla w konsoli liste elementow
	void AddAt(T valueToAdd, T valueWhereToAdd); // Metoda, która dodaje nowy element tam gdzie wskazany element w argumencie

private:
	//Struktura pomocnicza, value - wartosc elementu w liscie, next - pointer, ktory wskazuje nastepny element
	struct Node {
		T* value;
		Node* next;
	};

	struct NodeToRemove { // Struktura pomocniczna dla metody List<typename T>::Remove(T value)
		Node* currentNode; 
		Node* prevNode;
	};

	Node* head; // Element poczatkowy listy
	Node* back; // Element ostatni listy
	int size = 0; // Ilosc elementow w liscie
private:
	NodeToRemove* SearchNode(T value);
};

