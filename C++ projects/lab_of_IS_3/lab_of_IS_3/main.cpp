#include <iostream>
#include "parser.h"

using namespace std;



int main(int argc, const char* argv[]) {

	string input_file = "train_data.txt";
	string test_file = "test_data.txt";
	string result_file = "result.txt";
	Classifier* classifier = ParseTrainData(input_file);
	ParseTestData(test_file, classifier, result_file);
	
	return 0;
}