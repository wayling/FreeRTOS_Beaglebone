/*
 * (C) Copyright 2004
 * Texas Instruments
 *
 * (C) Copyright 2000-2004
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __BBCONSOLE_H_
#define __BBCONSOLE_H_			1

#define CFG_PRINTF

#define DM3730_L4_PERIPHERAL	0x49000000
#define OMAP34XX_UART3			(DM3730_L4_PERIPHERAL+0x20000)

#ifdef CFG_PRINTF

#define CFG_NS16550
#define CFG_NS16550_SERIAL
#define CFG_NS16550_REG_SIZE	-4
#define CFG_NS16550_CLK			(48000000)
#define CFG_NS16550_COM1		0x44e09000

#define CONFIG_SERIAL1			1	/* use UART3 */
#define CONFIG_CONS_INDEX		1

#define CONFIG_BAUDRATE			115200
#define CFG_PBSIZE				256

#define printf(fmt,args...)	serial_printf (fmt ,##args)
#define getc() serial_getc()
int	 serial_init(void);
void serial_setbrg(void);
void serial_putc(const char);
void serial_puts(const char *);
int	 serial_getc(void);
int	 serial_tstc(void);
void serial_printf (const char *fmt, ...);

#else /* CFG_PRINTF */

#define printf(fmt,args...)
#define getc() ' '

#endif	/* CFG_PRINTF */

#endif	/* __BBCONSOLE_H_ */
