/*
 * simple.c
 *
 *This is a universal test for reading and writing
 *This
 *  Created on: 29.05.2016
 *      Author: Kevin
 */


#include <stdlib.h>
#include "xparameters.h"


int main()
{


	//eventuell hier ein Skript schreiben, dass einem die
	//Dateien erstellt
	int* own_a = NULL;
	int* own_v = NULL;

	int* ext_a = NULL;
	int* ext_v = NULL;


	#if XPAR_CPU_ID == 0
		//Write to own memory
		own_a = (int*) XPAR_MICROBLAZE_0_LMB_BRAM_IF_CNTRL_MICROBLAZE_0_BASEADDR;
		*own_a = 20;
		own_v = (int*) XPAR_MICROBLAZE_0_LMB_BRAM_IF_CNTRL_MICROBLAZE_0_BASEADDR + 0x00000001;
		//Read from own memory
		*own_v = *own_a;


		//Write to extern memory
		ext_a = (int*) XPAR_AXI_BRAM_CTRL_1_S_AXI_BASEADDR + 0x000000001;
		*ext_a = 30;
		ext_v = (int*) XPAR_AXI_BRAM_CTRL_1_S_AXI_BASEADDR + 0x000000002;
		*ext_v = *ext_a;

	#elif XPAR_CPU_ID == 1
		own_a = (int*) XPAR_MICROBLAZE_1_LMB_BRAM_IF_CNTRL_MICROBLAZE_1_BASEADDR;
		*own_a = 20;
		own_v = (int*) XPAR_MICROBLAZE_1_LMB_BRAM_IF_CNTRL_MICROBLAZE_1_BASEADDR + 0x00000001;
		//Read from own memory
		*own_v = *own_a;


		//Write to extern memory
		ext_a = (int*) XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR + 0x000000001;
		*ext_a = 30;
		ext_v = (int*) XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR + 0x000000002;
		*ext_v = *ext_a;
	#elif XPAR_CPU_ID == 2
		// to be continued...
	#elif XPAR_CPU_ID == 3
		// to be continued...
	#endif

	return 0;
}
