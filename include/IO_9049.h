//Pin definitions for the 9049
//Needs access to basic MSP430 headers maybe
void init_IO_9049( void );

//port 1

//port 2
#define UART_CTS_PIN BIT7
#define UART_RXD_PIN BIT6
#define UART_TXD_PIN BIT5
#define UART_RTS_PIN BIT0

//port 3
#define J4_SCLK_PIN BIT3
#define J4_MISO_PIN BIT2
#define J4_MOSI_PIN BIT1

//port 4
#define DSCSW_STS_PIN BIT7
#define OUT_EN_PIN BIT6
#define CS0_PIN BIT3
#define CS1_PIN BIT2
#define QRESET_PIN BIT0

//port 5

//port 6

//port 7
#define LED4_PIN BIT7
#define LED3_PIN BIT6
#define LED2_PIN BIT5
#define LED1_PIN BIT4
#define N_CI_PIN BIT3
#define BUFFER_DIR_PIN BIT2
#define LCD_BKLT_PIN BIT1
#define OUT01_PIN BIT0

//port 8
#define LCD_D0_PIN BIT7
#define LCD_D1_PIN BIT6
#define LCD_D2_PIN BIT5
#define LCD_D3_PIN BIT4
#define LCD_D4_PIN BIT3
#define LCD_D5_PIN BIT2
#define LCD_D6_PIN BIT1
#define LCD_D7_PIN BIT0

//port 9
#define LED12_PIN BIT7
#define LED11_PIN BIT6
#define LED10_PIN BIT5
#define LED9_PIN BIT4
#define LED8_PIN BIT3
#define LED7_PIN BIT2
#define LED6_PIN BIT1
#define LED5_PIN BIT0

//port 10
#define RS_PIN BIT3
#define RW_PIN BIT2
#define E_PIN BIT1
#define N_LCD_ON_PIN BIT0
