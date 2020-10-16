#pragma once
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Classifier
{
public:

	Classifier(int _k, int _n, char* _class_names, vector<double>* _Matrices, vector<double>* _S_matrices);

	~Classifier() {
		delete[] Matrices;
		delete[] S_matrices;
		delete[] class_names;
	}


	/*�� ������ ����� ������� �� �����/� ���� ���� ���� �������.
		�������������� ������
		���������� �� ���� �������
		�����, � �������� ��� ������� ���� ������.*/  

	void get_class(vector<double> matr, ofstream &result_file); //��������� � ������ ������ ��������� ������(�������)
	void write_centers_of_classes(ofstream &result_file); //������� ���� � ������ ������
	double get_distance(vector<double> v, int clss); //���������� ������� �� ���� �������
	//����� ��������������� �������

	int k;
	int n;
	char* class_names;
	vector<double>* Matrices;
	vector<double>* S_matrices;

private: 
	void write_matrix(vector<double> matr, ofstream& result_file);
	vector<double> vect_matr_mult(vector<double> v, vector<double> S);
	double vec_vec_mult(vector<double> v1, vector<double> v2);
};

