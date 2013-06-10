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

const int TIME_UP = 10;
const int TIME_DOWN = 11;

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


// check if the silence button was pressed
bool checkSilence(int a)
{
  if(analogRead(SILENCE) > 500)
  {
    alarm[a] = false;
    return true;
  }
  else
    return false;
}

// check if a button was pressed
void checkButtons()
{
  int change = 0;
  if(digitalRead(TIME_UP))
    change = 5;
  else if(digitalRead(TIME_DOWN))
    change = -5;

  if(change)
  {
    int tmr = selectedTimer();
    timer[tmr] += change;
    if(timer[tmr] < 0)
      timer[tmr] = 0;
    if(timer[tmr] >= 36000)
      timer[tmr] = 35999;
  }
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
  int a = -1;
  for(int i=0; i<N_TIMERS; i++)
    if(alarm[i])
    {
      a = i;
      break;
    }
  if(a == -1)
    return;
    
  // play
  int time = 500 / ((a+1) * 2);
  for(int i=0; i<(a+1); i++)
  {
    unsigned long tm = (time * 2) + millis();
    tone(SPEAKER, NOTE_A4, time);
    while(millis() < tm)
      displayNumbers();
    //delay(time * 2); // half time playing, half time silent
    if(checkSilence(a))
      return;
  }
  // don't play
  for(int i=0; i<5; i++)
  {
    if(checkSilence(a))
      return;
    //delay(100);
    unsigned long tm = (time * 2) + millis();
    while(tm > millis())
      displayNumbers();
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

// return the selected timer
int selectedTimer()
{
  if(digitalRead(TIMER_1))
    return 1;
  else if(digitalRead(TIMER_2))
    return 2;
  else
    return 0;
}

// show all the numbers in the display
void displayNumbers()
{
  int h, m, s;
  int n[5];
  int tmr = selectedTimer();
  
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
  displayNumbers();
  if(isAlarmed())
    playAlarm();
  else
  {
    displayNumbers();
    checkButtons();
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
  pinMode(TIME_UP, INPUT);
  pinMode(TIME_DOWN, INPUT);
  
  // initialize timers
  for(int i=0; i<N_TIMERS; i++)
    timer[i] = 0;
}
