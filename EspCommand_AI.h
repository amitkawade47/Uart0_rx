
#define HIGH(port,pin)           port |= (1<<pin)
#define LOW(port,pin)           port &= (~(1<<pin))
#define OUTPUT(port,pin)           port &= (~(1<<pin))
#define INPUT(port,pin)           port |= (1<<pin)
#define READ(port,pin)		(((port & (1<<pin))==(1<<pin))?1:0)

#define Relay_0_PORT P2
#define Relay_1_PORT P0
#define Relay_2_PORT P12
#define Relay_3_PORT P3
#define Relay_4_PORT P5
#define Relay_5_PORT P1
#define Relay_6_PORT P1
#define Relay_7_PORT P2
#define Led_PORT P2
#define Buzzer_PORT P2

#define Relay_0_MODE_PORT PM2
#define Relay_1_MODE_PORT PM0
#define Relay_2_MODE_PORT PM12
#define Relay_3_MODE_PORT PM3
#define Relay_4_MODE_PORT PM5
#define Relay_5_MODE_PORT PM1
#define Relay_6_MODE_PORT PM1
#define Relay_7_MODE_PORT PM2
#define Led_MODE_PORT PM2
#define Buzzer_MODE_PORT PM2

#define Relay_0_PIN 0
#define Relay_1_PIN 0
#define Relay_2_PIN 0
#define Relay_3_PIN 1
#define Relay_4_PIN 1
#define Relay_5_PIN 6
#define Relay_6_PIN 0
#define Relay_7_PIN 3
#define Led_PIN 2
#define Buzzer_PIN 1


#define Feedback_0_PORT P0
#define Feedback_1_PORT P13
#define Feedback_2_PORT P12
#define Feedback_3_PORT P12
#define Feedback_4_PORT P5
#define Feedback_5_PORT P1
#define Feedback_6_PORT P1
#define Feedback_7_PORT P1

#define Feedback_0_MODE_PORT PM0
#define Feedback_1_MODE_PORT PM13
#define Feedback_2_MODE_PORT PM12
#define Feedback_3_MODE_PORT PM12
#define Feedback_4_MODE_PORT PM5
#define Feedback_5_MODE_PORT PM1
#define Feedback_6_MODE_PORT PM1
#define Feedback_7_MODE_PORT PM1

#define Feedback_0_PIN 1
#define Feedback_1_PIN 7
#define Feedback_2_PIN 2
#define Feedback_3_PIN 1
#define Feedback_4_PIN 0
#define Feedback_5_PIN 7
#define Feedback_6_PIN 5
#define Feedback_7_PIN 3

void RelayFbPortInit(void);
void EspCommandPoll(void);
void ReadFbStatus(void);
unsigned char ReadFb(unsigned char Fb);
