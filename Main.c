#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

// Morse code representations
char* morseCode[36] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", // A-Z
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----." // 0-9
};

char* letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

void textToMorse(char* text) {
    for (int i = 0; text[i] != '\0'; i++) {
        char c = toupper(text[i]);
        if (c >= 'A' && c <= 'Z') {
            printf("%s ", morseCode[c - 'A']);
        } else if (c >= '0' && c <= '9') {
            printf("%s ", morseCode[c - '0' + 26]);
        } else if (c == ' ') {
            printf("/ "); // Represent space with /
        } else {
            printf("Invalid character: %c\n", c);
        }
    }
    printf("\n");
}

void morseToText(char* morse) {
    char temp[MAX];
    int j = 0;

    // Remove extra spaces and validate input
    for (int i = 0; morse[i] != '\0'; i++) {
        if (morse[i] == ' ' || morse[i] == '/') {
            if (j > 0 && temp[j - 1] != ' ') {
                temp[j++] = ' ';
            }
        } else if (morse[i] == '.' || morse[i] == '-') {
            temp[j++] = morse[i];
        } else if (morse[i] == '\n') {
            break;
        } else {
            printf("Invalid Morse code character: %c\n", morse[i]);
            return;
        }
    }
    temp[j] = '\0';

    char* token = strtok(temp, " /"); // Split by space and /
    while (token != NULL) {
        int found = 0;
        for (int i = 0; i < 36; i++) {
            if (strcmp(token, morseCode[i]) == 0) {
                printf("%c", letters[i]);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Invalid Morse code sequence: %s\n", token);
        }
        token = strtok(NULL, " /");
    }
    printf("\n");
}

int main() {
    char text[MAX];
    char morse[MAX];
    int choice;

    printf("Choose an option:\n");
    printf("1. Text to Morse code\n");
    printf("2. Morse code to text\n");
    scanf("%d", &choice);
    getchar(); // Consume the newline character

    switch (choice) {
        case 1:
            printf("Enter text to convert to Morse code: ");
            fgets(text, sizeof(text), stdin);
            text[strcspn(text, "\n")] = 0; // Remove the newline character
            printf("Morse code: ");
            textToMorse(text);
            break;
        case 2:
            printf("Enter Morse code to convert to text (space-separated, use / for space): ");
            fgets(morse, sizeof(morse), stdin);
            morse[strcspn(morse, "\n")] = 0; // Remove the newline character
            printf("Text: ");
            morseToText(morse);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}