//
// Ports
//
const int TIMER = A0;          // potentiometer port (changes time)
const int SPEAKER = 8;         // speaker port
const int SELECTOR = 2;        // button port (select time)
const int SILENCE = 3;         // silence button
const int NOTE_A4 = 440;

//
// Timer potentiometer
//
const int TIMER_READS = 20;  // number of reads from the potentiomenter
                             //   before moving - this should reduce glitches.
const int TIMER_DIF = 10;    // only considers a potentiomenter movement when
                             //   it moves this much
const int TIMER_MAX = 10800; // 3 hours
// one potentiometer unit will change this much seconds
const float TIMER_COEF = (float)TIMER_MAX / 800;

//
// Timer selector
//
const int N_TIMERS = 4;      // number of timers
unsigned long next_sec = 0;  // millisecond of the next second

//
// Global variable
//
int last_pot = 0;            // last reading from potentiometer
int last_button = 0;         // last reading from selector button
signed int timer[N_TIMERS];         // current time of each timer
bool alarm[N_TIMERS];        // check if alarm is on
int selected = 0;            // timer currently selected

// format time in hours / minutes / seconds
void time_fmt(int timer, int& h, int& m, int& s)
{
  s = timer % 60;
  m = (timer / 60) % 60;
  h = timer / (60 * 60);
}

// print the timer to a serial output
void print_timer()
{
  int h, m, s;
  for(int i=0; i<N_TIMERS; i++)
  {
    time_fmt(timer[i], h, m, s);
    Serial.print("[");
    if(i == selected)
      Serial.print("(*)");
    Serial.print(h);
    Serial.print(":");
    Serial.print(m);
    Serial.print(":");
    Serial.print(s);
    Serial.print("] ");
  }
  Serial.println("");
}

// change the timer when moving the potentiometer
void move_timer(int amt)
{
  timer[selected] += (TIMER_COEF * (float)amt);
  if(timer[selected] < 0)
    timer[selected] = 0;
  if(timer[selected] > (TIMER_MAX * TIMER_COEF))
    timer[selected] = (TIMER_MAX * TIMER_COEF);
  print_timer();
}

// check if the potentiometer is moving
void checkTimer()
{
  int pot = 0;
  for(int i=0; i<TIMER_READS; i++)
    pot += analogRead(TIMER);
  pot /= TIMER_READS;
  if(pot < last_pot-TIMER_DIF || pot > last_pot+TIMER_DIF)
  {
    if(pot > last_pot)
      move_timer(pot - last_pot);
    else if(pot < last_pot)
      move_timer((pot - last_pot) * 1.3);
    last_pot = analogRead(TIMER);
  }
}

// check if the button was pressed
void checkSelector()
{
  int b;
  if((b = digitalRead(SELECTOR)) != last_button)
  {
    last_button = b;
    selected++;
    if(selected >= N_TIMERS)
     selected = 0;   
    Serial.print("Timer selected: ");
    Serial.println(selected);
    print_timer();
  }
}

// check if the silence button was pressed
bool checkSilence(int a)
{
  if(digitalRead(SILENCE))
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
      {
        Serial.print("Alarm on! ");
        Serial.println(i);
        alarm[i] = true;
      }
    }
  }
  print_timer();
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
    Serial.print("Beep! ");
    tone(SPEAKER, NOTE_A4, time);
    delay(time * 2); // half time playing, half time silent
    if(checkSilence(a))
      return;
  }
  Serial.println("");
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
    checkTimer();
    checkSelector();
    delay(1);
  }
}

// initialize the ATMEGA
void setup()
{
  Serial.begin(9600);
  pinMode(SELECTOR, INPUT);
  pinMode(SILENCE, INPUT);
  for(int i=0; i<N_TIMERS; i++)
    timer[i] = 0;
  timer[3] = 5;
  last_pot = analogRead(TIMER);
  last_button = digitalRead(SELECTOR);
}
