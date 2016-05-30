/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_io.h"
#include "xparameters.h"
void print(char *str);

//extern void Xil_Out16LE(u32 Addr, u16 Value);
//extern void Xil_Out32LE(u32 Addr, u32 Value);

//Uartlite XPAR_AXI_UARTLITE_0_BASEADDR
void send_to_Uart(u32 Value)
{
	Xil_Out32LE(XPAR_AXI_UARTLITE_0_BASEADDR,Value);
}

void send_address_to_UART(u32 Addr)
{
	u32 val = Xil_In32LE(Addr);
	send_to_Uart(val);
}


int main()
{
    init_platform();

    //May not work ? (AXI is mapped here but a
    //value only is given
    send_to_Uart((u32) 5);


	int* own_a = NULL;
	//int* own_v = NULL;

	int* ext_a = NULL;
	//int* ext_v = NULL;


	#if XPAR_CPU_ID == 0
		//Write to own memory
		own_a = (int*) XPAR_MICROBLAZE_0_LMB_BRAM_IF_CNTRL_MICROBLAZE_0_BASEADDR;
		Xil_Out32LE(own_a,20);
		//*own_a = 20;
		//REad From own memory to see if it worked
		send_address_to_UART((u32) own_a);

		//own_v = (int*) XPAR_MICROBLAZE_0_LMB_BRAM_IF_CNTRL_MICROBLAZE_0_BASEADDR + 0x00000001;
		//Read from own memory
		//*own_v = *own_a;


		//Write to extern memory
		ext_a = (int*) XPAR_AXI_BRAM_CTRL_1_S_AXI_BASEADDR + 0x000000001;
		Xil_Out32LE(ext_a,30);
		//ext_v = (int*) XPAR_AXI_BRAM_CTRL_1_S_AXI_BASEADDR + 0x000000002;
		send_address_to_UART((u32) own_a);

	#elif XPAR_CPU_ID == 1
		//Write to own memory
		own_a = (int*) XPAR_MICROBLAZE_1_LMB_BRAM_IF_CNTRL_MICROBLAZE_1_BASEADDR;
		Xil_Out32LE(own_a,20);
		//*own_a = 20;
		//REad From own memory to see if it worked
		send_address_to_UART((u32) own_a);

		//own_v = (int*) XPAR_MICROBLAZE_0_LMB_BRAM_IF_CNTRL_MICROBLAZE_0_BASEADDR + 0x00000001;
		//Read from own memory
		//*own_v = *own_a;


		//Write to extern memory
		ext_a = (int*) XPAR_AXI_BRAM_CTRL_1_S_AXI_BASEADDR; // + 0x000000001;
		Xil_Out32LE(ext_a,30);
		//ext_v = (int*) XPAR_AXI_BRAM_CTRL_1_S_AXI_BASEADDR + 0x000000002;
		send_address_to_UART((u32) ext_a);
	#endif


    print("Hello World\n\r");

    cleanup_platform();
    return 0;
}
