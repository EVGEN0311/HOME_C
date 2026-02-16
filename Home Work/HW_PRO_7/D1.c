#include <stdio.h>
#include <stdlib.h>

static void hdRange(tree *r, int hd, int *mn, int *mx) {
    if (!r) return;
    if (hd < *mn) *mn = hd;
    if (hd > *mx) *mx = hd;
    hdRange(r->left, hd - 1, mn, mx);
    hdRange(r->right, hd + 1, mn, mx);
}

typedef struct {
    tree *node;
    int hd;
} QItem;

void btUpView(tree *root) {
    if (!root) return;

    int mn = 0, mx = 0;
    hdRange(root, 0, &mn, &mx);

    int n = mx - mn + 1;
    int *has = (int*)calloc((size_t)n, sizeof(int));
    datatype *val = (datatype*)malloc((size_t)n * sizeof(datatype));
    if (!has || !val) exit(1);

    int cap = 64, front = 0, back = 0;
    QItem *q = (QItem*)malloc((size_t)cap * sizeof(QItem));
    if (!q) exit(1);

    q[back++] = (QItem){ root, -mn };

    while (front < back) {
        QItem cur = q[front++];
        int idx = cur.hd;

        if (!has[idx]) {
            has[idx] = 1;
            val[idx] = cur.node->key;
        }

        if (cur.node->left) {
            if (back == cap) {
                cap *= 2;
                q = (QItem*)realloc(q, (size_t)cap * sizeof(QItem));
                if (!q) exit(1);
            }
            q[back++] = (QItem){ cur.node->left, idx - 1 };
        }

        if (cur.node->right) {
            if (back == cap) {
                cap *= 2;
                q = (QItem*)realloc(q, (size_t)cap * sizeof(QItem));
                if (!q) exit(1);
            }
            q[back++] = (QItem){ cur.node->right, idx + 1 };
        }
    }

    int first = 1;
    for (int i = 0; i < n; i++) {
        if (has[i]) {
            if (!first) putchar(' ');
            printf("%d", (int)val[i]);
            first = 0;
        }
    }

    free(q);
    free(has);
    free(val);
}
