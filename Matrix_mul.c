#include "platform.h"
#include "xparameters.h"
#include "xil_io.h"

#define RESULTADDR 0xC0001000

unsigned int calc_row_col(int* start_row, int* start_col, unsigned int col_len);

int main() {
	init_platform();

	unsigned int* mutex_MB0 = (unsigned int*)XPAR_BRAM_1_HIGHADDR-20;
	unsigned int* mutex_MB1 = (unsigned int*)XPAR_BRAM_2_HIGHADDR-20;
	mutex_MB0[0] = 0;
	mutex_MB1[0] = 0;

	unsigned int* MB0_finished = (unsigned int*)XPAR_BRAM_1_HIGHADDR-16;
	unsigned int* MB1_finished = (unsigned int*)XPAR_BRAM_2_HIGHADDR-16;
	MB0_finished[0] = 0;
	MB1_finished[0] = 0;

	unsigned int* result_vec = (unsigned int*)RESULTADDR;
	unsigned short col_length = 2;
	unsigned short row_length = 2;

	unsigned int x = 0;
	unsigned short i = 0;
	unsigned short j = 0;

#if XPAR_CPU_ID == 0

	//0xC0001000
	int* my_addr = (int*)XPAR_LM_BRAM_IF_CNTLR_0_BASEADDR;
	int* your_addr = (int*)XPAR_BRAM_2_BASEADDR;

	MB0_finished[0] = 0;//warte auf mich

	while(mutex_MB0[0] != 0){;}//warte,dass der speicher zugreifbar ist

	mutex_MB0[0] = 1;//sperren

	for (; x < col_length*row_length; x++)
	{
		Xil_Out32LE((XPAR_LM_BRAM_IF_CNTLR_0_BASEADDR + 4*x), (x+1));//Matrix 1 und 2 ist [1,2; 3,4]
		Xil_Out32LE((XPAR_BRAM_2_BASEADDR + 4*x), (x+1));
	}

	mutex_MB0[0] = 0;//sperre aufheben
	MB0_finished[0] = 1;//bin fertig

//	for(i = 0; i < row_length*col_length;i++)
//	{
//		xil_printf("test0:%d\n", my_addr[i]);
//		xil_printf("test1:%d\n", your_addr[i]);
//		//all ok?
//	}

	while(mutex_MB0[0] != 0 || mutex_MB1[0] != 0){;}

	mutex_MB0[0] = 1;
	mutex_MB1[0] = 1;

	unsigned short ii = 0;

	//hole mir die 0.Reihe und jede übernächste
	for(i=0;i<row_length;i++)
	{
		for(j=0;j<col_length;j++)
		{
			result_vec[ii] = calc_row_col(my_addr+row_length*2*i, your_addr, col_length);
			//xil_printf("result: %d \n", result_vec[ii]);//der ging auch
			ii++;
			your_addr++;
		}
		//result_vec += row_length * 4;
		ii += row_length;
		//my_addr++;
		//xil_printf("\t%d\n", *result_vec);
	}

	mutex_MB0[0] = 0;
	mutex_MB1[0] = 0;

//	volatile int t= 0;
//	for(;t < 5000000; t++)
//	{
//		t;
//	}

	//muss hier eig. nie warten,da beide dasselbe parallel ab arbeiten => gleiche Zeit
	xil_printf("\n");
	while(MB1_finished[0] != 1)
	{
		xil_printf(",");
	}//warte auf mb1
	xil_printf("\n");

	while(mutex_MB0[0] != 0 || mutex_MB1[0] != 0){;}

	mutex_MB0[0] = 1;
	mutex_MB1[0] = 1;
	result_vec = RESULTADDR;
	//xil_printf("Ergebnis:\n");
	for(i = 0; i < row_length*col_length; i++)
	{
		xil_printf("res:%d", *result_vec);//der ging
		xil_printf("\n");
		result_vec++;
	}

	mutex_MB0[0] = 0;
	mutex_MB1[0] = 0;


//	xil_printf("\n end of MB0\n\n");
//	xil_printf("=================\n\n");

#elif XPAR_CPU_ID == 1

	//0xC0001000
	int* my_addr = (int*)XPAR_LM_BRAM_IF_CNTLR_1_BASEADDR;
	int* your_addr = (int*)XPAR_BRAM_1_BASEADDR;
//
//	volatile int t= 0;
//	for(;t < 50000; t++)
//	{
//		t;
//	}

	// schreiben macht mb0
//	if(mutex_MB1[0] == 0){
//			mutex_MB1[0] = 1;
//			for (; x < col_length+row_length; x++)
//			{
//					Xil_Out32LE((XPAR_LM_BRAM_IF_CNTLR_1_BASEADDR + 4*x), x+1);
//			}
//			mutex_MB1[0] = 0;
//		}
//	if(mutex_MB0[0] == 0)
//	{
//		mutex_MB0[0] = 1;
//		for(i = 0; i < 4;i++)
//		{
//			xil_printf("my:%d\n", my_addr[i]);
//			xil_printf("your:%d\n", your_addr[i]);
//			//all ok?-> scheint so
//		}
//		mutex_MB0[0] = 0;
//	}

	xil_printf("\n");
	while(MB0_finished[0] != 1)
	{
		xil_printf(".");
	}//warte auf mb0

	while(mutex_MB0[0] != 0 || mutex_MB1[0] != 0){;}

	MB1_finished[0] = 0;//warte auf mich
	mutex_MB0[0] = 1;
	mutex_MB1[0] = 1;

	unsigned short ii = 0;
	result_vec = RESULTADDR + row_length * 4;

	//hole mir die 1.Reihe und jede übernächste
	for(i = 0;i<row_length;i++)
	{
		for(;j<col_length;j++)
		{
			result_vec[ii] = calc_row_col(my_addr+row_length*(2*i+1), your_addr, col_length);
			//xil_printf("result: %d \n", result_vec[ii]);
			ii++;
			your_addr++;
		}
		//result_vec += row_length * 4;
		ii += row_length;
	}
	mutex_MB0[0] = 0;
	mutex_MB1[0] = 0;
	MB1_finished[0] = 1;

//ausgabe ueber mb0

#elif XPAR_CPU_ID == 2

#elif XPAR_CPU_ID == 3
	#endif

	cleanup_platform();
	return 0;
}

unsigned int calc_row_col(int* start_row, int* start_col, unsigned int col_len)
{
	unsigned short i = 0;
	unsigned int val = 0;

		for(; i < col_len;i++)
		{
			val +=  start_row[i] * start_col[i*col_len];
		}
		//xil_printf("func()%d\n", val);
		return val;
}
