# Chrome Dinosaur Game Clone (OpenFrameworks)

## 0. 프로젝트 개요

이 프로젝트는 **OpenFrameworks(C++)**를 기반으로, 인터넷 연결이 끊겼을 때 크롬 브라우저에서 표시되는 **공룡 게임(Dino Game)**을 재현한 2D 점프 게임입니다.  
기본 동작 외에도 **밤낮 전환**, **공룡 상하 반전**, **점수 기반 이벤트 출력** 등 다양한 인터랙션 기능을 추가하여 게임의 몰입감과 피드백 요소를 강화했습니다.  
이미지 및 폰트 리소스를 포함한 완전한 게임 형태로 구성되어 있으며, OpenFrameworks의 Project Generator를 통해 실행할 수 있습니다.

---

## 1. 구현한 것

- 크롬 공룡 게임의 기본 구조 (장애물 점프 회피 게임)
- 점프, 상하 반전, 밤낮 전환 등 사용자 상호작용 기능
- 점수 기반 이벤트 출력 및 시각적 효과
- 점수 / 속도 / 최고점 UI 표시
- 리소스 이미지 및 폰트 적용

---

## 2. 주요 기능

| 키 입력 | 기능 설명                            |
|---------|-------------------------------------|
| 스페이스바 | 점프 (장애물 회피)                  |
| ↑ / ↓ 키 | 공룡 상하 반전                      |
| r 키     | 밤 시간대일 때, 달의 색깔 변경      |
| 게임 오버 후 스페이스바 | 게임 재시작                |

---

## 3. 실행 방법

1. OpenFrameworks의 **Project Generator**로 새 프로젝트 생성
2. 생성된 프로젝트의 `src/` 폴더에 `src.zip`의 소스 파일 7개 복사  
   - `main.cpp`, `ofApp.h`, `ofApp.cpp`, `Dinosaur.h`, `Dinosaur.cpp`, `Obstacle.h`, `Obstacle.cpp`
3. `bin/data/` 폴더에 `bindata.zip`의 리소스 10개 복사  
   - 이미지 9개, TTF 폰트 1개 포함
4. 실행: **Ctrl + F5** 또는 IDE에서 Run

---

## 4. 게임 방법

- 공룡은 오른쪽에서 생성되는 장애물을 **점프해서 회피**해야 하며, 가능한 높은 점수를 획득하는 것이 목표입니다.
- 공룡이 장애물에 닿으면 **Game Over** 문구와 함께 게임이 종료됩니다.
- **스페이스바를 누르면 게임이 다시 시작**됩니다.

---

## 5. 구현 세부 내용

- 점수 시스템:
  - 점수가 **500의 배수**일 경우: `surpassed $score points!` 문구가 화면 중앙에서 **3회 깜빡임**
  - 최고점수 갱신 시: `update best score!` 문구가 **반복 깜빡이며 출력**
- 밤낮 전환 시스템:
  - 점수 구간이 `n*1000 ~ n*1000+200`일 때: 배경이 **밤(검정색)**으로 바뀌고, 공룡/장애물 색상이 **반전(흰색)**됨
  - `n*1000+180 ~ n*1000+200` 구간 동안은 **장애물이 생성되지 않음**
- 게임 UI:
  - **오른쪽 상단**에 현재 점수, 속도, 최고점수 실시간 표시

---

## 6. 기술 스택

- **Language**: C++
- **Framework**: [OpenFrameworks](https://openframeworks.cc/)
- **IDE 추천**: Visual Studio 2022, Xcode 등

---

## 7. 스크린샷

> ![alt text](image.png)

## 8. 디렉토리 구조

```
DinoGameProject/
├── src/
│   ├── main.cpp
│   ├── ofApp.h / ofApp.cpp
│   ├── Dinosaur.h / Dinosaur.cpp
│   ├── Obstacle.h / Obstacle.cpp
├── bin/
│   └── data/
│       ├── *.png (9 images)
│       └── *.ttf (1 font)
├── README.md
├── src.zip
└── bindata.zip
```

