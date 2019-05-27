#pragma once

#include "ofMain.h"

class Map
{
	static const int LENGTH = 256;

public:
	void setup(float data[256][256],int scale);
	void update(ofFloatColor color);
	void draw();

private:
	ofMesh mesh;	
	ofVec3f v;
	
};