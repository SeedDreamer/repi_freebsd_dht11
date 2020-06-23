#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include "DHT11.h"
#include "time.h"

clockid_t clock_id = CLOCK_MONOTONIC_FAST; 

long int get_wait_us(int state,int PIN)
{
/*
    struct timespec time_start={0,0};
    struct timespec time_end={0,0};
    
    long int wait_time=0;
   
    //gettimeofday(&time_start, NULL);
    
    clock_gettime(clock_id, &time_start);
    
    while(gpio_pin_get(handle, PIN) == state);
    
    //gettimeofday(&time_end, NULL);
    clock_gettime(clock_id, &time_end);
    
    if (time_end.tv_nsec < time_start.tv_nsec)
    {
       //s = (time_end.tv_sec-time_start.tv_sec) - 1;
        printf("There is 'end < start'. \n");
       // printf("us: %f\n", (1E9-time_start.tv_nsec)+time_end.tv_nsec);
        wait_time = (1E9-time_start.tv_nsec)+time_end.tv_nsec;
        return wait_time;  
    }
    else
    {
        //s = time_end.tv_sec - time_start.tv_sec;
        //printf("us: %ld\n", time_end.tv_nsec - time_start.tv_nsec);
        wait_time = time_end.tv_nsec - time_start.tv_nsec;
        return wait_time;
    }
    */
    struct timeval time_start={0,0};
    struct timeval time_end={0,0};
      
    gettimeofday(&time_start, NULL);
        
    while(gpio_pin_get(handle, PIN) == state);
    
    gettimeofday(&time_end, NULL);
    
    
    if (time_end.tv_usec < time_start.tv_usec)
    {
       
        printf("There is 'end < start'. \n");
         
        return (1E9-time_start.tv_usec)+time_end.tv_usec;;  
    }
    else
    {
        //s = time_end.tv_sec - time_start.tv_sec;
        //printf("us: %ld\n", time_end.tv_nsec - time_start.tv_nsec);
        return time_end.tv_usec - time_start.tv_usec;
    }
}

void delay_us(unsigned int howLong)
{
   
  struct timeval tNow, tLong, tEnd ;

  gettimeofday(&tNow, NULL) ;
  tLong.tv_sec  = howLong / 1000000 ;
  tLong.tv_usec = howLong % 1000000 ;
  timeradd (&tNow, &tLong, &tEnd) ;

  while (timercmp(&tNow, &tEnd, <))
    gettimeofday(&tNow, NULL) ;
    
    /*
    struct timespec ts = {0,howLong*1000};
    //TIMER_ABSTIME
    clock_nanosleep(clock_id, 0, &ts, NULL);
  */
}

void delay_ms(unsigned int ms)
{
    delay_us(ms*1000);
}
void delay_s(unsigned int s)
{
    struct timespec ts = {s,0};
    //TIMER_ABSTIME
    clock_nanosleep(clock_id, 0, &ts, NULL);
}
long int get_wait_us_bak(int state,int PIN)
{ 
    struct timespec ts = {0,40*1000*1000};
    //TIMER_ABSTIME
    clock_nanosleep(clock_id, 0, &ts, NULL);
    if(gpio_pin_get(handle, PIN) == state)
        return 70000;
    else
        return 30000;

}
