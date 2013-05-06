/*
        skyeye_bus.h - necessary definition for skyeye bus
        Copyright (C) 2003-2007 Skyeye Develop Group
        for help please send mail to <skyeye-developer@lists.sf.linuxforum.net>

        This program is free software; you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation; either version 2 of the License, or
        (at your option) any later version.

        This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with this program; if not, write to the Free Software
        Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/
/*
 * 12/16/2006   Michael.Kang  <blackfin.kang@gmail.com>
 */
#ifndef __SKYEYE_BUS_H__
#define __SKYEYE_BUS_H__

#include "breakpoint.h"

/*
 * The type for before action or after action.
 */
typedef enum{
	Before_act = 0,
	After_act
}before_after_t;

typedef struct bus_recorder_s{
	access_t rw;
	short size;
	int addr;
	uint32_t* value;
	before_after_t when;
}bus_recorder_t;

/* snooping the bus activities and record it */
void bus_snoop(access_t rw, short size, int addr, uint32_t value, before_after_t when);

/* get the bus access information */
bus_recorder_t* get_last_bus_access();
void io_do_cycle (void * state);
/* register one bus */
typedef int(*bus_read_t)(short size, generic_address_t addr, uint32_t * value);
typedef int(*bus_write_t)(short size, generic_address_t addr, uint32_t value);

int default_bus_read(short size, generic_address_t addr, uint32_t * value);
int default_bus_write(short size, generic_address_t addr, uint32_t value);
void register_bus_operation(bus_read_t, bus_write_t);
#endif
