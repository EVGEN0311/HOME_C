#include <stdio.h>
#include <string.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (input == NULL || output == NULL) {
        printf("Error \n");
        return 1;
    }

    char s[100], n[100], p[100];
    

    if (fscanf(input, "%s %s %s", s, n, p) != 3) {
        printf("Error \n");
        fclose(input);
        fclose(output);
        return 1;
    }

    
    fprintf(output, "Hello, %s %s!\n", n, s);

    fclose(input);
    fclose(output);
    return 0;
}
