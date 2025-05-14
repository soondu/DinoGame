#pragma once
#include "ofMain.h"

class ofApp;

class Dinosaur {
public:
	ofImage dino;
	ofImage deaddino;
	ofImage leftdino;
	ofImage rightdino;

	ofImage wdino;
	ofImage wdeaddino;
	ofImage wleftdino;
	ofImage wrightdino;

	bool field[201][541];

	int x, y;
	bool isJump;
	bool footSwitch;
	float jumpDuration;
	float jumpHeight;
	float lastSwitchTime;
	float jumpStartTime;

	void update();
	void draw(bool);
	void jump();
	ofImage remove(ofImage image);
	Dinosaur();

private:
	ofApp* app;
};