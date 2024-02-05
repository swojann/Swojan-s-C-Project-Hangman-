#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_LIVES 10
#define MAX_WORDS 5
#define WORD_LENGTH 20
#define HINT_LENGTH 100

typedef struct {
    char word[WORD_LENGTH];
    char hint[HINT_LENGTH];
    int used;
} Word;

void displayWelcomeMessage() {
    printf("Welcome to\n");
     printf("--------------------------------------------\n");
      printf("| H  H    A    N   N   GGGG  M   M    A    N   N |\n");
      printf("| H  H   A A   NN  N  G      MM MM   A A   NN  N |\n");
      printf("| HHHH  AAAAA  N N N  G  GG  M M M  AAAAA  N N N |\n");
      printf("| H  H  A   A  N  NN  G   G  M   M  A   A  N  NN |\n");
      printf("| H  H  A   A  N   N   GGG   M   M  A   A  N   N |\n");
      printf("--------------------------------------------\n\n");
    printf("*****************\n\n");
    printf("Rules:\n");
    printf("1. You have %d guesses/lives to guess the word.\n", MAX_LIVES);
    printf("2. You must guess all %d words to win the game.\n", MAX_WORDS);
    printf("3. Failing to guess a word correctly ends the game.\n");
    printf("4. A hint will be provided for each word.\n\n");
}

int getYesNoResponse() {
    char response[10];
    printf("Do you want to proceed? (yes/no): ");
    scanf("%9s", response);
    return (strcmp(response, "yes") == 0 || strcmp(response, "y") == 0);
}

void initializeWords(Word words[MAX_WORDS]) {
    strcpy(words[0].word, "PRASUN");
    strcpy(words[0].hint, "Who is the coolest teacher?");
    words[0].used = 0;
    
    strcpy(words[1].word, "HITLER");
    strcpy(words[1].hint, "A famous Austrian Painter");
    words[1].used = 0;
    
    strcpy(words[2].word, "ZOMBIE");
    strcpy(words[2].hint, "A dead person who comes to life");
    words[2].used = 0;
    
    strcpy(words[3].word, "PAJAMAS"); // Removed space for simplicity in processing
    strcpy(words[3].hint, "Something that is worn as a night dress");
    words[3].used = 0;
    
    strcpy(words[4].word, "MESSI");
    strcpy(words[4].hint, "The greatest of all time (football)");
    words[4].used = 0;
}

void displayHint(const Word* word) {
    printf("\nHint: %s\n", word->hint);
}

void displayGuessedWord(const char* guessed) {
    for (int i = 0; i < strlen(guessed); ++i) {
        printf("%c ", guessed[i]);
    }
    printf("\n");
}

int playGame(Word words[MAX_WORDS]) {
    srand(time(NULL)); // Initialize random seed.
    int wins = 0;
    char guesses[26]; // Tracking guessed letters
    int guessCount = 0;

    for (int i = 0; i < MAX_WORDS; ++i) {
        int wordIndex;
        do {
            wordIndex = rand() % MAX_WORDS;
        } while (words[wordIndex].used);
        
        Word* currentWord = &words[wordIndex];
        currentWord->used = 1;
        int lives = MAX_LIVES;
        char guessed[strlen(currentWord->word) * 2]; // Adjust for spaces between underscores
        for (int j = 0; j < strlen(currentWord->word); j++) {
            guessed[j*2] = '_';
            if (j < strlen(currentWord->word) - 1) {
                guessed[j*2 + 1] = ' ';
            }
        }
        guessed[strlen(currentWord->word) * 2 - 1] = '\0'; // Null-terminate the string
        guessCount = 0;

        printf("\nGuess the word! You have %d lives.\n", lives);
        displayHint(currentWord);

        while (lives > 0) {
            printf("\n");
            displayGuessedWord(guessed);
            printf("(Lives: %d) [Guessed: %.*s]: ", lives, guessCount, guesses);
            char guess;
            scanf(" %c", &guess);
            guess = toupper(guess);

            // Check if already guessed
            int alreadyGuessed = 0;
            for (int j = 0; j < guessCount; ++j) {
                if (guesses[j] == guess) {
                    alreadyGuessed = 1;
                    printf("You've already guessed '%c'. Try a different one.\n", guess);
                    break;
                }
            }

            if (alreadyGuessed) continue;

            guesses[guessCount++] = guess;

            int correctGuess = 0;
            for (int j = 0; j < strlen(currentWord->word); ++j) {
                if (guess == currentWord->word[j]) {
                    guessed[j*2] = currentWord->word[j];
                    correctGuess = 1;
                }
            }

            if (!correctGuess) {
                printf("Wrong guess!\n");
                --lives;
            } else {
                // Update guessed word
                int allGuessed = 1;
                for (int j = 0; j < strlen(currentWord->word); ++j) {
                    if (guessed[j*2] == '_') {
                        allGuessed = 0;
                        break;
                    }
                }
                if (allGuessed) {
                    printf("\n");
                    displayGuessedWord(guessed);
                    printf("Correct! The word is %s.\n", currentWord->word);
                    wins++;
                    break;
                }
            }

            if (lives == 0) {
                printf("You've run out of lives. The word was %s.\n", currentWord->word);
                return 0; // Ends the game immediately if a word is not guessed
            }
        }
    }

    return wins == MAX_WORDS; // Return 1 if all words are guessed correctly, otherwise 0
}

int main() {
    Word words[MAX_WORDS];
    initializeWords(words);

    displayWelcomeMessage();

    if (!getYesNoResponse()) {
        printf("Exiting game. Goodbye!\n");
        return 0;
    }

    if (playGame(words)) {
        printf("\nCongratulations! You've guessed all words correctly! You won the game!\n");
    } else {
        printf("\nGame over. Better luck next time!\n");
    }

    return 0;
}
