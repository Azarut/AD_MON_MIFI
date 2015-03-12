extern uint8_t Init_SIM800(void);

extern uint8_t SIM800_data[15];
extern uint8_t AD_Answer[48];
extern uint8_t SIM800_Answer[48];

extern uint8_t AT[3];
extern uint8_t ECHO[5]; 
extern uint8_t SET_SMS_OP_1[10]; 
extern uint8_t SET_SMS_OP_2[15]; 
extern uint8_t READ_SMS[10]; 
extern uint8_t DEL_SMS[19];
extern uint8_t APN[19]; 
extern uint8_t CHK_CONNECT[9];
extern uint8_t CHK_IP[9];
extern uint8_t SRV_CONNECT[43];
extern uint8_t SEND_DATA[11];
extern uint8_t CHK_GPRS[10];
extern uint8_t GPRS_CONNECT[11];
extern uint8_t GPRS_DISCONNECT[12];
extern uint8_t END_LINE[1];
