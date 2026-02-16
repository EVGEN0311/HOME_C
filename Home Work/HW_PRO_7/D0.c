#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list {
    char word[20];
    struct list *next;
};

struct list* add_to_list(struct list *head, const char *w) {
    struct list *node = (struct list*)malloc(sizeof(struct list));
    if (!node) exit(1);
    strncpy(node->word, w, sizeof(node->word) - 1);
    node->word[sizeof(node->word) - 1] = '\0';
    node->next = NULL;

    if (!head) return node;

    struct list *p = head;
    while (p->next) p = p->next;
    p->next = node;
    return head;
}

void swap_elements(struct list *a, struct list *b) {
    char tmp[20];
    strcpy(tmp, a->word);
    strcpy(a->word, b->word);
    strcpy(b->word, tmp);
}

void print_list(struct list *head) {
    struct list *p = head;
    while (p) {
        printf("%s", p->word);
        if (p->next) putchar(' ');
        p = p->next;
    }
}

void delete_list(struct list *head) {
    while (head) {
        struct list *n = head->next;
        free(head);
        head = n;
    }
}

int main(void) {
    char s[10000];
    if (!fgets(s, sizeof(s), stdin)) return 0;

    char *dot = strchr(s, '.');
    if (dot) *dot = '\0';

    size_t len = strlen(s);
    while (len && (s[len - 1] == '\n' || s[len - 1] == '\r')) s[--len] = '\0';

    struct list *head = NULL;

    char *p = s;
    while (*p == ' ') p++;
    while (*p) {
        char w[20];
        int k = 0;
        while (*p && *p != ' ') {
            if (k < 19) w[k++] = *p;
            p++;
        }
        w[k] = '\0';
        if (k > 0) head = add_to_list(head, w);
        while (*p == ' ') p++;
    }

    if (head) {
        int swapped;
        do {
            swapped = 0;
            struct list *cur = head;
            while (cur->next) {
                if (strcmp(cur->word, cur->next->word) > 0) {
                    swap_elements(cur, cur->next);
                    swapped = 1;
                }
                cur = cur->next;
            }
        } while (swapped);
    }

    print_list(head);
    delete_list(head);
    return 0;
}

