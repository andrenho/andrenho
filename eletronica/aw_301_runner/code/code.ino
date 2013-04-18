#include <stdint.h>

const byte FOREVER = 10;
const byte PIEZO = 7;
const byte WARMUP_PIN = 15;
const uint16_t* runs[] = {
  (uint16_t[]){ 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 0 }, // W1D1
  (uint16_t[]){ 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 0 }, // W1D2
  (uint16_t[]){ 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 0 }, // W1D3
  (uint16_t[]){ 90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 0 }, // W2D1
  (uint16_t[]){ 90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 0 }, // W2D2
  (uint16_t[]){ 90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 0 }, // W2D3
  (uint16_t[]){ 90, 90, 180, 180, 90, 90, 180, 180, 0 }, // W3D1
  (uint16_t[]){ 90, 90, 180, 180, 90, 90, 180, 180, 0 }, // W3D2
  (uint16_t[]){ 90, 90, 180, 180, 90, 90, 180, 180, 0 }, // W3D3
  (uint16_t[]){ 180, 90, 300, 150, 180, 90, 300, 0 }, // W4D1
  (uint16_t[]){ 180, 90, 300, 150, 180, 90, 300, 0 }, // W4D2
  (uint16_t[]){ 180, 90, 300, 150, 180, 90, 300, 0 }, // W4D3
  (uint16_t[]){ 300, 180, 300, 180, 300, 0 }, // W5D1
  (uint16_t[]){ 480, 300, 480, 0 }, // W5D2
  (uint16_t[]){ 1200, 0 }, // W5D3
  (uint16_t[]){ 300, 180, 480, 180, 300, 0 }, // W6D1
  (uint16_t[]){ 600, 180, 600, 0 }, // W6D2
  (uint16_t[]){ 1350, 0 }, // W6D3
  (uint16_t[]){ 1500, 0 }, // W7D1
  (uint16_t[]){ 1500, 0 }, // W7D2
  (uint16_t[]){ 1500, 0 }, // W7D3
  (uint16_t[]){ 1680, 0 }, // W8D1
  (uint16_t[]){ 1680, 0 }, // W8D2
  (uint16_t[]){ 1680, 0 }, // W8D3
  (uint16_t[]){ 1800, 0 }, // W9D1
  (uint16_t[]){ 1800, 0 }, // W9D2
  (uint16_t[]){ 1800, 0 }, // W9D3
};

enum { WARMUP, RUN, WALK } state;
int day = 0;
int current = 0; // current iteration

void setup() {
  // setup piezo
  pinMode(PIEZO, OUTPUT);

  // setup input pins
  for(int i=14; i >= 9; i--) {
    pinMode(i, INPUT);
    day <<= 1;
    day += (digitalRead(i) == HIGH ? 1 : 0);
  }
  if(day > 26) {
    beep(FOREVER);
  }
  
  // setup warmup
  pinMode(WARMUP_PIN, INPUT);
  state = (digitalRead(WARMUP_PIN) == HIGH ? WARMUP : RUN);
}


void beep(int count) {
  for(int i=0; i<count; i++) {
again:
    digitalWrite(PIEZO, HIGH);
    delay(400);
    digitalWrite(PIEZO, LOW);
    delay(300);
    if(count == FOREVER) {
      goto again;
    }
  }
}


void loop() {
  // warmup
  if(state == WARMUP) {
    beep(3);
    delay(1000 * 60 * 5);
    state = RUN;
  }

  // loop
  current = 0;
  while(runs[day][current] != 0) {
    
    // beep
    if(state == RUN) {
      beep(2);
      state = WALK; // for next iteration
    } else if(state == WALK) {
      beep(1);
      state = RUN; // for next iteration
    }
    
    // wait
    delay(1000 * runs[day][current]);
    current++;
  }

  // warmout
  beep(3);
  delay(1000 * 60 * 5);
  beep(FOREVER);
}
