#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_
typedef struct Node {
    int key;
    struct Node *next, *prev;
    struct Edge_Node *edge;
} Node;
typedef struct Edge_Node {
    int length;
    struct Node *head, *tail;
} Edge_Node;
Node *gen_node(int key);
Edge_Node *gen_edge_node();
void list_add_front(Node **node, int key);
void list_add_back(Node **node, int key);
Node *list_add_next(Node **node, int key);
Node *list_delete_node(Node **node);
Node *str_to_list(char *str);
char *list_to_str(Node *node);
int list_count(Node *node, int target);
Node **list_split(Node *node, int wedge);
#endif /* LINKED_LIST_H_ */
