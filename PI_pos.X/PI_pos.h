/*
 * -------------------------------------------------------------------
 * MPLAB 16-Bit Device Blocks for Simulink v3.38.
 *
 *   Product Page:  http://www.microchip.com/SimulinkBlocks
 *           Forum: http://www.microchip.com/forums/f192.aspx
 *           Wiki:  http://microchip.wikidot.com/simulink:start
 * -------------------------------------------------------------------
 * File: PI_pos.h
 *
 * Code generated for Simulink model 'PI_pos'.
 *
 * Model version                  : 1.40
 * Simulink Coder version         : 8.4 (R2013a) 13-Feb-2013
 * C/C++ source code generated on : Sat Nov 12 23:47:58 2016
 */

#ifndef RTW_HEADER_PI_pos_h_
#define RTW_HEADER_PI_pos_h_
#ifndef PI_pos_COMMON_INCLUDES_
# define PI_pos_COMMON_INCLUDES_
#include <math.h>
#include <string.h>
#include "rtwtypes.h"
#include "rtGetInf.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#endif                                 /* PI_pos_COMMON_INCLUDES_ */

#include "PI_pos_types.h"
#define FCY                            1.8425E+6

/* Include for pic 30F */
#include <p30Fxxxx.h>
#include <libpic30.h>                  /* For possible use with C function Call block (delay_ms or delay_us functions might be used by few peripherals) */
#include <libq.h>                      /* For possible use with C function Call block */

/* Macros for accessing real-time model data structure */
#ifndef rtmCounterLimit
# define rtmCounterLimit(rtm, idx)     ((rtm)->Timing.TaskCounters.cLimit[(idx)])
#endif

#ifndef rtmStepTask
# define rtmStepTask(rtm, idx)         ((rtm)->Timing.TaskCounters.TID[(idx)] == 0)
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((void*) 0)
#endif

#ifndef rtmTaskCounter
# define rtmTaskCounter(rtm, idx)      ((rtm)->Timing.TaskCounters.TID[(idx)])
#endif

/* Declare UART2 Tx Circular Buffer Structure */
#define Tx_BUFF_SIZE_Uart2             (16)

typedef struct MCHP_UART2_TxStr{
  volatile uint8_T buffer[Tx_BUFF_SIZE_Uart2];/* Size Rx_BUFF_SIZE_Uart2 is 16 */
  uint_T tail;                         /* tail is the index for the next value to be read from the Circular buffer */
  volatile uint_T head;                /* head is the index for the next value to be written into the Circular buffer */
} MCHP_UART2_TxStr;

/* Declare UART2 Rx Circular Buffer Structure */
#define Rx_BUFF_SIZE_Uart2             (16)

typedef struct MCHP_UART2_RxStr{
  volatile uint8_T buffer[Rx_BUFF_SIZE_Uart2];/* Size Rx_BUFF_SIZE_Uart2 is 16 */
  volatile uint_T tail;                /* tail is the index for the next value to be written into the Circular buffer */
  uint_T head;                         /* head is the index for the next value to be read from the Circular buffer */
} MCHP_UART2_RxStr;

/* To read the UART2 Rx Circular with a custom code: read the next value: buffer[head], then increment head index by 1 modulo Rx_BUFF_SIZE_Uart2 (=16).
   code example:
   if (U2STAbits.URXDA != 0)
 // SET U2RXIF bit to 1 Flush internal UART buffer through the interrupt
   if (MCHP_UART2_Rx.tail != MCHP_UART2_Rx.head)	{  		// is buffer not empty ?
   output = (uint8_T) MCHP_UART2_Rx.buffer[MCHP_UART2_Rx.head ++];     // Read one char
   MCHP_UART2_Rx.head &= (Rx_BUFF_SIZE_Uart2-1); 	// modulo : use a simple bitewise "and" operator as <Rx_BUFF_SIZE_Uart2> is a power of 2
   }
 */

/* Block signals (auto storage) */
typedef struct {
  int16_T U2CH1;                       /* '<Root>/Data Type Conversion1' */
  uint16_T U2CH1_m;                    /* '<Root>/Saturation' */
  uint16_T QEI1;                       /* '<Root>/QEI1' */
  uint16_T U2CH1_g;                    /* '<Root>/QEI' */
} B_PI_pos_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S1>/Integrator' */
} DW_PI_pos_T;

/* Real-time Model Data Structure */
struct tag_RTM_PI_pos_T {
  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    struct {
      uint8_T TID[2];
      uint8_T cLimit[2];
    } TaskCounters;
  } Timing;
};

/* Block signals (auto storage) */
extern B_PI_pos_T PI_pos_B;

/* Block states (auto storage) */
extern DW_PI_pos_T PI_pos_DW;

/* Model entry point functions */
extern void PI_pos_initialize(void);
extern void PI_pos_step0(void);
extern void PI_pos_step1(void);

/* Real-time Model object */
extern RT_MODEL_PI_pos_T *const PI_pos_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'PI_pos'
 * '<S1>'   : 'PI_pos/Discrete PID Controller'
 */
#endif                                 /* RTW_HEADER_PI_pos_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
