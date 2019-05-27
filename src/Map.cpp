#include "Map.h"

void Map::setup(float data[256][256],int scale)
{
	mesh.setMode(OF_PRIMITIVE_TRIANGLES);

	for (int j = 0; j <LENGTH; j++) {
		for (int i = 0; i < LENGTH; i++) {
			/*v.x = ofMap(i, 0, LENGTH, -LENGTH / 2 * scale, LENGTH / 2 * scale);
			v.y = ofMap(j, 0, LENGTH, -LENGTH / 2 * scale, LENGTH / 2 * scale);*/
			v.x = i *scale;
			v.y = j * scale;
			v.z = data[j][i] * scale;
			mesh.addVertex(v);
			//mesh.addColor(ofFloatColor(30.0 / 255.0, 190.0 / 255.0, 180.0 / 255.0, ofMap(v.z,0,30,0.,1.)));
			mesh.addColor(ofFloatColor(236, 240, 241, ofMap(v.z, 0, 30, 0, 255)));
		}
	}


	// Generate order of indices to set triangles per rows and column
	for (int j = 0; j < LENGTH - 1; j++) {
		for (int i = 0; i < LENGTH - 1; i++) {

			mesh.addIndex(i + j * LENGTH);         // 0
			mesh.addIndex((i + 1) + j * LENGTH);     // 1
			mesh.addIndex(i + (j + 1)*LENGTH);     // 6

			mesh.addIndex((i + 1) + j * LENGTH);     // 1
			mesh.addIndex((i + 1) + (j + 1)*LENGTH); // 7
			mesh.addIndex(i + (j + 1)*LENGTH);     // 6
		}
	}
}

void Map::update(ofFloatColor color)
{
	mesh.clearColors();
	for (int j = 0; j <LENGTH; j++) {
		for (int i = 0; i < LENGTH; i++) {
			mesh.addColor(color);
		}
	}
}

void Map::draw()
{
	mesh.drawWireframe();
}