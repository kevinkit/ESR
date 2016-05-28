/*
 * readwriteprocessor1.c
 *
 *  Created on: 28.05.2016
 *      Author: Kevin
 */

#define	TO_PROCESSOR_0  0xC0000000 //201326592
#define TO_PROCESSOR_1  0xC2000000 //203423744
#define TO_PROCESSOR_2  0xC4000000 //205520896
#define TO_PROCESSOR_3  0xC6000000 //207618048


#define distance 0x02000000 //distance between adresses
#define id 0 //who am I ?

#define OWN 0xC0002000 //own adress
#define amount 4 //amount of CPUs in the whole system



#define SIZE 10 //Size of private memory , that is only for own purpose

#include <stdlib.h>
#include <stdio.h>
#include "xparameters.h"


int read(
		int ADRESS){
	int *adr = (int*) ADRESS;
	return adr[0];
}


void write_int(
		int ADRESS,
		int m) {
	int *adr = (int*) ADRESS;
	*adr = m;
}

int main()
{
	return 0;
	int i = 0;
	int j = 0;
	int res[SIZE];
	int dres[SIZE];
	//Write to own Memory
	for(;i<SIZE;i++){
		write_int(OWN+i,i);
	}
	//Read from own Memory
	for(i=0;i<SIZE;i++){
		res[i] = read(OWN+i) << 1; //multiply by 2 to see diferences later
	}

	//Write to  other processors
	for(;j < amount;j++){
		for(i=SIZE;i<2*SIZE;i++){ //Writing to memory_addr > 10
			write_int(TO_PROCESSOR_1+j*distance,res[i]);
		}
	}

	//Write to  other processors
	for(j=0;j < amount;j++){
		for(i=SIZE;i<2*SIZE;i++){ //Writing to memory_addr > 10
			//Do not write to own adress
			if (j == id)
				continue;

			dres[i] = read(TO_PROCESSOR_0+j*distance);
		}
	}

	return 0;
}
