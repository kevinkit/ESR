#include <stdio.h>
#include "platform.h"
#include "xil_io.h"
#include "xparameters.h"

//void print(char *str);

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


	u32 own_a;
	int own_v;

	u32 ext_a;
	int ext_v;

	volatile int t = 0;


	#if XPAR_CPU_ID == 0
		//Write to own memory
		own_a = (u32) XPAR_MICROBLAZE_0_LMB_BRAM_IF_CNTRL_MICROBLAZE_0_BASEADDR;
		Xil_Out32LE(own_a,20);
		//*own_a = 20;
		//REad From own memory to see if it worked
		xil_printf("Wrote to adress %d\n",own_a);
		own_v = (int) Xil_In32LE(own_a);
		xil_printf("Value read:%d",own_v);

		if(own_v == 20){
			print("READ/WRITE to own Memory was correct\n");
		}


		//own_v = (int*) XPAR_MICROBLAZE_0_LMB_BRAM_IF_CNTRL_MICROBLAZE_0_BASEADDR + 0x00000001;
		//Read from own memory
		//*own_v = *own_a;


		//Write to extern memory
		ext_a = (u32) (XPAR_AXI_BRAM_CTRL_1_S_AXI_BASEADDR + 1);
		xil_printf("value of baseaddr %x \n", XPAR_AXI_BRAM_CTRL_1_S_AXI_BASEADDR);
		Xil_Out32LE(ext_a,55);
		for(t = 0; t < 10; t++)
		{
			t;
		}
		//ext_v = (int*) XPAR_AXI_BRAM_CTRL_1_S_AXI_BASEADDR + 0x000000002;
		xil_printf("Wrote to ext adress %x\n", ext_a);
		ext_v = (int) Xil_In32LE(own_a);
		xil_printf("Value read:%x\n",&ext_v);

		if(ext_v == 30){
			print("READ/WRITE to ext Memory was correct");
		}


	#elif XPAR_CPU_ID == 1
		//Write to own memory
		own_a = (u32) XPAR_MICROBLAZE_1_LMB_BRAM_IF_CNTRL_MICROBLAZE_1_BASEADDR;
		Xil_Out32LE(own_a,20);
		//*own_a = 20;
		//REad From own memory to see if it worked
		xil_printf("Wrote to adress %d\n",(u32) own_a);
		own_v = (int) Xil_In32LE(own_a);
		xil_printf("Value read:%d",own_v);

		if(own_v == 20){
			print("\nREAD/WRITE to own Memory was correct");
		}


		//own_v = (int*) XPAR_MICROBLAZE_0_LMB_BRAM_IF_CNTRL_MICROBLAZE_0_BASEADDR + 0x00000001;
		//Read from own memory
		//*own_v = *own_a;


		//Write to extern memory
		ext_a = (u32) XPAR_AXI_BRAM_CTRL_0_S_AXI_BASEADDR + 0x000000001;
		Xil_Out32LE(ext_a,30);
		//ext_v = (int*) XPAR_AXI_BRAM_CTRL_1_S_AXI_BASEADDR + 0x000000002;
		xil_printf("Wrote to ext adress %d\n",(u32) ext_a);
		ext_v = (int) Xil_In32LE(own_a);
		xil_printf("Value read:%d",ext_v);

		if(ext_v == 30){
			print("READ/WRITE to ext Memory was correct");
		}
	#endif


    print("Hello World\n\r");

    cleanup_platform();
    return 0;
}
