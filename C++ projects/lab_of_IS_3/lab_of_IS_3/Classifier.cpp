#include "Classifier.h"
#include <string>

Classifier::Classifier(int _k, int _n, char* _class_names, vector<float>* _Matrices) {

	n = _n;
	k = _k;
	class_names = _class_names;
	Matrices = _Matrices;

}

string get_class() {
	//присвоить класс объекту
} 

float get_centers_of_classes() {
	//получить ядра классов
}

float get_distance() {
	//посчитать расстояния объекта до всех классов
}







