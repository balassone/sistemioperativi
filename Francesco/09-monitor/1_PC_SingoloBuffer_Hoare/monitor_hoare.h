typedef struct{
	int mutex; //id mutex
	int urgent_sem; //id urgent
	int num_var_cond; //int numsemafori
	int id_cons; //id condition
	int id_shared; //id shm
	int* cond_counts; //numero di processi in attesa della condizione i
	int* urgent_count; //numero di processi in attesa su urgent
} Monitor;

void init_monitor (Monitor*, int);
void enter_monitor (Monitor*);
void leave_monitor (Monitor*);
void remove_monitor (Monitor*);
void wait_condition(Monitor*, int);
void signal_condition(Monitor*, int);
int queue_condition(Monitor*, int);
