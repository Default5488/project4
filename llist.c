#include <stdio.h>
#include <stdlib.h>
#include "list.h"
/**
* See list.h for expected behavior of functions
**/

typedef struct node {
    ElemType val;
    struct node *next;
} NODE;


struct list_struct {
    NODE *front;
    NODE *back;
};


/*
* returns pointer to newly created empty list
*/
LIST *lst_create() {
LIST *l = malloc(sizeof(LIST));

  l->front = NULL;
  l->back = NULL;
  return l;
}

void lst_free(LIST *l) 
{
NODE *p = l->front;
NODE *pnext;

  while(p != NULL) {
    pnext = p->next;   // keeps us from de-referencing a freed ptr
    free(p);
    p = pnext;
  }
  // now free the LIST 
  free(l);
}


void lst_print(LIST *l) {
NODE *p = l->front;

  printf("[");
  while(p != NULL) {
    printf(FORMAT, p->val);
    p = p->next;
  }
  printf("]\n");
}

/**
* !Done, Needs testing
* TODO: .:.
*   function:  lst_are_equal
*   description:  returns true(1) if lst1 and lst2
*      contain exactly the same sequenc of values.
*      Returns 0 otherwise.
**/
int lst_are_equal(LIST *lst1, LIST *lst2) 
{
  NODE *p1;
  NODE *p2;
  p1 = lst1->front;
  p2 = lst2->front;

  while((p1->next != NULL) && (p2->next != NULL))
  {
    if(p1->val != p2->val)//Checks for invalid comparision
      return 0;//If values don't equal, returns 0
  } 

  if((p1->next == NULL ) || (p2->next == NULL))//If one or the other is null, not equal val
    return 0;
  return 1;//All checks passed, strings are even
}

/**
 * Runs until reaching head at NULL, when null, returns backwards reversing the list
 **/
NODE *recrusiveReverseList(NODE *p)//! Do we pass NODE or LIST?
{
  if(p==NULL) return NULL;
  if(p->next==NULL) return p;//One size node
  NODE *tmp = recrusiveReverseList(p->next);//*Stores values in reverse order
  printf("Looped\n");
  tmp->next->next = p;
  p->next = NULL;//First is now last
  return tmp;
}


/**
* TODO: !Testing!
* TODO: Logic is to start at front of list, use recursion to walk to end and print in reverse
* 
* Try to do without looking at notes!
* Hints:  recursive helper function
*/
void lst_print_rev(LIST *l) //! Probably needs filter, to verify none NULL ptr sending/returned
{
  NODE *p = l->front;
  // NODE *tmp = NULL;

  printf("\n\n***Before reverse print**\n");
  lst_print(l);
  printf("\n***Reverse***");
  recrusiveReverseList(p);
}


void lst_push_front(LIST *l, ElemType val) {
NODE *p = malloc(sizeof(NODE));

  p->val = val;
  p->next = l->front;
  
  l->front = p;
  if(l->back == NULL)   // was empty, now one elem
      l->back = p;
}

void lst_push_back(LIST *l, ElemType val) {
NODE *p;

  if(l->back == NULL)   // list empty - same as push_front
	lst_push_front(l, val);
  else {  // at least one element before push
	p = malloc(sizeof(NODE));
	p->val = val;
	p->next = NULL;
	l->back->next = p;

	l->back = p;  
  }
}

/** 
* !Done needs testing
*   TODO: Testing
*   modifications to enable this operation
*   to execute in O(1) time.  (You will almost
*   certainly modify other functions and the 
*   data structure itself -- see header).
**/
int lst_length(LIST *l) {
NODE *p = l->front;
int n=0;

  while(p != NULL) {
    n++;
    p = p->next;
  }
  return n;
}

int lst_is_empty(LIST *l) {
  return l->front == NULL;
}


/** 
* !Done needs testing
*  TODO: Test functionality of implementation
*
*    function:  lst_count
*     description:  Counts number of occurrences 
*     		of x in the list and returns 
*     		that value.
*/
int lst_count(LIST *l, ElemType x) 
{
  int occurrence = 0;
  NODE *p;
  p = l->front;

  while(p->next != NULL)//* Or while(p)
  {
    if(p->val == x)
    {
      occurrence++;
      p = p->next;
    }else{
      p = p->next;
    }
  }
  return occurrence; 
}




/* These are "sanity checker" functions that check to see
*     list invariants hold or not.
*/
int lst_sanity1(LIST *l) {
  if(l->front == NULL && l->back != NULL){
	fprintf(stderr, "lst_sanity1 error:  front NULL but back non-NULL\n");
	return 0;
  }
  if(l->back == NULL && l->front != NULL){
	fprintf(stderr, "lst_sanity1 error:  back NULL but front non-NULL\n");
	return 0;
  }
  return 1;
}

int lst_sanity2(LIST *l) {
  if(l->back != NULL && l->back->next != NULL) {
	fprintf(stderr, "lst_sanity2 error:  back elem has a non-NULL next?\n");
	return 0;
  }
  return 1;
}

/**
* ?TODO: Is this a need todo function?
* function:  find_back()
* description:  returns a pointer to the last
*               node of the given list.
*		Note that we are operating at
*		the "node level".
*
*		if p is NULL, NULL is returned.
*
* purpose:  mostly for debugging -- enables sanity3
*/
static NODE * find_back(NODE *p) {

  if(p ==  NULL)
	return NULL;

  while(p->next != NULL) {
	p = p->next;
  }
  return p;
}

/*
*   makes sure that the back pointer is also the last reachable
*    node when you start walking from front.
*    HINT:  use pointer comparison
*/
int lst_sanity3(LIST *l) {
NODE *real_back;

  real_back = find_back(l->front);

  return (real_back == l->back);
}



ElemType lst_pop_front(LIST *l) {
ElemType ret;
NODE *p;
 

  if(lst_is_empty(l))
	return DEFAULT;   // no-op

  ret = l->front->val;
  
  if(l->front == l->back) {  // one element
	free(l->front);
	l->front = NULL;
	l->back = NULL;
  }
  else {
	p = l->front;  // don't lose node being deleted
	l->front = l->front->next;  // hop over
	free(p);
  }
  return ret;
}

     
  


/**
*    TODO: Testing Needed
*   !Needs testing
*    if list is empty, we do nothing and return arbitrary value
*    otherwise, the last element in the list is removed and its
*      value is returned.
*
*/
ElemType lst_pop_back(LIST *l) {
  NODE* tmp = l->front;//Points to front of list
  NODE* prev  = NULL;
  // int pos;//Pos of linked list
  
  if(tmp == NULL){
    l->front = tmp->next;//Changes head to next position
    free(l->front);//Frees head
  }

  while(tmp->next != NULL){
    prev = tmp;//Last point before removal
    tmp = tmp->next;
  }

  prev->next = tmp->next;//Removes current tmp
  free(tmp);//Frees current tmp
  return DEFAULT;
} 


/**
*  TODO: Testing
*  !Testing
*  For full credit, you cannot allocate any new memory!
* *Recursive helper function to reverse the order of the LL
*  description:  self-evident 
*/
void lst_reverse(LIST *l) {
  NODE *prev = NULL;
  NODE *curr = l->front;
  NODE *next = NULL;

  while(curr != NULL){
    next = curr->next;//Stores next value
    curr->next = prev;
    prev = curr;
    curr = next;
  }
}


/*
* removes first occurrence of x (if any).  Returns
*   0 or 1 depending on whether x was found
*/
int lst_remove_first(LIST *l, ElemType x) {
NODE *p;
NODE *tmp;

  if(l->front == NULL) return 0;
  if(l->front->val == x) {
	lst_pop_front(l);
	return 1;
  }
  // lst non-empty; no match on 1st elem
  p = l->front;

  while(p->next != NULL) {
     if(x == p->next->val) {
	tmp = p->next;
	p->next = tmp->next;
	if(tmp == l->back) 
	    l->back = p;
	free(tmp);
	return 1;
     }
     p = p->next;
  }
  return 0;
}


/**
* TODO: Not Listed
* function: lst_remove_all_slow
* description:  removes all occurrences of x
*   from given list (if any).
*   Returns number of occurrences (i.e., deletions).
* 
* notes:  it is called "slow" because in the worst
*   case, it takes quadratic time.
*   (Discussion of why and when this happens is a
*   lecture topic).
*/
int lst_remove_all_slow(LIST *l, ElemType x) {
int n=0;
  while(lst_remove_first(l, x))
	n++;
  return n;
}

/** 
 * TODO: Not Listed
 * function: lst_sra_bad_case (sra:  slow_remove_all)
 *
 * description: constructs a list of length n such that 
 * the above function takes quadratic time to remove
 * all occurrences of a specified value. 
 *
 * By convention, the specified value will be 0
 */
LIST *lst_sra_bad_case(int n) {
LIST *l = lst_create();
int i;
int k=n/2;

  for(i=0; i<k; i++) {
	lst_push_front(l, 0);
  }
  for(i=0; i<n-k; i++) {
	lst_push_front(l, 1);
  }
  return l;
}

/** 
* TODO: Not Listed
*   function:  lst_remove_all_fast
*   description:  same behavior/semantics as
*      lst_remove_all_slow.  However, this function
*      must guarantee linear time worst case 
*      runtime (hence, "fast").
*
*   REQUIREMENT:  linear worst-case runtime.
*
*   Note:  your solution may be either recursive or 
*   iteratieve.
**/
int lst_remove_all_fast(LIST *l, ElemType x) {
  return 0;
}


int lst_is_sorted(LIST *l){
NODE *p = l->front;

  while(p!=NULL && p->next != NULL) {//? Might only need p->Next != NULL
	if(p->val > p->next->val)
	  return 0;
	p = p->next;
  }
  return 1;
}


/** 
* TODO: .:. Testing needed
* function:  lst_insert_sorted
*
* description:  assumes given list is already in sorted order
*	   and inserts x into the appropriate position
* 	   retaining sorted-ness.
* Note 1:  duplicates are allowed.
*
* Note 2:  if given list not sorted, behavior is undefined/implementation
* 		dependent.  We blame the caller.
* 		So... you don't need to check ahead of time if it is sorted.
*/
void lst_insert_sorted(LIST *l, ElemType x) {
    NODE *curr = l->front;
    NODE *prev = NULL;
    NODE *newNode = (NODE*)malloc(sizeof(NODE*));

    if(curr == NULL)
      return;//! ? Return Type?
    else{
      prev = curr;
      while(curr != NULL){
        if((x >= curr->val) && (x <= curr->next->val)){//Compares x value, in bounds !Needs
          newNode->val = x;
          newNode->next = curr->next;
          prev->next = newNode;
          curr = curr->next;
        }else{
          curr = curr->next;
        }
      }
    }
}

/** 
* TODO: Testing
 * function:  lst_merge_sorted
 *
 * description:  assumes both list a and b are in
 * 	sorted (non-descending) order and merges them
 * 	into a single sorted list with the same
 * 	elements.  
 *
 * 	This single sorted list is stored in a while
 * 	b becomes empty.
 *
 * 	if either of given lists are not sorted, 
 * 	we blame the caller and the behavior is
 * 	implementation dependent -- i.e., don't worry
 * 	about it!
 *
 * 	Example:
 *
 * 		a:  [2 3 4 9 10 30]
 * 		b:  [5 8 8 11 20 40]
 *
 * 		after call on (a,b)
 *
 * 		a:  [2 3 4 5 8 8 9 10 11 20 30 40]
 * 		b:  []
 * 
 * implementation:  should not allocate ANY new list
 * 	nodes -- it should just re-link existing
 * 	nodes.
 *
 * 	Must be linear time in the |a|+|b| -- i.e.,
 * 	the total number of elements being processed.
 */
void lst_merge_sorted(LIST *a, LIST *b){
    while(a->front->next != NULL && b->front->next != NULL){
      if(b->front->val >= a->front->val){
        b->front->next = a->front->next;
        a->front->next = NULL;//Free's pointer
        a->front->next = b->front;//?Reference?
      }
    }
}

/**
* TODO: Need's Testing, Particuallary pointer reference from head => clone list
* function:  lst_clone
*
* description:  makes a "deep copy" of the given list a
*   and returns it (as a LIST pointer).
*
*/
LIST * lst_clone(LIST *a) {
  LIST *head = NULL;
  NODE *clone = NULL;//*Revisions made here
  head->front = clone;
  NODE *p = a->front;
  while(p != NULL){//?Are all variables deep copied
    clone = malloc(sizeof(struct NODE*));//?Correct dynamic allocation?
    clone->val = p->val;
    clone->next = p->next;
    p = p->next;
  }
  return head;
}



/**
* TODO: Testing
* function:  lst_from_array 
*
* description:  creates a new list populated with the
*      elements of array a[] in the same order as 
*      they appear in a[] (element at a[0] will be the
*      first element in the list and so-on).  List is
*      returned as a LIST pointer.
*
*      Parameter n indicates the length of the given array.
*
* runtime requirement:  THETA(n)
*/
LIST * lst_from_array(ElemType a[], int n){//!Can you return NODE types out of LIST return functions
    LIST *head = NULL;//New Wrapper of size n ->k \n
    NODE *p = malloc(n*sizeof(struct NODE*));//Linked list
    NODE *newNode = NULL;

    if(n < 1)
      printf("Invalid array size\n");
    else{
      //Creates head nodes
      p->val = a[0];
      p->next = newNode;
      for(int x = 1; x < n; x++){//?Does this need to be free'd so it can hold new variables? 
        newNode = malloc(sizeof(struct NODE*));
        newNode->val = a[x];
        newNode->next = NULL;//Points to empty position
        p->next = newNode;
      }
    }
  return head;
}


/**
 * ! I don't know how the return types work with ElemType is it structured correctly
* TODO: Testing
* function:  lst_to_array 
*
* description:  allocates an array of ElemType and populates
*         it with the elements in the given list (as with
*         lst_from_array elements are in the same order in
*         both data structures).
*
* runtime requirement:  THETA(n)
*
* ! Needs to utlize dynamic array allocation
**/
ElemType * lst_to_array(LIST *lst) {
  NODE *p = lst->front;
  int x = 0;
  int len = lst_length(lst);//*Returns lst length
  ElemType **lstArray = malloc((len + 1)*sizeof(ElemType*));//! Does this allocate full length of array

  while(p != NULL && x <= len){
    *lstArray[x] = p->val;
    x++;
    p = p->next;
  }
  return *lstArray;//!Is this returning a pointer or a double pointer
}


/**
* TODO: .
* function:  lst_prefix
*
* description:  removes the first k elements from the
*               given list which are used to form a new list
*		which is then returned.
*
*		if n is the length of the given list, we have the
*		following boundary conditions:
*
*		  if k==0:
*			lst unchanged and an empty list returned
*		  if k>=n:
*			lst becomes empty and a list containing
*			all elements previously in lst is returned.
*
*		examples:
*
*		  EX1:  lst:  [2, 3, 9, 7, 8]
*			k:    3
*
*			after call:
*			   lst:  [7, 8]
*			   returned list:  [2, 3, 9]
*
*		  EX2  lst:  [2, 3, 9, 7, 8]
*			k:    0
*
*			after call:
*			   lst:  [2, 3, 9, 7, 8]  (unchanged)
*			   returned list:  []
*
*		  EX3  lst:  [2, 3, 9, 7, 8]
*			k:    5
*
*			after call:
*			   lst:  []
*			   returned list:  [2, 3, 9, 7, 8]
*
* REQUIREMENTS:
*
*	RUNTIME:  THETA(n) worst case where n is the length of the given list
*
*       ORDERING:  the ordering of the returned prefix should be the same as
*                  in the given list
*
*       MEMORY:    for full credit, no new nodes should be allocated or deallocated;
*		   you should just "re-use" the existing nodes.  HOWEVER, you will
*		   need to allocate a LIST structure itself (i.e., for the returned
*		   list).
*/
LIST * lst_prefix(LIST *lst, unsigned int k) {

  return NULL;

}




/**
* TODO: Needs to be finished than tested
* function:  lst_filter_leq
*
* description:  removes all elements of the given list (lst) which
*		are less than or equal to a given value (cutoff)
*		
*		A list containing the removed elements is returned.
*
* examples:
*
*	EX1: 	lst:  [4, 9, 2, 4, 8, 12, 7, 3]
*		cutoff:  4
*
*		after call:
*			lst:  [9, 8, 12, 7]
*			returned list:  [4, 2, 4, 3]
*
*       -----------------------------------------
*	EX2: 	lst:  [6, 5, 2, 1]
*		cutoff:  6
*
*		after call:
*			lst:  []
*	 		returned list:  [6, 5, 2, 1]
*
* REQUIREMENTS:
*
*	RUNTIME:  THETA(n) where n is the length of the given list
*
*       ORDERING:  the ordering of the returned list should be the same as
*                  in the given list
*
*       MEMORY:    for full credit, no new nodes should be allocated or deallocated;
*		   you should just "re-use" the existing nodes.  HOWEVER, you will
*		   need to allocate a LIST structure itself (i.e., for the returned
*		   list).
*			
*/
LIST * lst_filter_leq(LIST *lst, ElemType cutoff) {
  LIST *head = NULL;
  NODE *c = lst->front;
  NODE *prev = NULL;
  NODE *next = NULL;

  
  if(c == NULL)
    printf("Invalid list length");
  else{
    prev = c;
    next = c->next;
    while(c != NULL){
      if(c->val <= cutoff){//Evaluates cutoff point
        prev->next = next;
      }
      c = c->next;
      next = c->next;//Maintanes the head
    }
  }
  return head;
}

/**
* TODO: .
* function:  lst_concat
*
* description:  concatenates lists a and b; resulting
*    concatenation is reflected in list a; list b becomes
*    empty.
*
*    example:
*
*	EX1:  a: [2, 9, 1]
*	      b: [5, 1, 2]
*
*	after call:
*
*		a: [2, 9, 1, 5, 1, 2]
*		b: []
*
* REQUIREMENTS:  
*
*     runtime:  O(1)
*
*     sanity:  this operation makes sense when a and b
*		are distinct lists.  For example, we don't
*		want/allow the caller to do something like
*		this:
*
*			LIST *my_list;
*
*			lst_push_front(my_lst, 4);
*			lst_push_front(my_lst, 2);
*
*			lst_concat(my_lst, my_lst);
*
*		your implementation must detect if it is being
*		called this way.  If so the function does nothing
*		and (optionally) prints an error message to
*		stderr.
*	
*/
void lst_concat(LIST *a, LIST *b) {

  //Checks sanity -> concat
  NODE *al = a->front;
  NODE *bl = b->front;

  while(al != NULL){
    if(al->next == NULL && bl->next != NULL){
      al->next = bl;//Set's null ptr to bl pos
      al = al->next;//al walk
      bl = bl->next;//bl walk
      al->next = NULL;
    }else if(bl->next == NULL)
      printf("End of concatination\n");
  }
}
