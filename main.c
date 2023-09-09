#include <stdio.h>
#include "doubly_linked_list.h"
#include <stdlib.h>

int main(void) {
    struct doubly_linked_list_t *doublyLinkedList = dll_create();
    if(doublyLinkedList == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }

    int option;

    while(1) {
        printf("Please input option:");
        if(scanf("%d", &option) != 1) {
            printf("Incorrect input");
            dll_clear(doublyLinkedList);
            free(doublyLinkedList);
            doublyLinkedList = NULL;
            return 1;
        }
        else if(option < 0 || option > 14) {
            printf("Incorrect input data\n");
            continue;
        }
        else if(option == 0) {
            dll_clear(doublyLinkedList);
            free(doublyLinkedList);
            doublyLinkedList = NULL;
            return 0;
        }
        else if(option == 1) {
            int value, res;
            printf("Please input value to push:");
            if(scanf("%d", &value) != 1) {
                printf("Incorrect input");
                dll_clear(doublyLinkedList);
                free(doublyLinkedList);
                doublyLinkedList = NULL;
                return 1;
            }

            res = dll_push_back(doublyLinkedList, value);
            if(res == 2) {
                printf("Failed to allocate memory");
                dll_clear(doublyLinkedList);
                free(doublyLinkedList);
                doublyLinkedList = NULL;
                return 8;
            }
        }
        else if(option == 2) {
            if(dll_is_empty(doublyLinkedList)) {
                printf("List is empty\n");
                continue;
            }

            int value;
            value = dll_pop_back(doublyLinkedList, NULL);
            printf("%d\n", value);
        }
        else if(option == 3) {
            int value, res;
            printf("Please input value to push:");
            if(scanf("%d", &value) != 1) {
                printf("Incorrect input");
                dll_clear(doublyLinkedList);
                free(doublyLinkedList);
                doublyLinkedList = NULL;
                return 1;
            }

            res = dll_push_front(doublyLinkedList, value);
            if(res == 2) {
                printf("Failed to allocate memory");
                dll_clear(doublyLinkedList);
                free(doublyLinkedList);
                doublyLinkedList = NULL;
                return 8;
            }
        }
        else if(option == 4) {
            if(dll_is_empty(doublyLinkedList)) {
                printf("List is empty\n");
                continue;
            }

            int value;
            value = dll_pop_front(doublyLinkedList, NULL);
            printf("%d\n", value);
        }
        else if(option == 5) {
            int value, index, res;
            printf("Please input value to insert:");
            if(scanf("%d", &value) != 1) {
                printf("Incorrect input");
                dll_clear(doublyLinkedList);
                free(doublyLinkedList);
                doublyLinkedList = NULL;
                return 1;
            }
            printf("Please input index to insert:");
            if(scanf("%d", &index) != 1) {
                printf("Incorrect input");
                dll_clear(doublyLinkedList);
                free(doublyLinkedList);
                doublyLinkedList = NULL;
                return 1;
            }

            if(index > dll_size(doublyLinkedList) || index < 0) {
                printf("Index out of range\n");
                continue;
            }

            res = dll_insert(doublyLinkedList, index, value);

            if(res == 2) {
                printf("Failed to allocate memory");
                dll_clear(doublyLinkedList);
                free(doublyLinkedList);
                doublyLinkedList = NULL;
                return 8;
            }
        }
        else if(option == 6) {
            if(dll_is_empty(doublyLinkedList)) {
                printf("List is empty\n");
                continue;
            }

            int value, index, err_code;
            printf("Please input index to insert:");
            if(scanf("%d", &index) != 1) {
                printf("Incorrect input");
                dll_clear(doublyLinkedList);
                free(doublyLinkedList);
                doublyLinkedList = NULL;
                return 1;
            }

            if(index >= dll_size(doublyLinkedList) || index < 0) {
                printf("Index out of range\n");
                continue;
            }

            value = dll_remove(doublyLinkedList, index, &err_code);

            printf("%d\n", value);
        }
        else if(option == 7) {
            if(dll_is_empty(doublyLinkedList)) {
                printf("List is empty\n");
                continue;
            }

            printf("%d\n", dll_back(doublyLinkedList, NULL));
        }
        else if(option == 8) {
            if(dll_is_empty(doublyLinkedList)) {
                printf("List is empty\n");
                continue;
            }

            printf("%d\n", dll_front(doublyLinkedList, NULL));
        }
        else if(option == 9) {
            if(dll_is_empty(doublyLinkedList)) {
                printf("1\n");
            }
            else printf("0\n");
        }
        else if(option == 10) {
            printf("%d\n", dll_size(doublyLinkedList));
        }
        else if(option == 11) {
            dll_clear(doublyLinkedList);
        }
        else if(option == 12) {
            if(dll_is_empty(doublyLinkedList)) {
                printf("List is empty\n");
                continue;
            }

            int value, index, err_code;
            printf("Please input index to insert:");
            if(scanf("%d", &index) != 1) {
                printf("Incorrect input");
                dll_clear(doublyLinkedList);
                free(doublyLinkedList);
                doublyLinkedList = NULL;
                return 1;
            }

            if(index >= dll_size(doublyLinkedList) || index < 0) {
                printf("Index out of range\n");
                continue;
            }

            value = dll_at(doublyLinkedList, index, &err_code);

            printf("%d\n", value);
        }
        else if(option == 13) {
            if(dll_is_empty(doublyLinkedList)) {
                printf("List is empty\n");
                continue;
            }

            dll_display(doublyLinkedList);
            printf("\n");
        }
        else if(option == 14) {
            if(dll_is_empty(doublyLinkedList)) {
                printf("List is empty\n");
                continue;
            }

            dll_display_reverse(doublyLinkedList);
            printf("\n");
        }
    }
}
