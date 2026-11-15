/*
** EPITECH PROJECT, 2024
** kk
** File description:
** jobs
*/

#include "../include/my.h"

static int grand;

//status == 0 means suspended
void add_job(pid_t pid, char *s)
{
    job_t *new_job = malloc(sizeof(job_t));

    new_job->pid = pid;
    new_job->command = my_strdup(s);
    new_job->status = 0;
    new_job->next = jobs;
    jobs = new_job;
}

static int little_if(job_t *current, job_t *prev, pid_t pid)
{
    if (current->pid == pid) {
        current->status = 1;
        kill(current->pid, SIGCONT);
        waitpid(current->pid, &shell.status1, WUNTRACED | WCONTINUED);
        shell.status = WEXITSTATUS(shell.status1);
        child_stat(shell.status1);
        if (prev == NULL) {
            jobs = current->next;
        } else {
            prev->next = current->next;
        }
        free(current);
        return 1;
    }
    return 0;
}

void fore_g(pid_t pid)
{
    job_t *current = jobs;
    job_t *prev = NULL;

    while (current != NULL) {
        if (little_if(current, prev, pid) == 1)
            return;
        prev = current;
        current = current->next;
    }
    fprintf(stderr, "fg: No current job.\n");
}

void fg_cmd(char **c)
{
    if (count_arr_size(c) > 1) {
        fprintf(stderr, "fg: No such job.\n");
        shell.status = 1;
        return;
    }
    if (jobs == NULL){
        fprintf(stderr, "fg: No current job.\n");
        shell.status = 1;
        return;
    }
    fore_g(jobs->pid);
}

static int little_if1(job_t *current, job_t *prev, pid_t pid)
{
    if (current->pid == pid) {
        current->status = 1;
        kill(current->pid, SIGCONT);
        waitpid(current->pid, &shell.status1, 0);
        if (prev == NULL)
            jobs = current->next;
        else
            prev->next = current->next;
        free(current);
        return 1;
    }
    return 0;
}

static void back_g(pid_t pid)
{
    job_t *current = jobs;
    job_t *prev = NULL;

    while (current != NULL) {
        if (little_if1(current, prev, pid) == 1)
            return;
        prev = current;
        current = current->next;
    }
    fprintf(stderr, "fg: No current job.\n");
}

void jobs_fct(job_t *current, int *i)
{
    char c = 0;

    if (current == NULL) {
        grand = *i;
        return;
    }
    (*i)++;
    jobs_fct(current->next, i);
    if (*i == grand)
        c = '+';
    if (*i == grand - 1)
        c = '-';
    if (*i < grand - 1)
        c = ' ';
    printf("[%d]  %c Suspended (signal)            %s\n",
    abs(*i - grand) + 1, c, current->command);
    (*i)--;
}

void bg_cmd(char **c)
{
    if (count_arr_size(c) > 1) {
        fprintf(stderr, "bg: No such job.\n");
        shell.status = 1;
        return;
    }
    if (jobs == NULL){
        fprintf(stderr, "bg: No current job.\n");
        shell.status = 1;
        return;
    }
    back_g(jobs->pid);
}
