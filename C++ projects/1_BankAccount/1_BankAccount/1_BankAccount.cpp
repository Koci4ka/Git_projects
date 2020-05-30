#include <iostream>
#include <string>
using namespace std;

class BankAccount {
public:
	BankAccount(string given_surename = "", int given_pass1 = 0, int given_pass2 = 0, float given_balance = 0)// можно передавать в конструктор только имя, паспорт и начальный баланс
			/*Минимальные данные: фамилия,
			серия паспорта
			номер паспорта
			текущий баланс счета*/
	{
		surname = given_surename;
		pass1 = given_pass1;
		pass2 = given_pass2;
		balance = given_balance;
		MaxCrediting = given_balance; // макс зачисление
		MaxWriteOff = 0; // макс списание 
		LastCrediting = given_balance; // зачисление
		LastWriteOff = 0; // списание
	}

	~BankAccount() {}

	float getBalance() const { return balance; } // вывести текущий баланс
	float getMaxCrediting() const { return MaxCrediting; } //вернуть максимальное пополнение в виде числа
	float getMaxWriteOff() const { return MaxWriteOff; } // перейти к макс списанию
	bool putCrediting(float NewCrediting) { //зачислить средства
		if (NewCrediting < 0) {
			cout << "Введите корректную сумму" << endl;
			return; //false
		}
		balance += NewCrediting;
		if (NewCrediting >= MaxCrediting) {
			MaxCrediting = NewCrediting;
		}
		LastCrediting = NewCrediting; //return true
		//cout << LastCrediting;
	}

	int putWriteOff(float NewWriteOff) { //списать средства
		if (NewWriteOff < 0) {
			cout << "Введите корректную сумму" << endl; //обозначить случаи через 0 1 2
			return;
		}
		balance -= NewWriteOff;
		if (NewWriteOff >= MaxWriteOff) {
			MaxWriteOff = NewWriteOff;
		}
		LastWriteOff = NewWriteOff;
	}


private:
	string surname; //фамилия
	int pass1; // серия паспорта
	int pass2; // номер паспорта
	float balance; // текущий баланс
	float MaxCrediting; // макс зачисление 
	float MaxWriteOff; // макс списание 
	float LastCrediting; // зачисление
	float LastWriteOff; // списание
};

int main()
{
	setlocale(LC_ALL, "Russian");
	BankAccount bank;
	int action;
	string surname;
	float pass1, pass2;
	bool result;
	cout << "Введите фамилию, серию и номер паспорта: " << endl;
	cin >> surname >> pass1 >> pass2;

	cout << "Действия, которые возвомжны с Вашим счетом:" << endl;
	cout << "1 - Пополнение счета в банке" << endl;
	cout << "2 - Списание денежных средств" << endl;
	cout << "3 - Вывести текущий баланс" << endl;
	cout << "4 - Вывести максимальное пополнение средств" << endl;
	cout << "5 - Вывести максимальное списание средств" << endl;
	cout << "6 - Показать список возможных действий" << endl;
	cout << "0 - Выйти из программы" << endl;
	cout << "=======================================================================" << endl;

	while (cin >> action) {
		if (action == 1) //пополнить счет
		{
			result = bank.putCrediting(1000.5); //проверить через if result
			float mybalance1;
			mybalance1 = bank.getBalance();
			cout << "Счет успешно пополнен" << endl;
			cout << "Текущий баланс " << mybalance1 << endl;

		}
		else if (action == 2)
		{
			result = bank.putWriteOff(50.5); //списать средства
			float mybalance2;
			mybalance2 = bank.getBalance();
			cout << "Списание успешно произведено" << endl;
			cout << "Текущий баланс " << mybalance2 << endl;
		}
		else if (action == 3)
		{
			cout << "Текущий баланс " << bank.getBalance() << endl; //вывести баланс
		}
		else if (action == 4)
		{
			cout << "Макс пополнение " << bank.getMaxCrediting() << endl; // макс пополнение 
		}
		else if (action == 5)
		{
			cout << "Макс списание " << bank.getMaxWriteOff() << endl; //макс списание
		}
		else if (action == 6)
		{
			cout << "Действия, которые возвомжны с Вашим счетом:" << endl;
			cout << "1 - Пополнение счета в банке" << endl;
			cout << "2 - Списание денежных средств" << endl;
			cout << "3 - Вывести текущий баланс" << endl;
			cout << "4 - Вывести максимальное пополнение средств" << endl;
			cout << "5 - Вывести максимальное списание средств" << endl;
			cout << "6 - Показать список возможных действий" << endl;
			cout << "0 - Выйти из программы" << endl;
			cout << "=======================================================================" << endl;
		}
		else
		{
			break;
		}
		cout << "=======================================================================" << endl;
	}
	return 0;
}
