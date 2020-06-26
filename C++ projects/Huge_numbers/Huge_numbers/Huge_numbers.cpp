#include <iostream>
#include <string>
#include <locale>
#include <windows.h>
using namespace std;

class HugeNumbers {
public:
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

	~HugeNumbers() {}

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

	int isGreaterABS(unsigned char* number_get2) { //определяем, какое число из 2х больше по модулю, если размеры одинак
		for (int i = size; i >= 0; i--) {
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
		int size2 = given_number2.size;  // 2 чисто 
		bool isPositive2 = given_number2.isPositive;
		int number_of_digits2 = given_number2.number_of_digits;
		unsigned char* number_get2 = given_number2.number_get; /**/

		int size3;
		bool isPositive3;
		int number_of_digits3; //макс размер из двух чисел +1 (3 число) 
		unsigned char* number_get3;


		if (number_of_digits > number_of_digits2) { //размер 3 числа 
			number_of_digits3 = (number_of_digits + 1);
		}
		else number_of_digits3 = (number_of_digits2 + 1); //максимально возм size3

		if (isPositive == isPositive2) { //знак 3 числа
			isPositive3 = isPositive;
			// здесь складываем 2 массива 
			size3 = ((number_of_digits3 + 1) / 2);
			number_get3 = new unsigned char[size3];
			// пробегаемся по массивам number_get и 2, в стоблик складываем
			int a = 0;
			for (int i = 0; i < size3; i++) {
				number_get[i] = number_get[i] + number_get2[i];
				number_get[i + 1] = (number_get[i] / 10); //если сложение больше 100 (перенос)
				number_get[i] = number_get[i] % 10; //убираем третий разряд, его сохранили 
			}
		}
		else {
			int x = this->isGreaterABS(number_get2);
			if (x == 1) {
				isPositive3 = isPositive;
				// this->Subtraction(given_number2);
			}
			else if (x == -1) {
				isPositive3 = isPositive2;
				//given_number2.Subtraction(*this);
			}
			else {
				//можем выходить и вернуть hugenumbers = 0
			}
		}
		return (given_number2);
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

	cout << "Введите число" << endl;
	cin >> s;
	cout << "======================================" << endl;
	HugeNumbers number(s);
	

	cout << "Возможные операции: " << endl;
	cout << "1 - Вывод числа в консоль " << endl;
	cout << "2 - Определить знак числа " << endl;
	cout << "3 - Вывод суммы двух чисел " << endl;
	cout << "4 - Вывод разности двух чисел " << endl;
	cout << "9 - Просмотр операций " << endl;
	cout << "0 - Завершить программу " << endl;
	cout << "======================================" << endl;
	
	while (cin >> value) {
		if (value == 1) 
		{
			cout << "Введенное число === ";
			number.showNumber();
		}
		else if (value == 2) //done
		{
			bool result;
			cout << "Знак числа === ";
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
			cout << "Введите первое слагамое " << endl;
			cin >> number1;
			cout << "Введите второе слагамое " << endl;
			cin >> number2;
			HugeNumbers huge1(number1);
			HugeNumbers huge2(number2);
			cout << "Сумма двух чисел равна === " << endl;
			HugeNumbers huge3 = huge1.Add(huge2);
		}

		else if (value == 4) {

		}

		else if (value == 9)
		{
			cout << "Возможные операции: " << endl;
			cout << "1 - Вывод числа в консоль " << endl;
			cout << "2 - Определить знак числа " << endl;
			cout << "3 - Вывод суммы двух чисел " << endl;
			cout << "4 - Вывод разности двух чисел " << endl;
			cout << "9 - Просмотр операций " << endl;
			cout << "0 - Завершить программу " << endl;
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
