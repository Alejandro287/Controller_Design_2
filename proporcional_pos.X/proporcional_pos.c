/*
 * -------------------------------------------------------------------
 * MPLAB 16-Bit Device Blocks for Simulink v3.38.
 *
 *   Product Page:  http://www.microchip.com/SimulinkBlocks
 *           Forum: http://www.microchip.com/forums/f192.aspx
 *           Wiki:  http://microchip.wikidot.com/simulink:start
 * -------------------------------------------------------------------
 * File: proporcional_pos.c
 *
 * Code generated for Simulink model 'proporcional_pos'.
 *
 * Model version                  : 1.31
 * Simulink Coder version         : 8.4 (R2013a) 13-Feb-2013
 * C/C++ source code generated on : Wed Oct 19 14:35:43 2016
 */

#include "proporcional_pos.h"
#include "proporcional_pos_private.h"

/* Block signals (auto storage) */
B_proporcional_pos_T proporcional_pos_B;

/* Real-time model */
RT_MODEL_proporcional_pos_T proporcional_pos_M_;
RT_MODEL_proporcional_pos_T *const proporcional_pos_M = &proporcional_pos_M_;

/* Model step function for TID0 */
void proporcional_pos_step0(void)      /* Sample time: [0.001s, 0.0s] */
{
  /* local block i/o variables */
  boolean_T rtb_Switch;
  boolean_T rtb_Switch1;
  real_T rtb_Gain1;

  /* S-Function (MCHP_QEI): '<Root>/QEI1' */
  proporcional_pos_B.QEI1 = POSCNT;    /* Read QEI  position */

  /* Gain: '<Root>/Gain1' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion3'
   *  Sum: '<Root>/Sum'
   */
  rtb_Gain1 = (38273.442483521161 - (real_T)proporcional_pos_B.QEI1) * 0.07;

  /* Switch: '<Root>/Switch' */
  rtb_Switch = (rtb_Gain1 >= 0.0);

  /* S-Function (MCHP_Digital_Output_Write): '<Root>/Digital Output Write' */
  LATDbits.LATD0 = rtb_Switch;

  /* Switch: '<Root>/Switch1' */
  if (rtb_Gain1 >= 0.0) {
    rtb_Switch1 = FALSE;
  } else {
    rtb_Switch1 = TRUE;
  }

  /* End of Switch: '<Root>/Switch1' */

  /* S-Function (MCHP_Digital_Output_Write): '<Root>/Digital Output Write1' */
  LATDbits.LATD2 = rtb_Switch1;
}

/* Model step function for TID1 */
void proporcional_pos_step1(void)      /* Sample time: [0.01s, 0.0s] */
{
  /* S-Function (MCHP_QEI): '<Root>/QEI' */
  proporcional_pos_B.QEI = POSCNT;     /* Read QEI  position */

  /* DataTypeConversion: '<Root>/Data Type Conversion2' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion'
   *  Gain: '<Root>/Gain3'
   */
  proporcional_pos_B.U2CH1 = (int16_T)fmod((int16_T)floor(0.004703 * (real_T)
    proporcional_pos_B.QEI), 65536.0);

  /* MCHP_UART_Tx-Matlab Block for UARTRef 2: <Root>/UART Tx-Matlab/Outputs */
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
        MCHP_UART2_Tx.buffer[MCHP_UART2_Tx.tail] = proporcional_pos_B.U2CH1 ;/* LSB First*/
        MCHP_UART2_Tx.tail = (MCHP_UART2_Tx.tail + 1) & (Tx_BUFF_SIZE_Uart2 - 1);
        MCHP_UART2_Tx.buffer[MCHP_UART2_Tx.tail] = (proporcional_pos_B.U2CH1 >>
          8);                          /* MSB Last*/
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
void proporcional_pos_initialize(void)
{
  /* Registration code */

  /* block I/O */
  (void) memset(((void *) &proporcional_pos_B), 0,
                sizeof(B_proporcional_pos_T));

  /* S-Function "Microchip MASTER" initialization Block: <Root>/Microchip Master */

  /* Start for S-Function (MCHP_QEI): '<Root>/QEI1' */
  /* Initialize QEI  Peripheral */
  MAXCNT = 200;
  DFLTCON = 0x01C0;
  QEICON = 0x0F00;

  /* Start for S-Function (MCHP_PWM): '<Root>/PWM1' */
  PWMCON1 = 0x10;
  PWMCON2 = 0x06;
  DTCON1 = 0x09;
  FLTACON = 0x87;
  PTPER = 0x0399;
  SEVTCMP = 0x0399;
  PTCON = 0x8003;                      /* Enable PWM */
  PDC1 = proporcional_pos_ConstB.DataTypeConversion5;/* Period for Channel 1 */

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

  /* S-Function (MCHP_PWM): '<Root>/PWM1' */
  /* PWM Output Function !! */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
