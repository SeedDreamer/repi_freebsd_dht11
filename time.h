#ifndef TIME_H
#define TIME_H

struct timespec time_start;
struct timespec time_end;
long int get_wait_us(int state, int PIN);
void delay_us(unsigned int howLong);
void delay_ms(unsigned int ms);
void delay_s(unsigned int s);
#endif