//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------

//==============================================================================
// WARNING:
//
// This file is auto-generated by AppBuilder and should not be modified.
// Any hand modifications will be lost if the project is regenerated.
//==============================================================================
// library
#include <stdio.h>
// hal
#include <si32_device.h>
// application
#include "gCpu.h"

//==============================================================================
//2nd LEVEL  INTERRUPT HANDLERS
//==============================================================================
/*NONE*/

//==============================================================================
//1st LEVEL  INTERRUPT HANDLERS
//==============================================================================
void SysTick_Handler(void)
{
   msTicks++;
   /*NO SECOND LEVEL HANDLER SPECIFIED*/
}

//==============================================================================
//CONFIGURATION FUNCTIONS
//==============================================================================
// Sets up systick
void gCpu_enter_default_config(void)
{
  SystemCoreClock = 20000000;
  if (SysTick_Config(SystemCoreClock / 1000))
  {
    printf("ERROR: SysTick_Config failed\n");
  }

  // Set Priority for Cortex-M3 System Interrupts.
  NVIC_SetPriority(SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1);
}

// MODULE VARIABLES
//------------------------------------------------------------------------------
// Variable that incrments 1000 times / second
volatile uint32_t msTicks;

//-eof--------------------------------------------------------------------------
