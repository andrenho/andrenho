const int FOREVER == 10;
const int PIEZO = 7;
const int WARMUP_PIN = 15;
const int** runs = {
  { 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 0 },
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
