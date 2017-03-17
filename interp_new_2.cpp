/* GPL  V.3  
  Esrin Interpretator Main Module
  Ahmed Sadikhov, ahmed.sadikhov@gmail.com
*/

#include "esrin.h"
#include "mm.h"
#include "standart.h"


struct band_list_el  exec_band[BAND_SIZE] ;
 
int band_size, prg_start, prg_exit;


/* input bufer, input bufer pointer  */
char ib[MAX_INB_LEN], *ibp;

void flush_input_bufer(){

  memset(ib, '\0', MAX_INB_LEN);
  ibp = ib;

}
/*

	char x,y;
	int q,h;
	float s,f;

	push_char('A');
	push_char('b');
	pop_char(&x);
	pop_char(&y);


	printf("val of x = %c\n", x);
	printf("val of y = %c\n", y);


	push_int(17);
	pop_int(&q);

	printf("val of q = %d\n", q);

	q++;

	push_int(q);
	pop_int(&h);


	printf("val of h = %d\n", h);

	push_float(9.45);
	pop_float(&s);

	printf("val of s = %f\n", s);

	s = s/2;

	push_float(s);
	pop_float(&f);


	printf("val of f = %f\n", f);

*/

void print_exec_band(struct band_list_el band[], int size){

  int i;

  for (i=0; i<size; ++i){
    printf("hpos -> %d\t",i);
    print_tok(band[i].id);
    printf("\t");
    print_tok(band[i].band_id);
	printf("\thpos = %d lgm %d tok %s   ofst %d std_func_id %d", band[i].head_pos, band[i].lgm, band[i].tok, band[i].ofst, band[i].std_func_id);
    if (band[i].band_id == FUNK || band[i].band_id == FCALL1 || \
	band[i].band_id == SNMEM)
      printf("%s sntip %d  fid  %d  dt_size %d\n ", band[i].tok, band[i].sntip, band[i].fid, band[i].dt_size);
    else{
      if (band[i].band_id == GLBMT)
	printf(" dt_size  %d", band[i].dt_size);
      printf("\n");
    }
  }
}


int exec_idt_adrs(struct band_list_el *bll){

	unsigned long v_adrs;
	int tip;

	v_adrs = stack_base - bll->ofst;
	tip = bll->tip;		

	push_adrs(v_adrs);
	push_tip(tip);

	return 0;

}


int exec_idt_val(struct band_list_el *bll){

	unsigned long v_adrs;
	int tip, ival;
	float fval;
	char cval;

	v_adrs = stack_base - bll->ofst;
	tip = bll->tip;		

	switch(tip){
		case 1:
			ival = get_val_int(v_adrs);
			push_int(ival);
			break;
		case 2:
			fval = get_val_float(v_adrs);
			push_float(fval);
			break;
		case 3:
			cval = get_val_char(v_adrs);
			push_char(cval);
			break;	
	}

	return 0;
}


int exec_numb(struct band_list_el *bll){

   //deprecated
  //int i;

  //deprecated
  //i = (int)atoi(bll->tok);
  push_int(bll->int_val);

  return 0;
}

int exec_yaz_std(struct band_list_el *bll){

   int int_val;

   pop_int(&int_val);

   printf("%d",int_val);
   
   return 0;
}

int exec_std_fcall1(struct band_list_el *bll){

  int i;

  switch(bll->std_func_id){

	  case STD_YAZ:
		  exec_yaz_std(bll);
		  return 0;
	  case STD_OXU:
		  printf("oxu func executed\n");
		  return 0;
	  case STD_KVK:
		  printf("kvk func executed\n");
		  return 0;
 
  }

  return 0;
}

int exec_fcall1(struct band_list_el *bll){

  int i;

  if (bll->std_func_id != 0)
	 return exec_std_fcall1(bll);

  printf("Non standart function\n");

  return 0;
}

int exec_asgn(struct band_list_el *bll){

	unsigned long adrs;
	int tip, int_val;
	float float_val;
	char char_val;

	pop_tip(&tip);
	pop_adrs(&adrs);

	//tip = bll->tip;

	switch(tip){
		case 1:
			pop_int(&int_val);
			set_val_int(adrs, int_val);
			break;
		case 2:
			pop_float(&float_val);
			set_val_float(adrs, float_val);
			break;
		case 3:
			pop_char(&char_val);
			set_val_char(adrs, char_val);
			break;	
	}

	return 0;
}

/* bll->band_id == PUT_RET_ADDR  
   put return addres to stek
   ret addr in bll->head_pos
 */
int exec_put_ret_addr( struct band_list_el *bll){

	//ret addr is save in int head_pos field
	push_int(bll->head_pos);

    return 0;
}


/* bll-id == QAYTYAR1  */
int exec_qaytar1(struct band_list_el *bll){

	int int_val;

	pop_int(&int_val);

	return int_val;
}

int exec_func( struct band_list_el *bll){

	printf("Entering to Funk\n");

    return 0;
}

int exec_son(struct band_list_el *bll){

	char ch;
	ch = getchar();
	exit(0);

  //we never reah here, just to make compiler happy
  return 1;
}

// get address of variable (aha funks parametr)
// get value from stack and assign to variable
int exec_fparm_idt_val(struct band_list_el *bll){
  
	unsigned long addrs;
	int int_val;

	pop_int(&int_val);
	addrs = stack_base - bll->ofst;

	set_val_int(addrs, int_val);

	return 0;
}

/* bll and parent bll  */
int pre_exec_new(struct band_list_el *head){

  struct band_list_el *bll = head;

  int id = bll->band_id;

  switch(id){

	case IDT_ADRS:
		return exec_idt_adrs(bll);
	case IDT_VAL:
		return exec_idt_val(bll);
	case NUMB:
		return exec_numb(bll);
	case ASGN:
		return exec_asgn(bll);
	case FCALL1:
		return exec_fcall1(bll);
	case FUNK:
			return exec_func(bll);
	case SON:
		return exec_son(bll);
	case FPARM_IDT_VAL:
		return exec_fparm_idt_val(bll);
	default:
		return 0;
}

}



int main (){

	struct band_list_el *head;
	int pos;
	
  /* clear input bufer */
  flush_input_bufer();

  load_bin("prg.esr_bin", exec_band, &band_size);
 
  print_exec_band(exec_band, band_size);

  head = exec_band;

 begin:
 loop:

  pos = pre_exec_new(head);

  if (pos)
    head = exec_band + pos;
  else
    head++;

  if (head >= exec_band + band_size)
    goto exit; /* end of program, exit  */

  goto loop;

 exit:
    exit(0);

}