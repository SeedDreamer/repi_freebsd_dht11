#include "DHT11.h"
#include "read_dht11.h"
#include "time.h"
#include <unistd.h>
extern int date_temp[2];
extern int date_humid[2];
extern int date_validtion[1];

int read_8bit(int list[], int n, int PIN)
{
    long int i, wtime;
    for (i=0;i<=7;i++)
    {
        //wait to high
        while (!gpio_pin_get(handle, PIN));
        wtime = get_wait_us(1,PIN);
        //test        
        list[n] *= 2;
        if (wtime > 46)      
            list[n]++;
        //else
            //pass;
            //return -1;                        
    }
    return 0;
}

int read_dht11_date(int PIN)
{
    //call dht11
    //gpio_pin_output(handle, PIN);
    gpio_pin_low(handle, PIN);
    delay_us(25000);
    
    gpio_pin_high(handle, PIN);
  
    //init read date form dhtll
    gpio_pin_input(handle, PIN);
    gpio_pin_pulldown(handle, PIN);
    delay_us(40);
        
    if (gpio_pin_get(handle, PIN) == 0)
    {    //wait 
        while (!gpio_pin_get(handle, PIN));
        while (gpio_pin_get(handle, PIN));
        while (!gpio_pin_get(handle, PIN));
        //start read date
        //read temp H
        read_8bit(date_temp, 0,PIN);  
        //read temp L
        read_8bit(date_temp, 1,PIN); 
        //read date_humid H
        read_8bit(date_humid, 0,PIN); 
        //read date_humid L
        read_8bit(date_humid, 1,PIN);
        //read validtion
        read_8bit(date_validtion, 0,PIN);
        return 1;
    }       
    else
        return 0;
}
