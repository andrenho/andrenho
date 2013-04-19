volatile uint8_t f_wdt=1;

void system_sleep() {
	set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
	sleep_enable();
	sleep_mode();                        // System sleeps here
	sleep_disable();                     // System continues execution here when watchdog timed out 
}


void watchdog_init()
{
	cli();
	wdt_reset();
	WDTCSR = (1<<WDCE) | (1<<WDE); // enable WDT
	WDTCSR = (1<<WDIE) | (1<<WDP2) | (1<<WDP1); // interrupt every 1 sec
	sei();
}


ISR(WDT_OVERFLOW_vect) {
//ISR(WDT_vect) {
	f_wdt=1;  // set global flag
}
