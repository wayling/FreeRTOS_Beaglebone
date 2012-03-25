/*
    FreeRTOS V7.0.1 - Copyright (C) 2011 Real Time Engineers Ltd.

    ***************************************************************************
    *                                                                         *
    * If you are:                                                             *
    *                                                                         *
    *    + New to FreeRTOS,                                                   *
    *    + Wanting to learn FreeRTOS or multitasking in general quickly       *
    *    + Looking for basic training,                                        *
    *    + Wanting to improve your FreeRTOS skills and productivity           *
    *                                                                         *
    * then take a look at the FreeRTOS books - available as PDF or paperback  *
    *                                                                         *
    *        "Using the FreeRTOS Real Time Kernel - a Practical Guide"        *
    *                  http://www.FreeRTOS.org/Documentation                  *
    *                                                                         *
    * A pdf reference manual is also available.  Both are usually delivered   *
    * to your inbox within 20 minutes to two hours when purchased between 8am *
    * and 8pm GMT (although please allow up to 24 hours in case of            *
    * exceptional circumstances).  Thank you for your support!                *
    *                                                                         *
    ***************************************************************************

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    ***NOTE*** The exception to the GPL is included to allow you to distribute
    a combined work that includes FreeRTOS without being obliged to provide the
    source code for proprietary components outside of the FreeRTOS kernel.
    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public 
    License and the FreeRTOS license exception along with FreeRTOS; if not it 
    can be viewed here: http://www.freertos.org/a00114.html and also obtained 
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

/* 
	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used.
*/


/*
 * Creates all the demo application tasks, then starts the scheduler.  The WEB
 * documentation provides more details of the demo application tasks.
 * 
 * Main.c also creates a task called "Check".  This only executes every three 
 * seconds but has the highest priority so is guaranteed to get processor time.  
 * Its main function is to check that all the other tasks are still operational.
 * Each task (other than the "flash" tasks) maintains a unique count that is 
 * incremented each time the task successfully completes its function.  Should 
 * any error occur within such a task the count is permanently halted.  The 
 * check task inspects the count of each task to ensure it has changed since
 * the last time the check task executed.  If all the count variables have 
 * changed all the tasks are still executing error free, and the check task
 * toggles the onboard LED.  Should any task contain an error at any time 
 * the LED toggle rate will change from 3 seconds to 500ms.
 *
 * To check the operation of the memory allocator the check task also 
 * dynamically creates a task before delaying, and deletes it again when it 
 * wakes.  If memory cannot be allocated for the new task the call to xTaskCreate
 * will fail and an error is signalled.  The dynamically created task itself
 * allocates and frees memory just to give the allocator a bit more exercise.
 *
 */

/* Standard includes. */

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include <semphr.h>
#include <bbconsole.h>

void HelloWorld1(void * pvParameters);
void HelloWorld2(void * pvParameters);
void FlashLED1(void * pvParameters);
void FlashLED2(void * pvParameters);
void CreateHWSemaphore(void);

#define WITH_SEMAPHORE 0
#define WIH_CRITICAL   1

#if WITH_SEMAPHORE

xSemaphoreHandle xSemaphore;

void CreateHWSemaphore()
{
    //prvSetupHardware();
	xSemaphore = xSemaphoreCreateMutex();
	if(xSemaphore == 0)
	{
		printf("\n semaphore creation failed \n");
	}
	else
	{
		printf("\n semaphore creation successful \n");
	}
}

portTASK_FUNCTION( HelloWorld1, pvParameters )
{
	pvParameters = 0;
	int i = 0;
    //prvSetupHardware();
	while(1)
	{
		if(i == 500)
		{
			xSemaphoreTake(xSemaphore, 100);
			printf("Hello world 1 \n");
			xSemaphoreGive(xSemaphore);
		}
		i++;
		if(i > 50000)
			i = 0;
	}
}

portTASK_FUNCTION( HelloWorld2, pvParameters )
{
	pvParameters = 0;
	int i = 0;

	while(1)
	{
		if(i == 500)
		{
			xSemaphoreTake(xSemaphore, 100);
			printf("Hello world 2 \n");
			xSemaphoreGive(xSemaphore);
		}
		i++;
		if(i > 50000)
			i = 0;
	}
}

#elif WIH_CRITICAL

void CreateHWSemaphore()
{
	return;
}

portTASK_FUNCTION( HelloWorld1, pvParameters )
{
	pvParameters = 0;
	int i = 0;

	while(1)
	{
		if(i == 500)
		{
			portENTER_CRITICAL();
			printf("Hello world 1 \n");
			portEXIT_CRITICAL();
		}
		i++;
		if(i > 50000)
			i = 0;
	}
}

portTASK_FUNCTION( HelloWorld2, pvParameters )
{
	pvParameters = 0;
	int i = 0;

	while(1)
	{
		if(i == 500)
		{
			portENTER_CRITICAL();
			printf("Hello world 2 \n");
			portEXIT_CRITICAL();
		}
		i++;
		if(i > 50000)
			i = 0;
	}
}

#else

void CreateHWSemaphore(void)
{

}

portTASK_FUNCTION( HelloWorld1, pvParameters )
{
	pvParameters = 0;
	int i = 0;

	while(1)
	{
		if(i == 500)
		{
			printf("Hello world 1 \n");
		}
		i++;
		if(i > 50000)
			i = 0;
	}
}

portTASK_FUNCTION( HelloWorld2, pvParameters )
{
	pvParameters = 0;
	int i = 0;

	while(1)
	{
		if(i == 500)
		{
			printf("Hello world 2 \n");
		}
		i++;
		if(i > 50000)
			i = 0;
	}
}

#endif

int one;
int MAX123 = 10000;
static void delay(int start)
{
	int i;
	one = start;
	for(i = 0; i < MAX123; i++)
	{
		one++;
		if(one > MAX123)
			break;
	}
}

#define partstNUM_LEDS			( 1 )

static void vParTestSetLED( unsigned portBASE_TYPE uxLED, signed portBASE_TYPE xValue )
{
	unsigned int GPIO_PIN = 0;
	if( uxLED <= partstNUM_LEDS){
		/* I define LED0 (GPIO_149) as 0
		 * and 	LED1 (GPIO_150) as 1 */
		switch(uxLED){
			case 0:
				{
					GPIO_PIN=PIN21;
					break;
				}
			case 1:
				{
					GPIO_PIN=PIN22;
					break;
				}
			default: break;
		};
		if ( xValue )
			(*(REG32(GPIO1_BASE + GPIO_SETDATAOUT))) = GPIO_PIN;
		else
			(*(REG32(GPIO1_BASE + GPIO_CLEARDATAOUT))) = GPIO_PIN;
	}
}

portTASK_FUNCTION(FlashLED1, pvParameters)
{
	pvParameters = 0;

	while(1)
	{
		portENTER_CRITICAL();
		vParTestSetLED(0, 1);
		delay(0);
		vParTestSetLED(0, 0);
		delay(800);
		portEXIT_CRITICAL();
	}
}

portTASK_FUNCTION(FlashLED2, pvParameters)
{
	pvParameters = 0;

	while(1)
	{
		portENTER_CRITICAL();
		vParTestSetLED(1, 1);
		delay(0);
		vParTestSetLED(1, 0);
		delay(800);
		portEXIT_CRITICAL();
	}
}
