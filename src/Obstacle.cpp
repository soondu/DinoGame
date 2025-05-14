#include "Obstacle.h"

Obstacle::Obstacle(int startX, int startY, float obstacleSpeed, bool bw) {
    image.load("cactus1.png"); //190x400
    cactus1.load("1cactus.png");//140x280
    cactus2.load("2cactus.png");//250x240
    cactus3.load("3cactus.png");//295x190
    cactus4.load("4cactus.png"); //360x190

    image.resize(image.getWidth() * 0.6, image.getHeight() * 0.6);
    cactus1.resize(cactus1.getWidth() * 0.6, cactus1.getHeight() * 0.6);
    cactus2.resize(cactus2.getWidth() * 0.7, cactus2.getHeight() * 0.7);
    cactus3.resize(cactus3.getWidth() * 0.88, cactus3.getHeight() * 0.88);
    cactus4.resize(cactus4.getWidth() * 0.88, cactus4.getHeight() * 0.88);

    cactus1 = ground(cactus1);
    cactus2 = ground(cactus2);
    cactus3 = ground(cactus3);
    cactus4 = ground(cactus4);
    image = ground(image);

    wimage = remove(image);
    wcactus1 = remove(cactus1);
    wcactus2 = remove(cactus2);
    wcactus3 = remove(cactus3);
    wcactus4 = remove(cactus4);

    x = startX;
    y = startY;
    speed = obstacleSpeed;

    int randomChoice = ofRandom(5);
    if (bw) {
        if (randomChoice == 0) {
            image = wimage;
            y -= 58;
        }
        else if (randomChoice == 1) {
            image = wcactus1;
            y += 7;
        }
        else if (randomChoice == 2) {
            image = wcactus2;
            y += 7;
        }
        else if (randomChoice == 3) {
            image = wcactus3;
            y += 7;
        }
        else if (randomChoice == 4) {
            image = wcactus4;
            y += 7;
        }
    }
    else {
        if (randomChoice == 0) {
            y -= 58;
        }
        else if (randomChoice == 1) {
            image = cactus1;
            y += 7;
        }
        else if (randomChoice == 2) {
            image = cactus2;
            y += 7;
        }
        else if (randomChoice == 3) {
            image = cactus3;
            y += 7;
        }
        else if (randomChoice == 4) {
            image = cactus4;
            y += 7;
        }
    }
}
ofImage Obstacle::remove(ofImage image) {
    ofPixels pixels = image.getPixels();
    ofColor c = image.getColor(3, image.getHeight() / 2);
    for (int y = 0; y < pixels.getHeight(); y++) {
        for (int x = 0; x < pixels.getWidth(); x++) {
            ofColor color = pixels.getColor(x, y);
            if (color == c) {
                pixels.setColor(x, y, ofColor(255)); // 흰색으로 반전
            }
            else if (color == ofColor(150, 150, 150)) {}
            else {
                pixels.setColor(x, y, ofColor(0)); // 나머지 색은 검정으로 설정
            }
        }
    }
    image.setFromPixels(pixels);
    image.update();

    return image;
}
ofImage Obstacle::ground(ofImage image) {
    ofPixels pixels = image.getPixels();
    ofColor c = image.getColor(3, image.getHeight() / 2);
    for (int y = pixels.getHeight() - 17; y < pixels.getHeight(); y++) {
        for (int x = 0; x < pixels.getWidth(); x++) {
            ofColor color = pixels.getColor(x, y);
            if (color != c) {
                pixels.setColor(x, y, ofColor(150, 150, 150)); // 나머지 색은 회색으로 설정
            }
        }
    }
    image.setFromPixels(pixels);
    image.update();

    return image;
}

void Obstacle::update() {
    x -= speed;
}

void Obstacle::draw() {
    image.draw(x, y);
}

bool Obstacle::isOffScreen() {
    return x + image.getWidth() < 0;
}