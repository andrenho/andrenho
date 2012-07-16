const int POT = A0;
const int BUTTON = 2;

const int POT_READS = 20;
const int POT_DIF = 10;
const int TIMER_MAX = 10800; // 3 hours
const float TIMER_COEF = (float)TIMER_MAX / 800;
const int N_TIMERS = 4;

int last_pot = 0;
int timer[N_TIMERS];
int last_button = 0;
int sel_timer = 0;

void time_fmt(int timer, int& h, int& m, int& s)
{
  s = timer % 60;
  m = (timer / 60) % 60;
  h = timer / (60 * 60);
}

void print_timer()
{
  int h, m, s;
  time_fmt(timer[sel_timer], h, m, s);  
  Serial.print("Timer ");
  Serial.print(sel_timer);
  Serial.print(" => ");
  Serial.print(h);
  Serial.print(":");
  Serial.print(m);
  Serial.print(":");
  Serial.println(s);
}

void move_timer(int amt)
{
  timer[sel_timer] += (TIMER_COEF * (float)amt);
  if(timer[sel_timer] < 0)
    timer[sel_timer] = 0;
  if(timer[sel_timer] > (TIMER_MAX * TIMER_COEF))
    timer[sel_timer] = (TIMER_MAX * TIMER_COEF);
  print_timer();
}

void checkPotentiometer()
{
  int pot = 0;
  for(int i=0; i<POT_READS; i++)
    pot += analogRead(POT);
  pot /= POT_READS;
  if(pot < last_pot-POT_DIF || pot > last_pot+POT_DIF)
  {
    if(pot > last_pot)
      move_timer(pot - last_pot);
    else if(pot < last_pot)
      move_timer((pot - last_pot) * 1.3);
    last_pot = analogRead(POT);
  }
}

void checkButton()
{
  int b;
  if((b = digitalRead(BUTTON)) != last_button)
  {
    last_button = b;
    sel_timer++;
    if(sel_timer >= N_TIMERS)
     sel_timer = 0;   
    Serial.print("Timer selected: ");
    Serial.println(sel_timer);
    print_timer();
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT);
  for(int i=0; i<N_TIMERS; i++)
    timer[i] = 0;
  last_pot = analogRead(POT);
  last_button = digitalRead(BUTTON);
}

void loop()
{
  checkPotentiometer();
  checkButton();
  delay(1);
}
