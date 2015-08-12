/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2012; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            EXAMPLE CODE
*
*                                             NXP LPC18xx
*                                               on the
*                                    KEIL MCB1800 Evaluation Board
*
* Filename      : app.c
* Version       : V1.00
* Programmer(s) : FT
*                 FF
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <includes.h>
/** Atmel includes*/
#include "stdio_serial.h"
#include "led.h"
#include "arduino_due_x.h"
#include "ioport.h"
#include "conf_uart_serial.h"
#include "wdt.h"

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

                                                                /* --------------- APPLICATION GLOBALS ---------------- */
static  OS_TCB         AppTaskStartTCB;
static  CPU_STK        AppTaskStartStk[APP_CFG_TASK_START_STK_SIZE];

/*
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  AppTaskStart              (void  *p_arg);
static  void  AppObjCreate              (void);
static  void  AppTaskCreate             (void);

/*
*********************************************************************************************************
*                                    LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                                main()
*
* Description : The standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/

int  main (void)
{
    OS_ERR   err;
#if (CPU_CFG_NAME_EN == DEF_ENABLED)
    CPU_ERR     cpu_err;
#endif

    //BSP_PreInit();

    Mem_Init();                                                 /* Initialize the Memory Managment module               */
    Math_Init();                                                /* Initialize the Mathematical module                   */


#if (CPU_CFG_NAME_EN == DEF_ENABLED)
    CPU_NameSet((CPU_CHAR *)"LPC1857",
                (CPU_ERR  *)&cpu_err);
#endif

    CPU_IntDis();                                               /* Disable all interrupts until we are ready to ...     */
                                                                /* ... accept them                                      */

    OSInit(&err);                                               /* Init uC/OS-III                                       */

    OSTaskCreate((OS_TCB      *)&AppTaskStartTCB,               /* Create the start task                                */
                 (CPU_CHAR    *)"App Task Start",
                 (OS_TASK_PTR  )AppTaskStart,
                 (void        *)0,
                 (OS_PRIO      )APP_CFG_TASK_START_PRIO,
                 (CPU_STK     *)&AppTaskStartStk[0],
                 (CPU_STK_SIZE )APP_CFG_TASK_START_STK_SIZE_LIMIT,
                 (CPU_STK_SIZE )APP_CFG_TASK_START_STK_SIZE,
                 (OS_MSG_QTY   )0,
                 (OS_TICK      )0,
                 (void        *)0,
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR      *)&err);

    OSStart(&err);                                              /* Start multitasking (i.e. give control to uC/OS-III. */

    return (1);
}


/*
*********************************************************************************************************
*                                          AppTaskStart()
*
* Description : The startup task.  The uC/OS-II ticker should only be initialize once multitasking starts.
*
* Argument(s) : p_arg       Argument passed to 'AppTaskStart()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Note(s)     : (1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                   used.  The compiler should not generate any code for this statement.
*
*               (2) Interrupts are enabled once the task starts because the I-bit of the CCR register was
*                   set to 0 by 'OSTaskCreate()'.
*********************************************************************************************************
*/

static  void  AppTaskStart (void *p_arg)
{
    CPU_INT32U  cnts;
    OS_ERR      os_err;

    (void)p_arg;

    Due_BSP_Init();

    //BSP_PostInit();                                             /* Initialize BSP functions                             */
    CPU_Init();

    cnts = 84000000UL / OSCfg_TickRate_Hz; //BSP_CPU_ClkGet() / OSCfg_TickRate_Hz;
    OS_CPU_SysTickInit(cnts);                                   /* Initialize the SysTick.                              */

#if OS_CFG_STAT_TASK_EN > 0
    OSStatTaskCPUUsageInit(&os_err);                            /* Compute CPU capacity with no task running            */
#endif

    APP_TRACE_INFO(("\n\n\r"));
    APP_TRACE_INFO(("Creating Application Objects...\n\r"));
    AppObjCreate();                                             /* Create Application Kernel objects                    */

    APP_TRACE_INFO(("Creating Application Tasks...\n\r"));
    AppTaskCreate();                                            /* Create Application Tasks                             */

    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
        LED_Toggle(LED0_GPIO);
        OSTimeDlyHMSM(0, 0, 2, 0,
                      OS_OPT_TIME_HMSM_STRICT,
                     &os_err);
    }
}


/*
*********************************************************************************************************
*                                          AppTaskCreate()
*
* Description : Create application tasks.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTaskStart()
*
* Note(s)     : none.
*********************************************************************************************************
*/

static void AppTaskCreate(void)
{

}


/*
*********************************************************************************************************
*                                          AppObjCreate()
*
* Description : Create application kernel objects tasks.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTaskStart()
*
* Note(s)     : none.
*********************************************************************************************************
*/

static void AppObjCreate(void)
{

}
