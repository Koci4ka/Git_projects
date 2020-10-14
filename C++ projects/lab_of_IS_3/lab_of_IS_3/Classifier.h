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


	/*На выходе нужно вывести на экран/в файл ядра всех классов.
		распознаваемый объект
		расстояния до всех классов
		класс, к которому был отнесен этот объект.*/  

	string get_class(); //вычислить у какому классу относится объект
	float get_centers_of_classes(); //вычислить ядра в каждом классе
	float get_distance(); //расстояние объекта до всех классов
	//вывод распознаваемого объекта

private:

	int k;
	int n;
	char* class_names;
	vector<float>* Matrices;

};

