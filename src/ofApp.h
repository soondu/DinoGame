#pragma once
#include "ofMain.h"
#include "Obstacle.h"
#include "Dinosaur.h"


class ofApp : public ofBaseApp {

public:
	Dinosaur dino;
	vector<Obstacle> obstacles;

	bool blink;
	int best;
	ofColor mooncolor; //´Þ»ö±ò


	float score;
	float speed;
	int sc;
	int sp;
	bool bw;

	bool isGameOver;
	bool isJump;
	float lastObstacleTime;
	void resetGame();
	void remove(ofImage&);
	void flipImage(ofImage& image); //°ø·æ µÚÁý±â

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	ofTrueTypeFont font;
};
