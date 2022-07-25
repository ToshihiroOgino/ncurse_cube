#include "linked_list.h"

#include <stdlib.h>

Node *gen_node(int key) {
    Node *n = (Node *)malloc(sizeof(Node));
    n->key = key;
    n->next = 0;
    n->prev = 0;
    n->edge = 0;
    n->edge = gen_edge_node(n, n, 1);
    return n;
}

Edge_Node *gen_edge_node(Node *head, Node *tail, int length) {
    Edge_Node *en = (Edge_Node *)malloc(sizeof(Edge_Node));
    en->head = head;
    en->tail = tail;
    en->length = length;
    return en;
}

void list_add_front(Node **node, int key) {
    if ((*node) == 0) {
        (*node) = gen_node(key);
        return;
    }
    Node *n = gen_node(key);
    n->next = (*node)->edge->head;
    (*node)->edge->head->prev = n;
    (*node)->edge->head = n;
    (*node)->edge->length += 1;
    n->edge = (*node)->edge;
}

void list_add_back(Node **node, int key) {
    if ((*node) == 0) {
        (*node) = gen_node(key);
        return;
    }
    Node *n = gen_node(key);
    n->prev = (*node)->edge->tail;
    n->edge = (*node)->edge;
    (*node)->edge->length += 1;
    (*node)->edge->tail->next = n;
    (*node)->edge->tail = n;
}

Node *list_add_next(Node **node, int key) {
    if ((*node) == 0) {
        (*node) = gen_node(key);
        return (*node);
    } else if ((*node)->edge->tail == (*node)) {
        list_add_back(node, key);
        return (*node)->edge->tail;
    } else if ((*node)->edge->head == (*node)) {
        list_add_front(node, key);
        return (*node)->edge->head->next;
    }
    Node *n = gen_node(key);
    n->next = (*node)->next;
    (*node)->next = n;
    n->prev = (*node);
    (*node)->edge->length += 1;
    n->edge = (*node)->edge;
    return n;
}

Node *list_delete_node(Node **node) {
    if ((*node) == 0)
        return 0;

    (*node)->edge->length -= 1;
    if ((*node) == (*node)->edge->head && (*node) == (*node)->edge->tail) {
        free(*node);
        return 0;
    } else if ((*node)->edge->head == (*node)) {
        Node *res = (*node)->next;
        (*node)->edge->head = (*node)->next;
        (*node)->next->prev = 0;
        free(*node);
        return res;
    } else if ((*node)->edge->tail == (*node)) {
        Node *res = (*node)->prev;
        (*node)->edge->tail = (*node)->prev;
        (*node)->prev->next = 0;
        free(*node);
        return res;
    }
    Node *res = (*node)->next;
    (*node)->prev->next = (*node)->next;
    (*node)->next->prev = (*node)->prev;
    free(*node);
    return res;
}
