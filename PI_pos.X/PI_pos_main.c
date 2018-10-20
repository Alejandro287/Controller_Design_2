/*
 * -------------------------------------------------------------------
 * MPLAB 16-Bit Device Blocks for Simulink v3.38.
 *
 *   Product Page:  http://www.microchip.com/SimulinkBlocks
 *           Forum: http://www.microchip.com/forums/f192.aspx
 *           Wiki:  http://microchip.wikidot.com/simulink:start
 * -------------------------------------------------------------------
 * File: PI_pos_main.c
 *
 * Code generated for Simulink model 'PI_pos'.
 *
 * Model version                  : 1.40
 * Simulink Coder version         : 8.4 (R2013a) 13-Feb-2013
 * C/C++ source code generated on : Sat Nov 12 23:47:58 2016
 */

#define MCHP_isMainFile
#include "PI_pos.h"

/* Microchip Global Variables */
/* Set Fuses Options */
_FOSC( FRC_PLL4 & FRC & CSW_FSCM_OFF ) ;
_FWDT( WDT_OFF ) ;
_FBORPOR( BORV27 & PBOR_OFF ) ;

/* Scheduler */
void __attribute__((__interrupt__,__auto_psv__)) _T1Interrupt(void)
{
  {
    struct {
      unsigned int Flags0 : 1;
      unsigned int Flags1 : 1;
    } static volatile Overrun;

    struct {
      unsigned int Flags0 : 1;
      unsigned int Flags1 : 1;
    } static volatile event;

    static int_T taskCounter[2] = { 0, 0 };

    _T1IF = 0;                         /* Re-enable interrupt */

    /* Check subrate overrun, set rates that need to run this time step*/
    if (taskCounter[1] == 0) {         /* task dropped on overload */
      event.Flags1 = 1U;
    }

    /* Update task internal counters */
    taskCounter[1]++;
    if (taskCounter[1] == 10) {
      taskCounter[1]= 0;
    }

    /* Step the model for base rate */
    /* Start profiling task 0 */
    PI_pos_step0();

    /* Get model outputs here */
    _T1IF = 0;                         /* Re-enable interrupt */

    /* Stop profiling task 0 */
    if (_T1IF ) {
      return;                          /* Will re-enter into the interrupt */
    }

    /* Re-Enable Interrupt. IPL value is 2 at this point */
    _IPL0 = 1;                         /* Set IPL to 1 (interrupt priority is 2) */
    _IPL1 = 0;

    /* Step the model for any subrate */
    /* Handle Task 1 */
    if (Overrun.Flags1) {
      return;                          /* Priority to higher rate steps interrupted */
    }

    if (event.Flags1) {
      Overrun.Flags1 = 1;
      do {
        /* Start profiling task 1 */
        event.Flags1 = 0U;
        PI_pos_step1();

        /* Get model outputs here */
        ;                              /* Execute task tid 1 */

        /* Stop profiling task 1 */
      } while (event.Flags1);

      Overrun.Flags1 = 0U;
    }

    /* Disable Interrupt. IPL value is 1 at this point */
    _IPL1 = 1;                         /* Set IPL to 2 (interrupt priority was 1) */
    _IPL0 = 0;
  }
}

int main()
{
  /* Initialize model */
  /* Configure Pins as Analog or Digital */
  ADPCFG = 0x30;

  /* Configure Remappables Pins */

  /* Configure Digitals I/O directions */
  TRISD = 0xFFFA;
  TRISE = 0xFFFD;
  TRISF = 0xFFDF;

  /* Initialize model */
  PI_pos_initialize();

  /* Configure Timers */
  /* --- TIMER 1 --- This timer is enabled at end of configuration functions. */
  _T1IP = 2;                           /* Set timer Interrupt Priority */
  _T1IF = 0;                           /* Reset pending Interrupt */
  _T1IE = 1;                           /* Enable Timer Interrupt. */
  PR1 = 0x0732;                        /* Period */

  /* Enable Time-step */
  TMR1 = 0x0731;
  T1CON = 0x8000;                      /* Timer 1 is the source trigger for the model Time-step */

  /* Main Loop */
  for (;;) ;
}                                      /* end of main() */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
