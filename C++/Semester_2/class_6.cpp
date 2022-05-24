using namespace std;

#include <iostream>

// element class
template<class T>
class Element
{
protected:

	Element* next;
	Element* prev;
	T info;

public:
	Element(T data) // constructor (data)
	{
		next = prev = NULL;
		info = data;
	}

	Element(Element* Next, Element* Prev, T data) // constructor (next, prev, data)
	{
		next = Next;
		prev = Prev;
		info = data;
	}

	Element(const Element& el) // copy constructor
	{
		next = el.next;
		prev = el.prev;
		info = el.info;
	}

	Element<T>* getNext() {
		return next;
	}

	void setNext(Element* Next) {
		next = Next;
	}

	Element<T>* getPrev() {
		return prev;
	}

	void setPrev(Element* Prev) {
		prev = Prev;
	}

	T getInfo() {
		return info;
	}

	void setInfo(T Info) {
		info = Info;
	}

	template<class T1> // friend output
	friend ostream& operator<<(ostream& s, Element<T1>& el);
	// template <class T1>
    // friend istream& operator>>(istream& s, Element<T1>& el);
};

template<class T1> // realize friend output for Element
ostream& operator<<(ostream& s, Element<T1>& el)
{
	s << el.info;
	return s;
}
// template<class T1> // realize friend output for Element
// istream& operator>>(istream& s, Element<T1>& el)
// {
// 	s >> el.info;
// 	return s;
// }

// linked_list class
template<class T>
class LinkedList
{
protected:

	Element<T>* head;
	Element<T>* tail;
	int count;

public:

	LinkedList() // constructor (void)
	{
		head = tail = NULL;
		count = 0;
	}

	LinkedList(T* arr, int len) // constructor (arr, len)
	{
		if (len < 1) throw "Incorrect array size";
		Element<T>* current = new Element<T>(arr[0]);
		head = current;
		for (int i = 1; i<len; i++)
		{
			current = current->getNext();
			current = new Element<T>(arr[i]);
		}
		tail = current;
		count = len;
	}

	virtual ~LinkedList() // virtual destructor
	{
		cout << "\nLinkedList class destructor";
		if (head != NULL)
		{
			Element<T>* current = head;
			Element<T>* temp = head->getNext();
			for (; current != tail; current = temp, temp = temp->getNext())
				delete current;
		}
		head = NULL; tail = NULL;
	}

	virtual Element<T>* operator[](int index) = 0;

	virtual Element<T>* pop() = 0; // virtual pop
	virtual Element<T>* push(T value) = 0; // virtual push (value)

	virtual void filter(bool (*cmp)(T), LinkedList<T>* dest) = 0;

	virtual bool isEmpty() { return (LinkedList<T>::count == 0); } // virtual isEmpty

	template<class T1> // friend output
	friend ostream& operator<<(ostream& s, LinkedList<T1>& el);
};

template<class T1> // realize friend output for LinkedList
ostream& operator<<(ostream& s, LinkedList<T1>& el)
{
	Element<T1>* current; // может переопределить вывод
	for (current = el.head; current != NULL; current = current->getNext())
		s << *current << ", ";
	return s;
}

// Stack class
template<class T> 
class Stack : public LinkedList<T>
{
public:
	Stack<T>() : LinkedList<T>() {} // constructor (void) : LinkedList (void)

	virtual Element<T>* push(T value) // LinkedList push (value) realize
	{
		if (LinkedList<T>::head == NULL)
		{
			LinkedList<T>::tail = new Element<T>(value);
			LinkedList<T>::head = LinkedList<T>::tail;
		}
		else
		{
			LinkedList<T>::tail->setNext(new Element<T>(value));
			LinkedList<T>::tail = LinkedList<T>::tail->getNext();
		}
		LinkedList<T>::count++;
		return LinkedList<T>::tail;
	}

	virtual Element<T>* pop() // LinkedList pop realize
	{
		if (LinkedList<T>::tail == NULL)
			return NULL;
		Element<T>* res = LinkedList<T>::tail;
		if (LinkedList<T>::head == LinkedList<T>::tail)
			LinkedList<T>::head = LinkedList<T>::tail = NULL;
		else
		{
			Element<T>* current;
			for (current = LinkedList<T>::head; 
				current->getNext() != LinkedList<T>::tail; current = current->getNext());
			LinkedList<T>::tail = current;
			LinkedList<T>::tail->setNext(NULL);
		}
		LinkedList<T>::count--;
		return res;
	}

	virtual Element<T>* insert(T value, Element<T>* predecessor=NULL) // virtual insert (value, predecessor)
	{
		if (LinkedList<T>::head == NULL)
		{
			if (predecessor != NULL) throw "Predecessor not exists";
			return push(value);
		}
		if (predecessor == NULL)
		{
			Element<T>* newElem = new Element<T>(value);
			newElem->setNext(LinkedList<T>::head);
			LinkedList<T>::head = newElem;
			LinkedList<T>::count++;
			return newElem;
		}
		Element<T>* newElem = new Element<T>(value);
		Element<T>* successor = predecessor->getNext();
		predecessor->setNext(newElem);
		newElem->setNext(successor);
		if (predecessor == LinkedList<T>::tail)
			LinkedList<T>::tail = LinkedList<T>::tail->getNext();
		LinkedList<T>::count++;
		return newElem;
	}

	virtual Element<T>* operator[](int index)
	{
		if(index<0 || index>=LinkedList<T>::count) throw "Incorrect index";

		Element<T>* current = LinkedList<T>::head;

		for (int i = 0;
			current != NULL && i < index;
			current = current->getNext(), i++);

		return current;
	}

	virtual ~Stack() { cout << "\nStack class destructor"; } // virtual destructor

	template <class T1>
    friend istream& operator>>(istream& s, Stack<T1>& el); 
};

template <class T1>
istream& operator>>(istream& s, Stack<T1>& el)
{
	Element<T1>* pom = el.head;
	T1 val;
	for (int i = 0; i<el.count; i++) {
		s >> val;
		pom->setInfo(val);
		pom = pom->getNext();
	}
	return s;
}

// DoubleSidedStack class
template<class T>
class DoubleSidedStack : public Stack<T>
{
public:
	DoubleSidedStack() : Stack<T>() { cout << "\nDoubleSidedStackclass constructor"; } // constructor (void) : Stack
	virtual ~DoubleSidedStack() { cout << "\nDoubleSidedStack class destructor"; } // virtual destructor

	//Зачем перегружать оператор []? Ответ: Можно смотреть к чему ближе
	Element<T>* operator[](int index) // operator [] (index)
	{
		if(index<0 || index>=LinkedList<T>::count) throw "Incorrect index";

		if (index < LinkedList<T>::count/2)
		{
			Element<T>* current = LinkedList<T>::head;
			for (int i = 0;
			current != NULL && i < index;
			current = current->getNext(), i++);
			return current;
		}
		else
		{
			Element<T>* current = LinkedList<T>::tail;
			for (int i = LinkedList<T>::count;
			current != NULL && i>index;
			current = current->getPrev(), i--)
			return current;
		}

		return NULL;
	}

	virtual Element<T>* push(T value) // virtual push (value) - changed
	{
		Element<T>* tail_predecessor_push = LinkedList<T>::tail;
		Element<T>* res = Stack<T>::push(value);
		res->setPrev(tail_predecessor_push);
		return res;
	}

	virtual Element<T>* pop() // virtual pop - changed
	{
		if (LinkedList<T>::tail == LinkedList<T>::head)
			return Stack<T>::pop();
		Element<T>* res = LinkedList<T>::tail;
		LinkedList<T>::tail = LinkedList<T>::tail->getPrev();
		LinkedList<T>::tail->setNext(NULL);
		res->setPrev(NULL);
		LinkedList<T>::count--;
		return res;
	}

	virtual Element<T>* insert(T value, Element<T>* predecessor = NULL) // virtual insert (value, predecessor) - improved
	{
		if (LinkedList<T>::head == NULL)
		{
			if (predecessor != NULL) throw "Predecessor not exists";
			return push(value);
		}
		if (predecessor == NULL)
		{
			Stack<T>::insert(value);
			LinkedList<T>::head->getNext()->setPrev(LinkedList<T>::head);
			return LinkedList<T>::head;
		}
		Element<T>* successor = predecessor->getNext();
		Element<T>* inserted = Stack<T>::insert(value, predecessor);
		if(predecessor != LinkedList<T>::tail) successor->setPrev(inserted);
		inserted->setPrev(predecessor);
		return inserted;
	}

	virtual void filter(bool (*cmp)(T), LinkedList<T>* dest)
	{
		for (Element<T>* cur = LinkedList<T>::head; cur != NULL; cur = cur->getNext())
	        if (cmp(cur->getInfo()))
	            dest->push(cur->getInfo());
	}

	virtual void filter_recursion(bool (*cmp)(T), DoubleSidedStack<T>* dest, Element<T>* el)
	{
		if (el==NULL) return;
		if (cmp(el->getInfo()))
			dest->push(el->getInfo());
		return filter_recursion(cmp, dest, el->getNext());
	}

	// Поиск элемента по значению
    virtual Element<T>* find(T value)
    {
        Element<T>* p = LinkedList<T>::head;
        for (; p->getInfo() != value && p != NULL; p = p->getNext());
        return p;
	}

	virtual Element<T>* find_recursion(T value, Element<T>* el)
	{
		if (el->getInfo() == value || el==NULL)
		{
			return el;
		}
		return find_recursion(value, el->getNext());
	}

	template<class T1>
	friend ostream& operator<<(ostream& s, DoubleSidedStack<T1>& el);
};

template<class T1>
ostream& operator<<(ostream& s, DoubleSidedStack<T1>& el)
{
	Element<T1>* current;
	for (current = el.tail; current != NULL; current = current->getPrev())
		s << *current << ", ";
	return s;
}

// my_class class
template <class T>
class my_class : public DoubleSidedStack<T>
{
	my_class() : DoubleSidedStack<T>() { } // constructor (void) : my_class
	virtual ~my_class() { } // virtual destructor

	virtual Element<T>* push(Customer value) // virtual push (value) - changed
	{
		Element<Customer>* pom = new Element<Customer>(value);
		pom->setNext(DoubleSidedStack<Customer>::head);
		DoubleSidedStack<Customer>::head->setPrev(pom);
		DoubleSidedStack<Customer>::head = pom;
		DoubleSidedStack<Customer>::count++;
		return pom;
	}

	virtual Element<Customer>* pop() // virtual pop (void) - changed
	{
		Element<Customer>* pom = DoubleSidedStack<Customer>::head;
		pom->getNext()->setPrev(NULL);
		pom->setNext(NULL);
		DoubleSidedStack<Customer>::count--;
		return pom;
	}

	virtual Element<Customer>* find(Customer value)
    {
        Element<Customer>* p = LinkedList<Customer>::head;
        for (; p->getInfo().lastname != value.lastname && p != NULL; p = p->getNext());
        return p;
	}

	virtual void filter(int AverageCheckAmount, LinkedList<Customer>* dest)
	{
		for (Element<Customer>* cur = LinkedList<Customer>::head; cur != NULL; cur = cur->getNext())
	        if (cur->getInfo().averageCheckAmount == AverageCheckAmount)
	            dest->push(cur->getInfo());
	}

};

// Customer class	
class Customer
{
public:
	char* firstname;
	char* lastname;
	char* city;
	char* street;
	int houseNumber;
	int apartmentNumber;
	int accountNumber;
	int averageCheckAmount;
	// push - в начало 
	// pop - из начала
	// Поиск по фамилии, фильтр по средней сумме чека. (search, filter)
	Customer()
	{
		firstname = lastname = city = street = NULL;
		houseNumber = apartmentNumber =
		accountNumber = averageCheckAmount = 0;
	}
	Customer(char* Firstname, char* Lastname,
			 char* City, char* Street,
			 int HouseNumber, int ApartmentNumber,
			 int AccountNumber, int AverageCheckAmount)
	{
		firstname = Firstname;
		lastname = Lastname;
		city = City;
		street = Street;
		houseNumber = HouseNumber;
		apartmentNumber = ApartmentNumber;
		accountNumber = AccountNumber;
		averageCheckAmount = AverageCheckAmount;
	}

	~Customer() {}

	friend ostream& operator<<(ostream& s, Customer& value);
};

ostream& operator<<(ostream& s, Customer& value)
{
	s <<value.firstname<<", "<<value.lastname<<", "
	  <<value.city<<", "<<value.street<<", "<<value.houseNumber<<", "
	  << value.apartmentNumber<<", "<<value.accountNumber<<", "
	  <<value.averageCheckAmount<<endl;
	return s;
}

int main()
{
	DoubleSidedStack<int> s;
	for (int i = 0; i<5; i++)
	{
		s.push(i);
	}
	cout << s;
	s.pop();
	cout << s << endl;
	Element<int> el = *s[3];
	cout << el;
	//---
	Customer c1("sanya", "anna", "volk", "street", 3, 4, 2, 3);
	Customer c2("dsfa", "anna", "volk", "street", 3, 4, 2, 4);
	Customer c3("sdsafda", "kolya", "volk", "street", 3, 4, 2, 14);
	Customer c4("sgvfsaa", "ton", "volk", "street", 3, 4, 2, 40);

	my_class<Customer> m;
	m.push(c1);
	m.push(c2);
	return 0;

	LinkedList<double>* p = new 
}