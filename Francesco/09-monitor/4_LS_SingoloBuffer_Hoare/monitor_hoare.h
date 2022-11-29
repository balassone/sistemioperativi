#ifndef MONITOR_HOARE_H
#define MONITOR_HOARE_H

typedef struct {
	
	int mutex;
	int urgent_sem;
	int id_shared;
	int id_conds;

	int num_var_cond;

	int* cond_counts; 
	int* urgent_count;

} Monitor;

void init_monitor(Monitor*, int);
void enter_monitor(Monitor*);
void leave_monitor(Monitor*);
void remove_monitor(Monitor*);
void wait_condition(Monitor*, int);
void signal_condition(Monitor*, int);
int queue_condition(Monitor*, int);

#endif //MONITOR_HOARE_H
