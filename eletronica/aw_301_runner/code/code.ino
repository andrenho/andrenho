#include <avr/sleep.h>
//#include <avr/wdt.h>

/************* GLOBAL VARIABLES ***************/

const int FOREVER = 10;
const int PIEZO = 7;
const int WARMUP_PIN = 15;
const int days[] = { 
    0,  17,  34, // W1
   51,  64,  77, // W2
   90,  99, 108, // W3
  117, 125, 133, // W4
  141, 147, 151, // W5
  153, 159, 163, // W6
  165, 167, 169, // W7
  171, 173, 175, // W8
  177, 179, 181, // W9
  0
};

enum State { WARMUP, RUN, WALK, WARMOUT, DONE } state = WARMUP;
volatile int day = 0;
volatile int current = 0;
volatile int timer = 0;

volatile boolean f_wdt=1;

/*********** PUBLIC METHODS *************/

void setup() {
  //Serial.begin(9600);
  read_controls();
  //beep(2);
  //setup_watchdog(9);
  setup_watchdog(5);
}


void loop() {
  if(f_wdt == 1) {
    f_wdt = 0;
  
    step();
    delay(50);
  }
  system_sleep();
}

/************* PRIVATE METHODS ***********/

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


inline void read_controls(){ 
  // setup piezo
  pinMode(PIEZO, OUTPUT);

  // setup input pins
  for(int i=14; i >= 9; i--) {
    pinMode(i, INPUT_PULLUP); // INPUT_PULLUP
    day <<= 1;
    day += (digitalRead(i) == HIGH ? 0 : 1);
  }
  if(day > 26) {
    beep(FOREVER);
  }
  
  // setup warmup
  pinMode(WARMUP_PIN, INPUT_PULLUP);
  state = (digitalRead(WARMUP_PIN) == LOW ? WARMUP : RUN);
  day = 0; // TODO
  current = days[day];
}


inline void step() {
  static int runs[] = {
  60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 0, // W1D1
  60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 0, // W1D2
  60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 60, 90, 0, // W1D3
  90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 0, // W2D1
  90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 0, // W2D2
  90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 90, 120, 0, // W2D3
  90, 90, 180, 180, 90, 90, 180, 180, 0, // W3D1
  90, 90, 180, 180, 90, 90, 180, 180, 0, // W3D2
  90, 90, 180, 180, 90, 90, 180, 180, 0, // W3D3
  180, 90, 300, 150, 180, 90, 300, 0, // W4D1
  180, 90, 300, 150, 180, 90, 300, 0, // W4D2
  180, 90, 300, 150, 180, 90, 300, 0, // W4D3
  300, 180, 300, 180, 300, 0, // W5D1
  480, 300, 480, 0,           // W5D2
  1200, 0,                    // W5D3
  300, 180, 480, 180, 300, 0, // W6D1
  600, 180, 600, 0,           // W6D2
  1350, 0,                    // W6D3
  1500, 0, // W7D1
  1500, 0, // W7D2
  1500, 0, // W7D3
  1680, 0, // W8D1
  1680, 0, // W8D2
  1680, 0, // W8D3
  1800, 0, // W9D1
  1800, 0, // W9D2
  1800, 0, // W9D3
  0
};
  /*
  if(runs[current] == 0) {
    state = WARMOUT;
  }*/
  
  if(timer == 0) {
    
    /*Serial.print("State: ");
    switch(state) {
      case WARMUP:  Serial.println("WARMUP");  break;
      case WARMOUT: Serial.println("WARMOUT"); break;
      case RUN:     Serial.println("RUN");     break;
      case WALK:    Serial.println("WALK");    break;
      case DONE:    Serial.println("DONE");    break;
    }*/
      
    if(state == WARMUP) {
      beep(3);
      timer = 300 / 8;
      state = RUN;
    } else if(state == WARMOUT) {
      beep(3);
      timer = 300/8;
      state = DONE;
    } else if(state == DONE) {
      beep(FOREVER);
    } else { // state != WARMUP
      if(state == RUN) {
        beep(2);
        state = WALK;
      } else if(state == WALK) {
        beep(1);
        state = RUN;
      }
      timer = runs[current] / 8;
    }
    //Serial.print("Timer set to ");
    //Serial.println(timer);
    current++;
    //Serial.print("Current set to ");
    //Serial.println(current);
  } else {
    --timer;
    //Serial.print("Timer: ");
    //Serial.println(timer);
  }
}

/************ TIMER ROUTINES *************/

// 0=16ms, 1=32ms,2=64ms,3=128ms,4=250ms,5=500ms
// 6=1 sec,7=2 sec, 8=4 sec, 9= 8sec
inline void setup_watchdog(int ii) {
  byte bb;
  int ww;
  if (ii > 9 ) 
    ii=9;
  bb=ii & 7;
  if (ii > 7) 
    bb|= (1<<5);
  bb|= (1<<WDCE);
  ww=bb;

  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  WDTCSR = bb;
  WDTCSR |= _BV(WDIE);
}


inline void system_sleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();
  sleep_mode();                        // System sleeps here
  sleep_disable();                     // System continues execution here when watchdog timed out 
}

ISR(WDT_OVERFLOW_vect) {
//ISR(WDT_vect) {
  f_wdt=1;  // set global flag
}
