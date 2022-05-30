#include "Exception_6.cpp"

// ------------------------------------------------------------------------------------------------------------- MY_MANIP (100%) -----------------------------------------------------------------------------------------------------------------

ostream& my_manip(ostream& s)
{
    s.width(5);
    return s;
}

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
	s << "\n";
	my_manip(s);
	s << el.info;
	return s;
}

// ------------------------------------------------------------------------------------------------------------- ELEMENT (100%) / LINKED LIST (100%)  -----------------------------------------------------------------------------------------------------------------

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
		if (len < 1) throw NegativeSize("Negative Array length", len);
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
	virtual void filter(T, LinkedList<T>* dest, bool more) = 0;
	virtual void filter(T, LinkedList<T>* dest, Element<T>* cur, bool more) = 0;

	bool isEmpty() { return (LinkedList<T>::count == 0); }

	virtual void save(string fileName)
	{
		ofstream fout(fileName);
        if (fout.is_open())
        {
			fout << count << "\n";
			Element<T>* pom = head;
			T info;
			for (int i = 0; i < count; i++)
			{
				info = pom->getInfo();
				fout << info << "\n";
				pom = pom->getNext();
			}
			fout.close();
        }
	}
	virtual void load(string fileName)
	{
		ifstream fin;
		fin.open(fileName);
		if (fin.is_open())
		{
			int ct;
			fin >> ct;

			if (ct != count)
			{
				count = 0;
				if (head != NULL)
				{
					Element<T>* current = head;
					Element<T>* temp = head->getNext();
					for (; current != tail; current = temp, temp = temp->getNext())
						delete current;
				}
				head = NULL; tail = NULL;
				T val;
				for (int i = 0; i < ct; i++)
				{
					fin >> val;
					push(val);
				}
			} else {
				Element<T>* pom = head;
				T val;
				for (int i = 0; i < count; i++)
				{
					fin >> val;
					pom->setInfo(val); 
					pom = pom->getNext();
				}
			}
			fin.close();
		}
	}

	template<class T1>
	friend ostream& operator<<(ostream& s, LinkedList<T1>& el);
	template <class T1>
    friend istream& operator>>(istream& s, LinkedList<T1>& el);
};

template<class T1> 
ostream& operator<<(ostream& s, LinkedList<T1>& el)
{
	Element<T1>* current;
	s << "\n{";
	for (current = el.head; current->getNext() != NULL; current = current->getNext())
		s << *current << ", ";
	s << *current;
	s << "\n}";
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

// ------------------------------------------------------------------------------------------------------------- LINKED LIST (100%) / STACK (100%) -----------------------------------------------------------------------------------------------------------------

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
		if(index<0 || index>=LinkedList<T>::count)

		if (index < 0) throw NegativeIndex("Negative index in operator [] ", index);
		if (index >= LinkedList<T>::count) throw TooLargeIndex("Too large index in operator [] ", index);

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
			if (predecessor != NULL) throw ElementNotExists("Stack predecessor in inserts not exists: ", "NULL");
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

	virtual void filter(T check, LinkedList<T>* dest, bool more)
	{
		for (Element<T>* cur = LinkedList<T>::head; cur != NULL; cur = cur->getNext())
		{
			if (cur->getInfo() > check && more)
	            dest->push(cur->getInfo());
			if (cur->getInfo() < check && !more)
	            dest->push(cur->getInfo());
		}
	}

	virtual void filter(T check, LinkedList<T>* dest, Element<T>* cur, bool more)
	{
		if (cur==NULL) return;
		if (cur->getInfo() > check && more)
	        dest->push(cur->getInfo());
		if (cur->getInfo() < check && !more)
	        dest->push(cur->getInfo());
		return filter(check, dest, cur->getNext(), more);
	}
};

// ------------------------------------------------------------------------------------------------------------- STACK (100%) / DOUBLE SIDED STACK (100%) -----------------------------------------------------------------------------------------------------------------

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
		if (index < 0) throw NegativeIndex("Negative index in operator [] ", index);
		if (index >= LinkedList<T>::count) throw TooLargeIndex("Too large index in operator [] ", index);

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
			if (predecessor != NULL) throw ElementNotExists("DoubleSidedStack predecessor in insert not exists: ", "NULL");
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
			if (LinkedList<T>::count == 1)
				LinkedList<T>::tail->setPrev(NULL);
			return p;
		}
        for (; p->getNext() != NULL &&  p->getNext()->getInfo() != value; p = p->getNext());
		if (p->getNext()->getInfo() == value)
		{
			Element<T>* res = p->getNext();
			p->setNext(res->getNext());
			if (res->getNext() != NULL) res->getNext()->setPrev(p);
			if (res->getNext() == NULL) LinkedList<T>::tail = p;
			res->setNext(NULL);
			res->setPrev(NULL);
			LinkedList<T>::count--;
        	return res;
		}
		return NULL;
	}

	// filter ищет по значению, поэтому нет смысла переопределять его для DoubleSidedStack
};

// ------------------------------------------------------------------------------------------------------------- DOUBLE SIDED STACK (100%) / CUSTOM STACK (100%) -----------------------------------------------------------------------------------------------------------------

template <class Customer>
class CustomStack : protected DoubleSidedStack<Customer>
{
public:
	CustomStack() : DoubleSidedStack<Customer>()
	{
		cout << "\nCustomStack class constructor";
	}
	virtual ~CustomStack()
	{
		cout << "\nCustomStack class destructor";
	}

	virtual Element<Customer>* operator[](int index)
	{
		return DoubleSidedStack<Customer>::operator[](index);
	}

	virtual Element<Customer>* push(Customer value)
	{
		Element<Customer>* pom = new Element<Customer>(value);
		if (LinkedList<Customer>::count == 0)
		{
			LinkedList<Customer>::head = LinkedList<Customer>::tail = pom;
			LinkedList<Customer>::count++;
			return pom;
		}
		pom->setNext(LinkedList<Customer>::head);
		if (pom->getNext() != NULL ) LinkedList<Customer>::head->setPrev(pom);
		LinkedList<Customer>::head = pom;
		LinkedList<Customer>::count++;
		return pom;
	}

	virtual Element<Customer>* pop()
	{
		if (LinkedList<Customer>::count == 0) return NULL;
		Element<Customer>* res = LinkedList<Customer>::head;
		if (LinkedList<Customer>::count == 1)
		{
			LinkedList<Customer>::head = LinkedList<Customer>::tail = NULL;
		}
		res->getNext()->setPrev(NULL);
		LinkedList<Customer>::head = res->getNext();
		res->setNext(NULL);
		LinkedList<Customer>::count--;
		return res;
	}

	virtual Element<Customer>* insert(Customer value, Element<Customer>* predecessor = NULL)
	{
		return DoubleSidedStack<Customer>::insert(value, predecessor);
	}

	virtual Element<Customer>* find(Customer value)
    {
        Element<Customer>* p = LinkedList<Customer>::head;
        for (; p->getInfo().lastname != value.lastname && p != NULL; p = p->getNext());
        return p;
	}

	virtual Element<Customer>* find(Customer value, Element<Customer>* el)
	{
		if (el->getInfo().lastname == value.lastname || el==NULL)
			return el;
		return find(value, el->getNext());
	}

	Element<Customer>* find(string lastName)
	{
		Element<Customer>* p = LinkedList<Customer>::head;
        for (; p->getInfo().lastname != lastName && p != NULL; p = p->getNext());
        return p;
	}

	Element<Customer>* find(string lastName, Element<Customer>* el)
	{
		if (el->getInfo().lastname == lastName || el==NULL)
			return el;
		return find(lastName, el->getNext());
	}

	virtual Element<Customer>* remove(Customer value)
	{
		return DoubleSidedStack<Customer>::remove(value);
	}

	virtual void filter(bool (*cmp)(Customer), LinkedList<Customer>* dest)
	{
		for (Element<Customer>* cur = LinkedList<Customer>::head; cur != NULL; cur = cur->getNext())
	        if (cmp(cur->getInfo()))
	            dest->push(cur->getInfo());
	}

	virtual void filter(bool (*cmp)(Customer), LinkedList<Customer>* dest, Element<Customer>* cur)
	{
		if (cur==NULL) return;
		if (cmp(cur->getInfo()))
			dest->push(cur->getInfo());
		return filter(cmp, dest, cur->getNext());
	}

	virtual void filter(Customer check, LinkedList<Customer>* dest, bool more = false)
	{
		for (Element<Customer>* cur = LinkedList<Customer>::head; cur != NULL; cur = cur->getNext())
		{
			if (cur->getInfo().averageCheckAmount > check.averageCheckAmount && more)
	            dest->push(cur->getInfo());
			if (cur->getInfo().averageCheckAmount < check.averageCheckAmount && !more)
	            dest->push(cur->getInfo());
		}
	}

	virtual void filter(Customer check, LinkedList<Customer>* dest,
					    Element<Customer>* cur, bool more = false)
	{
		if (cur==NULL) return;
		if (cur->getInfo().averageCheckAmount > check.averageCheckAmount && more)
	        dest->push(cur->getInfo());
		if (cur->getInfo().averageCheckAmount < check.averageCheckAmount && !more)
	        dest->push(cur->getInfo());
		return filter(check, dest, cur->getNext(), more);
	}

	virtual void save(string fileName)
	{
		ofstream fout(fileName);
        if (fout.is_open())
        {
			fout << LinkedList<Customer>::count << "\n";
			Element<Customer>* pom = LinkedList<Customer>::head;
			Customer info;
			for (int i = 0; i < LinkedList<Customer>::count; i++)
			{
				info = pom->getInfo();
				fout << info << "\n";
				pom = pom->getNext();
			}
			fout.close();
        }
	}
	virtual void load(string fileName)
	{
		ifstream fin;
		fin.open(fileName);
		if (fin.is_open())
		{
			int ct;
			fin >> ct;

			if (ct != LinkedList<Customer>::count)
			{
				LinkedList<Customer>::count = 0;
				if (LinkedList<Customer>::head != NULL)
				{
					Element<Customer>* current = LinkedList<Customer>::head;
					Element<Customer>* temp = LinkedList<Customer>::head->getNext();
					for (; current != LinkedList<Customer>::tail; current = temp, temp = temp->getNext())
						delete current;
				}
				LinkedList<Customer>::head = NULL; LinkedList<Customer>::tail = NULL;
				Customer val;
				for (int i = 0; i < ct; i++)
				{
					fin >> val;
					push(val);
				}
			} else {
				Element<Customer>* pom = LinkedList<Customer>::head;
				Customer val;
				for (int i = 0; i < LinkedList<Customer>::count; i++)
				{
					fin >> val;
					pom->setInfo(val); 
					pom = pom->getNext();
				}
			}
			fin.close();
		}
	}

	template<class T1>
	friend ostream& operator<<(ostream& s, CustomStack<T1>& el);
	template <class T1>
    friend istream& operator>>(istream& s, CustomStack<T1>& el);
};

template<class T1> 
ostream& operator<<(ostream& s, CustomStack<T1>& el)
{
	Element<T1>* current;
	s << "\n{";
	for (current = el.head; current->getNext() != NULL; current = current->getNext())
		s << *current << ", ";
	s << *current;
	s << "\n}";
	return s;
}

template <class T1>
istream& operator>>(istream& s, CustomStack<T1>& el)
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

// ------------------------------------------------------------------------------------------------------------- CUSTOM STACK (100%) / CUSTOMER (100%) -----------------------------------------------------------------------------------------------------------------

class Customer
{
public:
	string firstname;
	string lastname;
	string city;
	string street;
	int houseNumber;
	int apartmentNumber;
	int accountNumber;
	int averageCheckAmount;

	Customer(string Firstname = "unknown", string Lastname = "unknown",
			 string City = "unknown", string Street = "unknown",
			 int HouseNumber = 0, int ApartmentNumber = 0,
			 int AccountNumber = 0, int AverageCheckAmount = 0)
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

	~Customer() { }

	bool operator==(Customer cus)
	{
		return firstname == cus.firstname && 
			   lastname == cus.lastname &&
			   city == cus.city &&
			   street == cus.street &&
			   houseNumber == cus.houseNumber &&
			   apartmentNumber == cus.apartmentNumber &&
			   accountNumber == cus.accountNumber &&
			   averageCheckAmount == cus.averageCheckAmount;		
	}

	bool operator!=(Customer cus)
	{
		return firstname != cus.firstname || 
			   lastname != cus.lastname ||
			   city != cus.city ||
			   street != cus.street ||
			   houseNumber != cus.houseNumber ||
			   apartmentNumber != cus.apartmentNumber ||
			   accountNumber != cus.accountNumber ||
			   averageCheckAmount != cus.averageCheckAmount;		
	}

	bool operator<(Customer cus)
	{
		return averageCheckAmount < cus.averageCheckAmount;
	}

	bool operator>(Customer cus)
	{
		return averageCheckAmount > cus.averageCheckAmount;
	}

	friend ostream& operator<<(ostream& s, Customer& value);
	friend istream& operator>>(istream& s, Customer& value);
};

ostream& operator<<(ostream& s, Customer& value)
{
	if (typeid(s) == typeid(ofstream))
	{
		s << value.firstname << " "
		  << value.lastname << " "
		  << value.city << " "
		  << value.street << " "
		  << value.houseNumber << " "
		  << value.apartmentNumber << " "
		  << value.accountNumber << " "
		  << value.averageCheckAmount << "\n";
	} else 
	{
		s <<"("<<value.firstname<<", "<<value.lastname<<", "
		  <<value.city<<", "<<value.street<<", "<<value.houseNumber<<", "
	  	  << value.apartmentNumber<<", "<<value.accountNumber<<", "
		  <<value.averageCheckAmount<<")";
	}
	return s;
}

istream& operator>>(istream& s, Customer& value)
{
	if (typeid(s) == typeid(ifstream))
	{
		s >> value.firstname
		  >> value.lastname
		  >> value.city
		  >> value.street
		  >> value.houseNumber
		  >> value.apartmentNumber
		  >> value.accountNumber
		  >> value.averageCheckAmount;
	} else 
	{
		cout << "\nEnter fields: ";
		cout << "\nFirstname (string): ";
		s >> value.firstname;
		cout << "\nLastname (string): ";
		s >> value.lastname;
		cout << "\nCity (string): ";
		s >> value.city;
		cout << "\nStreet (string): ";
		s >> value.street;
		cout << "\nHouse Number (int): ";
		s >> value.houseNumber;
		cout << "\nApartment Number (int): ";
		s >> value.apartmentNumber;
		cout << "\nAccount Number (int): ";
		s >> value.accountNumber;
		cout << "\nAverage Check Amount (int): ";
		s >> value.averageCheckAmount;
	}
	return s;
}

// ------------------------------------------------------------------------------------------------------------- CUSTOMER (100%) / MAIN (all checked) -----------------------------------------------------------------------------------------------------------------

bool f(double d) { return d>10; }

bool g(Customer c) { return c.averageCheckAmount<500; }

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

	// // Ввод значений в List
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

	// // Ввод значений в List
	// cout << *list;
	// cin >> *list;
	// cout << *list;

	list->filter(f, filteredList);
	cout << *filteredList << " filtered list by double > 10";

	list->filter(f, filteredList, el);
	cout << *filteredList << " filtered list + by double > 10 recursion after el";

	cout << "\n---------------------------------------------------------------------------DYNAMIC_CAST------------------------------------------------------------------------------------------";

	DoubleSidedStack<double>* castedList = dynamic_cast<DoubleSidedStack<double>*>(list);
	cout << *castedList;

	delete list;
	delete filteredList;

	cout << "\n---------------------------------------------------------------------------MY ClASS WORK------------------------------------------------------------------------------------------";
	CustomStack<Customer> custom;
	Customer c1("Stepan", "Aniskov", "Moscow", "Taganskaya", 123, 13, 1, 150);
	Customer c2("Ivan", "Ivanov", "Moscow", "Proletarskaya", 56, 140, 2, 750);
	Customer c3("Anton", "Dudetski", "Kalach", "Leninskaya", 3, 1, 3, 370);
	Customer c4("Igor", "Ivanov", "Jeneva", "Kloshevskaya", 40, 32, 4, 2720);
	Customer c5("Pasha", "Isanov", "Rio", "Whatevskaya", 1, 2, 5, 525);
	Customer customers[] = {c1, c2, c3, c4};
	for (int i = 0; i<4; i++)
		custom.push(customers[i]);

	cout << custom << " custom";
	cout << endl << "operator[](2): " << *custom.operator[](2);
	cout << endl << "operator[](0): " << *custom.operator[](0);
	cout << endl << "pop(): " << *custom.pop();
	Element<Customer>* customEl = custom.find(c2);
	cout << endl << "customEl = find(c2): " << *customEl;
	cout << endl << "find(c4, c2): " << *custom.find(c4, customEl);
	cout << custom << " custom";
	custom.insert(c5, custom.find(c4));
	cout << custom << " custom after insert(c5, find(c4))";
	custom.remove(c1);
	cout << c1;
	cout << custom << " custom after remove(c1)";

	LinkedList<Customer>* filteredCustomList = new DoubleSidedStack<Customer>();

	// // Ввод значений в Custom
	// cout << custom;
	// cin >> custom;
	// cout << custom;

	custom.filter(g, filteredCustomList);
	cout << *filteredCustomList << " filtered custom list by average check amount < 500";

	custom.filter(g, filteredCustomList, custom.find(c3));
	cout << *filteredCustomList << " filtered custom list by average check amount < 500 recursion after c3";

	cout << "\n---------------------------------------------------------------------------FILE SAVE/LOAD------------------------------------------------------------------------------------------";

	custom.save("list.txt");
	filteredCustomList->load("list.txt");
	cout << *filteredCustomList;

	delete filteredCustomList;

	cout << "\n---------------------------------------------------------------------------PROGRAM END------------------------------------------------------------------------------------------";

	return 0;
}