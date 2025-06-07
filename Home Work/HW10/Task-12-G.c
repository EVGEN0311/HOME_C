#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");

    if (input == NULL || output == NULL) {
        printf("ERROR \n");
        return 1;
    }

    char line[1000];
    if (fgets(line, sizeof(line), input) == NULL) {
        printf("ERROR \n");
        fclose(input);
        fclose(output);
        return 1;
    }

    
    line[strcspn(line, "\n")] = '\0';

    
    char *word = strtok(line, " "); 
    while (word != NULL) {
        fprintf(output, "%s\n", word); 
        word = strtok(NULL, " ");      
    }

    fclose(input);
    fclose(output);

    return 0;
}
