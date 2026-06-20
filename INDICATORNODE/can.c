#include<lpc21xx.h>
#include"types.h"
#include"defines.h"
#include"delay.h"
#include"can_defines.h"
#include"can.h"

void Init_CAN1(void)
{
	//cfg p0.25 as CAN1_RX pin (RD1)
	PINSEL1|=0x00040000;

	//Reset CAN1 controller
	SETBIT(C1MOD, RM_BIT);

	//all received msgs are accepted
	CLRBIT(AFMR, ACCOFF_BIT);
	SETBIT(AFMR, ACCBP_BIT);

	//set baudrate for CAN
	C1BTR=BTR_LVAL;

	//enable CAN controller
	CLRBIT(C1MOD, RM_BIT);

}
void CAN1_Tx(CANF txF)
{
	//checking that thr tx buffer is empty
	while(READBIT(C1GSR, TBS1_BIT)==0);

	//cfg Tx ID
	C1TID1=txF.ID;

	//cfg RTR & DLC
	C1TFI1=(txF.BFV.RTR<<RTR_BIT)|
			(txF.BFV.DLC<<DLC_BITS);

	//check whether D/R frame to transmit
	if(txF.BFV.RTR==0)
	{
		//if D frame, wr to data transmit buffers
		C1TDA1=txF.Data1;  //bytes 1-4
		C1TDB1=txF.Data2;  //bytes 5-8
	}

	//select Tx Buff 1 and start transmission
	C1CMR|=1<<STB1_BIT | 1<<TR_BIT;

	//wait until tx complete
	while(READBIT(C1GSR, TCS1_BIT)==0);
}

void CAN1_Rx(CANF *rxF)
{
	//wait for CAN frame receive status
	while(READBIT(C1GSR, RBS_BIT)==0);

	//read 11-bit CANid of received frame
	rxF->ID=C1RID;

	//read and extract data/remote frame status
	rxF->BFV.RTR=(C1RFS>>RTR_BIT)&1;

	//and extract data length
	rxF->BFV.DLC=(C1RFS>>DLC_BITS)&15;

	//check if received frame is data frame
	if(rxF->BFV.RTR==0)
	{
		//extract data bytes 1-4
		rxF->Data1=C1RDA;

		//extract data bytes 5-8
		rxF->Data2=C1RDB;
	}

	//release receive buffer command
	SETBIT(C1CMR, RRB_BIT);
}

