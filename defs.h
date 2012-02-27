#ifndef DEFS_H_
#define DEFS_H_

/* Declares and defines includes, structures and functions for both client and server programs */

/* Include */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/select.h> 
#include <unistd.h>

/* Macros */
#define FLUSH_STDIN(x) {if(x[strlen(x)-1]!='\n'){do fgets(Junk,16,stdin);while(Junk[strlen(Junk)-1]!='\n');}else x[strlen(x)-1]='\0';}
char Junk[16];

#define NICKLEN 15
#define OBJLEN 40
#define MESLEN 256

/* Mail structure */
typedef struct {
  char dst_nick[NICKLEN];
  char src_nick[NICKLEN];
  char object[OBJLEN];
  char message[MESLEN];
  char date[30];
  int  read;
} mail_t;

/* List structure */
typedef struct list list;
struct list {
  void *data;
  list *next;
};

/* Declarations of functions */
void get_mail(mail_t *m, const char *nickname);
void print_mail(const mail_t *m);
void mail_to_str(const mail_t *m, char *s);
void str_to_mail(char *s, mail_t *m);

void get_text_from_stdin(char *dst, int sz, char *mess);
void get_field_by_number(char*, char*, int, char);
void display_formatted_string(char *str, char del, int deb);

list* create_list();
int is_empty(const list *l);
list* append_top(list *l, void *data);
list* append_end(list *l, void *data);
void clear(list *l);

#endif //DEFS_H_
