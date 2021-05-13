/*
 * This file is part of the EasyLogger Library.
 *
 * Copyright (c) 2015, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: Portable interface for each platform.
 * Created on: 2015-04-28
 */
 
#include <elog.h>

#include "usart.h"
#include "string.h"

static bool output_mutex =false; //for no-os application's logging

/**
 * EasyLogger port initialize
 *
 * @return result
 */
ElogErrCode elog_port_init(void) {
    ElogErrCode result = ELOG_NO_ERR;

    /* add your code here */
    
    return result;
}

/**
 * output log port interface
 *
 * @param log output of log
 * @param size log size
 */
void elog_port_output(const char *log, size_t size) {
    
    /* add your code here */

	HAL_UART_Transmit(&huart1,(uint8_t*)log,size,0xffff);
}

/**
 * output lock
 */
void elog_port_output_lock(void) {
    
    /* add your code here */
	if(output_mutex){
		unsigned char time_out = 20;
		while(output_mutex && time_out--){//100ms timout for multi-thread use log function
			HAL_Delay(1);
		}
		if(!output_mutex){
			output_mutex = true;	//lock
		}
	}
}

/**
 * output unlock
 */
void elog_port_output_unlock(void) {
    
    /* add your code here */
	output_mutex = false;
}

/**
 * get current time interface
 *
 * @return current time
 */
const char *elog_port_get_time(void) {
    
    /* add your code here */

	static char cur_sys_time[12]={0};
	 snprintf(cur_sys_time,12,"% 10u",HAL_GetTick());
	 //add dot to string(unit from 'MS' to 'S')
	 memmove(&cur_sys_time[8],&cur_sys_time[7],4);
	 cur_sys_time[7] = '.';
     return cur_sys_time;

}

/**
 * get current process name interface
 *
 * @return current process name
 */
const char *elog_port_get_p_info(void) {
    
    /* add your code here */
    return "";
    
}

/**
 * get current thread name interface
 *
 * @return current thread name
 */
const char *elog_port_get_t_info(void) {
    
    /* add your code here */
    return "";
    
}
