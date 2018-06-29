
#include "r_cg_macrodriver.h"
#include "EspCommand.h"
#include "EspCommand_AI.h"
#include "r_cg_serial.h"

void EspCommandPoll(void)
{	static unsigned char Counter = 0;
	if(Counter == 0)
	{
		if(ReceivedByte == '#')
		{
			Counter++;			
		}
		else
		{
			Counter = 0;
		}
	}
	else if(Counter == 1)
	{
		if((ReceivedByte == '1') || (ReceivedByte == '0'))
		{
			Action = ReceivedByte;
			Counter++;
		}
		else
		{
			Counter = 0;
		}
	}
	else if(Counter == 2)
	{
		if(ReceivedByte == '@')
		{
			Counter++;			
		}
		else
		{
			Counter = 0;
		}
	}
	else if(Counter == 3)
	{
		Device = ReceivedByte;
		Counter++;
	}
	else if(Counter == 4)
	{
		if(ReceivedByte == '$')
		{
			TakeRelayAction(Action,Device);
			Counter = 0;			
		}
		else
		{
			Counter = 0;
		}
	}
	else
	{
		Counter = 0;
	}
}

//*************************************************************************************

static void TakeRelayAction(unsigned char Act,unsigned char Dev)
{
	if(Act == '1')
	{
		switch(Dev)
		{
			case '0':
			HIGH(Relay_0_PORT,Relay_0_PIN);
			break;
		
			case '1':
			HIGH(Relay_1_PORT,Relay_1_PIN);
			break;

			case '2':
			HIGH(Relay_2_PORT,Relay_2_PIN);
			break;
		
			case '3':
			HIGH(Relay_3_PORT,Relay_3_PIN);
			break;

			case '4':
			HIGH(Relay_4_PORT,Relay_4_PIN);
			break;
		
			case '5':
			HIGH(Relay_5_PORT,Relay_5_PIN);
			break;

			case '6':
			HIGH(Relay_6_PORT,Relay_6_PIN);
			break;
		
			case '7':
			HIGH(Relay_7_PORT,Relay_7_PIN);
			break;
		
		}
	}
	else if(Act == '0')
	{
		switch(Dev)
		{
			case '0':
			LOW(Relay_0_PORT,Relay_0_PIN);
			break;
			
			case '1':
			LOW(Relay_1_PORT,Relay_1_PIN);
			break;

			case '2':
			LOW(Relay_2_PORT,Relay_2_PIN);
			break;
			
			case '3':
			LOW(Relay_3_PORT,Relay_3_PIN);
			break;

			case '4':
			LOW(Relay_4_PORT,Relay_4_PIN);
			break;
			
			case '5':
			LOW(Relay_5_PORT,Relay_5_PIN);
			break;

			case '6':
			LOW(Relay_6_PORT,Relay_6_PIN);
			break;
			
			case '7':
			LOW(Relay_7_PORT,Relay_7_PIN);
			break;
		}

	}
}

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
void RelayFbPortInit(void)
{
	PM0=(0xFCU); /* PM0 default value */
	PM2=(0xF0U); /* PM2 default value */
	PM3=(0xFCU); /* PM3 default value */
	PM4=(0xFEU); /* PM4 default value */
	PM5=(0xFCU); /* PM5 default value */
	PM6=(0xFCU); /* PM6 default value */
	PM12=(0xFEU); /* PM12 default value */
	PM14=(0x7FU); /* PM14 default value */
	PMC0=(0xFCU); /* PMC0 default value */
	PMC12=(0xFEU); /* PMC12 default value */
	PMC14=(0x7FU); /* PMC14 default value */

	
	OUTPUT(Relay_0_MODE_PORT,Relay_0_PIN);
	OUTPUT(Relay_1_MODE_PORT,Relay_1_PIN);
	OUTPUT(Relay_2_MODE_PORT,Relay_2_PIN);
	OUTPUT(Relay_3_MODE_PORT,Relay_3_PIN);
	OUTPUT(Relay_4_MODE_PORT,Relay_4_PIN);
	OUTPUT(Relay_5_MODE_PORT,Relay_5_PIN);
	OUTPUT(Relay_6_MODE_PORT,Relay_6_PIN);
	OUTPUT(Relay_7_MODE_PORT,Relay_7_PIN);
	OUTPUT(Led_MODE_PORT,Led_PIN);
	OUTPUT(Buzzer_MODE_PORT,Buzzer_PIN);

	
	INPUT(Feedback_0_MODE_PORT,Feedback_0_PIN);
	//INPUT(Feedback_1_MODE_PORT,Feedback_1_PIN);
	INPUT(Feedback_2_MODE_PORT,Feedback_2_PIN);
	INPUT(Feedback_3_MODE_PORT,Feedback_3_PIN);
	INPUT(Feedback_4_MODE_PORT,Feedback_4_PIN);
	INPUT(Feedback_5_MODE_PORT,Feedback_5_PIN);
	INPUT(Feedback_6_MODE_PORT,Feedback_6_PIN);
	INPUT(Feedback_7_MODE_PORT,Feedback_7_PIN);

	//Uart.UartRxPtr = RxCmdBuff;
}

void ReadFbStatus(void)
{
	static unsigned char HighCounter_u8[NO_OF_FEEDBACK],LowCounter_u8[NO_OF_FEEDBACK];
	unsigned char FbInput =0;
	static unsigned char Counter_200ms= TOTAL_NO_OF_SAMPLES;
	unsigned char CurrentStatus[NO_OF_FEEDBACK]= {0};
	if(Counter_200ms-- == 0)
	{
		for(FbInput=0;FbInput<NO_OF_FEEDBACK;FbInput++)
		{
			//TxChangeBuff[FbInput] =0;
			//if((HighCounter_u8[FbInput]>= THRESHOLD_NO_OF_SAMPLES) &&
			//  (LowCounter_u8[FbInput]>= THRESHOLD_NO_OF_SAMPLES))
			if((LowCounter_u8[FbInput]>= THRESHOLD_NO_OF_SAMPLES))
			  {
				  CurrentStatus[FbInput]= AC_OFF;
			  }
			  else
			  {
				CurrentStatus[FbInput]= AC_ON;  
			  }
			  if(OldStatus[FbInput] != CurrentStatus[FbInput])
			  {
				  OldStatus[FbInput]= CurrentStatus[FbInput];
				  TxChangeBuff[FbInput]= 1;
			  }
			  HighCounter_u8[FbInput] = 0;
			  LowCounter_u8[FbInput] = 0;
		}
		Counter_200ms = TOTAL_NO_OF_SAMPLES;		
	}
	else
	{
		for(FbInput=0;FbInput<NO_OF_FEEDBACK;FbInput++)
		{
			if(ReadFb(FbInput)==1)
			{
				HighCounter_u8[FbInput]++;
			}
			else
			{
				LowCounter_u8[FbInput]++;
			}
		}
	}
}

unsigned char ReadFb(unsigned char Fb)
{
	switch(Fb)
	{
		case 0:
		return READ(Feedback_0_PORT,Feedback_0_PIN);
		break;
		
		case 1:
		return READ(Feedback_1_PORT,Feedback_1_PIN);
		break;
		
		case 2:
		return READ(Feedback_2_PORT,Feedback_2_PIN);
		break;
		
		case 3:
		return READ(Feedback_3_PORT,Feedback_3_PIN);
		break;
		
		case 4:
		return READ(Feedback_4_PORT,Feedback_4_PIN);
		break;
		
		case 5:
		return READ(Feedback_5_PORT,Feedback_5_PIN);
		break;
		
		case 6:
		return READ(Feedback_6_PORT,Feedback_6_PIN);
		break;
		
		case 7:
		return READ(Feedback_7_PORT,Feedback_7_PIN);
		break;
	}
	
}

void SendFbPoll(void)
{
	static unsigned char CheckStatus =0;
	
	switch(SendFbState_enm)
	{
		case SEND_FB_CHECK_STATE:
			if(TxChangeBuff[CheckStatus]==1)
			{
				FormTxFrame(CheckStatus);
				SendFbState_enm = SEND_FB_WAIT_TILL_TX_COMPLETE;
			}
			
			TxChangeBuff[CheckStatus]= 0;
			CheckStatus++;
			if(CheckStatus >= NO_OF_FEEDBACK)
			{
				CheckStatus = 0;
			}
		break;
		
		case SEND_FB_WAIT_TILL_TX_COMPLETE:
			if(UartState_enm == UART_TX_COMPLETED)
			{
				SendFbState_enm = SEND_FB_CHECK_STATE; 
			}
		break;
	}
}


static void FormTxFrame(unsigned char state_u8)
{
	TxBuff[0]='#';
	if(OldStatus[state_u8]== AC_ON)
	{
		TxBuff[1] = '1';	
	}
	else
	{
		TxBuff[1] = '0';
	}
	TxBuff[2]='@';
	TxBuff[3] = 0x30 + state_u8;
	TxBuff[4]='$';
	InitiateUartTransmit(TxBuff,5);
}