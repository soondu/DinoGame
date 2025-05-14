#pragma once
#include "ofMain.h"

class Obstacle {
public:
	ofImage image;//big cactus
	ofImage cactus1;
	ofImage cactus2;//small cactus
	ofImage cactus3;
	ofImage cactus4;

	ofImage remove(ofImage);
	ofImage ground(ofImage);
	ofImage wimage;//big cactus
	ofImage wcactus1;
	ofImage wcactus2;//small cactus
	ofImage wcactus3;
	ofImage wcactus4;

	int x, y;
	int speed;
	Obstacle(int, int, float, bool);
	void update();
	void draw();
	bool isOffScreen();
};