#include <Arduino.h>
#include <TFT_eSPI.h>
#include "awsten_font.h"
#define font &AwstensHandwriting_Regular12pt7b

TFT_eSPI tft = TFT_eSPI();

enum ScrollDir {
    RIGHT_TO_LEFT,
    LEFT_TO_RIGHT,
    TOP_TO_BOTTOM,
    BOTTOM_TO_TOP
};

void setup() {
    tft.init();
    tft.setRotation(2); // 2 = buttons on top 
    tft.fillScreen(TFT_BLACK); // baseline 
    tft.setTextSize(1); 
    tft.setTextColor(TFT_GREEN, TFT_BLACK); // green font for fandom album
    tft.setFreeFont(font);
    randomSeed(23);  // fixed seed
}

void drawCentered(const char* text, int y) {
    int x = (tft.width() - tft.textWidth(text)) / 2;
    tft.drawString(text, x, y);
}

void scrollLinesOnce(const char* lines[], int count, int speed) {

    int screenW = tft.width();
    int screenH = tft.height();

    int lineHeight = 45;      
    int blockHeight = lineHeight * count;

    // find widest line for horizontal centering
    int maxWidth = 0;
    for (int i = 0; i < count; i++) {
        int w = tft.textWidth(lines[i]);
        if (w > maxWidth) maxWidth = w;
    }

    // choose random direction (0-3)
    ScrollDir dir = (ScrollDir)random(0, 4);

    unsigned long startTime = millis();

    while (true) {

        int offset = (millis() - startTime) / speed;

        // calculate base X/Y
        int baseX = 0;
        int baseY = 0;

        // check if animation is finished
        bool finished = false;

        switch (dir) {

            case RIGHT_TO_LEFT:
                baseX = screenW - offset;
                baseY = (screenH - blockHeight) / 2;
                finished = (baseX < -(maxWidth+10));  // fully off screen
                break;

            case LEFT_TO_RIGHT:
                baseX = -maxWidth + offset;
                baseY = (screenH - blockHeight) / 2;
                finished = (baseX > screenW + 10);
                break;

            case TOP_TO_BOTTOM:
                baseX = (screenW - maxWidth) / 2;
                baseY = -blockHeight + offset;
                finished = (baseY > screenH);
                break;

            case BOTTOM_TO_TOP:
                baseX = (screenW - maxWidth) / 2;
                baseY = screenH - offset;
                finished = (baseY < -blockHeight);
                break;
        }

        if (finished) break;

        // clear screen (or a rectangle for better performance)
        tft.fillScreen(TFT_BLACK);

        // draw each line, centered horizontally
        for (int i = 0; i < count; i++) {
            int w = tft.textWidth(lines[i]);
            int x = baseX + (maxWidth - w) / 2;
            tft.drawString(lines[i], x, baseY + i * lineHeight);
        }

        delay(16); // ~60 FPS
    }
}

void member_cycle() {

    const char* members[3] = {".Otto.", ".Geoff.", ".Awsten."};

    for (int i = 0; i < 3; i++) {

        tft.fillScreen(TFT_BLACK);

        drawCentered("My name's", 50);
        drawCentered(members[i], 110);
        drawCentered("and", 170);

        delay(1350);
    }
}



void friends() {
    const char* lines[] = {
        "We're",
        "all",
        ".friends."
        };
        
    tft.fillScreen(TFT_BLACK);
    scrollLinesOnce(lines, 3, 7);
    delay(500);
    tft.fillScreen(TFT_BLACK);
}

void loop() {
    member_cycle();
    friends(); 
}

