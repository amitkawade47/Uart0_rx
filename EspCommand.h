#define TOTAL_NO_OF_SAMPLES 200
#define THRESHOLD_NO_OF_SAMPLES (0.4*TOTAL_NO_OF_SAMPLES)
#define NO_OF_FEEDBACK 8
#define AC_ON 1
#define AC_OFF 0
typedef enum{
	CHECK_COMMAND =0,
	ANALYZE_COMMAND,
	TAKE_ACTION
}ESP_STATES_ENM;

ESP_STATES_ENM EspCommandState_enm =CHECK_COMMAND;

static unsigned char RxCmdBuff[100] ={0}; 
static unsigned char OldStatus[NO_OF_FEEDBACK],TxChangeBuff[NO_OF_FEEDBACK];
static void TakeRelayAction(void);