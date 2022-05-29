#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

class Exception : public exception
{
protected:
	//сообщение об ошибке
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

class NegativeSize : public Exception
{
protected:
	int size;
public:
    NegativeSize() : Exception() {}

	NegativeSize(const char* s, int Size) : Exception(s)
	{
		size = Size;
	}
	
	NegativeSize(char* s, int Size) : Exception(s)
	{
		size = Size;
	}

	NegativeSize(const NegativeSize& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy(str, e.str);
	}

	void print()
	{
		cout << "WrongSize: " << str << what();
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

class ElementNotExists : public Exception 
{
protected:
    char* info;
public:
    ElementNotExists() : Exception() {}

	ElementNotExists(const char* s, const char* Info) : Exception(s)
	{
		info = new char[strlen(Info) + 1];
		strcpy(info, Info);
	}
	
	ElementNotExists(char* s, char* Info) : Exception(s)
	{
		info = new char[strlen(Info) + 1];
		strcpy(info, Info);
	}

	ElementNotExists(const ElementNotExists& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy(str, e.str);
	}

	void print()
	{
		cout << "Element not exists: " << str << what();
	}
};