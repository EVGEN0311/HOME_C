#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);

    long long x, mx;
    int cnt = 0;
	
    for (int i = 0; i < N; i++) {
        scanf("%lld", &x);

        if (i == 0) {          // первый элемент
            mx = x;
            cnt = 1;
        } else if (x > mx) {   // нашли новый максимум
            mx = x;
            cnt = 1;
        } else if (x == mx) {  // максимум встретился ещё раз
            cnt++;
        }
    }

    printf("%d\n", cnt);
    return 0;
}

