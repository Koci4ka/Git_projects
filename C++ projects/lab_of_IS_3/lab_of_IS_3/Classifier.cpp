#include "Classifier.h"
#include <string>
#include <cmath>
#include <limits>

Classifier::Classifier(int _k, int _n, char* _class_names, vector<double>* _Matrices, vector<double>* _S_matrices) {

	n = _n;
	k = _k;
	class_names = _class_names;
	Matrices = _Matrices;
	S_matrices = _S_matrices;

}
/*На выходе нужно вывести на экран/в файл ядра всех классов
		распознаваемый объект
		расстояния до всех классов
		класс, к которому был отнесен этот объект.*/
void Classifier::get_class(vector<double> matr, ofstream& result_file) {
	result_file << "Testing object:" << endl;
	write_matrix(matr, result_file);
	result_file << "Computing class distances:" << endl;
	vector<double> dist;
	for (int i = 0; i < k; i++) {
		dist.push_back(get_distance(matr, i));
		result_file << "Distance: " << dist[i] << " ";
		result_file << "to class: " << class_names[i] << endl;	
	}
	double min_dist = numeric_limits<double>::infinity();
	int clss = -1;
	for (int i = 0; i < k; i++) {
		if (dist[i] < min_dist) {
			min_dist = dist[i];
			clss = i;
		}
	}
	result_file << "Predicted class: " << class_names[clss] << endl;
	result_file << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;;
} 


vector<double> Classifier::vect_matr_mult(vector<double> v, vector<double> S) {
	vector<double> res;
	for (int i = 0; i < n * n; i++) {
		res.push_back(0);
	}
	for (int i = 0; i < n * n; i++) { //номер столбцa в матрице
		for (int j = 0; j < n * n; j++) { // номер столбца в векторе
			res[i] += v[j] * S[j * n * n + i];
		}
	}
	return res;
}

double Classifier::vec_vec_mult(vector<double> v1, vector<double> v2) {
	double res = 0;
	for (int i = 0; i < n * n; i++) { 
		res += v1[i] * v2[i];
	}
	return res;
}

double Classifier::get_distance(vector<double> v, int clss) {
	vector<double> v1;
	for (int i = 0; i < n * n; i++) {
		v1.push_back(v[i] - Matrices[clss][i]);
	}
	vector<double> v2 = vect_matr_mult(v1, S_matrices[clss]);
	return sqrt(vec_vec_mult(v2, v1));
}



void Classifier::write_centers_of_classes(ofstream& result_file) {
	result_file << "Centers of classes:" << endl;
	for (int i = 0; i < k; i++) {
		result_file << "Class: " << class_names[i] << endl;
		result_file << "Center: " << endl;
		write_matrix(Matrices[i], result_file);
		result_file << "_________________________________________________" << endl;
	}
	result_file << "=================================================" << endl << endl;
}

void Classifier::write_matrix(vector<double> matr, ofstream& result_file) {

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			result_file << matr[i * n + j] << " ";	
		}
		result_file << endl;
	}
	result_file << endl;
}







