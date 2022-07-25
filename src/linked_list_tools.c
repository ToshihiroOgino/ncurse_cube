#include "linked_list.h"

#include <stdlib.h>
#include <string.h>

Node *str_to_list(char *str) {
    Node *node = 0;
    int len = strlen(str);
    for (int i = 0; i < len; i++)
        list_add_back(&node, (int)str[i]);
    return node;
}

char *list_to_str(Node *node) {
    if (node == 0)
        return "";

    int len = node->edge->length;
    node = node->edge->head;
    char *str = (char *)malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < len; i++) {
        str[i] = (char)node->key;
        node = node->next;
    }
    str[len] = '\0';
    return str;
}

int list_count(Node *node, int target) {
    int res = 0;
    node = node->edge->head;
    while (node != 0) {
        if (node->key == target)
            res++;
        node = node->next;
    }
    return res;
}

Node **list_split(Node *node, int wedge) {
    if (node == 0)
        return 0;
    int n = list_count(node, wedge) + 1;
    node = node->edge->head;
    Node **res = (Node **)malloc(sizeof(Node *) * n);
    for (int i = 0; i < n; i++) {
        res[i] = 0;
        while (node != 0 && node->key != wedge) {
            list_add_back(&res[i], node->key);
            node = node->next;
        }
    }
    return res;
}
