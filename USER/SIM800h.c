#include "stm32l053xx.h"
#include "SIM800h.h"
#include "hw_io.h"

uint8_t SIM800_data[15] = {0};
uint8_t AD_Answer[48] = {0};
uint8_t SIM800_Answer[48] = {0};
void Init_SIM800(void);

/*    АТ-комманды SIM800       */
uint8_t AT[3] = "AT\r";
uint8_t ECHO[5] = "ATE0\r"; 
uint8_t SET_SMS_OP_1[10] = "AT+CMGF=1\r"; 
uint8_t SET_SMS_OP_2[15] = "AT+CSCS= \"GSM\"\r"; 
uint8_t READ_SMS[10] = "AT+CMGR=1\r"; 
uint8_t DEL_SMS[19] = "AT+CMGDA=\"DEL ALL\"\r";
uint8_t APN[19] = "AT+CSTT=\"internet\"\r"; 
uint8_t CHK_CONNECT[9] =  "AT+CIICR\r";
uint8_t CHK_IP[9] = "AT+CIFSR\r";
uint8_t SRV_CONNECT[43] = "AT+CIPSTART=\"TCP\",\"054.203.229.250\",\"8081\"\r";
uint8_t SEND_DATA[11] = "AT+CIPSEND\r";
uint8_t CHK_GPRS[10] = "AT+CGATT?\r";
uint8_t GPRS_CONNECT[11] = "AT+CGATT=1\r";
uint8_t GPRS_DISCONNECT[12] = "AT+CIPCLOSE\r";
uint8_t END_LINE[1] = {0x1A};
/*******************************/

void Init_SIM800(void)
{		  
			SIM800_Command(AT, 3);
			if ((SIM800_Answer [0] != 'A') && (SIM800_Answer [2] != 'A') &&  (SIM800_Answer [2] != 'O'))
			{
				SIM800_On();
				Delay(1500);
				SIM800_Off();
			}
			Delay(15000);
		  SIM800_Command(ECHO, 5);
		  Delay(1000);
		  SIM800_Command(SET_SMS_OP_1, 10);
		  Delay(1000);
		  SIM800_Command(SET_SMS_OP_2, 15);
		  Delay(1000);
		  SIM800_Command(DEL_SMS, 19);
		  Delay(1000);
		  SIM800_Command(CHK_GPRS, 10);
		  Delay(1000);
	    SIM800_Command(GPRS_CONNECT, 11);
		  Delay(1000);
      SIM800_Command(APN, 19);
		  Delay(1000);
	    SIM800_Command(CHK_CONNECT, 9);
		  Delay(1000);
	    SIM800_Command(CHK_IP, 9);
		  Delay(1000);
}

