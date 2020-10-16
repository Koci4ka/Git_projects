#pragma once
#include <string>
#include "Classifier.h"

using namespace std;


Classifier* ParseTrainData(string file_name);

void ParseTestData(string test_name, Classifier* classifier, string result_name);