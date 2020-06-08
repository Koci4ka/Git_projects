#include <iostream>
#include <string>
using namespace std;

class HugeNumbers {
public:
	HugeNumbers(string given_number1 = "", string given_number2 = "")
	{
		first_number = given_number1;
		second_number = given_number2;
	}

	~HugeNumbers() {}

	bool foundSign1(string first_number) {}
	bool foundSign2(string second_number) {}
	string getSum(string first_number, string second_number) {}
	string getSubtraction (string first_number, string second_number) {}
	

private: 
	string first_number;
	string second_number;

};


int main()
{
	setlocale(LC_ALL, "Russian");
	HugeNumbers numbers;
	string number1;
	string number2;
	int value = 0;
	bool result;

	cout << "Операции, которые можно совершать: " << endl;
	cout << "1 - Вычислить сумму чисел  " << endl;
	cout << "2 - Вычислить разность чисел" << endl;
	cout << "9 - Показать возможные операции" << endl;
	cout << "0 - Выйти из программы" << endl;
	cout << "======================================" << endl;
	
	cout << "Введите первое число: " << endl;
	cin >> number1;
	cout << "Введите второе число: " << endl;
	cin >> number2;

	cout << "Определяется знак первого числа ";
	result = numbers.foundSign1(number1); //проверить через if result
	if (result == 1) {
		cout << "Число является положительным " << endl;
		cout << "======================================" << endl;
	}
	else {
		cout << "Число является отрицательным " << endl;
		cout << "======================================" << endl;
	}

	cout << "Определяется знак второго числа ";
	result = numbers.foundSign2(number2);
	if (result == 1) {
		cout << "Число является положительным " << endl;
		cout << "======================================" << endl;
	}
	else
	{
		cout << "Число является отрицательным " << endl;
		cout << "======================================" << endl;
	}



	while (cin >> value) {
		if (value == 1) 
		{
			cout << "Сумма чисел равна === " << numbers.getSum(number1, number2) << endl;

		}
		else if (value == 2)
		{
			cout << "Разность чисел равна === " << numbers.getSubtraction(number1, number2) << endl;
		}
		else if (value == 9)
		{
			cout << "Операции, которые можно совершать: " << endl;
			cout << "1 - Вычислить сумму чисел  " << endl;
			cout << "2 - Вычислить разность чисел" << endl;
			cout << "9 - Показать возможные операции" << endl;
			cout << "0 - Выйти из программы" << endl;
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
