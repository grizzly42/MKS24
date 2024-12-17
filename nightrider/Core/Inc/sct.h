/*
 * sct.h
 *
 *  Created on: Oct 10, 2024
 *      Author: 240671
 */

#ifndef SRC_SCT_H_
#define SRC_SCT_H_
#include "main.h"

void sct_init(void);

void sct_led(uint32_t value);

void sct_value(uint16_t value, uint8_t led);
void sct_bargraph_only(uint16_t lednum);
void sct_uni_bar(uint16_t ledBinI);

#endif /* SRC_SCT_H_ */
