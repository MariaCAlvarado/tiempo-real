#include <stdio.h>
#include <signal.h>
#include <unistd.h>


#include <alchemy/task.h>
#include <alchemy/timer.h>
#include <alchemy/sem.h>

#define ITER 100000

static RT_TASK tarea1;
static RT_TASK tarea2;

int global = 0;

void tareaUno(void *arg){
    int i;
	rt_sem_p(&sem, TM_INFINITE);
    for(i=0; i < ITER; i++){
        printf("Tarea 1 la variable global es %d -----\n", ++global);
		rt_sem_v(&sem);
    }
}

void tareaDos(void *arg){
    int i;
	rt_sem_p(&sem, TM_INFINITE);
    for(i=0; i < ITER; i++){
        printf("Tarea 2 la variable global es %d -----\n", --global);
		rt_sem_v(&sem);
    }
}

int main(int argc, char* argv[]){
	rt_sem_create(&sem, "sem", 1, S_FIFO);
    rt_task_create(&tarea1, "tarea 1", 0 , 1, 0);
    rt_task_create(&tarea2, "tarea 2", 0 , 1, 0);
    rt_task_start(&tarea1, &tareaUno,0);
    rt_task_start(&tarea2, &tareaDos,0);
    return 0;
}