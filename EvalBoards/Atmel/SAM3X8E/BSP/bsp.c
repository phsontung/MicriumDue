#include  <cpu_core.h>

/** Atmel includes*/
#include "stdio_serial.h"
#include "led.h"
#include "arduino_due_x.h"
#include "ioport.h"
#include "conf_uart_serial.h"
#include "wdt.h"

#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
void  CPU_TS_TmrInit (void)
{
    CPU_INT32U  fclk_freq;

    CPU_TS_TmrFreqSet((CPU_TS_TMR_FREQ)fclk_freq);
}
#endif

#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
CPU_TS_TMR  CPU_TS_TmrRd (void)
{
    CPU_TS_TMR  ts_tmr_cnts;

    return (ts_tmr_cnts);
}
#endif


/**
 * \brief Configure the console UART.
 */
static void configure_console(void)
{
    const usart_serial_options_t uart_serial_options = {
        .baudrate = CONF_UART_BAUDRATE,
#ifdef CONF_UART_CHAR_LENGTH
        .charlength = CONF_UART_CHAR_LENGTH,
#endif
        .paritytype = CONF_UART_PARITY,
#ifdef CONF_UART_STOP_BITS
        .stopbits = CONF_UART_STOP_BITS,
#endif
    };

    /* Configure console UART. */
    sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
    stdio_serial_init(CONF_UART, &uart_serial_options);

    /* Specify that stdout should not be buffered. */
#if defined(__GNUC__)
    setbuf(stdout, NULL);
#else

    /* Already the case in IAR's Normal DLIB default configuration: printf()
     * emits one character at a time.
     */
#endif
}

void board_init_rtos()
{
    /*
     * Init sequence for the DUE
     */
    const usart_serial_options_t usart_serial_options = {
        .baudrate   = 115200,
        .charlength = 0,
        .paritytype = UART_MR_PAR_NO,
        .stopbits   = false
    };
    sysclk_init();
    board_init();
    //configure_uart();
    stdio_serial_init(CONSOLE_UART, &usart_serial_options);

    //configure_console();

    /* Configure the pins connected to LEDs as output and set their
     * default initial state to high (LEDs off).
     */
    ioport_set_pin_dir(LED0_GPIO, IOPORT_DIR_OUTPUT);
    ioport_set_pin_level(LED0_GPIO, IOPORT_PIN_LEVEL_LOW);
    ioport_set_pin_dir(LED1_GPIO, IOPORT_DIR_OUTPUT);
    ioport_set_pin_level(LED1_GPIO, IOPORT_PIN_LEVEL_LOW);
    ioport_set_pin_dir(LED2_GPIO, IOPORT_DIR_OUTPUT);
    ioport_set_pin_level(LED2_GPIO, IOPORT_PIN_LEVEL_LOW);

    /* Output demo infomation. */
    printf("-- Micrium (uCOS 3) with Led Example --\n\r");
    printf("-- Board: %s\n\r", "Arduino Due");
    printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);
}

void Due_BSP_Init() {
	SystemInit();
    wdt_disable (WDT);
    board_init_rtos();
}