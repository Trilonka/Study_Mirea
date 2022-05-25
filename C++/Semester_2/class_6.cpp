#include "Exception.cpp"

// Methods: pop, push, [], insert, remove, find, filter.

// ------------------------------------------------------------------------------------------------------------- ELEMENT (100%) -----------------------------------------------------------------------------------------------------------------

template<class T>
class Element
{
protected:

	Element* next;
	Element* prev;
	T info;

public:
	Element(T data)
	{
		next = prev = NULL;
		info = data;
	}

	Element(Element* Next, Element* Prev, T data)
	{
		next = Next;
		prev = Prev;
		info = data;
	}

	Element(const Element& el)
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

	template<class T1>
	friend ostream& operator<<(ostream& s, Element<T1>& el);
};

template<class T1>
ostream& operator<<(ostream& s, Element<T1>& el)
{
	s << el.info;
	return s;
}

// ------------------------------------------------------------------------------------------------------------- ELEMENT (100%) / LINKED LIST (add exceptions, <<)  -----------------------------------------------------------------------------------------------------------------

template<class T>
class LinkedList
{
protected:

	Element<T>* head;
	Element<T>* tail;
	int count;

public:

	LinkedList()
	{
		cout << "\nLinkedList class constructor";
		head = tail = NULL;
		count = 0;
	}

	LinkedList(T* arr, int len)
	{
		if (len < 1) throw "Incorrect array size"; // Negative Array length
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

	virtual ~LinkedList()
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
	virtual Element<T>* push(T value) = 0;
	virtual Element<T>* pop() = 0;
	virtual Element<T>* insert(T value, Element<T>* predecessor=NULL) = 0;
	virtual Element<T>* find(T value) = 0;
	virtual Element<T>* find(T value, Element<T>* el) = 0;
	virtual Element<T>* remove(T value) = 0;
	virtual void filter(bool (*cmp)(T), LinkedList<T>* dest) = 0;
	virtual void filter(bool (*cmp)(T), LinkedList<T>* dest, Element<T>* cur) = 0;

	bool isEmpty() { return (LinkedList<T>::count == 0); }

	template<class T1>
	friend ostream& operator<<(ostream& s, LinkedList<T1>& el);
	template <class T1>
    friend istream& operator>>(istream& s, LinkedList<T1>& el);
};

template<class T1> 
ostream& operator<<(ostream& s, LinkedList<T1>& el)
{
	Element<T1>* current;
	s << "\n(";
	for (current = el.head; current->getNext() != NULL; current = current->getNext())
		s << *current << ", ";
	s << *current << ")";
	return s;
}

template <class T1>
istream& operator>>(istream& s, LinkedList<T1>& el)
{
	cout << "\nList size is: " << el.count << ". Enter " << el.count << " values: ";
	Element<T1>* pom = el.head;
	T1 val;
	for (int i = 0; i<el.count; i++)
	{
		s >> val;
		pom->setInfo(val); 
		pom = pom->getNext();
	}
	return s;
}

// ------------------------------------------------------------------------------------------------------------- LINKED LIST (add exceptions) / STACK (add exceptions) -----------------------------------------------------------------------------------------------------------------

template<class T> 
class Stack : public LinkedList<T>
{
public:
	Stack() : LinkedList<T>() 
	{
		cout << "\nStack class constructor";
	}

	virtual ~Stack()
	{
		cout << "\nStack class destructor";
	}

	virtual Element<T>* operator[](int index)
	{
		if(index<0 || index>=LinkedList<T>::count) throw "Incorrect index"; // Negative / Too large index

		Element<T>* current = LinkedList<T>::head;

		for (int i = 0;
			current != NULL && i < index;
			current = current->getNext(), i++);

		return current;
	}

	virtual Element<T>* push(T value)
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

	virtual Element<T>* pop()
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

	virtual Element<T>* insert(T value, Element<T>* predecessor=NULL)
	{
		if (LinkedList<T>::head == NULL)
		{
			if (predecessor != NULL) throw "Predecessor not exists"; // Stack element not exists
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

	virtual Element<T>* find(T value)
    {
        Element<T>* p = LinkedList<T>::head;
        for (; p->getInfo() != value && p != NULL; p = p->getNext());
		return p;
	}

	virtual Element<T>* find(T value, Element<T>* el)
	{
		if (el->getInfo() == value || el==NULL)
			return el;
		return find(value, el->getNext());
	}

	virtual Element<T>* remove(T value)
	{
		Element<T>* p = LinkedList<T>::head;
		if (p == NULL) return p;
		if (p->getInfo() == value)
		{
			LinkedList<T>::head = p->getNext();
			p->setNext(NULL);
			LinkedList<T>::count--;
			return p;
		}
        for (; p->getNext() != NULL &&  p->getNext()->getInfo() != value; p = p->getNext());
		if (p->getNext()->getInfo() == value)
		{
			Element<T>* res = p->getNext();
			p->setNext(res->getNext());
			res->setNext(NULL);
			LinkedList<T>::count--;
        	return res;
		}
		return NULL;
	}

	virtual void filter(bool (*cmp)(T), LinkedList<T>* dest)
	{
		for (Element<T>* cur = LinkedList<T>::head; cur != NULL; cur = cur->getNext())
	        if (cmp(cur->getInfo()))
	            dest->push(cur->getInfo());
	}

	virtual void filter(bool (*cmp)(T), LinkedList<T>* dest, Element<T>* cur)
	{
		if (cur==NULL) return;
		if (cmp(cur->getInfo()))
			dest->push(cur->getInfo());
		return filter(cmp, dest, cur->getNext());
	}
};

// ------------------------------------------------------------------------------------------------------------- STACK (add exceptions) / DOUBLE SIDED STACK (add exceptions) -----------------------------------------------------------------------------------------------------------------

template<class T>
class DoubleSidedStack : public Stack<T>
{
public:
	DoubleSidedStack() : Stack<T>()
	{
		cout << "\nDoubleSidedStack class constructor"; 
	}
	virtual ~DoubleSidedStack()
	{
		cout << "\nDoubleSidedStack class destructor";
	}

	virtual Element<T>* operator[](int index)
	{
		if(index<0 || index>=LinkedList<T>::count) throw "Incorrect index"; // Negative / Too large index

		Element<T>* current;
		if (index < LinkedList<T>::count/2)
		{
			current = LinkedList<T>::head;
			for (int i = 0;
			current != NULL && i < index;
			current = current->getNext(), i++);
			return current;
		}
		else
		{
			current = LinkedList<T>::tail;
			for (int i = LinkedList<T>::count-1;
			current != NULL && i>index;
			current = current->getPrev(), i--);
			return current;
		}
		return current;
	}

	virtual Element<T>* push(T value)
	{
		Element<T>* tail_predecessor_push = LinkedList<T>::tail;
		Element<T>* res = Stack<T>::push(value);
		res->setPrev(tail_predecessor_push);
		return res;
	}

	virtual Element<T>* pop()
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

	virtual Element<T>* insert(T value, Element<T>* predecessor = NULL)
	{
		if (LinkedList<T>::head == NULL)
		{
			if (predecessor != NULL) throw "Predecessor not exists"; // Stack element not exists
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
		if(successor != NULL) successor->setPrev(inserted);
		inserted->setPrev(predecessor);
		return inserted;
	}

    // find ищет по значению, поэтому нет смысла переопределять его для DoubleSidedStack

	virtual Element<T>* remove(T value)
	{
		Element<T>* p = LinkedList<T>::head;
		if (p == NULL) return p;
		if (p->getInfo() == value)
		{
			Stack<T>::remove(value);
			LinkedList<T>::head->setPrev(NULL);
			return p;
		}
        for (; p->getNext() != NULL &&  p->getNext()->getInfo() != value; p = p->getNext());
		if (p->getNext()->getInfo() == value)
		{
			Element<T>* res = p->getNext();
			p->setNext(res->getNext());
			res->getNext()->setPrev(p);
			res->setNext(NULL);
			res->setPrev(NULL);
			LinkedList<T>::count--;
        	return res;
		}
		return NULL;
	}

	// filter ищет по значению, поэтому нет смысла переопределять его для DoubleSidedStack
};

// ------------------------------------------------------------------------------------------------------------- DOUBLE SIDED STACK (add exceptions) / MY CLASS -----------------------------------------------------------------------------------------------------------------

template <class Customer>
class my_class : public DoubleSidedStack<Customer>
{
	my_class() : DoubleSidedStack<Customer>() { } // constructor (void) : my_class
	virtual ~my_class() { } // virtual destructor

	virtual Element<Customer>* push(Customer value) // virtual push (value) - changed
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

// ------------------------------------------------------------------------------------------------------------- MY CLASS / CUSTOMER -----------------------------------------------------------------------------------------------------------------

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

// ------------------------------------------------------------------------------------------------------------- CUSTOMER / MAIN -----------------------------------------------------------------------------------------------------------------

bool f(double d)
{
	return d>10;
}

int main()
{
	LinkedList<double>* list;
	cout << "---------------------------------------------------------------------------STACK WORK------------------------------------------------------------------------------------------";
	list = new Stack<double>();
	for (int i = 0; i<10; i++)
		list->push(i*2);

	cout << endl << "operator[](4): " << *list->operator[](4);
	cout << endl << "pop(): " << *list->pop();
	Element<double>* el = list->find(4);
	cout << endl << "el = find(4): " << *el;
	cout << endl << "find(14, el): " << *list->find(14, el);
	cout << *list << " list";
	list->insert(77, list->find(10));
	cout << *list << " list after insert(77, find(10))";
	list->remove(12);
	cout << *list << " list after remove(12)";

	LinkedList<double>* filteredList = new Stack<double>();

	// Ввод значений в List
	// cout << *list;
	// cin >> *list;
	// cout << *list;

	list->filter(f, filteredList);
	cout << *filteredList << " filtered list by double > 10";

	list->filter(f, filteredList, el);
	cout << *filteredList << " filtered list + by double > 10 recursion after el";

	delete list;
	delete filteredList;

	cout << "\n---------------------------------------------------------------------------DOUBLE SIDED STACK WORK------------------------------------------------------------------------------------------";
	list = new DoubleSidedStack<double>();
	for (int i = 0; i<10; i++)
		list->push(i*2-1);

	cout << endl << "operator[](3): " << *list->operator[](3);
	cout << endl << "operator[](9): " << *list->operator[](9);
	cout << endl << "pop(): " << *list->pop();
	el = list->find(7);
	cout << endl << "el = find(7): " << *el;
	cout << endl << "find(15, el): " << *list->find(15, el);
	cout << *list << " list";
	list->insert(77, list->find(11));
	cout << *list << " list after insert(77, find(11))";
	list->remove(3);
	cout << *list << " list after remove(3)";

	filteredList = new DoubleSidedStack<double>();

	// Ввод значений в List
	// cout << *list;
	// cin >> *list;
	// cout << *list;

	list->filter(f, filteredList);
	cout << *filteredList << " filtered list by double > 10";

	list->filter(f, filteredList, el);
	cout << *filteredList << " filtered list + by double > 10 recursion after el";

	delete list;
	delete filteredList;

	cout << "\n---------------------------------------------------------------------------MY ClASS WORK------------------------------------------------------------------------------------------";

	return 0;
}