#include <iostream>
#include <string>
#include <locale>
#include <windows.h>
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

	
	/*ввывести число - пробовала, метод ничего не выводил 
	знак числа - сделано 
	сложение вычитание ---  HugeNumbers Add(HugeNumbers number_2)  
			складываем намб1(наш класс) + намб2(его передали) = намб3 его возвращаем
	*/

	~HugeNumbers() {
		delete[] number_get;
	}

	void showNumber() {
		if (!isPositive) {
			cout << '-';
		}
		for (int i = (size-1); i >= 0; i--) {
			cout << int (number_get[i]);
		}
		cout << endl;
	}

	bool getSign() {
		return isPositive;
	}

	int isGreaterABS(HugeNumbers& given_number2) { //определяем, какое число из 2х больше по модулю, если размеры одинак
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

	HugeNumbers Add(HugeNumbers& given_number2) {
		/*size
		isPositive
		number_of_digits
		number_get - 1ое число


		сравнение по модулю двух чисел(размер массива, значения)
		рассмотреть случаи сложения, вычитания

		*/
	
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
			// здесь складываем 2 массива 
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
				//можем выходить и вернуть hugenumbers = 0
				return HugeNumbers();
			}
		}
	}

	HugeNumbers SubtractionABS(HugeNumbers& given_number2) {

		return given_number2;
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
		// пробегаемся по массивам number_get и 2, в стоблик складываем
		unsigned char a = 0;
		unsigned char b = 0;
		for (int i = 0; i < (size3-1); i++) {
			a = 0;
			b = 0;
			if (i < size) {
				a = number_get[i];
			}
			if (i < size2) {
				b = number_get2[i];
			}
			number_get3[i] += a + b;
			number_get3[i + 1] = (number_get3[i] / 100); //если сложение больше 100 (перенос)
			number_get3[i] = number_get3[i] % 100; //убираем третий разряд, его сохранили 
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

private: 
	
	int size;
	bool isPositive;
	unsigned char *number_get;
	int number_of_digits;
};



int main() {
	string s;
	setlocale(LC_ALL, "Russian");
	int value = 0;

	cout << "Enter a number" << endl;
	cin >> s;
	cout << "======================================" << endl;
	HugeNumbers number(s);
	

	cout << "Possible operations: " << endl;
	cout << "1 - Output a number to the console " << endl;
	cout << "2 - Define the sign of a number " << endl;
	cout << "3 - Output the sum of two numbers " << endl;
	cout << "4 - Output the difference between two numbers " << endl;
	cout << "9 - View operations " << endl;
	cout << "0 - Exit the program " << endl;
	cout << "======================================" << endl;
	
	while (cin >> value) {
		if (value == 1) 
		{
			cout << "The number entered === "; //введеное число - ...
			number.showNumber();
		}
		else if (value == 2) //done
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
		else if (value == 3) {
			string number1; //в методах суммы и вычитания будут новые числа, которые пользователь вводит 
			string number2;
			cout << "Enter the first term " << endl;
			cin >> number1;
			cout << "Enter the second term " << endl;
			cin >> number2;
			HugeNumbers huge1(number1);
			HugeNumbers huge2(number2);
			cout << "Sum of two numbers === ";
			HugeNumbers huge3 = huge1.Add(huge2);
			huge3.showNumber();
		}

		else if (value == 4) {

		}

		else if (value == 9)
		{
			cout << "Possible operations: " << endl;
			cout << "1 - Output a number to the console " << endl;
			cout << "2 - Define the sign of a number " << endl;
			cout << "3 - Output the sum of two numbers " << endl;
			cout << "4 - Output the difference between two numbers " << endl;
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
