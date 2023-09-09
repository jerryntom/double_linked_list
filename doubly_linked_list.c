#include "doubly_linked_list.h"
#include <stdlib.h>
#include <stdio.h>

struct doubly_linked_list_t* dll_create() {
    struct doubly_linked_list_t *doublyLinkedList;
    doublyLinkedList = calloc(1, sizeof(struct doubly_linked_list_t));
    if(doublyLinkedList == NULL) return NULL;

    return doublyLinkedList;
}

int dll_push_back(struct doubly_linked_list_t* dll, int value) {
    if(dll == NULL) return 1;

    if(dll->head == NULL) {
        struct node_t *head = calloc(1, sizeof(struct node_t));
        if(head == NULL) return 2;

        head->data = value;
        dll->head = head;
        dll->tail = head;
    }
    else if(dll->tail != NULL) {
        struct node_t *tail = calloc(1, sizeof(struct node_t));
        if(tail == NULL) return 2;
        tail->data = value;
        tail->prev = dll->tail;
        tail->prev->next = tail;
        dll->tail = tail;
    }

    return 0;
}

int dll_push_front(struct doubly_linked_list_t* dll, int value) {
    if(dll == NULL) return 1;

    if(dll->head == NULL) {
        struct node_t *head = calloc(1, sizeof(struct node_t));
        if(head == NULL) return 2;

        head->data = value;
        dll->head = head;
        dll->tail = head;
    }
    else {
        struct node_t *head = calloc(1, sizeof(struct node_t));
        if(head == NULL) return 2;
        head->data = value;
        head->next = dll->head;
        head->next->prev = head;
        dll->head = head;
    }

    return 0;
}

int dll_pop_back(struct doubly_linked_list_t* dll, int *err_code) {
    if(dll == NULL || dll->head == NULL) {
        if(err_code != NULL) *err_code = 1;
        return -1;
    }

    int value = dll->tail->data;

    struct node_t *tail = dll->tail;
    if(dll->tail->prev != NULL) {
        dll->tail = dll->tail->prev;
        free(tail);
        tail = NULL;
        dll->tail->next = NULL;
    }
    else {
        free(dll->head);
        dll->head = NULL;
        dll->tail = NULL;
    }

    if(err_code != NULL) *err_code = 0;
    return value;
}

int dll_pop_front(struct doubly_linked_list_t* dll, int *err_code) {
    if(dll == NULL || dll->head == NULL) {
        if(err_code != NULL) *err_code = 1;
        return -1;
    }

    int value = dll->head->data;

    struct node_t *head = dll->head;
    if(dll->head->next != NULL) {
        dll->head = dll->head->next;
        free(head);
        head = NULL;
        dll->head->prev = NULL;
    }
    else {
        free(dll->head);
        dll->head = NULL;
        dll->tail = NULL;
    }

    if(err_code != NULL) *err_code = 0;
    return value;
}

int dll_back(const struct doubly_linked_list_t* dll, int *err_code) {
    if(dll == NULL || dll->head == NULL) {
        if(err_code != NULL) *err_code = 1;
        return -1;
    }

    if(err_code != NULL) *err_code = 0;
    return dll->tail->data;
}

int dll_front(const struct doubly_linked_list_t* dll, int *err_code) {
    if(dll == NULL || dll->head == NULL) {
        if(err_code != NULL) *err_code = 1;
        return -1;
    }

    if(err_code != NULL) *err_code = 0;
    return dll->head->data;
}

struct node_t* dll_begin(struct doubly_linked_list_t* dll) {
    if(dll == NULL || dll->head == NULL) return NULL;

    return dll->head;
}

struct node_t* dll_end(struct doubly_linked_list_t* dll) {
    if(dll == NULL) return NULL;

    return dll->tail;
}

int dll_size(const struct doubly_linked_list_t* dll) {
    if(dll == NULL) return -1;

    if(dll->head == NULL) return 0;

    int size = 0;

    struct node_t *node = dll->head;
    size++;

    while(node->next != NULL) {
        node = node->next;
        size++;
    }

    return size;
}

int dll_is_empty(const struct doubly_linked_list_t* dll) {
    if(dll == NULL) return -1;

    if(dll->head == NULL) return 1;
    else return 0;
}

int dll_at(const struct doubly_linked_list_t* dll, unsigned int index, int *err_code) {
    if(dll == NULL || dll->head == NULL) {
        if(err_code != NULL) *err_code = 1;
        return -1;
    }

    int value;
    unsigned int pos = 0;

    struct node_t *node = dll->head;

    while(node->next != NULL && pos != index) {
        node = node->next;
        pos++;
    }

    if(pos != index) {
        if(err_code != NULL) *err_code = 1;
        return -1;
    }

    value = node->data;

    if(err_code != NULL) *err_code = 0;
    return value;
}

int dll_insert(struct doubly_linked_list_t* dll, unsigned int index, int value) {
    if(dll == NULL) return 1;

    unsigned int pos = 0;

    if(index >= 10000) return 1;

    if(dll->head == NULL) {
        if(index == 0) {
            dll_push_back(dll, value);
            return 0;
        }
        else return 1;
    }

    struct node_t *node = dll->head;

    while(node->next != NULL && pos != index) {
        node = node->next;
        pos++;
    }

    if(pos == index - 1) {
        struct node_t *insert_node = calloc(1, sizeof(struct node_t));
        if(insert_node == NULL) return 2;

        insert_node->data = value;
        insert_node->prev = node;

        dll->tail->next = insert_node;
        dll->tail = insert_node;
    }
    else if(index == 0 && pos == index) {
        struct node_t *insert_node = calloc(1, sizeof(struct node_t));
        if(insert_node == NULL) return 2;

        insert_node->data = value;
        insert_node->next = node;

        dll->head->prev = insert_node;
        dll->head = insert_node;
    }
    else if (pos != index) {
        return 1;
    }
    else {
        struct node_t *insert_node = calloc(1, sizeof(struct node_t));
        if(insert_node == NULL) return 2;

        int move_value1, move_value2;
        move_value1 = node->data;
        node->data = value;

        while(node->next != NULL) {
            move_value2 = move_value1;
            node = node->next;
            move_value1 = node->data;
            node->data = move_value2;
        }

        insert_node->data = move_value1;
        insert_node->prev = node;

        dll->tail->next = insert_node;
        dll->tail = insert_node;
    }

    return 0;
}

int dll_remove(struct doubly_linked_list_t* dll, unsigned int index, int *err_code) {
    if (dll == NULL || dll->head == NULL) {
        if(err_code != NULL) *err_code = 1;
        return 1;
    }

    unsigned int pos = 0;

    if (index >= 10000) return 1;

    struct node_t *node = dll->head;

    while (node->next != NULL && pos != index) {
        node = node->next;
        pos++;
    }

    if (pos == index && node->next == NULL) {
        if(err_code != NULL) *err_code = 0;
        return dll_pop_back(dll, err_code);
    }
    else if (index == 0 && pos == index) {
        if(err_code != NULL) *err_code = 0;
        return dll_pop_front(dll, err_code);
    }
    else if (pos != index) {
        if(err_code != NULL) *err_code = 1;
        return 1;
    }
    else {
        int value = node->data;

        if(node->next != NULL) node->data = node->next->data;

        while(node->next != NULL) {
            node = node->next;
            if(node->next != NULL) node->data = node->next->data;
        }
        dll_pop_back(dll, err_code);

        if(err_code != NULL) *err_code = 0;
        return value;
    }
}

void dll_display(const struct doubly_linked_list_t* dll) {
    if(dll == NULL || dll->head == NULL) return;

    struct node_t *node = dll->head;
    printf("%d ", node->data);

    while(node->next != NULL) {
        node = node->next;
        printf("%d ", node->data);
    }
}

void dll_display_reverse(const struct doubly_linked_list_t* dll) {
    if(dll == NULL || dll->head == NULL) return;

    struct node_t *node = dll->tail;
    printf("%d ", node->data);

    while(node->prev != NULL) {
        node = node->prev;
        printf("%d ", node->data);
    }
}

void dll_clear(struct doubly_linked_list_t* dll) {
    if(dll == NULL || dll->head == NULL) return;

    while(dll->head->next != NULL) {
        dll->head = dll->head->next;
        free(dll->head->prev);
        dll->head->prev = NULL;
    }

    free(dll->head);
    dll->head = NULL;
    dll->tail = NULL;
}
