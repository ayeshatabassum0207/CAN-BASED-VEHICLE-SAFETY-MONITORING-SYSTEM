#include"types.h"		// User-defined data type definitions (u8, u16, u32, etc.)

typedef struct CAN_FRAME	// Structure representing a CAN message frame
{
	u32 ID;		// CAN message identifier

	struct Bitfield		// Bitfield structure for CAN frame control information
	{
		u32 RTR:1;	// Remote Transmission Request bit (0 = Data Frame, 1 = Remote Frame)

		u32 DLC:4;	// Data Length Code indicating number of data bytes
	}BFV;			// Bitfield variable

	u32 Data1, Data2;	// CAN data fields used to transmit application data

	//u8 Data[8];		// Alternative array representation for up to 8 data bytes

}CANF;		// Alias name for CAN frame structure

void Init_CAN1(void);		// Initialize CAN1 peripheral

void CAN1_Tx(CANF txF);		// Transmit a CAN frame using CAN1

void CAN1_Rx(CANF *rxF);	// Receive a CAN frame using CAN1

void Init_CAN2(void);		// Initialize CAN2 peripheral

void CAN2_Tx(CANF txF);		// Transmit a CAN frame using CAN2

void CAN2_Rx(CANF *rxF);	// Receive a CAN frame using CAN2