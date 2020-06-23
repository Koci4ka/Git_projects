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

	void showNumber(HugeNumbers given_number) const {
	
		for (int i = size; i > 0; i--) {
			//....
		}
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

		int size3; //макс размер из двух чисел +1 (3 число) 
		bool isPositive3;
		int number_of_digits3;
		unsigned char *number_get3;

		if (size > size2) { //размер 3 числа 
			size3 = size;
		}
		else size3 = size2;

		if (isPositive == isPositive2) { //знак 3 числа
			isPositive3 = isPositive;
		}
		else {
			if (size > size2) {
				isPositive3 = isPositive;
			}
			else isPositive3 = isPositive2;
		}

		number_get3 = new unsigned char[size3];

		if (isPositive != isPositive2) { //если знаки разные - вычитание
										//если одинаковые - сложение
			Subtraction(given_number2);
		}
		else {
			for (int i = 0; i < size3; i++) {
				//..
			}
		}
		return (given_number2); 
	};

	HugeNumbers Subtraction(HugeNumbers& given_number2) {   
		//..
	}
	
	

private: 

	int size;
	bool isPositive;
	unsigned char *number_get;
	int number_of_digits;
};



int main() {
	string s;
	HugeNumbers number;
	setlocale(LC_ALL, "Russian");
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
		if (value == 1) //ничего не выводит???
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
		cout << "====================================99==" << endl;
	}



return 0;
}
