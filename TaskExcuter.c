#include <stdio.h>

#define max_tasks 16

typedef struct {
    unsigned int end_time;
    void (*fun_ptr)();
} task;

task tasks[max_tasks];
int current_task_count = 0;


void schule(void (*fun_ptr)(), unsigned int delay) {
    if (current_task_count > max_tasks) {
        printf("max task count reached");
        return;
    }

    tasks[current_task_count].fun_ptr = fun_ptr;
    tasks[current_task_count].end_time = HAL_GetTick() + delay;
    current_task_count++;

}

void schule_check() { //run in main loop

    for (int i = 0; i < current_task_count; i++) {
        if (HAL_GetTick() > tasks[i].end_time) {

            (tasks[i].fun_ptr)();

            /* Copy next element value to current element */
            for (int j = i; j < current_task_count - 1; j++)
            {
                tasks[j] = tasks[j + 1];
            }
            current_task_count--;
        }
    }
}
