#include "ofApp.h"

//--------------------------------------------------------------

void ofApp::setup() {
    ofSetFrameRate(60);
    ofBackground(255);
    bw = false;
    mooncolor = ofColor(255, 255, 0); //노란 달
    score = 0;
    speed = 0;
    sc = score;
    sp = speed;
    isGameOver = false;
    lastObstacleTime = 0;
    font.load("verdana.ttf", 20);
    //ofBackground(0,0,0);
}
//--------------------------------------------------------------

void ofApp::update() {
    if (isGameOver) return;

    //몇 페이즈인지 확인/출력
    speed = (score / 100) * 1.1 + 15;
    sc = score;
    sp = speed;
    //black or white
    if (((sc / 200) % 5) == 0 && sc > 200) bw = true;
    else bw = false;

    ofSeedRandom();
    dino.update();
    float currentTime = ofGetElapsedTimef();
    float random = ofRandom(1.0 - (speed / 200) * 0.05, 1.85);;
    if (currentTime - lastObstacleTime > random) {
        if (((sc / 20) - 9) % 50 > 1) {
            obstacles.push_back(Obstacle(ofGetWidth(), ofGetHeight() - 188, speed, bw));
            lastObstacleTime = currentTime;
        }
        else if (sc < 200) {
            obstacles.push_back(Obstacle(ofGetWidth(), ofGetHeight() - 188, speed, bw));
            lastObstacleTime = currentTime;
        }
    }


    for (auto& obstacle : obstacles) {
        obstacle.update();
    }

    obstacles.erase(remove_if(obstacles.begin(), obstacles.end(), [](Obstacle& ob) {
        return ob.isOffScreen();
        }), obstacles.end());

    for (auto& obstacle : obstacles) {
        if (dino.x + dino.dino.getWidth() - 40 > obstacle.x && dino.x + 30 < obstacle.x + obstacle.image.getWidth() &&
            dino.y + dino.dino.getHeight() - 50 > obstacle.y && dino.y +30 < obstacle.y + obstacle.image.getHeight()) {
            isGameOver = true;
        }
    }
    score += 0.3;
}


//--------------------------------------------------------------
void ofApp::draw() {
    if (bw) {
        ofBackground(0);
        ofSetColor(mooncolor);
        ofDrawCircle(130, 150, 40 + (sc / 50) * 2);
    }
    else {
        ofBackground(255);
    }
    ofSetColor(150, 150, 150);
    ofDrawRectangle(0, ofGetHeight() - 30, ofGetWidth(), 30);

    ofSetColor(255);
    dino.draw(bw);
    for (auto& obstacle : obstacles) {
        obstacle.draw();
    }

    ofSetColor(102, 0, 153);
    font.drawString("Score: " + ofToString(sc), ofGetWidth() - 300, 60);
    font.drawString("Speed: " + ofToString(sp), ofGetWidth() - 300, 100);
    if (best != 0) {
        if (score > best) {
            font.drawString("Best Score: " + ofToString(sc), ofGetWidth() - 300, 140);
        }
        else font.drawString("Best Score: " + ofToString(best), ofGetWidth() - 300, 140);
    }
    ofSetColor(255);


    if ((sc / 50) % 10 == 0 && score > 100 && !isGameOver) {
        if (((sc / 10) % 100) % 2) {
            if (bw) {
                ofSetColor(0);
            }
            else
                ofSetColor(255);
        }
        else {
            if (bw)
                ofSetColor(mooncolor);
            else ofSetColor(102, 0, 153);
        }
        font.drawString("Surpassed " + ofToString((sc / 50) * 50) + " points!", ofGetWidth() / 2 - 110, ofGetHeight() / 2);
    }

    if (score > best && score - best < 50 && best != 0) {
        if (blink) {
            ofSetColor(240, 20, 20);
            font.drawString("Update Best Score!", ofGetWidth() / 2 - 70, ofGetHeight() / 2 - 50);
            blink = !blink;
        }
        else {
            ofSetColor(255, 255, 255);
            font.drawString("Update Best Score!", ofGetWidth() / 2 - 70, ofGetHeight() / 2 - 50);
            blink = !blink;
        }
    }


    if (isGameOver) {
        ofSetColor(240, 20, 20);
        font.drawString("GAME OVER", ofGetWidth() / 2 - 70, ofGetHeight() / 2);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == ' ') {
        if (isGameOver) {
            resetGame();
        }
        else {
            dino.jump();
        }
    }
}

void ofApp::resetGame() {
    isGameOver = false;
    mooncolor = ofColor(255, 255, 0);
    //create maximum
    if (best == 0) {
        best = score;
    }
    else if (score > best) best = score;

    score = 0;
    obstacles.clear();
    lastObstacleTime = ofGetElapsedTimef();
}

// 공룡 뒤집기
void ofApp::flipImage(ofImage& image) {
    ofPixels pixels = image.getPixels(); // 이미지의 픽셀 데이터 가져오기
    int height = image.getHeight();
    int width = image.getWidth();

    for (int y = 0; y < height / 2; y++) {
        for (int x = 0; x < width; x++) {
            // 현재 픽셀의 반대 픽셀의 위치 계산
            int top = y * width + x;
            int bottom = (height - 1 - y) * width + x;

            // 위아래 픽셀 교환
            ofColor temp = pixels.getColor(x, y);
            pixels.setColor(x, y, pixels.getColor(x, height - 1 - y));
            pixels.setColor(x, height - 1 - y, temp);
        }
    }

    image.setFromPixels(pixels);
    image.update();
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    //밤일 때 r을 누르면 달의 색깔이 바뀐다
    if (key == 'r' && bw) {
        if (mooncolor == ofColor(255, 255, 0))
            mooncolor = ofColor(220, 220, 220);
        else mooncolor = ofColor(255, 255, 0);
    }

    //방향키 업다운을 누르면 공룡이 뒤집힌다
    if (key == OF_KEY_DOWN || key == OF_KEY_UP) {
        flipImage(dino.dino);
        flipImage(dino.deaddino);
        flipImage(dino.rightdino);
        flipImage(dino.leftdino);
        flipImage(dino.wdino);
        flipImage(dino.wdeaddino);
        flipImage(dino.wrightdino);
        flipImage(dino.wleftdino);
    }

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
