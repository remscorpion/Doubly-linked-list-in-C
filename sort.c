/**
 * Read a list of numbers, sort it, and print it out.
 *
 * @author Tomohiro Matsunaga TYPE IN YOUR NAME HERE
 */

#include <stdio.h>
#include <stdlib.h>

/** The name of this program. */
char *prog;

/**
 * A node in a doubly-linked list.
 *
 * The following diagram illustrates a single node.
 *
 *                    +------+
 *                    | -0.3 |
 *                    | next | ---> pointer to a
 * pointer to a  <--- | prev |      next node
 * previous node      +------+
 */
struct node {
    double value;       ///< A value
    struct node *next;  ///< Pointer to the next node
    struct node *prev;  ///< Pointer to the previous node
};

/**
 * A doubly-linked list.
 *
 * This doubly-linked list has dummy head and tail to simplify
 * insertion, deletion, and swapping.
 *
 * The following diagram illustrates a singleton list.
 *
 *           +------+      +------+      +------+
 *   list -> | dummy|      | -0.3 |      | dummy|
 *           | next | ---> | next | ---> | next | ---> NULL
 * NULL <--- | prev | <--- | prev | <--- | prev |
 *           +------+      +------+      +------+
 */
struct list {
    struct node head;  ///< Dummy head
    struct node tail;  ///< Dummy tail
};

struct list *list_new();
void list_add(struct list *, double);
void list_swap(struct node *);
void read(struct list *);
void sort(struct list *);
void print(struct list *);

int main(int argc, char *argv[]) {
    prog = argv[0];
    struct list *l = list_new();
    read(l);
    sort(l);
    print(l);
}

/**
 * Create a new empty doubly-linked list.
 * @return a new empty list
 */
struct list *list_new() {
    struct list *l;
    l = malloc(sizeof(struct list));  // initailize the list

    // make the list only have 2 dummy nodes, and point to each other
    l -> head.next = &l -> tail;
    l -> head.prev = NULL;
    l -> tail.prev = &l -> head;
    l -> tail.next = NULL;

    return l;
}

/**
 * Insert a value at the end of the doubly-linked list.
 * @param l  Pointer to a valid doubly-linked list
 * @param d  Value to add
 */
void list_add(struct list *l, double d) {
    // TODO
    struct node *new = malloc(sizeof(struct node));
    if (new == NULL) printf("malloc error\n");
    new -> value = d;
    new -> next = &l -> tail;  // new.next is the tail node 

    struct node *last = &l -> tail;  // initailize the last node
    last = last -> prev;
    new->prev = last;  // new.prew point to last node
    last->next = new;  // last.next point to new node
}

/**
 * Swap this node with the next.
 * @param n  the node to swap with its next neighbor
 */
void list_swap(struct node *n) {
  // initailize
  struct node *prevNode = n->prev;
  struct node *nextNode = n->next;
  struct node *nextNext = n->next->next;

  n->next = nextNext;
  prevNode->next = nextNode;
  nextNode->next = n;
  n->prev = nextNode;
  nextNode->prev = prevNode;
  nextNext->prev = n;
}

/**
 * Read values into a list.
 * @param l  Pointer to a valid doubly-linked list
 * Read values from standard input and insert them at the end of the
 * list.  Stop when EOF is encountered.
 */
void read(struct list *l) {
    // TODO
  double val;
  while (scanf("%lf", &val) != EOF) list_add(l, val);
}

/**
 * Sort the given list in ascending order.
 * @param l  Pointer to a valid doubly-linked list to sort
 */
void sort(struct list *l) {
    struct node *last = &l->tail;
    while (1) {
        int inorder = 1;
        struct node *n = l->head.next;
        while (n != last) {
            struct node *next = n->next;
            if (next == last) break;
            if (n->value > next->value) {
                list_swap(n);
                inorder = 0;
            }
            n = n->next;
        }
        if (inorder) break;
    }
}

/**
 * Print each value of the list, one per line to standard output
 * @param l  Pointer to valid doubly-linked list to print
 */
void print(struct list *l) {
    // TODO
  struct node *cur = &l -> head;
  cur = cur -> next;

  struct node *last = &l -> tail;
  cur = cur->next;

  while (cur != last){
    printf("%.3lf\n", cur -> value); 
  }
}
