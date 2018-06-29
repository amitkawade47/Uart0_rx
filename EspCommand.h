#define TOTAL_NO_OF_SAMPLES 200
#define THRESHOLD_NO_OF_SAMPLES (0.3*TOTAL_NO_OF_SAMPLES)
#define NO_OF_FEEDBACK 8
#define AC_ON 1
#define AC_OFF 0
typedef enum{
	CHECK_COMMAND =0,
	ANALYZE_COMMAND,
	TAKE_ACTION
}ESP_STATES_ENM;

typedef enum{
	SEND_FB_CHECK_STATE =0,
	SEND_FB_WAIT_TILL_TX_COMPLETE
}SEND_FB_STATES_ENM;

SEND_FB_STATES_ENM SendFbState_enm = SEND_FB_CHECK_STATE;
ESP_STATES_ENM EspCommandState_enm =CHECK_COMMAND;

static unsigned char Action,Device;
static unsigned char TxBuff[10]= {0};
//static unsigned char RxCmdBuff[100] ={0};
static unsigned char OldStatus[NO_OF_FEEDBACK],TxChangeBuff[NO_OF_FEEDBACK];
static void TakeRelayAction(unsigned char,unsigned char);
static void FormTxFrame(unsigned char);