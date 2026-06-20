#include <LPC21xx.h>   
#include "delay.h"
#include"can.h"   

main()   

{   

		CANF rxFrame;   

  Init_CAN1();   
  IODIR0|=1<<7;
  IOSET0=1<<7;

	while(1)   

	{   

        CAN1_Rx(&rxFrame);
		if(rxFrame.Data1==0x87654321)
		IOPIN0^=1<<7;    
		delay_ms(1000);

	}    

	

}   

//MID=rxFrame.ID

