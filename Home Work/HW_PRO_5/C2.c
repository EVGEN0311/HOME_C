#include <stdio.h>
#include <ctype.h>

int main(void) {
    long long st[200000];
    int top = 0;

    int c;
    while ((c = getchar()) != EOF) {
        if (isspace(c)) continue;

        if (isdigit(c)) {
            long long x = 0;
            while (c != EOF && isdigit(c)) {
                x = x * 10 + (c - '0');
                c = getchar();
            }
            st[top++] = x;
            if (c == EOF) break;
            ungetc(c, stdin);
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (top < 2) { printf("0\n"); return 0; }
            long long b = st[--top];
            long long a = st[--top];
            long long r = 0;

            if (c == '+') r = a + b;
            else if (c == '-') r = a - b;
            else if (c == '*') r = a * b;
            else r = a / b; // целочисленное деление

            st[top++] = r;
        } else if (c == '.') {
            break; // конец выражения
        } else {
            // неожиданный символ — пропустим
        }
    }

    if (top > 0) printf("%lld\n", st[top - 1]);
    else printf("0\n");

    return 0;
}
