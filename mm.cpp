/*
  License GPL V3.
  Ahmed Sadikhov, ahmed.sadikhov@gmail.com
  Esrin Memory Manager
  Release 1
  20 feb 2017  

*/

#include  "esrin.h"
#include <windows.h>

//TIPLER
/*
  tam	 -	int		- 1
  kesr	 -	float	- 2
  simvol -	char	- 3 
  ----
  unsigned long		-	is used as virtual address
  unsigned char*	-	is used as physical address
  int				-	is used to hold vars tip

*/


union val_types{
	int int_val;
	float float_val;
	char char_val;
} val;

#define MB 1048576 // 1MB = 1024*1024
#define GB 1073741824 // 1GB = 1024*1024*1024

struct page {
	unsigned char *data;
	byte mapped;
};


struct page mem[MAX_PAGE];

unsigned long stack = GB;
unsigned long stack_base = GB;

//return physical address for given virtual address
unsigned char *get_ph_adrs(unsigned long va){

	struct page *pg;
	int ind, ofst;

	ind = va/MB;
	ofst = va%MB;

	pg = mem + ind;

	if (!pg->mapped){
		pg->data = (unsigned char *)malloc(MB);
		pg->mapped = 1;
	}

	return pg->data + ofst;
}


void pop_char(char *val){

	unsigned char *ph_adrs;

	ph_adrs = get_ph_adrs(stack);

	//read value from stack pointer
	*val = *ph_adrs;

	//pdate stack pointer
	stack++;

}


void push_char(char val){

	unsigned char *ph_adrs;

	//update stack top pointer
	stack--;

	//get ph adrs of stack pointer
	ph_adrs = get_ph_adrs(stack);

	//write value
	*ph_adrs = val;
}


void pop_int(int *val){

	unsigned char *ph_adrs;
	int *iptr;

	ph_adrs = get_ph_adrs(stack);

	iptr = (int *)ph_adrs;

	//read value from stack pointer
	*val = *iptr;

	//pdate stack pointer
	stack += sizeof(int);

}

void push_int(int val){

	unsigned char *ph_adrs;

	int *iptr;

	//update stack top pointer
	stack -= sizeof(int);

	//get ph adrs of stack pointer
	ph_adrs = get_ph_adrs(stack);

	iptr = (int *)ph_adrs;

	//write value
	*iptr = val;
}


void pop_float(float *val){

	unsigned char *ph_adrs;
	float *fptr;

	ph_adrs = get_ph_adrs(stack);

	fptr = (float *)ph_adrs;

	//read value from stack pointer
	*val = *fptr;

	//pdate stack pointer
	stack += sizeof(float);

}

void push_float(float val){

	unsigned char *ph_adrs;

	float *fptr;

	//update stack top pointer
	stack -= sizeof(float);

	//get ph adrs of stack pointer
	ph_adrs = get_ph_adrs(stack);

	fptr = (float *)ph_adrs;

	//write value
	*fptr = val;
}


void pop_adrs(unsigned long *adrs){

	unsigned char *ph_adrs;
	unsigned long *ulptr;

	ph_adrs = get_ph_adrs(stack);

	ulptr = (unsigned long *)ph_adrs;

	//read value from stack pointer
	*adrs = *ulptr;

	//pdate stack pointer
	stack += sizeof(unsigned long);

}

void push_adrs(unsigned long adrs){

	unsigned char *ph_adrs;
	unsigned long *ulptr;

	//update stack top pointer
	stack -= sizeof(unsigned long);

	//get ph adrs of stack pointer
	ph_adrs = get_ph_adrs(stack);

	ulptr = (unsigned long *)ph_adrs;

	//write value
	*ulptr = adrs;
}



void pop_tip(int *tip){

	pop_int(tip);

}


void push_tip(int tip){

	push_int(tip);
}



void set_val_int(unsigned long v_adrs, int val_int){

	unsigned char *ph_adrs;
	int *ptr;

	ph_adrs = get_ph_adrs(v_adrs);
	ptr = (int *)ph_adrs;
	*ptr = val_int;

}

int get_val_int(unsigned long v_adrs){

	unsigned char *ph_adrs;
	int ival;

	ph_adrs = get_ph_adrs(v_adrs);
	ival = *(int *)ph_adrs;
	return ival;
}


float get_val_float(unsigned long v_adrs){

	unsigned char *ph_adrs;
	int ival;

	ph_adrs = get_ph_adrs(v_adrs);
	ival = *(int *)ph_adrs;
	return ival;
}


char get_val_char(unsigned long v_adrs){

	unsigned char *ph_adrs;
	int ival;

	ph_adrs = get_ph_adrs(v_adrs);
	ival = *(int *)ph_adrs;
	return ival;
}

void set_val_float(unsigned long v_adrs, float val_float){

 

}


void set_val_char(unsigned long v_adrs, char val_char){

 

}

void set_val(unsigned long adrs, int tip, union val_types val ){

	switch(tip){
		case 1: 
			set_val_int(adrs, val.int_val);
			break;
		case 2:
			set_val_float(adrs, val.float_val);
			break;
		case 3:
			set_val_char(adrs, val.char_val);
			break;
		default:
			printf("Icraci xetasi: tip desteklenmir. Zehmet olmasa proqram metnini\n");
			printf("ahmed.sadikhov@gmail.com unvanina gonderin\n");
	}
}