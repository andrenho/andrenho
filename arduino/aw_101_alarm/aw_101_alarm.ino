//
// Ports
//
const int SPEAKER = 9;         // speaker port
const int SILENCE = A0;        // silence button
const int NOTE_A4 = 440;
const int DIGIT_START = 0;     // first of the binary digits
const int DIGIT_V_START = 4;   // first of the digits supply

const int TIMER_1 = 12;        // timer selector
const int TIMER_2 = 13;

//
// Timer selector
//
const int N_TIMERS = 3;      // number of timers
unsigned long next_sec = 0;  // millisecond of the next second

//
// Global variable
//
signed int timer[N_TIMERS];  // current time of each timer
bool alarm[N_TIMERS];        // check if alarm is on
int selected = 0;            // timer currently selected


// format time in hours / minutes / seconds
void time_fmt(int timer, int& h, int& m, int& s)
{
  s = timer % 60;
  m = (timer / 60) % 60;
  h = timer / (60 * 60);
}


// check if the button was pressed
void checkSelector()
{
  // TODO
}

// check if the silence button was pressed
bool checkSilence(int a)
{
  if(analogRead(SILENCE) == 1023)
  {
    alarm[a] = false;
    return true;
  }
  else
    return false;
}

// run the timer (decrease) for one second
void oneSecond()
{
  for(int i=0; i<N_TIMERS; i++)
  {
    if(timer[i] > 0)
    {
      timer[i] -= 1;
      if(timer[i] == 0)
        alarm[i] = true;
    }
  }
}

// play alarm
void playAlarm()
{
  // find alarm
  int a = 0;
  for(int i=0; i<N_TIMERS; i++)
    if(alarm[i])
    {
      a = i;
      break;
    }
  // play
  int time = 500 / ((a+1) * 2);
  for(int i=0; i<(a+1); i++)
  {
    tone(SPEAKER, NOTE_A4, time);
    delay(time * 2); // half time playing, half time silent
    if(checkSilence(a))
      return;
  }
  // don't play
  for(int i=0; i<5; i++)
  {
    if(checkSilence(a))
      return;
    delay(100);
  }
}

// check if the timer is alarmed
bool isAlarmed()
{
  for(int i=0; i<N_TIMERS; i++)
    if(alarm[i])
      return true;
  return false;
}

// show all the numbers in the display
void displayNumbers()
{
  int tmr;
  if(digitalRead(TIMER_1))
    tmr = 0;
  else if(digitalRead(TIMER_2))
    tmr = 1;
  else
    tmr = 2;
  int h, m, s;
  int n[5];
  
  time_fmt(timer[tmr], h, m, s);
  n[0] = s % 10;
  n[1] = s / 10;
  n[2] = m % 10;
  n[3] = m / 10;
  n[4] = h % 10;
  
  for(int i=DIGIT_V_START, m=0; i<(DIGIT_V_START+5); i++, m++)
  {
    for(int k=0; k<4; k++)
      digitalWrite(k+DIGIT_START, (n[m] & (1 << k)) ? HIGH : LOW);
    digitalWrite(i, LOW);
    delay(2);
    digitalWrite(i, HIGH);
  }
}

// main loop
void loop()
{
  if(millis() > next_sec)
  {
    next_sec = millis() + 1000;
    oneSecond();
  }
  if(isAlarmed())
    playAlarm();
  else
  {
    checkSelector();
    displayNumbers();
    delay(1);
  }
}

// initialize the ATMEGA
void setup()
{
  // initialize 7 segment display
  for(int i=DIGIT_START; i<(DIGIT_START+4); i++)
    pinMode(i, OUTPUT);
  for(int i=DIGIT_V_START; i<(DIGIT_V_START+5); i++)
  {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  
  // initialize buttons 
  pinMode(SILENCE, INPUT);
  pinMode(TIMER_1, INPUT);
  pinMode(TIMER_2, INPUT);
  
  // initialize timers
  for(int i=0; i<N_TIMERS; i++)
    timer[i] = 0;
  timer[0] = 5;
}
