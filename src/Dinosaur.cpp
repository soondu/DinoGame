#include "Dinosaur.h"
#include "ofApp.h"

Dinosaur::Dinosaur() {
    leftdino.load("leftdino.png");//540x540
    rightdino.load("rightdino.png");
    deaddino.load("deaddino.png");
    dino.load("dinosaur.png");

    leftdino.resize(dino.getWidth() * 0.3, dino.getHeight() * 0.3);
    rightdino.resize(dino.getWidth() * 0.3, dino.getHeight() * 0.3);
    deaddino.resize(dino.getWidth() * 0.3, dino.getHeight() * 0.3);
    dino.resize(dino.getWidth() * 0.3, dino.getHeight() * 0.3);

    wdino = remove(dino);
    wdeaddino = remove(deaddino);
    wleftdino = remove(leftdino);
    wrightdino = remove(rightdino);

    x = 50;
    y = ofGetHeight() - dino.getHeight() - 33;
    footSwitch = false;
    lastSwitchTime = 0;
    isJump = false;
    jumpDuration = 0.8; // seconds
    jumpHeight = 550; // pixels
}


void Dinosaur::update() {
    float currentTime = ofGetElapsedTimef();
    if (currentTime - lastSwitchTime > 0.1) {
        footSwitch = !footSwitch;
        lastSwitchTime = currentTime;
    }

    if (isJump) {
        float jumpTime = currentTime - jumpStartTime;
        if (jumpTime < jumpDuration) {
            y = ofGetHeight() - dino.getHeight() - 20 - (sin((jumpTime / jumpDuration) * PI) * jumpHeight);
        }
        else {
            isJump = false;
            y = ofGetHeight() - dino.getHeight() - 33;
        }
    }
}

ofImage Dinosaur::remove(ofImage image) {
    ofPixels pixels = image.getPixels();
    ofColor c = image.getColor(image.getWidth() / 2, image.getHeight() / 2);
    for (int y = 0; y < pixels.getHeight(); y++) {
        for (int x = 0; x < pixels.getWidth(); x++) {
            ofColor color = pixels.getColor(x, y);
            if (color == c) {
                pixels.setColor(x, y, ofColor(255)); // 흰색으로 반전
            }
            else {
                color.a = 0;
                pixels.setColor(x, y, color); // 나머지 색은 투명으로 설정
            }
        }
    }
    image.setFromPixels(pixels);
    image.update();

    return image;
}

void Dinosaur::draw(bool bw) {
    ofEnableAlphaBlending();

    if (bw) {
        //ofBackground(0);
        ofSetColor(255);
        if (isJump) {
            wdino.draw(x, y);
        }
        else if (app->isGameOver) {
            wdeaddino.draw(x, y);
        }
        else {
            if (footSwitch) {
                wleftdino.draw(x, y);
            }
            else {
                wrightdino.draw(x, y);
            }
        }
    }
    else {
        //ofBackground(255);
        ofSetColor(255);
        if (isJump) {
            dino.draw(x, y);
        }
        else if (app->isGameOver) {
            deaddino.draw(x, y);
        }
        else {
            if (footSwitch) {
                leftdino.draw(x, y);
            }
            else {
                rightdino.draw(x, y);
            }
        }
    }


    ofDisableAlphaBlending();
}

void Dinosaur::jump() {
    if (!isJump) {
        isJump = true;
        jumpStartTime = ofGetElapsedTimef();
    }
}