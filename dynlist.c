/**
* CrazedoutSoft (c) 2024
* info@crazedout.com
* Fredrik Roos
* License: GPL
*/
#include "dynlist.h"

char** dyn_list_to_array(DLIST* root, char** array){

  unsigned int n = 0;
  dyn_list* ptr = root;
  while(ptr->next!=NULL){
   ptr=ptr->next;
   array[n] = malloc(ptr->dlen);
   memcpy(array[n], ptr->data, ptr->dlen);
   n++;
  }
  return array;
}

DNODE* dyn_list_get(DLIST* root, unsigned int index){

	dyn_list* ptr = root;
	unsigned int n = 0;
	while(ptr->next!=NULL){
	  ptr=ptr->next;
	  if(n++==index) return ptr;
	}
	return ptr;
}


DNODE* dyn_list_remove(DLIST* root, unsigned int index){

	dyn_list* ptr = root;
	dyn_list* tmp;
	dyn_list* rem = NULL;
	int i = 0;
	while(ptr->next!=NULL){
	  tmp = ptr;
	  ptr = ptr->next;
	  if(i==index){
	    tmp->next = ptr->next;
	    tmp->prev = ptr->prev;
	    rem=ptr;
	    break;
	  }
	  i++;
	}
	root->lsize--;
	return rem;
}

void dyn_list_delete(DLIST* root, unsigned int index){

	dyn_list* ptr = root;
	dyn_list* tmp;
	int i = 0;
	while(ptr->next!=NULL){
	  tmp = ptr;
	  ptr = ptr->next;
	  if(i==index){
	    tmp->next = ptr->next;
	    tmp->prev = ptr->prev;
	    free(ptr->data);
	    free(ptr);
	    break;
	  }
	  i++;
	}
	root->lsize--;
}

unsigned int dyn_list_free(DLIST* root){

	dyn_list* ptr = root->next;
	dyn_list* tmp;
	int i = 0;
	if(ptr==NULL) return 0;
	while(ptr->next!=NULL){
          tmp = ptr->next;
	  free(ptr->data);
	  free(ptr);
	  i++;
	  ptr=tmp;
	}
	free(ptr->data);
	free(ptr);
	dyn_list_init(root);

 return i+1;
}

void dyn_list_clear(DLIST* root){

  dyn_list_free(root);
  dyn_list_init(root);

}

DNODE* dyn_list_insert_node(DLIST* root, DNODE* node, unsigned int index){

	dyn_list* ptr = root;
	dyn_list* tmp = NULL;
	int n = 0;

	if(node==NULL) return NULL;

	while(ptr->next!=NULL){
	  if(n==index){
	    tmp = ptr->next;
	    break;
	  }
	  ptr=ptr->next;
	  n++;
	}
	ptr->next=node;
	node->next=tmp;
	node->prev=ptr;
	root->lsize++;
	return node;
}

DNODE* dyn_list_insert(DLIST* root, void* data, unsigned int len, unsigned int index){

	dyn_list* node = (dyn_list*)malloc(sizeof(dyn_list));
	if(node==NULL) return NULL;
	node->data = malloc(len);
	node->next = NULL;
	node->prev = NULL;
	node->dlen = len;
	memcpy(node->data, data, len);
	return dyn_list_insert_node(root,node,index);
}

DNODE* dyn_list_add_node(DLIST* root, DNODE* node){

	if(node==NULL) return NULL;

	dyn_list* ptr = root;
	while(ptr->next!=NULL){
	  ptr=ptr->next;
	}
	ptr->next = node;
	node->prev=ptr;
	root->lsize++;
	return node;

}

DNODE* dyn_list_add(DLIST* root, void* data, unsigned int len){

	dyn_list* node = (dyn_list*)malloc(sizeof(dyn_list));
	node->data = malloc(len);
	node->next = NULL;
	node->prev = NULL;
	node->dlen = len;
	memcpy(node->data, data, len);
	return dyn_list_add_node(root,node);
}

DLIST* dyn_list_sublist(DLIST* root, unsigned int offset, int length){

	int n = 0;
	dyn_list* ptr = root;
	dyn_list* sub = (DLIST*)malloc(sizeof(DLIST));
        dyn_list* node;
	dyn_list_init(sub);
	while(ptr->next!=NULL){
	  ptr=ptr->next;
	  if(n>=offset && n<=offset+length){
	    node = (DNODE*)malloc(sizeof(DNODE));
	    node->next=NULL;
 	    node->prev=NULL;
	    node->data = malloc(ptr->dlen);
	    memcpy(node->data, ptr->data, ptr->dlen);
	    dyn_list_add_node(sub,node);
	  }
 	  n++;
	}
        return sub;
}

DNODE* dyn_list_compare(DLIST* root, int (*compfunc)(DNODE* node, void* comp, unsigned int clen),
			   void* comp, unsigned int clen, unsigned int* index){

        dyn_list* ptr = root;
        unsigned int n = 0;
        while(ptr->next!=NULL){
          ptr=ptr->next;
          if(compfunc(ptr,comp,clen)==0) {
	   memcpy(index,&n,sizeof(unsigned int));
	   return ptr;
	  }
          n++;
        }
	return NULL;
}

void dyn_list_list(DLIST* root, void (*listfunc)(DNODE* node)){
	return dyn_list_list_off(root, listfunc, -1, 0);
}

void dyn_list_list_off(DLIST* root, void (*listfunc)(DNODE* node),
 				unsigned int offset, unsigned int length){
	dyn_list* ptr = root;
        int n = 0;
	while(ptr->next!=NULL){
	  ptr=ptr->next;
          if((n>=offset && n<=offset+length) || offset==-1){
	    listfunc(ptr);
	  }
	  n++;
	}
}

unsigned int dyn_list_size(const DLIST* root){

	const dyn_list* ptr = root;
	int n = 0;
	while(ptr->next!=NULL){
	  ptr = ptr->next;
	  n++;
	}
	return n;
}

DLIST* dyn_list_init(DLIST* root){

  memset(root,0,sizeof(dyn_list));
  root->next = NULL;
  root->prev = NULL;
  root->data = (char*)malloc(6);
  root->dlen = 6;
  root->lsize = 0;
  memcpy(root->data, DR_TXT, strlen(DR_TXT));

  return root;
}

