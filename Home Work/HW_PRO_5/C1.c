#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void trim_newline(char *s) {
    size_t n = strlen(s);
    while (n > 0 && (s[n-1] == '\n' || s[n-1] == '\r')) {
        s[--n] = '\0';
    }
}

static void prefix_function(const char *s, int n, int *pi) {
    pi[0] = 0;
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
}

static int kmp_border_end(const char *X, const char *Y, char sep) {
    int nX = (int)strlen(X);
    int nY = (int)strlen(Y);
    int n = nX + 1 + nY;

    char *t = (char*)malloc((size_t)n + 1);
    int  *pi = (int*)malloc((size_t)n * sizeof(int));
    if (!t || !pi) {
        free(t);
        free(pi);
        return 0;
    }

    memcpy(t, X, (size_t)nX);
    t[nX] = sep;
    memcpy(t + nX + 1, Y, (size_t)nY);
    t[n] = '\0';

    prefix_function(t, n, pi);
    int ans = pi[n - 1];

    free(t);
    free(pi);
    return ans;
}

int main(void) {
    char A[10005], B[10005];

    // пустой ввод -> по условию тестов надо вывести 0 0
    if (!fgets(A, sizeof(A), stdin)) {
        printf("0 0\n");
        return 0;
    }
    if (!fgets(B, sizeof(B), stdin)) {
        printf("0 0\n");
        return 0;
    }

    trim_newline(A);
    trim_newline(B);

    int ans1 = kmp_border_end(A, B, '#'); // max prefix(A) == suffix(B)
    int ans2 = kmp_border_end(B, A, '#'); // max suffix(A) == prefix(B)

    printf("%d %d\n", ans1, ans2);
    return 0;
}
