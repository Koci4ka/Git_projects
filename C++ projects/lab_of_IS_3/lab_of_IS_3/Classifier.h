#pragma once
#include <vector>

using namespace std;

class Classifier
{
public:

	Classifier(int _k, int _n, char* _class_names, vector<float>* _Matrices)
	{
		int n;
		int k;
		char* class_names;
		vector<float>* Matrices;
	}


	/*�� ������ ����� ������� �� �����/� ���� ���� ���� �������.
		�������������� ������
		���������� �� ���� �������
		�����, � �������� ��� ������� ���� ������.*/  

	string get_class(); //��������� � ������ ������ ��������� ������
	float get_centers_of_classes(); //��������� ���� � ������ ������
	float get_distance(); //���������� ������� �� ���� �������
	//����� ��������������� �������

private:

	int k;
	int n;
	char* class_names;
	vector<float>* Matrices;

};

