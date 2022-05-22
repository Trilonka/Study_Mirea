using namespace std;

#include <iostream>

// element class
template<class T>
class Element
{
// protected:
// 	Element* next;
// 	Element* prev;
// 	T info;
public:
	Element* next;
	Element* prev;
	T info;
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

	template<class T1> // friend output
	friend ostream& operator<<(ostream& s, Element<T1>& el);
	template <class T1>
    friend istream& operator>>(istream& s, Element<T1>& el);
};

template<class T1> // realize friend output for Element
ostream& operator<<(ostream& s, Element<T1>& el)
{
	s << el.info;
	return s;
}
template<class T1> // realize friend output for Element
istream& operator>>(istream& s, Element<T1>& el)
{
	s >> el.info;
	return s;
}

// linked_list class
template<class T>
class LinkedList
{
// protected:
// 	Element<T>* head;
// 	Element<T>* tail;
// 	int count;

public:
	Element<T>* head;
	Element<T>* tail;
	int count;

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
			current = current->next;
			current = new Element<T>(arr[i]);
		}
		tail = current;
		count = len;
	}

	T& operator[](int index) // operator [] (index)
	{
		if(index<0 || index>=count) throw "Incorrect index";

		Element<T>* current = head;

		for (int i = 0;
			current != NULL && i < index;
			current = current->next, i++);

		return current->info;
	}

	virtual ~LinkedList() // virtual destructor
	{
		cout << "\nLinkedList class destructor";
		if (head != NULL)
		{
			Element<T>* current = head;
			Element<T>* temp = head->next;
			for (; current != tail; current = temp, temp = temp->next)
				delete current;
		}
		head = NULL; tail = NULL;
	}

	virtual Element<T>* pop() = 0; // virtual pop
	virtual Element<T>* push(T value) = 0; // virtual push (value)

	virtual bool isEmpty() { return (LinkedList<T>::count == 0); } // virtual isEmpty

	template<class T1> // friend output
	friend ostream& operator<<(ostream& s, LinkedList<T1>& el);
};

template<class T1> // realize friend output for LinkedList
ostream& operator<<(ostream& s, LinkedList<T1>& el)
{
	Element<T1>* current;
	for (current = el.head; current != NULL; current = current->next)
		s << *current << "; ";
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
			LinkedList<T>::tail->next = new Element<T>(value);
			LinkedList<T>::tail = LinkedList<T>::tail->next;
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
				current->next != LinkedList<T>::tail; current = current->next);
			LinkedList<T>::tail = current;
			LinkedList<T>::tail->next = NULL;
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
			newElem->next = LinkedList<T>::head;
			LinkedList<T>::head = newElem;
			LinkedList<T>::count++;
			return newElem;
		}
		Element<T>* newElem = new Element<T>(value);
		Element<T>* successor = predecessor->next;
		predecessor->next = newElem;
		newElem->next = successor;
		if (predecessor == LinkedList<T>::tail)
			LinkedList<T>::tail = LinkedList<T>::tail->next;
		LinkedList<T>::count++;
		return newElem;
	}

	virtual ~Stack() { cout << "\nStack class destructor"; } // virtual destructor
};

// DoubleSidedStack class
template<class T>
class DoubleSidedStack : public Stack<T>
{
public:
	DoubleSidedStack() : Stack<T>() { cout << "\nDoubleSidedStackclass constructor"; } // constructor (void) : Stack
	virtual ~DoubleSidedStack() { cout << "\nDoubleSidedStack class destructor"; } // virtual destructor

	// Зачем перегружать оператор [] ?
	// T& operator[](int index) // operator [] (index)
	// {
	// 	if(index<0 || index>=count) throw "Incorrect index";

	// 	Element<T>* current = head;

	// 	for (int i = 0;
	// 		current != NULL && i < index;
	// 		current = current->next, i++);

	// 	return current->info;
	// }

	virtual Element<T>* push(T value) // virtual push (value) - changed
	{
		Element<T>* tail_predecessor_push = LinkedList<T>::tail;
		Element<T>* res = Stack<T>::push(value);
		res->prev = tail_predecessor_push;
		return res;
	}

	virtual Element<T>* pop() // virtual pop - changed
	{
		if (LinkedList<T>::tail == LinkedList<T>::head)
			return Stack<T>::pop();
		Element<T>* res = LinkedList<T>::tail;
		LinkedList<T>::tail = LinkedList<T>::tail->prev;
		LinkedList<T>::tail->next = NULL;
		res->prev = NULL;
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
			LinkedList<T>::head->next->prev = LinkedList<T>::head;
			return LinkedList<T>::head;
		}
		Element<T>* successor = predecessor->next;
		Element<T>* inserted = Stack<T>::insert(value, predecessor);
		if(predecessor != LinkedList<T>::tail) successor->prev = inserted;
		inserted->prev = predecessor;
		return inserted;
	}

	template<class T1>
	friend ostream& operator<<(ostream& s, DoubleSidedStack<T1>& el);
};

template<class T1>
ostream& operator<<(ostream& s, DoubleSidedStack<T1>& el)
{
	Element<T1>* current;
	for (current = el.tail; current != NULL; current = current->prev)
		s << *current << ", ";
	return s;
}

// my_class class
template <class T>
class my_class : protected DoubleSidedStack<T>
{
	my_class() : DoubleSidedStack<T>() { } // constructor (void) : my_class
	virtual ~my_class() { } // virtual destructor

	virtual Element<T>* push(T value) // virtual push (value) - changed
	{
		Element<T>* pom = new Element<T>(value);
		pom->next = DoubleSidedStack<T>::head;
		DoubleSidedStack<T>::head->prev = pom;
		DoubleSidedStack<T>::head = pom;
		DoubleSidedStack<T>::count++;
		return pom;
	}

	virtual Element<T>* pop() // virtual pop (void) - changed
	{
		Element<T>* pom = DoubleSidedStack<T>::head;
		pom->next->prev = NULL;
		pom->next = NULL;
		DoubleSidedStack<T>::count--;
		return pom;
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
	if (true)
	{
		DoubleSidedStack<double> S;
		cout << "\n";
		for (int i = 0; i < 20; i++)
		{
			S.push(i);
		}
		//S.insert(-1);
		S.insert(5.5, S.head->next->next->next->next->next);
		cout <<"\n"<< S;
		cout << "\n";
	}
	if (true)
	{
		Stack<double> S;
		for (int i = 0; i < 10; i++)
			S.push(i);
		S.insert(3.5, S.head->next->next->next);
		cout << S;
		cout << "\n";
	}
	if (true)
	{
		cout << "Only object\n";
		Stack<int> S;
		for (int i = 0; i < 100; i += 5)
			S.push(i);
		for (; !S.isEmpty(); cout << S.pop()->info << ", ");
		cout << "\n";
	}

	if (true)
	{
		cout << "\nBase pointer 1\n";
		LinkedList<int>* ptr = new DoubleSidedStack<int>;
		for (int i = 1; i < 100; i += 5)
			ptr->push(i);
		cout << *ptr << "\n";
		delete ptr;
		//добавить виртуальные деструкторы
	}

	if (true)
	{
		cout << "\nBase pointer 2\n";
		LinkedList<int>* ptr; Stack<int>* ptr2 = new Stack<int>; ptr = ptr2;
		for (int i = 1; i < 100; i += 5)
			ptr->push(i);
		cout << *ptr << "\n";
		delete ptr;
		//добавить виртуальные деструкторы
	}

	if (true)
	{
		cout << "\nStack pointer\n";
		Stack<int>* ptr = new Stack<int>;
		for (int i = 2; i < 100; i += 5)
			ptr->push(i);
		cout << *ptr << "\n";
		delete ptr;
	}

	// if (true)
	// {
	// 	cout << "\nmy_class Stack test\n";
	// 	Stack<my_class> S;
	// 	cout << "\ncycle\n";
	// 	for (int i = 3; i < 100; i += 5)
	// 		S.push(my_class(i));
	// 	cout << S;
	// }
	// if (true)
	// {
	// 	cout << "\nmy_class* p1 = new my_class";
	// 	my_class* p1 = new my_class;
	// 	delete p1;
	// }
	// if (true)
	// {
	// 	cout << "\nmy_class* p1 = new my_class()";
	// 	my_class* p1 = new my_class();
	// 	delete p1;
	// }
	// if (true)
	// {
	// 	cout << "\nmy_class* p1 = new my_class[]";
	// 	my_class* p1 = new my_class[10];
	// 	delete[] p1;
	// }
	char c; cin >> c;
	return 0;
}