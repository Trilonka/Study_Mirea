#include "Exception.cpp"

template <class T>
class BaseMatrix
{
protected:
    T** ptr;
    int height;
    int width;

public:
    BaseMatrix(int Height = 2, int Width = 2)
    {
        if (Height <= 0 || Width <= 0)
            throw WrongDimensions("Non-positive size of matrix ", Height, Width);
        height = Height;
        width = Width;
        ptr = new T* [height];
        for (int i = 0; i < height; i++)
            ptr[i] = new T[width];
    }

    BaseMatrix(const BaseMatrix& M)
    {
        height = M.height;
        width = M.width;
        ptr = new T* [height];
        for (int i = 0; i < height; i++)
        {
            ptr[i] = new T[width];
            for (int j = 0; j < width; j++)
                ptr[i][j] = M.ptr[i][j];
        }
    }

    ~BaseMatrix()
    {
        if (ptr != NULL)
        {
            for (int i = 0; i < height; i++)
                delete[] ptr[i];
            delete[] ptr;
            ptr = NULL;
        }
    }

    virtual BaseMatrix operator=(BaseMatrix M)
    {
        if (M.height == height && M.width == width)
        {
            for (int i = 0; i < height; i++)
                for (int j = 0; j < width; j++)
                    ptr[i][j] = M.ptr[i][j];
        }
        else
        {
            throw WrongSize("Different sizes of matrices in operator= ", height, width, M.height, M.width);
        }

        return* this;
    }

    T* operator[](int index)
    {
        if (index < 0)
        {
            throw NegativeIndex("Negative index in operator[] ", index, -1);
        }
        if (index >= height)
        {
            throw TooLargeIndex("Too large index in operator[] ", index, -1);
        }
        return ptr[index];
    }

    T& operator()(int row, int column)
    {
        if (row < 0 || column < 0)
        {
            throw NegativeIndex("Negative index in operator() ", row, column);
        }
        if (row >= height || column >= width)
        {
            throw TooLargeIndex("Too large index in operator() ", row, column);
        }
        return ptr[row][column];
    }

    BaseMatrix operator+(BaseMatrix M)
    {
        if (width != M.width || height != M.height)
        {
            throw WrongSize("Different sizes of matrices in operator+ ", height, width, M.height, M.width);
        }
        BaseMatrix res = *this;
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                res.ptr[i][j] += M.ptr[i][j];
        return res;
    }

    BaseMatrix operator+(T value)
    {
        BaseMatrix res = *this;
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                res.ptr[i][j] += value;
        return res;
    }

    void print()
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
                cout << ptr[i][j] << " ";
            cout << "\n";
        }
    }

    template <class T1>
    friend ostream& operator<<(ostream& ustream, BaseMatrix<T1>& obj);
    template <class T1>
    friend istream& operator>>(istream& ustream, BaseMatrix<T1>& obj);
};

template <class T1>
ostream& operator<<(ostream& ustream, BaseMatrix<T1>& obj)
{
    if (typeid(ustream) == typeid(ofstream))
    {
        ustream << obj.height << " " << obj.width << "\n";
        for (int i = 0; i < obj.height; i++)
        {
            for (int j = 0; j < obj.width; j++)
            {
                ustream << obj.ptr[i][j] << "\n";
            }
        }
        return ustream;
    }

    for (int i = 0; i < obj.height; i++)
    {
        for (int j = 0; j < obj.width; j++)
        {
            ustream << obj.ptr[i][j] << " ";
        }
        ustream << "\n";
    }

    return ustream;
}

template <class T1>
istream& operator>>(istream& ustream, BaseMatrix<T1>& obj)
{
    int height = -1, width = -1;
    if (typeid(ustream) == typeid(ifstream))
        ustream >> height >> width;

    if (height>=0 && width>=0 && height!=obj.height && obj.width!=width)
    {
        for (int i = 0; i < obj.height; i++)
                delete[] obj.ptr[i];
            delete[] obj.ptr;
            obj.height = height;
            obj.width = width;
            obj.ptr = new T1* [height];
            for (int i = 0; i < height; i++)
                obj.ptr[i] = new T1[width];
    }

    for (int i = 0; i < obj.height; i++)
        for (int j = 0; j < obj.width; j++)
            ustream >> obj.ptr[i][j];

    return ustream;
}

ostream& my_manip(ostream& s)
{
    s.precision(4);
    //s.fill('%');
    //s.width(10);
    return s;
}

template <class T>
class Matrix : public BaseMatrix<T>
{
public:
    Matrix(int Height = 2, int Width = 2) : BaseMatrix<T>(Height, Width) {}
    Matrix(const Matrix& M)
    {
        if (BaseMatrix<T>::ptr != NULL)
        {
            for (int i = 0; i < BaseMatrix<T>::height; i++)
                delete[] BaseMatrix<T>::ptr[i];
            delete[] BaseMatrix<T>::ptr;
            BaseMatrix<T>::ptr = NULL;
        }

        BaseMatrix<T>::height = M.height;
        BaseMatrix<T>::width = M.width;
        BaseMatrix<T>::ptr = new T* [BaseMatrix<T>::height];
        for (int i = 0; i < BaseMatrix<T>::height; i++)
        {
           BaseMatrix<T>::ptr[i] = new T[BaseMatrix<T>::width];
            for (int j = 0; j < BaseMatrix<T>::width; j++)
                BaseMatrix<T>::ptr[i][j] = M.ptr[i][j];
        }
    }

    ~Matrix() {}

    void generateRandMatrix(int border = 201)
    {
        srand(time(NULL));
        for (int i = 0; i < BaseMatrix<T>::height; i++)
        {
            for (int j = 0; j < BaseMatrix<T>::width; j++)
            {
                BaseMatrix<T>::ptr[i][j] = rand() % border - border/2;
            }
        }
    }

    Matrix<T> pascal_romb(int size = 3) // функция, указанная в варианте
    {
        if (size < 1)
            throw WrongPascalDimension("Wrong pascal triangle size ", size);
        Matrix<T> pom(size*2-1, size);
        int k = 1;
        for (int i = 0; i < pom.height/2+1; i++)
        {
            pom.ptr[i][0] = 1;
            for (int j = 1; j < pom.width; j++)
            {
                if (j < k)
                    pom.ptr[i][j] = pom.ptr[i-1][j-1] + pom.ptr[i-1][j];
                else 
                    pom.ptr[i][j] = 0;
            }
            k++;
        }
        k = 1;
        for (int i = pom.height-1; i > pom.height/2; i--)
        {
            pom.ptr[i][0] = 1;
            for (int j = 1; j < pom.width; j++)
            {
                if (j < k)
                    pom.ptr[i][j] = pom.ptr[i+1][j-1] + pom.ptr[i+1][j];
                else 
                    pom.ptr[i][j] = 0;
            }
            k++;
        }
        return pom;
    }
};


int main()
{
    try
    {
        my_manip(cout);
        BaseMatrix<double> BM1(5,7), BM2(5,7), BM3(3,3);
        for (int i = 0; i<5; i++)
        {
            for (int j = 0; j<7; j++)
            {
                BM1[i][j] = i*j-0.7422321;
                BM2[i][j] = 2*i - j + 1.55;
            }
        }
        BM1 = BM1 + BM2;
        cout << BM1 << endl;

        Matrix<double> M(4,3);

        M.generateRandMatrix();
        cout << M << endl;
        
        BaseMatrix<double> K = M.pascal_romb(6);
        K.print();
        cout << endl;

        // работа с файлом

        ofstream fout("matrix.txt");
        if (fout.is_open())
        {
            fout << M;
            fout.close();
        }
        ifstream fin;
        fin.open("matrix.txt");
        if (fin.is_open())
        {
            fin >> M;
            fin.close();
        }
        cout << M;

        BM3 = BM2; // вызовет WrongSize Exception
    }
    catch (WrongSize e)
    {
        e.print();
    }
    catch (WrongPascalDimension e)
    {
        e.print();
    }
    catch (WrongDimensions e)
    {
        e.print();
    }
    catch (IndexOutOfBounds e)
    {
        e.print();
    }
    catch (Exception e)
    {
        e.print();
    }
}
