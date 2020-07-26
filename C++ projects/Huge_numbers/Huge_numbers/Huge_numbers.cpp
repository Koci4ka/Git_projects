#include <iostream>
#include <string>
using namespace std;

class HugeNumbers {
public:
	HugeNumbers(int given_size, bool given_isPositive, unsigned char* given_number_get, int given_number_of_digits)
	{
		size = given_size;
		isPositive = given_isPositive;
		number_get = new unsigned char[size];
		for (int i = 0; i < size; i++) {
			number_get[i] = given_number_get[i];
		}
		number_of_digits = given_number_of_digits;
	}

	// Конструктор копирования
	HugeNumbers(const HugeNumbers& given_huge)
	{
		size = given_huge.size;
		isPositive = given_huge.isPositive;
		number_get = new unsigned char[size];
		for (int i = 0; i < size; i++) {
			number_get[i] = given_huge.number_get[i];
		}
		number_of_digits = given_huge.number_of_digits;
	}

	HugeNumbers(string given_number = "0")
	{
		size = 0;
		int string_size = given_number.size();
		bool wasSign = true;
		if (given_number[0] == '+') {
			isPositive = true;
			size = given_number.size() / 2;
		}
		else if (given_number[0] == '-') {
			isPositive = false;

			size = given_number.size() / 2;
		}
		else {
			isPositive = true;
			size = (given_number.size() + 1) / 2;
			wasSign = false;
		}

		number_get = new unsigned char[size];

		if (wasSign) {
			string_size -= 1;
			number_of_digits = given_number.size() - 1;
		}
		else {
			number_of_digits = given_number.size();
		}

		for (int i = 0; i < size; i++) {
			int c1 = 0, c2 = 0;
			if (i == (size - 1) && (string_size % 2 != 0)) {
				c2 = given_number[given_number.size() - 1 - 2 * i] - '0';
			}
			else {
				c1 = given_number[given_number.size() - 2 - 2 * i] - '0';
				c2 = given_number[given_number.size() - 1 - 2 * i] - '0';
			}
			number_get[i] = c1 * 10 + c2;
		}
	}

	//Оператор присваивания
	HugeNumbers& operator=(const HugeNumbers& given_huge) {
		if (this != &given_huge) {
			delete[] number_get;
			size = given_huge.size;
			isPositive = given_huge.isPositive;
			number_get = new unsigned char[size];
			for (int i = 0; i < size; i++) {
				number_get[i] = given_huge.number_get[i];
			}
			number_of_digits = given_huge.number_of_digits;
		}
		return *this;
	}

	~HugeNumbers() {
		delete[] number_get;
	}

	bool getSign() {
		return isPositive;
	}

	int isGreaterABS(HugeNumbers& given_number2) { //определяем, какое число из 2х больше по модулю, если размеры одинак
		if (number_of_digits > given_number2.number_of_digits) {
			return 1;
		}
		else if (given_number2.number_of_digits > number_of_digits) {
			return -1;
		}
		else {
			unsigned char* number_get2 = given_number2.number_get;
			for (int i = (size - 1); i >= 0; i--) {
				if (number_get[i] > number_get2[i]) {
					return 1;
				}
				else if (number_get2[i] > number_get[i]) {
					return -1;
				}
			}
			return 0;
		}
	}

	bool isGreater(HugeNumbers& given_number2) {
		if (isPositive && (!given_number2.isPositive || (number_of_digits > given_number2.number_of_digits))) { 
			return true;  //первое число строго больше
		}
		else if (given_number2.isPositive && (!isPositive || (given_number2.number_of_digits > number_of_digits))) {
			return false; // первое число строго меньше
		}
		else if ((isPositive == given_number2.isPositive) && (number_of_digits != given_number2.number_of_digits)) {
			if (number_of_digits > given_number2.number_of_digits) { /*знак одинаковый
																	   сравниваем кол-во цифр*/
				return true;
			}
			else return false;
		}
		else if ((isPositive == given_number2.isPositive) && (number_of_digits == given_number2.number_of_digits)) {
			for (int i = (size - 1); i >= 0; i--) { /*всё совпадает
								                      сравниваем цифры*/
				if (number_get[i] == given_number2.number_get[i]) {
					continue;
				}
				else if (number_get[i] > given_number2.number_get[i]) {
					return true; 
				}
				else if (number_get[i] < given_number2.number_get[i]) {
					return false; 
				}
				else return false;
			}
		}
		return false;
	}

	bool isLess(HugeNumbers& given_number2) {
		if (given_number2.isPositive && (!isPositive || (given_number2.number_of_digits > number_of_digits))) {
			return true;
		}
		else if (isPositive && (!given_number2.isPositive || (number_of_digits > given_number2.number_of_digits))) {
			return false;
		}
		else if ((isPositive == given_number2.isPositive) && (number_of_digits != given_number2.number_of_digits)) {
			if (number_of_digits > given_number2.number_of_digits) { 
				return false;
			}
			else return true;
		}
		else if ((isPositive == given_number2.isPositive) && (number_of_digits == given_number2.number_of_digits)) {
			for (int i = (size - 1); i >= 0; i--) { 
				if (number_get[i] == given_number2.number_get[i]) {
					continue;
				}
				else if (number_get[i] > given_number2.number_get[i]) {
					return false;
				}
				else if (number_get[i] < given_number2.number_get[i]) {
					return true;
				}
				else return true;
			}
		}
		return true;
	}

	bool isEqual(HugeNumbers& given_number2) {
		if (isPositive && (!given_number2.isPositive || (number_of_digits > given_number2.number_of_digits))) {
			return false; 
		}
		else if (given_number2.isPositive && (!isPositive || (given_number2.number_of_digits > number_of_digits))) {
			return false; 
		}
		else if ((isPositive == given_number2.isPositive) && (number_of_digits != given_number2.number_of_digits)) {
			if (number_of_digits > given_number2.number_of_digits) {
				return 1;
			}
			else return -1;
		}

		else if ((isPositive == given_number2.isPositive) && (number_of_digits == given_number2.number_of_digits)) {
			for (int i = (size - 1); i >= 0; i--) {
				if (number_get[i] == given_number2.number_get[i]) {
					continue;
				}
				else if (number_get[i] > given_number2.number_get[i]) {
					return false; 
				}
				else if (number_get[i] < given_number2.number_get[i]) {
					return false; 
				}
				else return true;
			}
		}
		return true;
	}

	HugeNumbers operator +(HugeNumbers& given_number2) {
		bool isPositive2 = given_number2.isPositive;
		int number_of_digits2 = given_number2.number_of_digits;

		bool isPositive3;
		int number_of_digits3; //макс размер из двух чисел +1 (3 число) 

		if (number_of_digits > number_of_digits2) { //размер 3 числа 
			number_of_digits3 = (number_of_digits + 1);
		}
		else number_of_digits3 = (number_of_digits2 + 1); //максимально возм size3

		if (isPositive == isPositive2) { //знак 3 числа
			isPositive3 = isPositive;
			HugeNumbers result = AddABS(given_number2);
			result.isPositive = isPositive3;
			return result;
		}
		else {
			int x = this->isGreaterABS(given_number2);
			if (x == 1) {
				isPositive3 = isPositive;
				HugeNumbers result = this->SubtractionABS(given_number2); // вычитание по модулю (первое больше)
				result.isPositive = isPositive3;
				return result;
			}
			else if (x == -1) {
				isPositive3 = isPositive2;
				HugeNumbers result = given_number2.SubtractionABS(*this);
				result.isPositive = isPositive3;
				return result;
			}
			else {
				return HugeNumbers();
			}
		}
	}

	HugeNumbers SubtractionABS(HugeNumbers& given_number2) { // 1 > 2
		int size2 = given_number2.size;
		int number_of_digits2 = given_number2.number_of_digits;
		unsigned char* number_get2 = given_number2.number_get;

		int size3;
		int number_of_digits3; //равен 1ому числу (3 число) 
		unsigned char* number_get3;
		unsigned char* temp_number_get3;

		number_of_digits3 = number_of_digits; //размер 3 числа

		size3 = ((number_of_digits3 + 1) / 2); //максимально возм size3
		number_get3 = new unsigned char[size3];
		for (int i = 0; i < size3; i++) {
			number_get3[i] = 0;
		}

		unsigned char a = 0;
		unsigned char b = 0;
		bool c = false;
		for (int i = 0; i < size3; i++) {
			a = 0;
			b = 0;
			if (i < size) {
				a = number_get[i];
			}
			if (i < size2) {
				b = number_get2[i];
			}
			if (c) {
				if (a >= b + 1) {
					number_get3[i] = a - b - 1;
					c = false;
				}
				else {
					number_get3[i] = 100 + a - b - 1;
				}
			}
			else {
				if (a >= b) {
					number_get3[i] = a - b;
					c = false;
				}
				else {
					number_get3[i] = 100 + a - b;
					c = true;
				}
			}
		}

		int n_zero = 0;
		for (int i = (size3 - 1); i >= 0; i--) {
			if (number_get3[i] == 0) {
				n_zero += 2;
			}
			else if (number_get3[i] < 10) {
				n_zero += 1;
				break;
			}
			else break;
		}
		if (n_zero == 2 * size3) {
			delete[] number_get3;
			return HugeNumbers();
		}
		else if (n_zero / 2 > 0) {
			temp_number_get3 = new unsigned char[size3 - (n_zero / 2)];
			for (int i = 0; i < size3 - n_zero / 2; i++) {
				temp_number_get3[i] = number_get3[i];
			}
			delete[] number_get3;
			number_get3 = temp_number_get3;
			size3 -= n_zero / 2;
			if (number_get3[size3 - 1] < 10) {
				number_of_digits3 = 2 * (size3 - 1) + 1;
			}
			else number_of_digits3 = 2 * size3;
		}
		return HugeNumbers(size3, true, number_get3, number_of_digits3);

	}

	HugeNumbers AddABS(HugeNumbers& given_number2) {
		int size2 = given_number2.size;
		int number_of_digits2 = given_number2.number_of_digits;
		unsigned char* number_get2 = given_number2.number_get;

		int size3;
		int number_of_digits3; //макс размер из двух чисел +1 (3 число) 
		unsigned char* number_get3;
		unsigned char* temp_number_get3;

		if (number_of_digits > number_of_digits2) { //размер 3 числа 
			number_of_digits3 = (number_of_digits + 1);
		}
		else number_of_digits3 = (number_of_digits2 + 1); //максимально возм size3

		size3 = ((number_of_digits3 + 1) / 2);
		number_get3 = new unsigned char[size3];
		for (int i = 0; i < size3; i++) {
			number_get3[i] = 0;
		}
		unsigned char a = 0;
		unsigned char b = 0;
		for (int i = 0; i < size3; i++) {
			a = 0;
			b = 0;
			if (i < size) {
				a = number_get[i];
			}
			if (i < size2) {
				b = number_get2[i];
			}

			number_get3[i] += a + b;

			if (number_get3[i] >= 100)
			{
				number_get3[i + 1] = (number_get3[i] / 100); //если сложение больше 100 (перенос)
				number_get3[i] = number_get3[i] % 100; //убираем третий разряд, его сохранили 
			}
		}


		if (number_get3[size3 - 1] == 0) {
			temp_number_get3 = new unsigned char[size3 - 1];
			for (int i = 0; i < size3 - 1; i++) {
				temp_number_get3[i] = number_get3[i];
			}
			delete[] number_get3;
			number_get3 = temp_number_get3;
			size3 -= 1;
		}
		if (number_get3[size3 - 1] >= 10) {
			number_of_digits3 = 2 * size3;
		}
		else number_of_digits3 = 2 * size3 - 1;
		return HugeNumbers(size3, true, number_get3, number_of_digits3);
	}

	HugeNumbers operator -(HugeNumbers& given_number2) {
		bool isPositive2 = !given_number2.isPositive;
		int number_of_digits2 = given_number2.number_of_digits;

		bool isPositive3;
		int number_of_digits3; //макс размер из двух чисел +1 (3 число) 

		if (number_of_digits > number_of_digits2) { //размер 3 числа 
			number_of_digits3 = (number_of_digits + 1);
		}
		else number_of_digits3 = (number_of_digits2 + 1); //максимально возм size3

		if (isPositive == isPositive2) { //знак 3 числа === 1 полож 2 отриц - сложение
			isPositive3 = isPositive;
			HugeNumbers result = AddABS(given_number2);
			result.isPositive = isPositive3;
			return result;
		}
		else {
			int x = this->isGreaterABS(given_number2);
			if (x == 1) {
				isPositive3 = isPositive;
				HugeNumbers result = this->SubtractionABS(given_number2); // вычитание по модулю (первое больше)
				result.isPositive = isPositive3;
				return result;

			}
			else if (x == -1) {
				isPositive3 = isPositive2;
				HugeNumbers result = given_number2.SubtractionABS(*this);
				result.isPositive = isPositive3;
				return result;
			}
			else {
				return HugeNumbers();
			}
		}
	}
	friend ostream& operator<<(ostream& os, const HugeNumbers& huge);


private:

	int size;
	bool isPositive;
	unsigned char* number_get;
	int number_of_digits;
};

std::ostream& operator <<(std::ostream& os, const HugeNumbers& huge) {

	if (!huge.isPositive) {
		os << '-';
	}

	for (int i = (huge.size - 1); i >= 0; i--) {
		if ((huge.number_get[i] < 10) && (i != huge.size - 1)) {
			os << 0;
		}
		os << int(huge.number_get[i]);
	}
	os << endl;
	return os;
}


int main() {
	string s;
	int value = 0;

	cout << "Enter a number" << endl;
	cin >> s;
	cout << "======================================" << endl;
	HugeNumbers number(s);

	cout << "Possible operations: " << endl;
	cout << "1 - Define the sign of the number " << endl;
	cout << "2 - Output the sum of two numbers " << endl;
	cout << "3 - Output the subtraction two numbers " << endl;
	cout << "4 - Compare the numbers " << endl;
	cout << "9 - View operations " << endl;
	cout << "0 - Exit the program " << endl;
	cout << "======================================" << endl;

	while (cin >> value) {
		if (value == 1)//ввести число и узнать знак
		{
			bool result;
			cout << "Number sign === ";
			result = number.getSign();
			if (result) {
				cout << "positive" << endl;
			}
			else {
				cout << "negative" << endl;
			}
		}
		else if (value == 2) {
			string number1; //в методах суммы, вычитания и сранения будут новые числа, которые пользователь вводит 
			string number2;
			cout << "Enter the first number " << endl;
			cin >> number1;
			cout << "Enter the second number " << endl;
			cin >> number2;
			HugeNumbers huge1(number1);
			HugeNumbers huge2(number2);
			cout << "Sum of two numbers = " << huge1 + huge2;
		}
		else if (value == 3) {
			string number1;
			string number2;
			cout << "Enter the first number " << endl;
			cin >> number1;
			cout << "Enter the second number " << endl;
			cin >> number2;
			HugeNumbers huge1(number1);
			HugeNumbers huge2(number2);
			cout << "Sub of two numbers = " << huge1 - huge2;
		}
		else if (value == 4) { /* список из операций
							   <
							   <=
							   >
							   >=
							   ==
							   !=

							   вывести команды
							   0 чтобы вернуться в главное меню*/
			int z;
			string number1;
			string number2;
			cout << "Possible actions: " << endl;
			cout << "1 - >" << endl;
			cout << "2 - >=" << endl;
			cout << "3 - <" << endl;
			cout << "4 - <=" << endl;
			cout << "5 - == " << endl;
			cout << "6 - != " << endl;
			cout << "0 - Exit the operation " << endl;
			cout << "======================================" << endl;
			while (cin >> z) {
				if (z == 1)
				{
					cout << "Enter the first number " << endl;
					cin >> number1;
					cout << "Enter the second number " << endl;
					cin >> number2;
					HugeNumbers huge1(number1);
					HugeNumbers huge2(number2); // первое больше - второе меньше 
					// первое не больше - второе <=
					if (huge1.isGreater(huge2)) { // false - первое <=
						cout << "The first number is greater" << endl;
						cout << "========================================" << endl;
					}
					else {
						cout << "The first number isn't greater" << endl;
						cout << "========================================" << endl;
					}
				}

				else if (z == 2) {
					cout << "Enter the first number " << endl;
					cin >> number1;
					cout << "Enter the second number " << endl;
					cin >> number2;
					HugeNumbers huge1(number1);
					HugeNumbers huge2(number2);
					if (!huge1.isLess(huge2)) { //false - первое <
						cout << "The first number is greater or equal" << endl;
						cout << "========================================" << endl;
					}
					else {
						cout << "The first number isn't greater or equal" << endl;
						cout << "========================================" << endl;
					}
				}
				else if (z == 3) {
					cout << "Enter the first number " << endl;
					cin >> number1;
					cout << "Enter the second number " << endl;
					cin >> number2;
					HugeNumbers huge1(number1);
					HugeNumbers huge2(number2);
					if (huge1.isLess(huge2)) {
						cout << "The first number is less" << endl;
						cout << "========================================" << endl;
					}
					else {
						cout << "The first number isn't less" << endl;
						cout << "========================================" << endl;
					}
				}
				else if (z == 4) {
					cout << "Enter the first number " << endl;
					cin >> number1;
					cout << "Enter the second number " << endl;
					cin >> number2;
					HugeNumbers huge1(number1);
					HugeNumbers huge2(number2);
					if (!huge1.isGreater(huge2)) {
						cout << "The second number is greater or equal" << endl;
						cout << "========================================" << endl;
					}
					else {
						cout << "The second number isn't greater or equal" << endl;
						cout << "========================================" << endl;
					}
				}
				else if (z == 5) {
					cout << "Enter the first number " << endl;
					cin >> number1;
					cout << "Enter the second number " << endl;
					cin >> number2;
					HugeNumbers huge1(number1);
					HugeNumbers huge2(number2);
					if (huge1.isEqual(huge2)) {
						cout << "The numbers are equal" << endl;
						cout << "========================================" << endl;
					}
					else {
						cout << "The numbers aren't equal" << endl;
						cout << "========================================" << endl;
					}
				}
				else if (z == 6) {
					cout << "Enter the first number " << endl;
					cin >> number1;
					cout << "Enter the second number " << endl;
					cin >> number2;
					HugeNumbers huge1(number1);
					HugeNumbers huge2(number2);
					if (!huge1.isEqual(huge2)) {
						cout << "The numbers aren't equal" << endl;
						cout << "========================================" << endl;
					}
					else {
						cout << "The numbers aren equal" << endl;
						cout << "========================================" << endl;
					}
				}
				else
				{
					break;
				}
			}
		}

		else if (value == 9)
		{
			cout << "Possible operations: " << endl;
			cout << "1 - Define the sign of the number " << endl;
			cout << "2 - Output the sum of two numbers " << endl;
			cout << "3 - Output the subtraction two numbers " << endl;
			cout << "4 - Compare the numbers " << endl;
			cout << "9 - View operations " << endl;
			cout << "0 - Exit the program " << endl;
			cout << "======================================" << endl;
		}

		else
		{
			break;
		}
		cout << "========================================" << endl;
	}
	return 0;
}
