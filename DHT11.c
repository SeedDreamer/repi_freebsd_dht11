#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "DHT11.h"
#include "read_dht11.h"
#include "time.h"

int date_temp[2];
int date_humid[2];
int date_validtion[1];
int PIN = 4;
int list_sum(int list[], int len)
{
    int i = 0;
    int total = 0; 
    for (i=0;i<len;i++)
        total += list[i];
    return total;
}

int open_pin(void)
{
    printf("PIN:%d\n", PIN);
    handle = gpio_open(0);
    if (handle == GPIO_INVALID_HANDLE)
            return 0;
    return 1;
}

int dht_init(void)
{   

    printf("Starting.....\n");
   
        gpio_pin_output(handle, PIN);
        gpio_pin_high(handle, PIN);
       // sleep(3);
        delay_s(3);
        //delay_us(3000000000000);
        if (read_dht11_date(PIN))
        {
            printf("DHT11 data read ok!\n");
        
            if (date_validtion[0] != (list_sum(date_temp,2) + list_sum(date_humid,2)))
            {
                printf("\n\n============================\n");
                printf(" No avail date!\n Pass\n");
                printf("============================\n\n");
                
      
            }   
            else
                printf("\n\n============================\n");
                printf("Avail date yes\n");
                printf("Hum -> %d.%d %%\n", date_temp[0], date_temp[1]);
                printf("Tem -> %d.%d °C \n", date_humid[0], date_humid[1]);
                printf("validtion -> %d \n", date_validtion[0]);
                printf("============================\n");

        }
        else
        {
            printf("DHT11 data not read\n");
            gpio_pin_output(handle, PIN);
            gpio_pin_high(handle, PIN);
           // sleep(2);
            delay_s(3);
            
        }
    return 0;

}


float get_tem(void)
{
    return date_temp[0]+(date_temp[1]*0.1);
}

float get_hum(void)
{
    return date_humid[0]+(date_humid[1]*0.1);
}

int main(void)
{
    int i = open_pin()? 1:0;
    int j;
    while(i)
    {
        for (j=0; j < 10; j++)
        {
            dht_init();
            printf("get_tem:%.2f\n", get_tem());
            printf("get_hum:%.2f\n\n", get_hum());
            memset(date_temp,0,sizeof(date_temp));
            memset(date_humid,0,sizeof(date_humid));
            memset(date_validtion,0,sizeof(date_validtion));
            printf("j = %d\n", j);
        }
        delay_s(5);
    }
    gpio_close(handle);
    return 0;
}
//note 运行久了会卡住，wcpu 100%


