#include <stdio.h>
#include "platform.h"
#include "xil_io.h"
#include "xparameters.h"

int main()
{
    init_platform();

	u32 own_a;
	int own_v;

	u32 ext_a;
	int ext_v;

	volatile int t = 0;


	#if XPAR_CPU_ID == 0
		for(t = 0; t < (XPAR_CPU_ID*5000000); t++)
		{
			t;
		}

		xil_printf("PROCESSOR: %d",XPAR_CPU_ID);



		//Write to own memory
		own_a = (u32) XPAR_LM_BRAM_IF_CNTLR_0_BASEADDR;
		Xil_Out32LE(own_a,20);

		//REad From own memory to see if it worked


		xil_printf("Wrote to adress %x\n",own_a);
		own_v = (int) Xil_In32LE(own_a);

		xil_printf("PROCESSOR: %d",XPAR_CPU_ID);
		xil_printf("Value read:%d\t\n",own_v);

		if(own_v == 20){
			print("READ/WRITE to own Memory was correct\n");
		}


		//own_v = (int*) XPAR_MICROBLAZE_0_LMB_BRAM_IF_CNTRL_MICROBLAZE_0_BASEADDR + 0x00000001;
		//Read from own memory
		//*own_v = *own_a;

		print("\n------------\n");

		//Write to extern memory
		ext_a = (u32) (XPAR_AXI_BRAM_CTRL_1_S_AXI_BASEADDR + 4);
		xil_printf("PROCESSOR: %d",XPAR_CPU_ID);
		xil_printf("value of baseaddr %x \n", XPAR_AXI_BRAM_CTRL_1_S_AXI_BASEADDR);
		Xil_Out32LE(ext_a,55);
		for(t = 0; t < 10; t++)
		{
			t;
		}
		//ext_v = (int*) XPAR_AXI_BRAM_CTRL_1_S_AXI_BASEADDR + 0x000000002;
		xil_printf("PROCESSOR: %d",XPAR_CPU_ID);
		xil_printf("Wrote to ext adress %x\n", ext_a);
		ext_v = (int) Xil_In32LE(ext_a);
		xil_printf("PROCESSOR: %d",XPAR_CPU_ID);
		xil_printf("Value read:%d\n",ext_v);

		if(ext_v == 55){
			print("READ/WRITE to ext Memory was correct\n");
		}
		print("");

	#elif XPAR_CPU_ID == 1
		for(t = 0; t < (XPAR_CPU_ID*5000000); t++)
		{
			t;
		}

		{
			t;
		}

		xil_printf("PROCESSOR: %d:\t",XPAR_CPU_ID);


		//Write to own memory
		own_a = (u32) XPAR_LM_BRAM_IF_CNTLR_1_BASEADDR;
		Xil_Out32LE(own_a,35);

		//REad From own memory to see if it worked
		xil_printf("Wrote to adress %x\n",(u32) own_a);
		own_v = (int) Xil_In32LE(own_a);
		xil_printf("PROCESSOR: %d",XPAR_CPU_ID);
		xil_printf("Value read:%d\n",own_v);

		if(own_v == 35){
			print("\nREAD/WRITE to own Memory was correct\n");
		}


		//Write to extern memory
		ext_a = (u32) XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR + 4;
		Xil_Out32LE(ext_a,53);
		xil_printf("PROCESSOR: %d",XPAR_CPU_ID);
		xil_printf("Wrote to ext adress %x\n",(u32) ext_a);
		ext_v = (int) Xil_In32LE(ext_a);
		xil_printf("PROCESSOR: %d",XPAR_CPU_ID);
		xil_printf("Value read:%d\n",ext_v);

		if(ext_v == 53){
			print("READ/WRITE to ext Memory was correct\n");
		}

	#elif XPAR_CPU_ID == 2
		for(t = 0; t < (XPAR_CPU_ID*5000000); t++)
		{
			t;
		}

		{
			t;
		}

		xil_printf("PROCESSOR: %d:\t",XPAR_CPU_ID);


		//Write to own memory
		own_a = (u32) XPAR_LM_BRAM_IF_CNTLR_2_BASEADDR;
		Xil_Out32LE(own_a,35);
		//*own_a = 20;
		//REad From own memory to see if it worked
		xil_printf("Wrote to adress %x\n",(u32) own_a);
		own_v = (int) Xil_In32LE(own_a);
		xil_printf("PROCESSOR: %d",XPAR_CPU_ID);
		xil_printf("Value read:%d\n",own_v);

		if(own_v == 35){
			print("\nREAD/WRITE to own Memory was correct\n");
		}


		//Write to extern memory
		ext_a = (u32) XPAR_AXI_BRAM_CTRL_3_S_AXI_BASEADDR + 4;
		Xil_Out32LE(ext_a,53);
		xil_printf("PROCESSOR: %d",XPAR_CPU_ID);
		xil_printf("Wrote to ext adress %x\n",(u32) ext_a);
		ext_v = (int) Xil_In32LE(ext_a);
		xil_printf("PROCESSOR: %d",XPAR_CPU_ID);
		xil_printf("Value read:%d\n",ext_v);

		if(ext_v == 53){
			print("READ/WRITE to ext Memory was correct\n");
		}
	#elif XPAR_CPU_ID == 3
		for(t = 0; t < (XPAR_CPU_ID*5000000); t++)
		{
			t;
		}

		{
			t;
		}

		xil_printf("PROCESSOR: %d:\t",XPAR_CPU_ID);


		//Write to own memory
		own_a = (u32) XPAR_LM_BRAM_IF_CNTLR_3_BASEADDR;
		Xil_Out32LE(own_a,35);

		//REad From own memory to see if it worked
		xil_printf("Wrote to adress %x\n",(u32) own_a);
		own_v = (int) Xil_In32LE(own_a);
		xil_printf("PROCESSOR: %d",XPAR_CPU_ID);
		xil_printf("Value read:%d\n",own_v);

		if(own_v == 35){
			print("\nREAD/WRITE to own Memory was correct\n");
		}


		//Write to extern memory
		ext_a = (u32) XPAR_AXI_BRAM_CTRL_2_S_AXI_BASEADDR + 4;
		Xil_Out32LE(ext_a,53);
		xil_printf("PROCESSOR: %d",XPAR_CPU_ID);
		xil_printf("Wrote to ext adress %x\n",(u32) ext_a);
		ext_v = (int) Xil_In32LE(ext_a);
		xil_printf("PROCESSOR: %d",XPAR_CPU_ID);
		xil_printf("Value read:%d\n",ext_v);

		if(ext_v == 53){
			print("READ/WRITE to ext Memory was correct\n");
		}
	#endif


    print("Hello World\n\r");

    cleanup_platform();
    return 0;
}
