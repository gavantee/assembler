#include "timer.h"

#include <time.h>
#include <stdio.h>

#include "emulator.h"

int mills;

void timer_init() {
  mills = clock() * 1000 / CLOCKS_PER_SEC;
}

void timer(int tim_cfg) {
  int t;
  switch(tim_cfg) {
  case 0:
    t = 500;
    break;
  case 1:
    t = 1000;
    break;
  case 2:
    t = 1500;
    break;
  case 3:
    t = 2000;
    break;
  case 4:
    t = 5000;
    break;
  case 5:
    t = 5000;
    break;
  case 6:
    t = 30000;
    break;
  case 7:
    t = 60000;
    break;
  }
  int new_mills = clock() * 1000 / CLOCKS_PER_SEC;
  if (new_mills - mills >= t) {
    // printf("Delay: %d", t);
    mills = new_mills;
    int_req(2);
  }
}

