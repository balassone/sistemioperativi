#ifndef MONITOR_SIGNAL_CONTINUE_H
#define MONITOR_SIGNAL_CONTINUE_H

typedef struct{
	int mutex;
	int id_shared;
	int id_conds;

	int num_var_cond;

	int* cond_counts;
} Monitor;

void init_monitor(Monitor*, int);
void enter_monitor(Monitor*);
void leave_monitor(Monitor*);
void remove_monitor(Monitor*);
void wait_condition(Monitor*, int);
void signal_condition(Monitor*, int);
int queue_condition(Monitor*, int);

#endif //MONITOR_SIGNAL_CONTINUE_H
