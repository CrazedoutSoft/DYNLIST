/**
* CrazedoutSoft (c) 2024
* info@crazedout.com
* Fredrik Roos
* License: GPL
*/
#ifndef _DYN_LIST_CRZ
#define _DYN_LIST_CRZ

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* dyn_list_struct */
typedef struct dyn_list_t {
    struct dyn_list_t *next;
    struct dyn_list_t *prev;
    void*  data;
    unsigned int dlen;
    unsigned int lsize;
} dyn_list;

#define DR_TXT "DLROOT\0"

/* DLIST and DNODE are of course the same struct. */
/* DLIST should be used when beeing ROOT of list */
/* DNODE when beeing a child of DLIST */
typedef dyn_list DLIST;
typedef dyn_list DNODE;

/* Define function-ptr for dyn_list_list() */
void (*listfunc)(dyn_list* node);

#define DLIST_LIST void (*listfunc)(dyn_list* node)

/* Define function ptr for dyn_list_compare */
int (*compfunc)(dyn_list* node, void* comp, unsigned int clen);

#define DLIST_COMPARE void (*compfunc)(dyn_list* node)

/* Init list */
dyn_list* 	dyn_list_init(dyn_list* list);

/* Clear list (Not root) */
void 		dyn_list_clear(dyn_list* list);

/* Send each node to 'compare' with comp and clen, if compare return 0 current node is returned. index is set to nodes index.*/
/* if compare never returns 0. NULL is returned and index is not tuched. */
dyn_list*	dyn_list_compare(dyn_list* list, int (*compfunc)(dyn_list* node, void* comp, unsigned int clen),
			void* comp, unsigned int clen, unsigned int* index);

/* Get node at index. if index>size-1 last node is returned. */
dyn_list* dyn_list_get(dyn_list* list, unsigned int index);

/*Add node to the end of list */
/* Return node added. */
dyn_list* 	dyn_list_add(dyn_list* list, void* data, unsigned int len);

/*Add node to the end of list */
/* Return node added. */
dyn_list* 	dyn_list_add_node(dyn_list* list, dyn_list* node);

/* Remove and free node at index */
void	 	dyn_list_delete(dyn_list* list, unsigned int index);

/* Remove and return node from list at index */
/* Does NOT free node */
dyn_list*	 dyn_list_remove(dyn_list* list, unsigned int index);

/* Create and insert node at index*/
/* Return created node */
dyn_list* 	dyn_list_insert(dyn_list* list, void* data, unsigned int len, unsigned int index);

/* Insert node at index*/
/* Return node */
dyn_list* 	dyn_list_insert_node(dyn_list* list, dyn_list* node, unsigned int index);

/* Send each dyn_list node to function ptr 'listfunc' */
/* List begins att list->next */
/* Return ptr to 'list' */
void	 	dyn_list_list(dyn_list* list, void (*listfunc)(dyn_list* node));

/* Create a new sublist from offset to offset+length */
/* Orig node data is copied and needs to be freed seperatly */
dyn_list* 	dyn_list_sublist(DLIST* root, unsigned int offset, int length);

/* Send each dyn_list node to function ptr 'listfunc' */
/* List begins att list->next */
/* Return ptr to 'list' */
void	 	dyn_list_list_off(dyn_list* list, void (*listfunc)(dyn_list* node),
			unsigned int offset, unsigned int length);

/* size of list*/
unsigned int 	dyn_list_size(const dyn_list* list);

/* Copy data of each node to static array */
char** dyn_list_to_array(DLIST* root, char** array);

/* Frees children but root */
/* Return nr nodes freed   */
unsigned int 	dyn_list_free(dyn_list* list);

#endif
