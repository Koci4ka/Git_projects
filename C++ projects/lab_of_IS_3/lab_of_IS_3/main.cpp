#include <iostream>
#include "parser.h"

using namespace std;



int main(int argc, const char* argv[]) {

	//if (argc < 2) {

		//cout << "error" << endl;
		//return -1;
		
//	}
	//string input_file = argv[1];
	string input_file = "train_data.txt";
	Classifier* classifier = ParseTrainData(input_file);
	cout << classifier->k << classifier->n << classifier->class_names[0] << classifier->Matrices[0].size() << endl;
	
	return 0;
}