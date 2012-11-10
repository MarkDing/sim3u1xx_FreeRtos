//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories. 
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User 
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
// library
#include <stdio.h>
// hal
#include <si32_device.h>
#include <SI32_PBHD_A_Type.h>
#include <SI32_PBSTD_A_Type.h>
// application
#include "gModes.h"
#include "myRtc0.h"
#include "myCpu.h"
/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"

/* The queue used to send strings to the print task for display on the LCD. */
xQueueHandle xLEDQueue;

//==============================================================================
// myApplication.
//==============================================================================
void task1(void * parameters)
{
	uint32_t count = 0;
	const portCHAR *pcPassMessage = "PASS";
	while(1)
	{
		if(SI32_PBSTD_A_read_pin(SI32_PBSTD_2, 8)==0)
		{
			printf("Task1 running %d\n",count++);
			xQueueSend( xLEDQueue, &pcPassMessage, portMAX_DELAY );
		}
	}
}

void task2(void * parameters)
{
	uint32_t count = 0;
	while(1)
	{
		printf("Task2 running %d\n",count++);
		vTaskDelay( 1000 );
	}
}

void task3(void * parameters)
{
	uint32_t count = 0;
	portCHAR *pcMessage;
	while(1)
	{
		/* Wait for a message to arrive. */
		xQueueReceive( xLEDQueue, &pcMessage, portMAX_DELAY );
		SI32_PBSTD_A_toggle_pins(SI32_PBSTD_2,0xc00);
		printf("Task3 running %d  %s\n",count++,pcMessage);
	}
}

int main()
{

	while(SI32_PBSTD_A_read_pin(SI32_PBSTD_2, 8) == 0);
   // Enter the default operating mode for this application (gModes.c)
   gModes_enter_my_default_mode();

   // Print a starting message
   printf("hello world\n");
	/* Create the queue used to pass message to vPrintTask. */
   xLEDQueue = xQueueCreate( 3, sizeof( portCHAR * ) );

   xTaskCreate( task1, "task1", 200, NULL, 1, NULL );
   xTaskCreate( task2, "task2", 200, NULL, 2, NULL );
   xTaskCreate( task3, "task3", 200, NULL, 2, NULL );

	/* Start the scheduler running the tasks and co-routines just created. */
   vTaskStartScheduler();

   while(1);
   // Loop forever...
}

//---eof------------------------------------------------------------------------
