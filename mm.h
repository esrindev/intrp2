#ifndef MM
#define MM


extern unsigned long stack ;
extern unsigned long stack_base ;

extern void pop_char(char *val);
extern void push_char(char val);
extern void pop_int(int *val);
extern void push_int(int val);
extern void pop_float(float *val);
extern void push_float(float val);
extern void pop_adrs(unsigned long *adrs);
extern void push_adrs(unsigned long adrs);
extern void pop_tip(int *tip);
extern void push_tip(int tip);
extern void set_val_int(unsigned long v_adrs, int val_int);
extern void set_val_float(unsigned long v_adrs, float val_float);
extern void set_val_char(unsigned long v_adrs, char val_char);
extern int	get_val_int(unsigned long v_adrs);
extern float get_val_float(unsigned long v_adrs);
extern char	get_val_char(unsigned long v_adrs);

#endif