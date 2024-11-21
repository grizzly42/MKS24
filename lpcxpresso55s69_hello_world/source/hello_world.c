/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2024 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_device_registers.h"
#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "fsl_power.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
uint32_t DWT1,DWT2;
uint32_t status;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int strcmp_safe(const char *str1, const char *str2, size_t max_len) {
	uint8_t result = 0;

	for (size_t i = 0; i < max_len; i++) {
		uint8_t char1 = str1[i];
		uint8_t char2 = (i < max_len && str2[i] != '\0') ? str2[i] : '\0';

		result |= char1 ^ char2;
	}

	return result;
}
int main(void)
{
	char ch;


	/* Init board hardware. */
	/* set BOD VBAT level to 1.65V */
	POWER_SetBodVbatLevel(kPOWER_BodVbatLevel1650mv, kPOWER_BodHystLevel50mv, false);
	/* attach main clock divide to FLEXCOMM0 (debug console) */
	CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitDebugConsole();
#if !defined(DONT_ENABLE_FLASH_PREFETCH)
	/* enable flash prefetch for better performance */
	SYSCON->FMCCR |= SYSCON_FMCCR_PREFEN_MASK;
#endif


	while (1)
	{
		ch = GETCHAR();
		//PUTCHAR(ch);
		char password_stored[20] = "xdxd";
			char input[20];

			PRINTF("\r\nEnter password: ");
			SCANF("%s",input);
			DWT1 = DWT -> CYCCNT;
			status = strcmp_safe(input,password_stored,strlen(password_stored));
			//PRINTF("hello world.\r\n");
			//status=function(x,y);
			DWT2 = DWT -> CYCCNT;
			PRINTF("\r\ninput: %s: ",input);
			if(status == 0){
				PRINTF("\r\ninput correct");
			}else{
				PRINTF("\r\ninput invalid");
			}

			PRINTF("\r\nCycles in function: %d: ", DWT2-DWT1);


	}
}
