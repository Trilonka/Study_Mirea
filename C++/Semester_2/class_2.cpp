#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class MyArrayParent
{
protected:
	//СЃРєРѕР»СЊРєРѕ РїР°РјСЏС‚Рё РІС‹РґРµР»РµРЅРѕ?
	int capacity;
	//РєРѕР»РёС‡РµСЃС‚РІРѕ СЌР»РµРјРµРЅС‚РѕРІ - СЃРєРѕР»СЊРєРѕ РїР°РјСЏС‚Рё РёСЃРїРѕР»СЊР·СѓРµРј
	int count;
	//РјР°СЃСЃРёРІ
	double* ptr;
public:
	//РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂС‹ Рё РґРµСЃС‚СЂСѓРєС‚РѕСЂ
	MyArrayParent(int Dimension = 1000)
	{
		cout << "\nMyArrayParent constructor" << endl;
		ptr = new double[Dimension];
		capacity = Dimension;
		count = 0;
	}
	//РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ РїСЂРёРЅРёРјР°РµС‚ СЃСѓС‰РµСЃС‚РІСѓСЋС‰РёР№ РјР°СЃСЃРёРІ
	MyArrayParent(double* arr, int len)
	{
		cout << "\nMyArrayParent constructor" << endl;
		capacity = (len >= 1000) ? len<<1 : 1000;
		count = len;
		ptr = new double[capacity];
		for(int i = 0; i<len; i++) {
			ptr[i] = arr[i];
		}
	}

    MyArrayParent(const MyArrayParent& P)
	{
        capacity = P.capacity;
        count = P.count;
        ptr = new double[capacity];
        for(int i = 0; i < count; i++) {
            ptr[i] = P.ptr[i];
        }
    }

    MyArrayParent operator=(const MyArrayParent& P)
	{
        if(capacity < P.capacity) {
			ptr = new double[P.capacity];
        }
		count = P.count;
        for(int i = 0; i< count; i++) {
            ptr[i] = P.ptr[i];
        }
        return *this;
    }

	//РґРµСЃС‚СЂСѓРєС‚РѕСЂ
	~MyArrayParent()
	{
		//cout << "\nMyArrayParent destructor";
		if (ptr != NULL)
		{
			delete[] ptr;
			ptr = NULL;
		}
	}

	//РѕР±СЂР°С‰РµРЅРёРµ Рє РїРѕР»СЏРј
	int Capacity() { return capacity; }
	int Size() { return count; }
	double GetComponent(int index)
	{
		if (index >= 0 && index < count)
			return ptr[index];
		//СЃРіРµРЅРµСЂРёСЂРѕРІР°С‚СЊ РёСЃРєР»СЋС‡РµРЅРёРµ, РµСЃР»Рё РёРЅРґРµРєСЃ РЅРµРїСЂР°РІРёР»СЊРЅС‹Р№
		return -1;
	}
	void SetComponent(int index, double value)
	{
		if (index >= 0 && index < count)
			ptr[index] = value;
		//СЃРіРµРЅРµСЂРёСЂРѕРІР°С‚СЊ РёСЃРєР»СЋС‡РµРЅРёРµ, РµСЃР»Рё РёРЅРґРµРєСЃ РЅРµРїСЂР°РІРёР»СЊРЅС‹Р№
	}

	//РґРѕР±Р°РІР»РµРЅРёРµ РІ РєРѕРЅРµС† РЅРѕРІРѕРіРѕ Р·РЅР°С‡РµРЅРёСЏ
	virtual void push(double value)
	{
		if(count < capacity) {
			ptr[count++] = value;
		}
	}

	//СѓРґР°Р»РµРЅРёРµ СЌР»РµРјРµРЅС‚Р° СЃ РєРѕРЅС†Р°
	void RemoveLastValue()
	{
		if (count > 0) {
			count--;
		}
	}

	double& operator[](int index)
	{
		return ptr[index];
		//РїРµСЂРµРіСЂСѓР·РєР° РѕРїРµСЂР°С‚РѕСЂР° []
	}

	void print()
	{
		cout << "\nMyArrParent, size: " << count<<", values: {";
		int i = 0;
		for (i = 0; i < count; i++)
		{
			cout << ptr[i];
			if (i != count - 1)
				cout << ", ";
		}
		cout << "}" << endl;
	}
};

class MyArrayChild : public MyArrayParent
{
public:
	//РёСЃРїРѕР»СЊР·СѓРµРј РєРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ СЂРѕРґРёС‚РµР»СЏ. РќСѓР¶РЅРѕ Р»Рё С‡С‚Рѕ-С‚Рѕ РµС‰С‘?
	MyArrayChild(int Dimension = 100) : MyArrayParent(Dimension) {
		 cout << "\nMyArrayChild constructor" << endl;
		  }
    MyArrayChild(double* arr, int len) : MyArrayParent(arr, len) {
		cout << "\nMyArrayChild constructor" << endl; 
		}
	~MyArrayChild() {
		 cout << "\nMyArrayChild destructor" << endl;  
		 }

	//СѓРґР°Р»РµРЅРёРµ СЌР»РµРјРµРЅС‚Р°
	void RemoveAt(int index = -1) 
	{
		if(index>=0 || index<count) {
			for(int i = index; i<count-1; i++) {
				ptr[i] = ptr[i+1];
			}
			count--;
		}
	}

	MyArrayChild newFunction() 
	{
		int pom;
		MyArrayChild result(capacity);
		for(int i = 0; i<count; i++) {
			pom = ptr[i];
			if((pom%10) * (pom/10%10) == (pom/100%10) * (pom/1000)) {
				result.push(pom);
			}
		}
		return result;
	}
	
	int IndexOf(double value, bool bFindFromStart = true) {
        if(bFindFromStart) {
            for(int i = 0; i<count; i++) {
                if(ptr[i]==value){
                    return i;
                }
            }
        } else {
            for(int i = count-1; i>=0; i--) {
                if(ptr[i]==value){
                    return i;
                }
            }
        }
        return -1;
    }

	void InsertAt(double value, int index = -1) {
        if(index>count || index<0) {
            push(value);
            return;
        }
        if(count < capacity) {
            for(int i = count; i>index; --i) {
                ptr[i] = ptr[i-1];
            }
            count++;
            ptr[index] = value;
        }
    }


	MyArrayChild subSequence(int startIndex = 0, int length = -1) {
		if(length==-1) length = count;
		MyArrayChild list(length*1.5);
		for(int i = startIndex; i<startIndex+length; i++) {
			list.push(GetComponent(i));
		}
		return list;
	}

	MyArrayChild operator+(double el) {
		push(el);
		return MyArrayChild(ptr, count);
	}

};

class MySortedArray : public MyArrayChild
{
protected:
	int BinSearch(double value, int left, int right)
	{
		int mid;
		while(left<right) {
			mid = (left+right)/2;
			if(fabs(ptr[mid]-value)<0.001) {
		
				return mid;
			}
			else if(value<ptr[mid]) {
				
				right = mid-1;
			}
			else {
				
				left = mid+1;
			}
		}
		return -1;
	}
	int BinSearch2(double value, int left, int right)
	{
		int mid;
		while(left<right) {
			mid = (left+right)/2;
			if(fabs(ptr[mid]-value)<0.001) {
				return mid;
			}
			else if(value<ptr[mid]) {
				right = mid-1;
			}
			else {	
				left = mid+1;
			}
		}
		if(ptr[mid]<value) return mid+1;
		if(ptr[mid]>value && ptr[mid-1]>value) return mid-1;
		return mid;
	}
public:
	MySortedArray(int Capacity = 100) : MyArrayChild(Capacity) {}
	MySortedArray(double* arr, int len) : MyArrayChild(arr, len) {}
	~MySortedArray() {}

	int IndexOf(double value, bool bFindFromStart = true)
	{	
		return BinSearch(value, 0, count);
	}

	void push(double value)
	{
		int index = BinSearch2(value, 0, count);
		InsertAt(value, index);
		// РќРµС‚ РЅРѕР±С…РѕРґРёРјРѕСЃС‚Рё РїСЂРѕРІРµСЂСЏС‚СЊ РІ push 0, 1, 2 СЌР»РµРјРµРЅС‚Р° РІ РјР°СЃСЃРёРІРµ (РІСЃРµ СЂР°Р±РѕС‚Р°РµС‚ РїСЂР°РІРёР»СЊРЅРѕ)
	}

};

int main()
{

	double arr[] = {9,2,12,7,1,532,23,123,66};
	double newArr[] = {1234, 2418, 8118, 9911, 6243};
	double sortedArr[] = {2,6,9,33,148,234,236};
	double sortedArr2[] = {};

	MyArrayParent first(arr, 9);
	MyArrayParent second = first;
	MyArrayParent third(second);
	cout << third[4] << endl;

	MyArrayChild* cFirst;
	MyArrayChild child(newArr, 5);
	cFirst = &child;
	cFirst->RemoveAt(2);
	cFirst->print();
	cout << cFirst->IndexOf(532) << endl;
	cFirst->InsertAt(7777,3);
	cFirst->print();
	MyArrayChild newCFirst = cFirst->newFunction();
	newCFirst.print();

	MySortedArray sortedC1(sortedArr, 7);
	MySortedArray sortedC2(sortedArr2, 0);
	cFirst = &sortedC1;
	cFirst->push(53);
	cFirst->print();
	cout << cFirst->IndexOf(234) << endl;
	cout << cFirst->IndexOf(-1000) << endl;

	cFirst = &sortedC2; // РќРµС‚ РЅРѕР±С…РѕРґРёРјРѕСЃС‚Рё РїСЂРѕРІРµСЂСЏС‚СЊ РІ push 0, 1, 2 СЌР»РµРјРµРЅС‚Р° РІ РјР°СЃСЃРёРІРµ
	cFirst->push(4);
	cFirst->push(3);
	cFirst->push(64);
	cFirst->print();

	return 0;
}