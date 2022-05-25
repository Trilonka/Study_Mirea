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

class WrongDimensions : public Exception
{
protected:
	int r_1;
    int c_1;
public:
    WrongDimensions() : Exception() {}

	WrongDimensions(const char* s, int R_1, int C_1) : Exception(s)
	{
		r_1 = R_1;
        c_1 = C_1;
	}
	
	WrongDimensions(char* s, int R_1, int C_1) : Exception(s)
	{
		r_1 = R_1;
        c_1 = C_1;
	}

	WrongDimensions(const WrongDimensions& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy(str, e.str);
	}

	void print()
	{
		cout << "WrongDimensions: " << str << what();
	}

};

class WrongSize : public WrongDimensions
{
protected:
	int r_2;
    int c_2;
public:
    WrongSize() : WrongDimensions() {}

	WrongSize(const char* s, int r_1, int c_1, int R_2, int C_2) : WrongDimensions(s, r_1, c_1)
	{
		r_2 = R_2;
        c_2 = C_2;
	}
	
	WrongSize(char* s, int r_1, int c_1, int R_2, int C_2) : WrongDimensions(s, r_1, c_1)
	{
		r_2 = R_2;
        c_2 = C_2;
	}

	WrongSize(const WrongSize& e)
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
	int r_i; int c_i;
public:
    IndexOutOfBounds() : Exception() {}

    IndexOutOfBounds(const char* s, int R_i, int C_i) : Exception(s)
	{
		r_i = R_i;
        c_i = C_i;
	}

	IndexOutOfBounds(char* s, int R_i, int C_i) : Exception(s)
	{
		r_i = R_i;
        c_i = C_i;
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
	int r_i; int c_i;
public:
    TooLargeIndex() : IndexOutOfBounds() {}

    TooLargeIndex(const char* s, int R_i, int C_i) : IndexOutOfBounds(s, R_i, C_i)
	{
		r_i = R_i;
        c_i = C_i;
	}

	TooLargeIndex(char* s, int R_i, int C_i) : IndexOutOfBounds(s, R_i, C_i)
	{
		r_i = R_i;
        c_i = C_i;
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
	int r_i; int c_i;
public:
    NegativeIndex() : IndexOutOfBounds() {}

    NegativeIndex(const char* s, int R_i, int C_i) : IndexOutOfBounds(s, R_i, C_i)
	{
		r_i = R_i;
        c_i = C_i;
	}

	NegativeIndex(char* s, int R_i, int C_i) : IndexOutOfBounds(s, R_i, C_i)
	{
		r_i = R_i;
        c_i = C_i;
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

class WrongPascalDimension : public WrongDimensions
{
protected:
	int size;
public:
    WrongPascalDimension() : WrongDimensions() {}

	WrongPascalDimension(const char* s, int Size) : WrongDimensions(s, size*2-1, size)
	{
		size = Size;
	}
	
	WrongPascalDimension(char* s, int Size) : WrongDimensions(s, size*2-1, size)
	{
		size = Size;
	}

	WrongPascalDimension(const WrongPascalDimension& e)
	{
		str = new char[strlen(e.str) + 1];
		strcpy(str, e.str);
	}

	void print()
	{
		cout << "WrongPascalDimension: " << str << what();
	}
};