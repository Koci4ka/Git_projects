#include "parser.h"
#include <fstream>
#include <iostream>
#include <vector>

void inversion(double** A, int N)
{
	double temp;
	double** E = new double* [N];

	for (int i = 0; i < N; i++)
		E[i] = new double[N];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
		{
			E[i][j] = 0.0;

			if (i == j)
				E[i][j] = 1.0;
		}

	for (int k = 0; k < N; k++)
	{
		temp = A[k][k];

		for (int j = 0; j < N; j++)
		{
			A[k][j] /= temp;
			E[k][j] /= temp;
		}

		for (int i = k + 1; i < N; i++)
		{
			temp = A[i][k];

			for (int j = 0; j < N; j++)
			{
				A[i][j] -= A[k][j] * temp;
				E[i][j] -= E[k][j] * temp;
			}
		}
	}

	for (int k = N - 1; k > 0; k--)
	{
		for (int i = k - 1; i >= 0; i--)
		{
			temp = A[i][k];

			for (int j = 0; j < N; j++)
			{
				A[i][j] -= A[k][j] * temp;
				E[i][j] -= E[k][j] * temp;
			}
		}
	}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			A[i][j] = E[i][j];

	for (int i = 0; i < N; i++)
		delete[] E[i];

	delete[] E;
}

Classifier* ParseTrainData(string file_name) {
	ifstream input_file;
	input_file.open(file_name);
	
	if (!input_file.is_open()) {
		cout << "Cannot open the input file" << endl;
		return nullptr;
	}

	int k, n; //k кол-во классов n - размер образцов
	input_file >> k;
	input_file >> n;


	char* class_names = new char[k];
	vector<double>* Matrices = new vector<double>[k];
	vector<double>* S_matrices = new vector<double>[k];

	for (int a = 0; a < k; a++) {
		input_file >> class_names[a];
		int m; // кол-во матриц в каждом классе
		input_file >> m;
		for (int i = 0; i < n * n; i++) {
			Matrices[a].push_back(0);
		}
		vector<double>* train_matrices = new vector<double>[m]; //m матриц, чтобы посчитать матрицу ковариации
		for (int b = 0; b < m; b++) {
			for (int i = 0; i < n * n; i++) {
				double x;
				input_file >> x;
				Matrices[a][i] += x;
				train_matrices[b].push_back(x);
			}
		}

		for (int i = 0; i < n * n; i++) {
			Matrices[a][i] /= m;
		}

		for (int i = 0; i < n*n*n*n; i++) {
			S_matrices[a].push_back(0);
		}


		for (int i = 0; i < n * n; i++) {
			for (int j = 0; j < n * n; j++) {
				for (int k = 0; k < m; k++) {
					S_matrices[a][i * n*n + j] += (train_matrices[k][i] - Matrices[a][i]) * (train_matrices[k][j] - Matrices[a][j]);
				}
				if (m > 1) {
					S_matrices[a][i * n * n + j] /= (m - 1);
				}
			}
		}

		double** S = new double* [n * n];
		for (int i = 0; i < n * n; i++) {
			S[i] = new double[n * n];
			for (int j = 0; j < n * n; j++) {
				S[i][j] = S_matrices[a][i * n * n + j];
				if (i == j) {
					S[i][j] += 1;
				}
		
			}
		}

		inversion(S, n * n);

		for (int i = 0; i < n * n; i++) {
			for (int j = 0; j < n * n; j++) {
				S_matrices[a][i * n * n + j] = S[i][j];
			}
		}

		for (int i = 0; i < n*n; i++)
			delete[] S[i];

		 delete[] S;
		 delete[] train_matrices;
	}


	input_file.close();
	return new Classifier(k, n, class_names, Matrices, S_matrices);
}

void ParseTestData(string test_name, Classifier* classifier, string result_name) {
	ifstream test_file;
	ofstream result_file;
	test_file.open(test_name);

	if (!test_file.is_open()) {
		cout << "Cannot open the test file" << endl;
		return;
	}
   //открыть файл для записи result_name
	int m; //m кол-во тестовых матриц
	test_file >> m;

	result_file.open(result_name);
	result_file.precision(2);
	
	classifier->write_centers_of_classes(result_file); //передать result_file, чтобы записать туда


	for (int i = 0; i < m; i++) {
		vector<double> current_test;
		double x;
		for (int j = 0; j < classifier->n * classifier->n; j++) {
			test_file >> x;
			current_test.push_back(x); 
		}

		classifier->get_class(current_test, result_file); 
	}

	test_file.close();
	result_file.close();
}


