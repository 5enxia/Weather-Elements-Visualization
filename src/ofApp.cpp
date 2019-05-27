#include "ofApp.h"
//#define MULTI

//--------------------------------------------------------------
void ofApp::setup() {
#ifdef MULTI
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			mapData[j][i].load("14.145" + ofToString(58 + i) + ".64"+ ofToString(42 + j) +".csv", "altitude");
			maps[j][i].setup(mapData[i][j].altitude, 1);
		}
	}
#else
	single_mapData.load("14.14560.6442.csv", "altitude");
	single_map.setup(single_mapData.altitude, 1);
#endif

	weatherData.load("data.avg_low_high_rain_shine.csv", "weather");

	date = weatherData.date;
	avg = weatherData.temp_avg;
	low = weatherData.temp_low;
	high = weatherData.temp_high;
	rain = weatherData.data_rain;
	shine = weatherData.data_shine;

	ofSetBackgroundColor(0);
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetCircleResolution(64);

	cam.disableMouseInput();
#ifdef MULTI
	cam.setDistance(1000);
#else
	cam.setDistance(10);
#endif
	sound.load("Deep_Gray.mp3");
	sound.play();
	sound.setLoop(true);
	sound.setVolume(volume);
	se.load("se.mp3");
	se.setVolume(0.25);
	alart4hot.load("alart4hot.mp3");
	alart4hot.setVolume(1);
	alart4rain.load("alart4rain.mp3");
	alart4rain.setVolume(1);
}

//--------------------------------------------------------------
void ofApp::update() {
	

	rZ += 0.025;
	
	pos = sound.getPosition();
	if (pos > 0.975) {
		if (volume >= 0.0) {
			volume -= 0.005;
		}
	}
	if (pos < 0.025) {
		if (volume <= 1.0) {
			volume += 0.005;
		}
	}
	sound.setVolume(volume);

	if ((ofGetFrameNum() + 10) % 360 == 0) {
		se.play();
	}

	if (ofGetFrameNum() % 360 == 0) {
		seedX = ofRandom(25,75);
		seedY = ofRandom(25,75);
		seedZ = ofRandom(25, 75);
		seedZ = ofRandom(25,75);
		lookX = ofMap(seedX, 0, 100, -256 / 2 * scale, 256 / 2 * scale);
		lookZ = ofMap(seedY, 0, 100, -256 / 2 * scale, 256 / 2 * scale);
		lookY = -ofMap(seedZ, 0, 100, 0, 10);
		cam.setDistance(ofRandom(50, 500));
		
		cam.lookAt(ofVec3f(lookX, lookY, lookZ));
		
		date.push_back(date[0]);
		date.erase(date.begin());

		avg.push_back(avg[0]);
		avg.erase(avg.begin());

		low.push_back(low[0]);
		low.erase(low.begin());

		high.push_back(high[0]);
		high.erase(high.begin());
		
		rain.push_back(rain[0]);
		rain.erase(rain.begin());

		shine.push_back(shine[0]);
		shine.erase(shine.begin());

		if (high[0] > 35)
		{
			alart4hot.play();
		}
		if (rain[0] > 50) {
			alart4rain.play();
		}

		change = 1;

		if (rain[0] < 1)
		{
			ofSetBackgroundColor(ofFloatColor(192. / 255., 57. / 255., 43. / 255.,0.5));
		}
		else if (rain[0] < 10) 
		{
			ofSetBackgroundColor(ofFloatColor(127. / 255., 140. / 255., 141. / 255., 0.5));
		}
		else {
			ofSetBackgroundColor(ofFloatColor(41. / 255., 128. / 255., 185. / 255., 0.5));
		}
	}

	if (change >= 0)
	{
		change -= 0.02;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	//map--------------------------------
	ofPushMatrix();
	ofEnableDepthTest();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2, 0);
	cam.begin();

	
	ofRotateX(-60);
	ofRotateZ(rZ);
#ifdef MULTI
	for (int i = -3; i < 3; i++)
	{
		for (int j = -3; j < 3; j++)
		{
			ofPushMatrix();
			ofTranslate(LENGTH * i, LENGTH * j, 0);
			maps[j + 3][i+3].draw();
			ofPopMatrix();
		}
	}
#else
	ofPushMatrix();
	ofTranslate(0, 0, 0);
	single_map.draw();
	ofPopMatrix();
#endif
	

	cam.end();
	ofDisableDepthTest();
	ofPopMatrix();


	//Grid--------------------------------
	/*int k = 1000;
	int c = 255;
	ofSetColor(c, 0, 0);
	ofDrawLine(ofVec3f(-k, 0, 0), ofVec3f(k, 0, 0));
	ofSetColor(0, c, 0);
	ofDrawLine(ofVec3f(0, -k, 0), ofVec3f(0, k, 0));
	ofSetColor(0, 0, c);
	ofDrawLine(ofVec3f(0, 0, -k), ofVec3f(0, 0, k));*/

	ofSetColor(ofFloatColor(1,0.75));
	int l = 30;
	int m = 8;
	int init = 1;
	int n = 4;
	/*for (int i = init; i < 16 *n; i++)
	{
		for (int j = 1; j < 9 * n; j++)
		{
			ofLine(l * i, l * j - l/m,l * i, l * j + l /m);
		}
	}
	for (int i = 1; i < 9 * n; i++)
	{
		for (int j = init; j < 16 * n; j++)
		{
			ofLine( l * j - l / m, l * i, l * j + l / m, l * i);
		}
	}*/

	//Gui--------------------------------
	ofFill();

	ofSetColor(ofFloatColor( change,0.75));
	ofDrawRectangle(0, 0, ofGetWidth() / 16 * 3, ofGetHeight());

	ofSetColor(ofFloatColor(1, 0.1));


	ofPushMatrix();
	ofTranslate(l, l);


	ofPushMatrix();
	ofTranslate(0, l);
	ofDrawBitmapString("", 0, 0);
	ofTranslate(0, l);
	ofTranslate(0, l);
	ofDrawBitmapString("", 0, 0);
	ofTranslate(0, l);
	ofDrawRectangle(0, 0 ,l*10, l);
	ofTranslate(0, l);
	ofTranslate(0, l);
	ofDrawBitmapString("", 0, 0);
	ofTranslate(0, l);
	ofDrawRectangle(0, 0, l * 10, l);
	ofTranslate(0, l);
	ofTranslate(0, l);
	ofDrawBitmapString("", 0, 0);
	ofTranslate(0, l);
	ofDrawRectangle(0, 0, l * 10, l);
	ofTranslate(0, l);
	ofTranslate(0, l);
	ofDrawBitmapString("", 0, 0);
	ofTranslate(0, l);
	ofDrawRectangle(0, 0, l * 10, l);
	ofTranslate(0, l);
	ofTranslate(0, l);
	ofDrawBitmapString("", 0, 0);
	ofTranslate(0, l);
	
	ofPushMatrix();
	ofTranslate(0, l * 5);
	ofDrawCircle(l * 5, 0, l * 4);
	ofTranslate(0, l * 5);
	ofDrawBitmapString("", 0, 0);

	ofPopMatrix();

	ofPopMatrix();

	ofSetColor(ofFloatColor(91. / 255., 255. / 255., 245. / 255., 0.75));

	ofPushMatrix();
	ofTranslate(0, l);
	ofDrawBitmapString("WEATHER_ELEMNTS_VISUALIZATION" , 0, 0);
	ofTranslate(0, l);
	ofTranslate(0, l);
	ofDrawBitmapString(date[0], 0, 0);
	ofTranslate(0, l);
	ofDrawRectangle(0, 0, ofMap(avg[0], -50, 50, 0, l * 10), l);
	ofTranslate(0, l);
	ofTranslate(0, l);
	ofDrawBitmapString("AVERAGE_TEMPERATURE " + ofToString(avg[0]), 0, 0);
	ofTranslate(0, l);
	if (high[0] > 35)
	{
		ofSetColor(ofFloatColor(255. / 255., 245. / 255., 91. / 255., 0.75));
	}
	ofDrawRectangle(0, 0, ofMap(high[0], -50, 50, 0, l * 10), l);
	ofTranslate(0, l);
	ofTranslate(0, l);
	ofDrawBitmapString("HIGHEST_TEMPERATURE " + ofToString(high[0]), 0, 0);
	ofTranslate(0, l);
	ofSetColor(ofFloatColor(91. / 255., 255. / 255., 245. / 255., 0.75));
	ofDrawRectangle(0, 0, ofMap(low[0], -50, 50, 0, l * 10), l);
	ofTranslate(0, l);
	ofTranslate(0, l);
	ofDrawBitmapString("LOWEST_TEMPERATURE " + ofToString(low[0]) , 0, 0);
	ofTranslate(0, l);
	if (rain[0] > 50)
	{
		ofSetColor(ofFloatColor(255. / 255., 245. / 255., 91. / 255., 0.75));
	}
	ofDrawRectangle(0, 0, ofMap(rain[0], 0, 150, 0, l * 10), l);
	ofTranslate(0, l);
	ofTranslate(0, l);
	ofDrawBitmapString("PRECIPITATION " + ofToString(rain[0]) + " M", 0, 0);
	ofTranslate(0, l);

	ofSetColor(ofFloatColor(91. / 255., 255. / 255., 245. / 255., 0.75));
	ofPushMatrix();
	ofTranslate(0, l * 5);
	int end_deg = -90 + ofMap(shine[0],0.0, 24.0, 0, 360);
	std::vector<ofPoint> vertices;
	for (int deg = -90; deg < end_deg; deg += 1) {
		vertices.push_back(ofPoint(l * 5 + l * 4 * cos(deg * DEG_TO_RAD), l * 4 * sin(deg * DEG_TO_RAD)));
	}
	ofBeginShape();
	ofVertices(vertices);
	ofVertex(l * 5, 0);
	ofEndShape(true);
	ofTranslate(0, l * 5);
	ofDrawBitmapString("DAY_LENGTH " + ofToString(shine[0]) + " HOUR", 0, 0);

	ofPopMatrix();

	ofPopMatrix();


	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
