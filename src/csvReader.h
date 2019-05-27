#pragma once
#include "ofMain.h"
class csvReader
{
public:
	void load(string filePath, string fileType);
	float altitude[256][256];
	vector<string> date;
	vector<float> temp_avg;
	vector<float> temp_low;
	vector<float> temp_high;
	vector<float> data_rain;
	vector<float> data_shine;
private:
	int currentIndex;
	vector<string> words;
	string filePath, fileType;
};

