using namespace std;
#include "iostream"

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

	char* getName()
	{
		return lastname;
	}

	friend ostream& operator<<(ostream& s, Customer& value);
	friend istream& operator>>(istream& s, Customer& value);
};

ostream& operator<<(ostream& s, Customer& value)
{
	s <<"("<<value.firstname<<", "<<value.lastname<<", "
	  <<value.city<<", "<<value.street<<", "<<value.houseNumber<<", "
	  << value.apartmentNumber<<", "<<value.accountNumber<<", "
	  <<value.averageCheckAmount<<")";
	return s;
}

istream& operator>>(istream& s, Customer& cus)
{
	cout << "hello";
	cout << "hi man";
	s >> cus.firstname;
	cout << "ton ton";
	// cout << "\nEnter fields: ";
	// cout << "\nFirstname (char*): ";
	// s >> cus.firstname;
	// cout << "\nLastname (char*): ";
	// s >> cus.lastname;
	// cout << "\nCity (char*): ";
	// s >> cus.city;
	// cout << "\nStreet (char*): ";
	// s >> cus.street;
	// cout << "\nHouse Number (int): ";
	// s >> cus.houseNumber;
	// cout << "\nApartment Number (int): ";
	// s >> cus.apartmentNumber;
	// cout << "\nAccount Number (int): ";
	// s >> cus.accountNumber;
	// cout << "\nAverage Check Amount (int): ";
	// s >> cus.averageCheckAmount;
	return s;
}

int main()
{
	char n[] = ("dfs");

	char* k = "fds";
	char* kk = new char;
	char* kkk = n;

	cin >> kkk;
	cout << "hello kkk\n";
	cin >> kk;
	cout << "hello kk\n";
	
	cin >> k;
	cout << "hello k\n";
	delete kk;
	delete kkk;
	return 0;
}