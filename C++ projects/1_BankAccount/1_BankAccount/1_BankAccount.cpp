#include <iostream>
#include <string>
using namespace std;

class BankAccount {
public:
	BankAccount(string given_surename = "", int given_pass1 = 0, int given_pass2 = 0, float given_balance = 0)// ����� ���������� � ����������� ������ ���, ������� � ��������� ������
			/*����������� ������: �������,
			����� ��������
			����� ��������
			������� ������ �����*/
	{
		surname = given_surename;
		pass1 = given_pass1;
		pass2 = given_pass2;
		balance = given_balance;
		MaxCrediting = given_balance; // ���� ����������
		MaxWriteOff = 0; // ���� �������� 
		LastCrediting = given_balance; // ����������
		LastWriteOff = 0; // ��������
	}

	~BankAccount() {}

	float getBalance() const { return balance; } // ������� ������� ������
	float getMaxCrediting() const { return MaxCrediting; } //������� ������������ ���������� � ���� �����
	float getMaxWriteOff() const { return MaxWriteOff; } // ������� � ���� ��������
	bool putCrediting(float NewCrediting) { //��������� ��������
		if (NewCrediting < 0) {
			cout << "������� ���������� �����" << endl;
			return false;
		}
		balance += NewCrediting;
		if (NewCrediting >= MaxCrediting) {
			MaxCrediting = NewCrediting;
		}
		LastCrediting = NewCrediting;
		return true;
	}

	int putWriteOff(float NewWriteOff) { //������� ��������
		if (NewWriteOff < 0) {
			cout << "������� ���������� ����� " << endl; //���������� ������ ����� 0 1 2
			return 0;
		}
		else if (NewWriteOff > balance) {
			cout << "�����, ��������� ����, ��������� ������� ������" << endl;
			return 1;
		}
		else {
			balance -= NewWriteOff;
			if (NewWriteOff >= MaxWriteOff) {
				MaxWriteOff = NewWriteOff;
			}
			LastWriteOff = NewWriteOff;
			return 2;
		}
	}


private:
	string surname; //�������
	int pass1; // ����� ��������
	int pass2; // ����� ��������
	float balance; // ������� ������
	float MaxCrediting; // ���� ���������� 
	float MaxWriteOff; // ���� �������� 
	float LastCrediting; // ����������
	float LastWriteOff; // ��������
};

int main()
{
	setlocale(LC_ALL, "Russian");
	BankAccount bank;
	int action;
	string surname;
	float pass1, pass2;
	bool result;
	float cash = 0;
	cout << "������� �������, ����� � ����� ��������: " << endl;
	cin >> surname >> pass1 >> pass2;

	cout << "��������, ������� ��������� � ����� ������:" << endl;
	cout << "1 - ���������� ����� � �����" << endl;
	cout << "2 - �������� �������� �������" << endl;
	cout << "3 - ������� ������� ������" << endl;
	cout << "4 - ������� ������������ ���������� �������" << endl;
	cout << "5 - ������� ������������ �������� �������" << endl;
	cout << "6 - �������� ������ ��������� ��������" << endl;
	cout << "0 - ����� �� ���������" << endl;
	cout << "=======================================================================" << endl;

	while (cin >> action) {
		if (action == 1) //��������� ����
		{
			cout << "������� ����� ���������� ";
			cin >> cash;
			result = bank.putCrediting(cash); //��������� ����� if result
			float mybalance1;
			if (result == 1) {
				mybalance1 = bank.getBalance();
				cout << "���� ������� ��������" << endl;
				cout << "������� ������ " << mybalance1 << endl;
			}
			else {
				cout << "��� ��������� �������� ���������� ������� '1' ��� '6' ��� ��������� ��������� �������� � ����� ������" << endl;
			}

		}
		else if (action == 2)
		{
			cout << "������� ����� �������� ";
			cin >> cash;
			result = bank.putWriteOff(cash); //������� ��������
			float mybalance2;
			if (result == 0) {
				cout << "��� ��������� �������� �������� ������� '2' ��� '6' ��� ��������� ��������� �������� � ����� ������" << endl;
			}
			else if (result == 1) {
				cout << "��� ��������� �������� �������� ������� '2' ��� '6' ��� ��������� ��������� �������� � ����� ������" << endl;
			}
			else {
				mybalance2 = bank.getBalance();
				cout << "�������� ������� �����������" << endl;
				cout << "������� ������ " << mybalance2 << endl;
			}
		}
		else if (action == 3)
		{
			cout << "������� ������ " << bank.getBalance() << endl; //������� ������
		}
		else if (action == 4)
		{
			cout << "���� ���������� " << bank.getMaxCrediting() << endl; // ���� ���������� 
		}
		else if (action == 5)
		{
			cout << "���� �������� " << bank.getMaxWriteOff() << endl; //���� ��������
		}
		else if (action == 6)
		{
			cout << "��������, ������� ��������� � ����� ������:" << endl;
			cout << "1 - ���������� ����� � �����" << endl;
			cout << "2 - �������� �������� �������" << endl;
			cout << "3 - ������� ������� ������" << endl;
			cout << "4 - ������� ������������ ���������� �������" << endl;
			cout << "5 - ������� ������������ �������� �������" << endl;
			cout << "6 - �������� ������ ��������� ��������" << endl;
			cout << "0 - ����� �� ���������" << endl;
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
