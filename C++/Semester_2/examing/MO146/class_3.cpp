using namespace std;

#include <iostream>
#include <cstring>

class EmptyArray;
class NegativeIndex;
class TooLargeIndex;

template<class T>
class MyArrayParentTemplate
{
protected:
    //сколько памяти выделено?
    int capacity;
    //количество элементов - сколько памяти используем
    int count;
    //массив
    T* ptr;
public:
    //конструкторы и деструктор
    MyArrayParentTemplate(int Dimension = 100)
    {
        cout << "\nMyArrayParentTemplate constructor";
        //здесь должно быть выделение памяти
        capacity = Dimension;
        count = 0;
    }

    //деструктор
    ~MyArrayParentTemplate()
    {
        cout << "\nMyArrayParentTemplate destructor";
    }

    //обращение к полям
    int Capacity() { return capacity; }
    int Size() { return count; }

    //добавление нового значения
    virtual void push(T value) = 0;
    //удаление элемента
    virtual T pop() = 0;

};

template <class T>
class MyArrayChildTemplate : public MyArrayParentTemplate<T>
{
public:
	MyArrayChildTemplate(int Dimension = 100) : MyArrayParentTemplate<T>(Dimension)
	{
		cout << "\nMyArrayChildTemplate constructor" << endl;
		MyArrayParentTemplate<T>::ptr = new T[Dimension];
	}

    MyArrayChildTemplate(T* arr, int len) : MyArrayParentTemplate<T>(len*2)
	{
		cout << "\nMyArrayChildTemplate constructor" << endl;
		MyArrayParentTemplate<T>::count = len;
		MyArrayParentTemplate<T>::ptr = new T[len*2];
		for(int i = 0; i<len; i++) {
			MyArrayParentTemplate<T>::ptr[i] = arr[i];
		}
	}

	MyArrayChildTemplate(const MyArrayChildTemplate& P) : MyArrayParentTemplate<T>(P)
	{
		cout << "\nMyArrayChildTemplate copy constructor" << endl;
        MyArrayParentTemplate<T>::capacity = P.capacity;
        MyArrayParentTemplate<T>::count = P.count;
        MyArrayParentTemplate<T>::ptr = new T[MyArrayParentTemplate<T>::capacity];
        for(int i = 0; i < MyArrayParentTemplate<T>::count; i++) {
            MyArrayParentTemplate<T>::ptr[i] = P.ptr[i];
        }
	}

	~MyArrayChildTemplate()
	{
		cout << "\nMyArrayChildTemplate destructor" << endl;
		if (MyArrayParentTemplate<T>::ptr != NULL)
		{
			delete[] MyArrayParentTemplate<T>::ptr;
			MyArrayParentTemplate<T>::ptr = NULL;
		}
	}

	void push(T value)
	{
		if(MyArrayParentTemplate<T>::count < MyArrayParentTemplate<T>::capacity) {
            for (int i = MyArrayParentTemplate<T>::count++; i > 0; --i) {
                MyArrayParentTemplate<T>::ptr[i] = MyArrayParentTemplate<T>::ptr[i-1];
            }
            MyArrayParentTemplate<T>::ptr[0] = value;
		} else {
			T* pom = new T[MyArrayParentTemplate<T>::capacity*2];
			for (int i = 0; i<MyArrayParentTemplate<T>::count; i++) {
				pom[i+1] = MyArrayParentTemplate<T>::ptr[i];
			}
			delete[] MyArrayParentTemplate<T>::ptr;
			MyArrayParentTemplate<T>::ptr = pom;
			MyArrayParentTemplate<T>::ptr[0] = value;
			MyArrayParentTemplate<T>::capacity*=2;
		}
	}

	T pop()
	{
		if (MyArrayParentTemplate<T>::count == 0) throw EmptyArray("Array is empty, nothing to pop");

		return MyArrayParentTemplate<T>::ptr[MyArrayParentTemplate<T>::count--];
	}

    T& operator[](int i)
    {   
        if (i >= MyArrayParentTemplate<T>::count) throw TooLargeIndex("Index in operator[] too large", i);
        if (i < 0) throw NegativeIndex("Negative index in operator[]", i);
        return MyArrayParentTemplate<T>::ptr[i];
    }

    T* find(T value)
    {
        for (int i = 0; i < MyArrayParentTemplate<T>::count; i++) {
            if (MyArrayParentTemplate<T>::ptr[i] == value) {
                return &MyArrayParentTemplate<T>::ptr[i];
            }
        }
        cout << "No element `" << value << "' in array. Return NULL\n";
        return NULL;
    }

    MyArrayChildTemplate<T> no_duplicates()
    {
        MyArrayChildTemplate<T> result(*this);
        for (int i = 0; i < result.count; ++i) {
            for (int j = i+1; j < result.count; ++j) {
                cout << result.ptr[i] << " " << result.ptr[j] << " " << (result.ptr[i] == result.ptr[j]) << endl;
                if (result.ptr[i] == result.ptr[j]) {
                    for (int k = j--; k < result.count - 1; ++k) {
                        result.ptr[k] = result.ptr[k + 1];
                    }
                    result.count--;
                }
            }
        }
        return result;
    }

    void print()
    {
        cout << "[";
        for (int i = 0; i< MyArrayParentTemplate<T>::count-1; i++) {
            cout << MyArrayParentTemplate<T>::ptr[i] << ", ";
        }
        if ( MyArrayParentTemplate<T>::count > 0) cout << MyArrayParentTemplate<T>::ptr[MyArrayParentTemplate<T>::count-1];
        cout << "]\n";
    }
};

class Exception : public exception
{
protected:

	char *str;

public:
    Exception()
	{
		str = NULL;
	}

	Exception(const char *s)
	{
		str = new char[strlen(s) + 1];
		strcpy(str, s);
	}

	Exception(char *s)
	{
		str = new char[strlen(s) + 1];
		strcpy(str, s);
	}

	Exception(const Exception &e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy(str, e.str);
	}

	~Exception()
	{
		delete[] str;
	}

	virtual void print()
	{
		cout << "Exception: " << str << what();
	}
};

class EmptyArray : public Exception
{
protected:
	char* str;
public:
	EmptyArray() : Exception() {}

	EmptyArray(const char *s) : Exception(s) {}

	EmptyArray(char *s) : Exception(s) {}

	EmptyArray(const EmptyArray &e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy(str, e.str);
	}

	virtual void print()
	{
		cout << "EmptyArray: " << str << what();
	}
};

class IndexOutOfBounds : public Exception
{
protected:
	int index;
public:
    IndexOutOfBounds() : Exception() {}

    IndexOutOfBounds(const char* s, int Index) : Exception(s)
	{
		index = Index;
	}

	IndexOutOfBounds(char* s, int Index) : Exception(s)
	{
		index = Index;
	}
	
	IndexOutOfBounds(const IndexOutOfBounds& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy(str, e.str);
	}

	void print()
	{
		cout << "IndexOutOfBounds: " << str << what();
	}
};

class TooLargeIndex : public IndexOutOfBounds
{
protected:
	int index;
public:
    TooLargeIndex() : IndexOutOfBounds() {}

    TooLargeIndex(const char* s, int Index) : IndexOutOfBounds(s, Index)
	{
		index = Index;
	}

	TooLargeIndex(char* s, int Index) : IndexOutOfBounds(s, Index)
	{
		index = Index;
	}
	
	TooLargeIndex(const TooLargeIndex& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy(str, e.str);
	}

	void print()
	{
		cout << "TooLargeIndex: " << str << what();
	}
};

class NegativeIndex : public IndexOutOfBounds
{
protected:
	int index;
public:
    NegativeIndex() : IndexOutOfBounds() {}

    NegativeIndex(const char* s, int Index) : IndexOutOfBounds(s, Index)
	{
		index = Index;
	}

	NegativeIndex(char* s, int Index) : IndexOutOfBounds(s, Index)
	{
		index = Index;
	}
	
	NegativeIndex(const NegativeIndex& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy(str, e.str);
	}

	void print()
	{
		cout << "NegativeIndex: " << str << what();
	}
};

int main()
{
    MyArrayChildTemplate<double> list;
    for (int i = 0; i<7; ++i) {
        list.push(i);
        list.push(3);
        list.push(8-i);
    }
    list.print();
    MyArrayChildTemplate<double> copy = list.no_duplicates();
    copy.print();

    cout << copy.find(42) << endl;

    char c; cin >> c;
    return 0;
}