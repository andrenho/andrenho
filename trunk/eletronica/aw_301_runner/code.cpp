const int FOREVER == 10;
const int PIEZO = 7;
const int WARMUP_PIN = 15;
const int** runs = {
  { 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 0 }, // W1D1
  { 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 0 }, // W1D2
  { 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 0 }, // W1D3
  { 90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 0 }, // W2D1
  { 90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 0 }, // W2D2
  { 90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 0 }, // W2D3
  { 90, 90, 180, 180, 90, 90, 180, 180, 0 }, // W3D1
  { 90, 90, 180, 180, 90, 90, 180, 180, 0 }, // W3D2
  { 90, 90, 180, 180, 90, 90, 180, 180, 0 }, // W3D3
  { 180, 90, 300, 150, 180, 90, 300, 0 }, // W4D1
  { 180, 90, 300, 150, 180, 90, 300, 0 }, // W4D2
  { 180, 90, 300, 150, 180, 90, 300, 0 }, // W4D3
  { 300, 180, 300, 180, 300, 0 }, // W5D1
  { 480, 300, 480, 0 }, // W5D2
  { 1200, 0 }, // W5D3
  { 300, 180, 480, 180, 300, 0 }, // W6D1
  { 600, 180, 600, 0 }, // W6D2
  { 1350, 0 }, // W6D3
  { 1500, 0 }, // W7D1
  { 1500, 0 }, // W7D2
  { 1500, 0 }, // W7D3
  { 1680, 0 }, // W8D1
  { 1680, 0 }, // W8D2
  { 1680, 0 }, // W8D3
  { 1800, 0 }, // W9D1
  { 1800, 0 }, // W9D2
  { 1800, 0 }, // W9D3
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
again:
  for(int i=0; i<count; i++) {
    analogWrite(PIEZO, 128);
    delay(500);
    analogWrite(PIEZO, 0);
    delay(500);
  }
  if(count == FOREVER) {
    goto again;
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
