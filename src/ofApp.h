#pragma once

#include "ofMain.h"
#include "csvReader.h"
#include "Map.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	const int LENGTH = 256;

	//weatherData
	csvReader weatherData;
	vector<string> date;
	vector<float> avg;
	vector<float> low;
	vector<float> high;
	vector<float> rain;
	vector<float> shine;
	float change = 0;

	//MapData
	int scale = 1;
	csvReader single_mapData;
	csvReader mapData[6][6];
	Map single_map;
	Map maps[6][6];

	//sound
	ofSoundPlayer sound;
	ofSoundPlayer se;
	ofSoundPlayer alart4hot;
	ofSoundPlayer alart4rain;
	float volume = 0.0;

	//camera
	ofEasyCam cam;
	float rZ = 0;	
	float pos;
	float lookX, lookY, lookZ;
	int seedX,seedY,seedZ;

	//gui

};
