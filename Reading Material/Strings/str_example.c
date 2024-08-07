#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Function to capitalize the first letter of each word
char*  capitalizeFirstLetter(char *word) {
    char changed[100];
    memset(changed, 0, sizeof(changed));
    if (word[0] != '\0') {
        changed[0] = toupper(word[0]);
    }
    for (int i = 1; word[i] != '\0'; i++) {
        changed[i] = tolower(word[i]);
    }
    return changed;
}

int main() {
    char input[100];
    char *token;

    printf("Enter a string with words separated by colons (:): ");
    scanf("%s", input);  // Reading a line of input

    // Tokenize the string using colon as the delimiter
    token = strtok(input, ":");
    char ans[100];
    memset(ans, 0, sizeof(ans));
    while (token != NULL) {
        char temp[100];
        memset(temp, 0, sizeof(temp));
        strcpy(temp,capitalizeFirstLetter(token));
        strcat(ans, temp);
        strcat(ans, " ");
        token = strtok(NULL, ":");

    }
    printf("The string with first letter of each word capitalized is: ");
    printf("%s", ans);
    printf("\n");

    return 0;
}
