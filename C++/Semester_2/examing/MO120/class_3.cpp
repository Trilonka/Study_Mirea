using namespace std;

#include <iostream>

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
		
		ptr = new T[Dimension];
		capacity = Dimension;
		count = 0;
	}

	MyArrayParentTemplate(T* arr, int len)
	{
		cout << "\nMyArrayParentTemplate constructor" << endl;
		capacity = (len >= 100) ? len*2 : 100;
		count = len;
		ptr = new T[capacity];
		for(int i = 0; i<len; i++) {
			ptr[i] = arr[i];
		}
	}

	MyArrayParentTemplate(const MyArrayParentTemplate& P)
	{
		cout << "\nMyArrayParentTemplate copy constructor" << endl;
        capacity = P.capacity;
        count = P.count;
        ptr = new T[capacity];
        for(int i = 0; i < count; i++) {
            ptr[i] = P.ptr[i];
        }
    }

	//деструктор
	~MyArrayParentTemplate()
	{
		cout << "\nMyArrayParentTemplate destructor";
		if (ptr != NULL)
		{
			delete[] ptr;
			ptr = NULL;
		}
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
private:
	int hash_code(const char* key)
	{
		int code = 0;
		int i = -1;
		while (key[++i]!='\0') {
			code += key[i];
		}
		if (code >= MyArrayParentTemplate<T>::count) throw "Key not exists";
		return code;
	}
public:
	MyArrayChildTemplate(int Dimension = 100) : MyArrayParentTemplate<T>(Dimension)
	{
		cout << "\nMyArrayChildTemplate constructor" << endl;
	}

	MyArrayChildTemplate(T* arr, int len) : MyArrayParentTemplate<T>(arr, len)
	{
		cout << "\nMyArrayChildTemplate constructor" << endl;
	}

	MyArrayChildTemplate(const MyArrayChildTemplate& P) : MyArrayParentTemplate<T>(P)
	{
		cout << "\nMyArrayChildTemplate copy constructor" << endl;
	}

	~MyArrayChildTemplate()
	{
		cout << "\nMyArrayChildTemplate destructor" << endl;
	}

	T& operator()(const char* key)
	{
		if (key[0]=='\0') throw "Empty key in operator()";

		int code = hash_code(key);

		return MyArrayParentTemplate<T>::ptr[code];
	}

	void push(T value)
	{
		if(MyArrayParentTemplate<T>::count < MyArrayParentTemplate<T>::capacity) {
			MyArrayParentTemplate<T>::ptr[MyArrayParentTemplate<T>::count++] = value;
		} else {
			T* pom = new T[MyArrayParentTemplate<T>::capacity*2];
			for (int i = 0; i<MyArrayParentTemplate<T>::count; i++) {
				pom[i] = MyArrayParentTemplate<T>::ptr[i];
			}
			delete[] MyArrayParentTemplate<T>::ptr;
			MyArrayParentTemplate<T>::ptr = pom;
			MyArrayParentTemplate<T>::ptr[MyArrayParentTemplate<T>::count++] = value;
			MyArrayParentTemplate<T>::capacity*=2;
		}
	}

	T pop()
	{
		if (MyArrayParentTemplate<T>::count == 0) throw "Nothing to pop";
		MyArrayParentTemplate<T>::count--;
		return MyArrayParentTemplate<T>::ptr[MyArrayParentTemplate<T>::count];
	}

	T pop(const char* key)
	{
		if (MyArrayParentTemplate<T>::count == 0) throw "Nothing to pop";

		int code = hash_code(key);

		T result =  MyArrayParentTemplate<T>::ptr[code];

		for(int i = code; i<MyArrayParentTemplate<T>::count-1; i++) {
			MyArrayParentTemplate<T>::ptr[code] = 
				 MyArrayParentTemplate<T>::ptr[code+1];
		}

		MyArrayParentTemplate<T>::count--;
		return result;
	}
};

int main()
{
	MyArrayChildTemplate<double> child;
	for (int i = 0; i<940; i++) {
		child.push(i*3.2);
	}

	MyArrayParentTemplate<double>* parent_p = &child;

	MyArrayChildTemplate<double>* child_p = dynamic_cast<MyArrayChildTemplate<double>*>(parent_p);

	cout << child_p->operator()("hi") << " on position: " << child_p->operator()("hi") / 3.2 << endl;

	cout << child_p->pop("hi") << endl;

	cout << child_p->operator()("hi") << " on position: " << child_p->operator()("hi") / 3.2 << endl;

	return 0;
}