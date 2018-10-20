/*
 * -------------------------------------------------------------------
 * MPLAB 16-Bit Device Blocks for Simulink v3.38.
 *
 *   Product Page:  http://www.microchip.com/SimulinkBlocks
 *           Forum: http://www.microchip.com/forums/f192.aspx
 *           Wiki:  http://microchip.wikidot.com/simulink:start
 * -------------------------------------------------------------------
 * File: PI_pos.c
 *
 * Code generated for Simulink model 'PI_pos'.
 *
 * Model version                  : 1.40
 * Simulink Coder version         : 8.4 (R2013a) 13-Feb-2013
 * C/C++ source code generated on : Sat Nov 12 23:47:58 2016
 */

#include "PI_pos.h"
#include "PI_pos_private.h"

/* Block signals (auto storage) */
B_PI_pos_T PI_pos_B;

/* Block states (auto storage) */
DW_PI_pos_T PI_pos_DW;

/* Real-time model */
RT_MODEL_PI_pos_T PI_pos_M_;
RT_MODEL_PI_pos_T *const PI_pos_M = &PI_pos_M_;

/* Model step function for TID0 */
void PI_pos_step0(void)                /* Sample time: [0.001s, 0.0s] */
{
  /* local block i/o variables */
  boolean_T rtb_Switch;
  boolean_T rtb_Switch1;
  real_T rtb_Gain2;
  real_T rtb_Abs;
  uint16_T u;
  int16_T tmp;

  /* S-Function (MCHP_QEI): '<Root>/QEI1' */
  PI_pos_B.QEI1 = POSCNT;              /* Read QEI  position */

  /* Step: '<Root>/Step' */
  if (((PI_pos_M->Timing.clockTick0) * 0.001) < 10.0) {
    tmp = 0;
  } else {
    tmp = 112;
  }

  /* End of Step: '<Root>/Step' */

  /* Sum: '<Root>/Sum' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion3'
   *  Gain: '<Root>/Gain2'
   */
  rtb_Gain2 = 212.630236019562 * (real_T)tmp - (real_T)PI_pos_B.QEI1;

  /* Sum: '<S1>/Sum' incorporates:
   *  DiscreteIntegrator: '<S1>/Integrator'
   *  Gain: '<S1>/Proportional Gain'
   */
  rtb_Abs = 10.0 * rtb_Gain2 + PI_pos_DW.Integrator_DSTATE;

  /* Switch: '<Root>/Switch' */
  rtb_Switch = (rtb_Abs >= 0.0);

  /* S-Function (MCHP_Digital_Output_Write): '<Root>/Digital Output Write' */
  LATDbits.LATD0 = rtb_Switch;

  /* Switch: '<Root>/Switch1' */
  if (rtb_Abs >= 0.0) {
    rtb_Switch1 = FALSE;
  } else {
    rtb_Switch1 = TRUE;
  }

  /* End of Switch: '<Root>/Switch1' */

  /* S-Function (MCHP_Digital_Output_Write): '<Root>/Digital Output Write1' */
  LATDbits.LATD2 = rtb_Switch1;

  /* Abs: '<Root>/Abs' */
  rtb_Abs = fabs(rtb_Abs);

  /* DataTypeConversion: '<Root>/Data Type Conversion5' */
  rtb_Abs = floor(rtb_Abs);
  if (rtIsNaN(rtb_Abs) || rtIsInf(rtb_Abs)) {
    u = 0U;
  } else {
    u = (uint16_T)fmod(rtb_Abs, 65536.0);
  }

  /* End of DataTypeConversion: '<Root>/Data Type Conversion5' */

  /* Saturate: '<Root>/Saturation' */
  if (u >= 1740U) {
    PI_pos_B.U2CH1_m = 1740U;
  } else if (u <= 10U) {
    PI_pos_B.U2CH1_m = 10U;
  } else {
    PI_pos_B.U2CH1_m = u;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* S-Function (MCHP_PWM): '<Root>/PWM1' */
  /* PWM Output Function !! */

  /* Gain: '<S1>/Integral Gain' */
  rtb_Gain2 *= 10.0;

  /* Update for DiscreteIntegrator: '<S1>/Integrator' */
  PI_pos_DW.Integrator_DSTATE += 0.001 * rtb_Gain2;

  /* Update for S-Function (MCHP_PWM): '<Root>/PWM1' */
  PDC1 = PI_pos_B.U2CH1_m;             /* Period for Channel 1 */

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.001, which is the step size
   * of the task. Size of "clockTick0" ensures timer will not overflow during the
   * application lifespan selected.
   */
  PI_pos_M->Timing.clockTick0++;
}

/* Model step function for TID1 */
void PI_pos_step1(void)                /* Sample time: [0.01s, 0.0s] */
{
  /* S-Function (MCHP_QEI): '<Root>/QEI' */
  PI_pos_B.U2CH1_g = POSCNT;           /* Read QEI  position */

  /* DataTypeConversion: '<Root>/Data Type Conversion1' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion'
   *  Gain: '<Root>/Gain3'
   */
  PI_pos_B.U2CH1 = (int16_T)fmod((int16_T)floor(0.004703 * (real_T)
    PI_pos_B.U2CH1_g), 65536.0);

  /* MCHP_UART_Tx-Matlab Block for UARTRef 2: <Root>/UART Tx-Matlab1/Outputs */
  {
    volatile static uint_T index = 0;
    int_T tmp;
    tmp = ~(MCHP_UART2_Tx.tail - MCHP_UART2_Tx.head);
    tmp = tmp & (Tx_BUFF_SIZE_Uart2 - 1);/* Modulo Buffer Size */
    if (tmp > 3)
      tmp = 3;                         /* Stop condition for do-while loop*/
    do {
      switch (index) {
       case 0:                         /* CH 1 */
        tmp = tmp - 3;
        if (tmp < 0)
          break;
        MCHP_UART2_Tx.buffer[MCHP_UART2_Tx.tail] = 5 ;/* Control byte */
        MCHP_UART2_Tx.tail = (MCHP_UART2_Tx.tail + 1) & (Tx_BUFF_SIZE_Uart2 - 1);
        MCHP_UART2_Tx.buffer[MCHP_UART2_Tx.tail] = PI_pos_B.U2CH1 ;/* LSB First*/
        MCHP_UART2_Tx.tail = (MCHP_UART2_Tx.tail + 1) & (Tx_BUFF_SIZE_Uart2 - 1);
        MCHP_UART2_Tx.buffer[MCHP_UART2_Tx.tail] = (PI_pos_B.U2CH1 >> 8);/* MSB Last*/
        MCHP_UART2_Tx.tail = (MCHP_UART2_Tx.tail + 1) & (Tx_BUFF_SIZE_Uart2 - 1);
        if (++index >= 1)
          index = 0;
      }
    } while (tmp >= 1);                /* either buffer is full or we send all datas */

    if (1U == U2STAbits.TRMT)
      _U2TXIF = 1;                     /* Tx Buffer is empty, enable Interrupt */
  }
}

/* Model initialize function */
void PI_pos_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)PI_pos_M, 0,
                sizeof(RT_MODEL_PI_pos_T));
  (PI_pos_M)->Timing.TaskCounters.cLimit[0] = 1;
  (PI_pos_M)->Timing.TaskCounters.cLimit[1] = 10;

  /* block I/O */
  (void) memset(((void *) &PI_pos_B), 0,
                sizeof(B_PI_pos_T));

  /* states (dwork) */
  (void) memset((void *)&PI_pos_DW, 0,
                sizeof(DW_PI_pos_T));

  /* S-Function "Microchip MASTER" initialization Block: <Root>/Microchip Master */

  /* Start for S-Function (MCHP_QEI): '<Root>/QEI1' */
  /* Initialize QEI  Peripheral */
  MAXCNT = 65535;
  DFLTCON = 0x01C0;
  QEICON = 0x0E00;

  /* Start for S-Function (MCHP_PWM): '<Root>/PWM1' */
  PWMCON1 = 0x10;
  PWMCON2 = 0x06;
  DTCON1 = 0x09;
  FLTACON = 0x87;
  PTPER = 0x0399;
  SEVTCMP = 0x0399;
  PTCON = 0x8003;                      /* Enable PWM */

  /* Start for S-Function (MCHP_QEI): '<Root>/QEI' */
  /* Initialize QEI  Peripheral */
  MAXCNT = 65535;
  DFLTCON = 0x01C0;
  QEICON = 0x0E00;

  /* MCHP_UART_Config Block for UART 2: <Root>/UART Configuration/Initialize */
  U2BRG = 0x0B;                        /* Baud rate: 9600 (-0.04%) */
  U2MODE = 0x8000;
  U2STA = 0x24C0;

  /* Configure UART2 Tx Interruption */
  MCHP_UART2_Tx.head = 0;              /* Initialise Circular Buffers */
  MCHP_UART2_Tx.tail = 0;
  _U2TXIP = 1;                         /*  Tx Interrupt priority set to 1 */
  _U2TXIF = 0;                         /*  */
  _U2TXIE = 1;                         /* Enable Interrupt */

  /* Configure UART2 Rx Interruption */
  MCHP_UART2_Rx.head = 0;              /* Initialise Circular Buffers */
  MCHP_UART2_Rx.tail = 0;
  _U2RXIP = 1;                         /* Rx Interrupt priority set to 1 */
  _U2RXIF = 0;                         /*  */
  _U2RXIE = 1;                         /* Enable Interrupt */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
