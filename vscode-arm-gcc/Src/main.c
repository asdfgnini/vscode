#include "main.h"


int main()
{
    bsp_Init();


    while(1)
    {
       bsp_LedToggle(1);
       bsp_LedToggle(2);
       bsp_DelayMS(500);
       
    }
}