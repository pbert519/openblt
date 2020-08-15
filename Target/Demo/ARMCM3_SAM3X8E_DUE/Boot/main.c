/************************************************************************************//**
* \file         Demo/_template/Boot/main.c
* \brief        Bootloader application source file.
* \ingroup      Boot__template
* \internal
*----------------------------------------------------------------------------------------
*                          C O P Y R I G H T
*----------------------------------------------------------------------------------------
*   Copyright (c) 2019  by Feaser    http://www.feaser.com    All rights reserved
*
*----------------------------------------------------------------------------------------
*                            L I C E N S E
*----------------------------------------------------------------------------------------
* This file is part of OpenBLT. OpenBLT is free software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published by the Free
* Software Foundation, either version 3 of the License, or (at your option) any later
* version.
*
* OpenBLT is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
* without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
* PURPOSE. See the GNU General Public License for more details.
*
* You have received a copy of the GNU General Public License along with OpenBLT. It 
* should be located in ".\Doc\license.html". If not, contact Feaser to obtain a copy.
*
* \endinternal
****************************************************************************************/

/****************************************************************************************
* Include files
****************************************************************************************/
//#include <lib/CMSIS/Device/ATMEL/sam3xa/include/pio/pio_sam3x8e.h>
#include "lib/CMSIS/Device/ATMEL/sam.h"
#include "boot.h"                                /* bootloader generic header          */
#include "chip.h"

/****************************************************************************************
* Function prototypes
****************************************************************************************/
static void Init(void);


/************************************************************************************//**
** \brief     This is the entry point for the bootloader application and is called
**            by the reset interrupt vector after the C-startup routines executed.
** \return    Program return code.
**
****************************************************************************************/
int main(void)
{
  /* initialize the microcontroller */
  Init();
  /* initialize the bootloader */
  BootInit();

  /* start the infinite program loop */
  while (1)
  {
    /* run the bootloader task */
    BootTask();
  }

  /* program should never get here */
  return 0;
} /*** end of main ***/


/************************************************************************************//**
** \brief     Initializes the microcontroller.
** \return    none.
**
****************************************************************************************/
static void Init(void)
{
  /* TODO ##Boot Initialize the microcontroller. This typically consists of configuring
   * the microcontroller's system clock and configuring the GPIO for the communication
   * peripheral(s) enabled in the bootloader's configuration header file "blt_conf.h".
   */
  SystemInit();

#if (BOOT_COM_CAN_ENABLE > 0)
  // CAN
  PIO_Configure(PIOA, PIO_PERIPH_A, PIO_PA1A_CANRX0, PIO_DEFAULT);
  PIO_Configure(PIOA, PIO_PERIPH_A, PIO_PA0A_CANTX0, PIO_DEFAULT);
  pmc_enable_periph_clk(ID_PIOA);
  pmc_enable_periph_clk(ID_CAN0);
#endif

#if (BOOT_COM_RS232_ENABLE > 0)

  // RS232
#endif

  // LED
  PIO_Configure(PIOC, PIO_OUTPUT_0, PIO_PC3, PIO_DEFAULT);
  PIO_Configure(PIOC, PIO_OUTPUT_0, PIO_PC2, PIO_DEFAULT);
  pmc_enable_periph_clk(ID_PIOC);
  
} /*** end of Init ***/


/*********************************** end of main.c *************************************/
