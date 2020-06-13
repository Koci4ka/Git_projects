#include <iostream>
#include <string>
#include <locale>
#include <windows.h>
using namespace std;

class HugeNumbers {
public:
	HugeNumbers(string given_number = "0")
	{
		int size;
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

	
	/*ввывести число
	знак числа
	сложение вычитание ---  HugeNumbers Add(HugeNumbers number_2)  
			складываем намб1(наш класс) + намб2(его передали) = намб3 его возвращаем

	*/

	~HugeNumbers() {}

	void showNumber(string given_number) const {
		int string_size = given_number.size();
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
		for (int i = 0; i < size; i++) {
			cout << int(number_get[i]);
		};
	}

	bool getSign(string given_number) {
		if (given_number[0] == '+') {
			return true;
		}
		else if (given_number[0] == '-') {
			return false;
		}
		else {
			return true;

		}
	};
	HugeNumbers Add(string given_number) {
		return given_number;
	};

	

private: 

	int size;
	bool isPositive;
	unsigned char *number_get;
};



int main() {
	setlocale(LC_ALL, "Russian");

	string s;
	HugeNumbers number;
	int value = 0;

	cout << "Введите число" << endl;
	cin >> s;
	cout << "======================================" << endl;

	cout << "Возможные операции: " << endl;
	cout << "1 - Вывод числа в консоль " << endl;
	cout << "2 - Определить знак числа " << endl;
	cout << "3 - Вывод суммы двух чисел " << endl;
	cout << "4 - Вывод разности двух чисел " << endl;
	cout << "9 - Просмотр операций " << endl;
	cout << "0 - Завершить программу " << endl;
	cout << "======================================" << endl;
	
	while (cin >> value) {
		if (value == 1) //ничего не выводит
		{
			cout << "Введенное число === ";
			number.showNumber(s);

		}
		else if (value == 2) //done
		{
			bool result;
			cout << "Знак числа === ";
			result = number.getSign(s);
			if (result) {
				cout << "positive" << endl;
			}
			else {
				cout << "negative" << endl;
			}

		}
		else if (value == 3) {
			string s2;
			cout << "Введите второе слагамое ";
			cin >> s2;
			cout << endl;
			cout << "Сумма двух чисел равна === ";
			number.Add(s2);
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
		cout << "======================================" << endl;
	}



return 0;
}
