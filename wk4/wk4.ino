#include <Wire.h>
#include <SPI.h>
#include "SSD1306Wire.h"
#include "animation.h"
#define Logo_width 64
#define Logo_height 64

SSD1306Wire  display(0x3c, 21, 22);
int button = 12;
int old_st = 0;
int cur_st = 0;
int walking = 0;
unsigned long old_time = 0;
unsigned long cur_time = 0;
int walk_count = 0;
int idle_count = 0;
int walk_duration = 120;
int idle_duration = 250;
int curpos_x = 0;

void setup() {
  pinMode(button,INPUT);
  Serial.begin(9600);
  display.init();
  display.setContrast(255); 
  cur_time = millis();
  old_time = cur_time;
  display.clear();
  display.drawXbm(0,0,Logo_width,Logo_height,idle[idle_count]);
  display.display();
}

void loop() { 
  cur_time = millis();
  cur_st = digitalRead(button);
  Serial.println(cur_st);
  delay(30);
  if(old_st == 0 && cur_st == 1)
  {
    walking = 1;
    walk_count = 0;
    old_time = cur_time;
    cur_time = cur_time + walk_duration;
  }
  if(old_st == 1 && cur_st == 0)
  {
    walking = 0;
    old_time = cur_time;
    cur_time = cur_time + idle_duration;
  }
  old_st = cur_st;
  if(walking)
  {
    if((cur_time - old_time) > walk_duration)
    {
      display.clear();
      curpos_x = curpos_x + 40*(cur_time - old_time)/1000;
      if(curpos_x > (64+64))
      {
        curpos_x = -64;
      }
      display.drawXbm(curpos_x,0,Logo_width,Logo_height,walk[walk_count]);
      display.display();
      walk_count++;
      if(walk_count > 7)
      {
        walk_count = 0;
      }
      old_time = cur_time;
    }
  }
  else{
    if((cur_time - old_time) > idle_duration)
    {
      display.clear();
      display.drawXbm(curpos_x,0,Logo_width,Logo_height,idle[idle_count]);
      display.display();
      idle_count++;
      if(idle_count > 1)
      {
        idle_count = 0;
      }
      old_time = cur_time;
    }
  }
}
