#ifndef _SIMPSHELL_H_
#define _SIMPSHELL_H_

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define SYS_GETLINE 0
#define SYS_STRTOK 0

#define HISTORY_FILE ".custom_shell_history"
#define MAX_HISTORY_ENTRIES 4096

#define INPUT_BUFFER_SIZE 1024
#define OUTPUT_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

#define CONVERT_TO_LOWERCASE 1
#define CONVERT_TO_UNSIGNED 2

#define COMMAND_NORMAL 0
#define COMMAND_LOGICAL_OR 1
#define COMMAND_LOGICAL_AND 2
#define COMMAND_CHAINED 3

extern char **environ;

/**
 * Custom structure for a singly linked list
 * @number: an integer field
 * @data: a string
 * @next_node: points to the next node in the list
 */
typedef struct list_node
{
    int number;
    char *data;
    struct list_node *next_node;
} my_list;


/**
 * Custom structure to hold various shell-related information
 * @arguments: a string generated from getline containing arguments
 * @arg_values: an array of strings generated from arguments
 * @path: a string representing the current command's path
 * @argument_count: the count of arguments
 * @line_counter: the error count
 * @error_number: the error code for exit() calls
 * @linecount_flag: set to 1 to count this line of input
 * @filename: the program's filename
 * @environment_list: a linked list representing the local copy of the environment
 * @history_data: a history node
 * @alias_data: an alias node
 * @custom_environment: a modified copy of the environment from the linked list
 * @environment_changed: set to 1 if the environment was changed
 * @execution_status: the return status of the last executed command
 * @command_buffer: address of a pointer to the command buffer, used for command chaining
 * @command_buffer_type: type of command chaining (NORMAL, OR, AND)
 * @read_file_descriptor: the file descriptor from which to read line input
 * @history_count: the history line number count
 */
typedef struct my_shell
{
    char *arguments;
    char **arg_values;
    char *path;
    int argument_count;
    unsigned int line_counter;
    int error_number;
    int linecount_flag;
    char *filename;
    my_list *environment_list;
    my_list *history_data;
    my_list *alias_data;
    char **custom_environment;
    int environment_changed;
    int execution_status;
    char **command_buffer;
    int command_buffer_type;
    int read_file_descriptor;
    int history_count;
} my_gf;

#define MY_STRUCT_INITIALIZER \
{NULL, NULL, NULL, \
       	0, 0, 0, 0, \
       	NULL, NULL, NULL, NULL, NULL, \
       	0, 0, NULL, \
	0, 0, 0}

typedef struct my_builtin_cmd
{
    char *type;
    int (*function)(my_gf *);
} my_cmd;

int ssh(my_gf *, char **);
int f_builtin(my_gf *);
void f_cmd(my_gf *);
void ch_cmd(my_gf *);

int isit_cmd(my_gf *, char *);
char *dup_xter(char *, int, int);
char *f_path(my_gf *, char *, char *);

int shloop(char **);

void ePuts(char *);
int ePutchar(char);
int Putfd(char c, int fd);
int Putsfd(char *str, int fd);

int _strlen(char *);
int _strcmp(char *, char *);
char *statWith(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char **strtokk(char *, char *);
char **strtokk1(char *, char);

char *_setmem(char *, char, unsigned int);
void freee(char **);
void *_realloc(void *, unsigned int, unsigned int);
int xfree(void **);

int interack(my_gf *);
int delim_ch(char, char *);
int _isalpha(int);
int _atoi(char *);

int e_atoi(char *);
void p_error(my_gf *, char *);
int d_print(int, int);
char *conv_numb(long int, int, int);
void rm_comments(char *);

int my_exit(my_gf *);
int my_cd(my_gf *);
int my_help(my_gf *);

int my_history(my_gf *);
int my_alias(my_gf *);

ssize_t get_inp(my_gf *);
int get_lin(my_gf *, char **, size_t *);
void sigint_hand(int);

void cl_info(my_gf *);
void s_info(my_gf *, char **);
void fr_info(my_gf *, int);

char *get_env(my_gf *, const char *);
int my_env(my_gf *);
int my_setenv(my_gf *);
int my_unsetenv(my_gf *);
int envList(my_gf *);

char **getEnv(my_gf *);
int unset_env(my_gf *, char *);
int set_env(my_gf *, char *, char *);

char *ghist_file(my_gf *gfav);
int wr_hist(my_gf *gfav);
int r_hist(my_gf *gfav);
int b_hist_list(my_gf *gfav, char *buf, int linecount);
int renum_hist(my_gf *gfav);

my_list *addNode(my_list **, const char *, int);
my_list *addNode_end(my_list **, const char *, int);
size_t pr_list_ele(const my_list *);
int delnode_n(my_list **, unsigned int);
void frList(my_list **);

size_t len_list(const my_list *);
char **list_2str(my_list *);
size_t pr_list(const my_list *);
my_list *node_starts(my_list *, char *, char);
ssize_t getNode_n(my_list *, my_list *);

int isit_chain(my_gf *, char *, size_t *);
void ch_chain(my_gf *, char *, size_t *, size_t, size_t);
int rpl_alias(my_gf *);
int rpl_var(my_gf *);
int rpl_str(char **, char *);

#endif
