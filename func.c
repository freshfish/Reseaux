#include "defs.h"

/**************************************************************************/
/* Usefull functions */

//Get text from standart input and put it in <dst> with a max size of <sz> characters
//Parameter <mess> allow to display a message
void get_text_from_stdin(char *dst, int sz, char *mess) {
  int len = 1;
  char *result, *lc;
  while(len < 2) {
    if(mess != NULL) printf("%s", mess);
    result = fgets(dst, sz, stdin);
    len = strlen(dst);
    if(len < 2) printf("Erreur : le champ est vide, merci de le compléter à nouveau\n");
    else {
      FLUSH_STDIN(dst);
      if (result != NULL) {
	lc = strchr(dst, '\n');
	if (lc != NULL) *lc = '\0'; 
      }
    }
  }
}

//Get the <field> field from the <a> string formatted with the <del> delimiter and puts it in <dst>
void get_field_by_number(char *a, char *dst, int field, char del) {
  char *t = a-1, *c = a; int i = 0;
  while (i <= field && t != NULL) {
    c = t+1;
    t = strchr(t+1,del);
    i++;
  }
  if(i!=field+1) {
    printf("Erreur dans la fonction get_field_by_number, le champ %i n'existe pas dans la chaîne :\n%s\n", field, a);
    exit(0);
  }
  if(!t){
    memcpy(dst, c, &a[strlen(a)]-c);
    dst[&a[strlen(a)]-c] = '\0';
  }
  else {
    memcpy(dst, c, t-c);
    dst[t-c] = '\0';
  }
}

//Display the <deb> fields (and following) of the <str> string formatted with the <del> delimiter
void display_formatted_string(char *str, char del, int deb) {
  char *t = str-1, *c = str, dst[15]; int i = deb;
  c = t+1;
  t = strchr(t+1,del);
  while (t != NULL) {
    c = t+1;
    t = strchr(t+1,del);
    if(!t && i!=1){
      memcpy(dst, c, &str[strlen(str)]-c);
      dst[&str[strlen(str)]-c] = '\0';
    }
    else {
      memcpy(dst, c, t-c);
      dst[t-c] = '\0';
    }
    printf("%i %s\n", i, dst);
    i++;
  }
}

/**************************************************************************/
/* Mail functions */
void get_mail(mail_t *m, const char *nickname) {
  get_text_from_stdin(m->dst_nick, NICKLEN, "Entrer le destinataire :\n");
  get_text_from_stdin(m->object,   OBJLEN,  "Entrer l'objet du mail :\n");
  get_text_from_stdin(m->message,  MESLEN,  "Entrer le message :\n");
  struct tm tim;
  time_t now = time(NULL);
  tim = *(localtime(&now));
  strftime(m->date,30,"%b %d, %Y; %H:%M:%S\n",&tim);
  char *lc = strchr(m->date, '\n');
  if (lc != NULL) *lc = '\0';
  strcpy(m->src_nick, nickname);
}

void print_mail(const mail_t *m) {
  printf("De : %s\n", m->src_nick);
  printf("A  : %s\n", m->dst_nick);
  printf("Date : %s\n", m->date);
  printf("Objet : %s\n", m->object);
  printf("Message : \n%s\n", m->message);
}

void mail_to_str(const mail_t *m, char *s) {sprintf(s,"mail|%s|%s|%s|%s|%s", m->dst_nick, m->src_nick, m->date, m->object, m->message);}


void str_to_mail(char *s, mail_t *m) {
  get_field_by_number(s,m->dst_nick,1,'|');
  get_field_by_number(s,m->src_nick,2,'|');
  get_field_by_number(s,m->date,3,'|');
  get_field_by_number(s,m->object,4,'|');
  get_field_by_number(s,m->message,5,'|');
}

/**************************************************************************/
/* List functions */
list* create_list() {return NULL;}

int is_empty(const list *l) {return (l == NULL);}

list* append_top(list *l, void *data) {
  list *n = (list*) malloc(sizeof(list));
  n->data = data;
  n->next = l;
  return n;
}

list* append_end(list *l, void *data) {
  if(l == NULL) {
    l = (list*) malloc(sizeof(list));
    l->next = NULL;
    l->data = data;
  }
  else {
    list *n = l;
    while(n->next != NULL) n = n->next;
    n->next = (list*) malloc(sizeof(list));
    n->next->next = NULL;
    n->next->data = data;
  }
  return l;
}

void clear(list *l) {
  if(l->next != NULL) clear(l->next);
  if(l->data != NULL) free(l->data);
  free(l);
}
