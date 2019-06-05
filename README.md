
# Praca zaliczeniowa - Algorytmy i struktury danych
<p align="center">
<img width="200" height="200" src="http://ict-silesia.pl/wp-content/uploads/2015/01/logo_wst_duze-e1421407661991.png">
</p>

**Przedmiot:** Algorytmy i Struktury Danych
**Wykładowca:** Dr. Barbara Marszal-Paszek
<p align="right">
<b>Wykonawca: </b> Wojciech Brzuszkiewicz <br>
<b>Data:</b> Czerwiec 2019r
</p>

# Lista jednokierunkowa

## Wstęp
### Poprawne działanie/kompilacja kodu
Wszystkie pliki, które są potrzebne do poprawnego działania kodu, są zawarte w folderze `src`
Wymagany jest kompilator, który obsługuje przynajmniej standarc C++14 lub wyższy.
Zalecam wygenerowanie własnego projektu w dowolnym IDE, oraz przekopiowanie zawartości plików źródłowych.

**Opis i hierarchia plików źródłowych**:
- /src
	- Lista.cpp - Plik zawierający funkcje `main()`dla listy
	- List.h - Plik zawierający definicje klasy szablonowej `List<typename T>`
	- List.cpp - Plik zawierający deklaracje metod klasy szablonowej `List<typename T>`
### Lista jednokierunkowa definicja słowna
Lista jednokierunkowa jest to dynamiczna struktura danych, która może tylko i wyłącznie iterować po elementach w jedną stronę, na którą wskazuję węzeł. Owa struktura danych składa się z węzła początkowego, oraz węzeł końcowy. Węzeł w liście kierunkowej zawiera wskaźnik do następnego elementu, oraz zmienną, która zawiera potrzebne dane. Węzeł końcowy w moim przypadku wskazuję na pusty wskaźnik tzw. `nullptr`. Można się spotkać z przykładem implementacji listy, gdzie ostatni węzeł wskazuje na początkowy. 
**Graficzna reprezentacja listy:**

![](https://upload.wikimedia.org/wikibooks/pl/d/d6/Lista-jednokierunkowa.gif)
Źródło obrazka: [Wikipedia](https://upload.wikimedia.org/wikibooks/pl/d/d6/Lista-jednokierunkowa.gif)
## Hierarchia klas w projektcie 
![](https://i.imgur.com/oy9jGMf.png)

### Legenda:
`ptr_` - Oznacza wskaźnik
`<typename T` - Klasa szablonowa `T` jest typem jakim będzie przechowywała lista

## Złożoność obliczeniowa poszczególnych operacji
Lista kierunkowa w przeciwieństwie do tablic, nie musi kopiować i tworzyć na nowo nowego kontenera. Co skutkuje tym, że dodawanie elementów do listy jest natychmiastowe i nie trzeba tracić zbędnego czasu na kopiowanie wszystkich elementów.

- Dodawanie na koniec listy - **O(1)**
- Dostęp do danego elementu w liście - **O(n)**
- Usuwanie elementu z listy - **O(n)**
### Metody obsługujące listę w projekcie:
`void Add(T value)` - Metoda, która odpowiada za dodawanie elementu na koniec listy.
Zawiera w sobie switcha, który odpowiada za rozpoznawanie czy nowy element ma być pierwszym, ostatnim elementem, czy n-1(Gdzie n jest to liczba elementów w liście). 
```cpp
template<typename T>
void List<T>::Add(T value)
{
	switch(size){
	case 0: // Lista jest pusta
	{
		head = new Node();
		head->value = new T(value);
		head->next = nullptr;
		size++;
		break;
	}
	case 1: // Lista posiada tylko 1 element
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
```
Jak widać w zamieszczonym kodzie, nigdzie nie ma żadnej pętli, więc złożoność obliczeniowa jest = **O(1)**
`void Flush()` - Metoda odpowiada za czyszczenie wszystkich elementów w liście. Złożoność obliczeniowa tej metody jest = **O(n)**. Ponieważ metoda iteruje po wszystkich elementach za pomocą pętli `for (int i = 0; i < size; i++)`, gdzie size jest liczbą elementów w liście. Złożoność obliczeniowa dla tej pętli jest = **O(n)**, więc złożoność.
```cpp
template<typename T>
void List<T>::Flush() {
	if (size == 0) // Jesli lista jest pusta to zakoncz dzialanie
		return;

	auto helper = head; // Tworzenie pomocniczeka wskaznika Node*
	for (int i = 0; i < size; i++) { // Klasyczna petla foreach O(n)
		if (helper->next == nullptr) { // Jesli element jest ostatni to 
			delete helper->next; // zniszcz wskaznik na nastepny element
			delete helper->value; // zniszcz wartosc wezla
			delete helper; // zniszcz sam wezel
			size--; // zmniejsz ilosc elementow o 1 
			break; // wyjdz z petli
		}
		//przecziwnym razie wykonaj to
		auto nextNode = helper->next; // 
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
```
`int Size()` - Jest to podstawowy getter, który zwraca zawartość atrybutu size z listy.
Złożoność obliczeniowa dla tej metody jest = **O(n)**
```cpp
template<typename T>
int List<T>::Size()
{
	return size;
}
```
`T* Search(T value)` - Metoda, która wyszukuje element w liście i zwraca addres obiektu, jeśli znajdzie. Metoda ta, porównuje parametr value z wartością n-tgo węzła w liście. Jest to przykład wyszukiwania linearnego, więc złożoność obliczeniowa jest = **O(n)**

```cpp
T* List<T>::Search(T value)
{
	if (size == 0)
		return nullptr; // jesli lista jest pusta, to zwroc pusty wskaznik
	
	auto helper = head; // tworzenie pomoniczego wsaznika, ktory wskazuje na   poczatek listy
	for (int i = 0; i < size; i++) { // funkcja foreach
		if (*helper->value == value) { // jesli znalazles element to
			return helper->value; // zwroc adres tego elementu
		}
		else { // przeciwnym razie
			if (helper->next == nullptr) { // sprawdz czy, n-ty element jest ostatnim w petli, jesli tak to zwroc pusty wskaznik
				return nullptr;
			}

			helper = helper->next; // w przeciwnym razie wskaz na nastepny element
		}
	}
}
```
`void Print()` - Metoda, która wyświetla wszystkie elementy w liście na ekranie konsoli. Wykorzystuje bibliotekę `<iostream>`, w celu obsługi strumienia **I/O**. Złożoność obliczeniowa dla tej metody jest = **O(n)**.
```cpp
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
```
`NodeToRemove* SearchNode(T value)` - Metoda pomocnicza z dostępem private. Wyszukuje ona element, który pasuję do porównania `value == Node.value`. Jeśli metoda nie znajdzie szukanego elementu, to zwróci `nullptr`. Złożoność obliczeniowa = **O(n)**
```cpp
template<typename T>
auto List<T>::SearchNode(T value) -> NodeToRemove*
{
	if (size == 0)
		return nullptr; // jesli lista jest pusta to zwroc pusty wskaznik
	
	if (*head->value == value) { // jesli element szukany jest pierwszym elementem w liscie to
		auto nodeToRemove = new NodeToRemove(); // stworz strukture pomocnicza
		nodeToRemove->currentNode = head; // przypisz dla currentNode adres pierwszego elementu
		nodeToRemove->prevNode = nullptr; // dla prevNode przypisz pusty, poniewaz pierwszy element nie moze miec swojego poprzednika
		return nodeToRemove; // zwroc pomocniczy obiekt
	}
// w przeciwnym razie 
	auto helper = new NodeToRemove(); 
	helper->currentNode = head->next; // stworz pomocniczy obiekt i przypisz adres 2 elementu
	helper->prevNode = head; // dla poprzednika przypisz adres pierwszego elementu
	for (int i = 0; i < size - 1; i++) { //petla for, ktora sie wykonuje do n-2 razy
		if (*helper->currentNode->value == value) // jesli znalazles element to
			return helper; // zwroc obiekt pomocniczy
		else { // w przeciwnym razie
			auto buffer = helper->currentNode->next; // wskaz na nastepny elemt
			helper->prevNode = helper->currentNode;
			helper->currentNode = buffer;
		}
	}
	delete helper; // zwlonij pamiec
	return nullptr; // jesli metoda nic nie zlalazla to zwroc pusty pointer
}
```
`void List<T>::AddAt(T valueToAdd, T valueWhereToAdd)` - Metoda dodająca nowy element przed wskazany element w parametrze. 
Metoda ta wykorzystuje metode pomocniczą `NodeToRemove* SearchNode(T value)`
Złożoność obliczeniowa dla tej operacji jest = **O(n)**
**Graficzna reprezentacja dodawania do listy**:
![](https://www.tutorialspoint.com/data_structures_algorithms/images/linked_list_insertion_2.jpg)
Head - element poczatkowy, next - jest to wskaznik na nastepny element.
**Źródło obrazka**: [Tutorials point]([https://www.tutorialspoint.com/data_structures_algorithms/linked_list_algorithms.htm](https://www.tutorialspoint.com/data_structures_algorithms/linked_list_algorithms.htm))

```cpp
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
```
`T Remove(T value)` - Metoda wyszukuje wskazany element z listy i go usuwa, zwracają kopie usuniętego elementu. Metoda ta wykorzystuje metodę pomocniczą `NodeToRemove* SearchNode(T value)`.  Złożoność obliczeniowa dla tej operacji jest = **O(n)**
```cpp
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
```
## Test programu
### Przykładowy kod
```cpp
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
```
Lista obiektów przechowywana w pamięci:
![](https://i.imgur.com/zYPnOkX.png)
Lista obiektów po wywołaniu metody Remove(3), oraz Remove(5):
![](https://i.imgur.com/ekm1aNN.png)
Output konsoli:
![](https://i.imgur.com/cgTWr5G.png)

## Konkluzja
Lista jest relatywnie dobrym kontenerem na mniejsze ilości danych, gdy chcemy przechowywać dynamicznie utworzone elementy.
### Głownymi zaletami jej są:
- Natychmiastowe dodanie nowego elementu na koniec tablicy
- Brak przymusu kopiowania i inicjaniozwania nowego kontenera na dane, przy rozszerzaniu kontenera 
- Brak liniowiości dodawanych nowych elementow(Elementy sa rozproszone po pamięci, w przeciwieństwie do tabilcy, gdzie dane są ułożone obok siebie.)
### Wady:
- Brak natychmiastowego dostępu do danych, trzeba iterować po liście żeby dostać sie do danego elementu
- Dodawanie/usuwanie elementu o danym indeksie zajmuje sporo czasu, ponieważ trzeba iterować po całej liście.
 