#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_TRIES 6
#define WORD_COUNT 5
#define WORD_LENGTH 20

// List of words
const char *wordList[WORD_COUNT] = {"apple", "banana", "orange", "grapes", "mango"};

// Function to choose a random word
void chooseWord(char *chosenWord) {
    srand(time(NULL)); // Seed random number generator
    int index = rand() % WORD_COUNT; // Pick a random index
    strcpy(chosenWord, wordList[index]); // Copy the chosen word
}

// Function to display the current guessed state
void displayWord(char *word, int *correctGuesses) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (correctGuesses[i]) {
            printf("%c ", word[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

// Function to check if the letter is in the word
int checkGuess(char letter, char *word, int *correctGuesses) {
    int found = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        if (tolower(word[i]) == tolower(letter)) {
            correctGuesses[i] = 1; // Mark this letter as guessed
            found = 1;
        }
    }
    return found;
}

// Main function
int main() {
    char chosenWord[WORD_LENGTH];
    chooseWord(chosenWord); // Pick a random word

    int wordLength = strlen(chosenWord);
    int correctGuesses[wordLength]; // Array to track correct guesses
    memset(correctGuesses, 0, sizeof(correctGuesses)); // Initialize to 0

    int attemptsLeft = MAX_TRIES;
    int correctLetters = 0;
    char guessedLetters[26] = {0}; // Track guessed letters
    int guessedCount = 0;

    printf("Welcome to Hangman!\n");
    
    while (attemptsLeft > 0 && correctLetters < wordLength) {
        printf("\nWord: ");
        displayWord(chosenWord, correctGuesses);
        printf("Attempts left: %d\n", attemptsLeft);
        printf("Guessed letters: ");
        for (int i = 0; i < guessedCount; i++) {
            printf("%c ", guessedLetters[i]);
        }
        printf("\n");

        // Get user input
        char guess;
        printf("Enter a letter: ");
        scanf(" %c", &guess);
        guess = tolower(guess); // Convert to lowercase

        // Check if the letter was already guessed
        int alreadyGuessed = 0;
        for (int i = 0; i < guessedCount; i++) {
            if (guessedLetters[i] == guess) {
                alreadyGuessed = 1;
                break;
            }
        }
        if (alreadyGuessed) {
            printf("You already guessed '%c'. Try again.\n", guess);
            continue;
        }

        // Add the letter to guessed letters
        guessedLetters[guessedCount++] = guess;

        // Check if the letter is in the word
        if (checkGuess(guess, chosenWord, correctGuesses)) {
            printf("Good job! '%c' is in the word.\n", guess);
            correctLetters = 0;
            for (int i = 0; i < wordLength; i++) {
                if (correctGuesses[i]) {
                    correctLetters++;
                }
            }
        } else {
            printf("Sorry, '%c' is not in the word.\n", guess);
            attemptsLeft--;
        }
    }

    // Check win/lose conditions
    if (correctLetters == wordLength) {
        printf("\nCongratulations! You guessed the word: %s\n", chosenWord);
    } else {
        printf("\nGame over! The word was: %s\n", chosenWord);
    }

    return 0;
}
