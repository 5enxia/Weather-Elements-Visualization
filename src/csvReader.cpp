#include "csvReader.h"

void csvReader::load(string filePath, string fileType)
{
	this->currentIndex = 0;

	ofFile file(filePath);

	if (!file.exists()) {
		ofLogError("The file " + filePath + " is missing");
	}

	ofBuffer buffer(file);

	for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
		string line = *it;

		this->words = ofSplitString(line, ",");

		if (fileType == "altitude")
		{
			for (int i = 0; i < this->words.size(); i++)
			{
				this->altitude[currentIndex][i] = std::stof(words[i]);
			}
			this->currentIndex++;
		}
		else if (fileType == "weather")
		{
			for (int i = 0; i < words.size(); i++)
			{
				if (i == 0)
				{
					this->date.push_back(words[i]);
				}
				if (i == 1)
				{
					this->temp_avg.push_back(std::stof(words[i]));
				}
				if (i==2)
				{
					this->temp_low.push_back(std::stof(words[i]));
				}
				if (i ==3)
				{
					this->temp_high.push_back(std::stof(words[i]));
				}
				if (i == 4)
				{
					this->data_rain.push_back(std::stof(words[i]));
				}
				if (i == 5)
				{
					this->data_shine.push_back(std::stof(words[i]));
				}
			}
			this->currentIndex++;
		}
		else {
			ofLogError(fileType + " is wrong");
		}
		
	}
}
