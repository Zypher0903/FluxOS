#include "../include/common.h"

typedef struct task {
    u32 esp;
    u32 ebp;
    u32 eip;
    struct task* next;
} task_t;

task_t* current_task = NULL;
task_t* task_queue = NULL;

void scheduler_tick(void) {
    if (!current_task) return;

    task_t* next = current_task->next;
    if (!next) next = task_queue;

    asm volatile(
        "pushl %%eax\n"
        "pushl %%ebx\n"
        "pushl %%ecx\n"
        "pushl %%edx\n"
        "movl %%esp, %0\n"
        "movl %2, %%esp\n"
        "popl %%edx\n"
        "popl %%ecx\n"
        "popl %%ebx\n"
        "popl %%eax\n"
        : "=m"(current_task->esp) : "m"(next->esp) : "memory"
    );

    current_task = next;
}
