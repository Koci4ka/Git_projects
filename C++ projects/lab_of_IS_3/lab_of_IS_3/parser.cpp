#include "parser.h"
#include <fstream>
#include <iostream>
#include <vector>


Classifier* ParseTrainData(string file_name) {
	ifstream input_file;
	input_file.open(file_name);
	
	if (!input_file.is_open()) {
		cout << "Cannot open the input file" << endl;
		return nullptr;
	}

	int k, n; //k ���-�� ������� n - ������ ��������
	input_file >> k;
	input_file >> n;


	char* class_names = new char[k];
	vector<float>* Matrices = new vector<float>[k];

	for (int a = 0; a < k; a++) {
		input_file >> class_names[a];
		int m; // ���-�� ������ � ������ ������
		input_file >> m;

		//vector<float> current_matrix;

		for (int i = 0; i < n * n; i++) {
			Matrices[a].push_back(0);
		}
		for (int b = 0; b < m; b++) {
			for (int i = 0; i < n * n; i++) {
				float x;
				input_file >> x;
				Matrices[a][i] += x;
			}
		}

		for (int i = 0; i < n * n; i++) {
			Matrices[a][i] /= m;
		}
		//Matrices->push_back(current_matrix);
	}
	input_file.close();
	return new Classifier(k, n, class_names, Matrices);
}

void ParseTestData(string test_name, Classifier* classifier, string result_name) {
	ifstream test_file;
	ofstream result_file;
	test_file.open(test_name);

	if (!test_file.is_open()) {
		cout << "Cannot open the test file" << endl;
		return;
	}
// ������� ���� ��� ������ result_name
	result_file.open(result_name);
	int m; //m ���-�� �������� ������
	test_file >> m;
	for (int i = 0; i < m; i++) {
		vector<float> current_test;
		float x;
		for (int j = 0; j < classifier->n * classifier->n; j++) {
			test_file >> x;
			current_test.push_back(x); 
		}

		/*�� ������ ����� ������� �� �����/� ���� ���� ���� �������
		�������������� ������
		���������� �� ���� �������
		�����, � �������� ��� ������� ���� ������.*/

		// ������� ����� � ��������������, ���. ��������� ������� float � ������ ������� ��� �������������� ������ � ��
		string get_class(vector<float> current_test); 
		string c; //�  - �����
		c = get_class(current_test);
		result_file << c;  //�������� � ��������� � ������ ������ ��������� ������ 

		float get_centers_of_classes(); 
		float get_distance();


		// �������� � ���� � result_file.txt ��� ������/n;

	 }
}


