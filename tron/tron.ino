#include "Arduboy.h"

#define DIR_UP 0
#define DIR_DOWN 1
#define DIR_LEFT 2
#define DIR_RIGHT 3

Arduboy arduboy;
unsigned int score = 0, highScore = 0;
char textBuf[15];

void startScreen() { 
  arduboy.clear();
  arduboy.setCursor(10, 20);
  arduboy.setTextSize(2);
  arduboy.print("TRONDUBOY");

  arduboy.setTextSize(1);
  arduboy.setCursor(6, 53);
  arduboy.print("PRESS FIRE TO START");
  arduboy.display();

  while(! (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON))) {
    delay(15);
  }
}

void newGame() {
  unsigned int playerX, playerY, playerDir;

  score = 0;
  
  arduboy.clear();
  arduboy.drawRect(0, 0, 128, 64, 1);

  arduboy.initRandomSeed();
  playerX = random(10, 118);
  playerY = random(10, 54);

  arduboy.drawPixel(playerX, playerY, 1);
  arduboy.display();

  playerDir = random(0, 3);
  
  while(true) {
    if (arduboy.pressed(UP_BUTTON)) {
      playerDir = DIR_UP;
    } else if (arduboy.pressed(DOWN_BUTTON)) {
      playerDir = DIR_DOWN;
    } else if (arduboy.pressed(LEFT_BUTTON)) {
      playerDir = DIR_LEFT;
    } else if (arduboy.pressed(RIGHT_BUTTON)) {
      playerDir = DIR_RIGHT;
    }

    switch(playerDir) {
      case DIR_UP:
        playerY--;
        break;
      case DIR_DOWN:
        playerY++;
        break;
      case DIR_LEFT:
        playerX--;
        break;
      case DIR_RIGHT:
        playerX++;
        break;      
    }

    if (arduboy.getPixel(playerX, playerY)) {
      break;
    }

    arduboy.drawPixel(playerX, playerY, 1);
    arduboy.display();
    score++;

    delay(30);
  }
}

void gameOver() { 
  arduboy.clear();
  arduboy.setCursor(10, 20);
  arduboy.setTextSize(2);

  if (score > highScore) {
    sprintf(textBuf, "NEW HI:%u", score);
  } else {
    sprintf(textBuf, "SCORE:%u", score);
  }
  
  arduboy.print(textBuf);

  arduboy.setTextSize(1);

  if (score <= highScore) {
    arduboy.setCursor(12, 42);
    sprintf(textBuf, "HI SCORE:%u", highScore);
    arduboy.print(textBuf);
  } else {
    highScore = score;
  }
  
  arduboy.setCursor(6, 53);
  arduboy.print("PRESS FIRE TO START");
  arduboy.display();

  while(! (arduboy.pressed(A_BUTTON) || arduboy.pressed(B_BUTTON))) {
    delay(15);
  }
}

void setup() {
  arduboy.beginNoLogo();
}

void loop() {
  while(true) {
    startScreen(); 
    newGame();  
    gameOver(); 
  }
}
