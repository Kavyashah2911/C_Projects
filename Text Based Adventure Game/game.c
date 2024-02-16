#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void displayMenu();
void playGame();
void displayIntroduction();
void scenario1();
void scenario2();
void gameOver();
void saveGame();
void loadGame();

// Player structure to store player information
struct Player {
    char name[50];
    int health;
};

// Global variables
struct Player player;

int main() {
    displayMenu();
    return 0;
}

void displayMenu() {
    int choice;

    printf("\nText Adventure Game Menu:\n");
    printf("1. New Game\n");
    printf("2. Load Game\n");
    printf("3. Quit\n");
    printf("Enter your choice: ");

    // Check the return value of scanf and handle any errors
    if (scanf("%d", &choice) != 1) {
        printf("Error reading input. Exiting...\n");
        exit(EXIT_FAILURE);
    }

    switch (choice) {
    case 1:
        playGame();
        break;
    case 2:
        loadGame();
        playGame();
        break;
    case 3:
        printf("Goodbye!\n");
        break;
    default:
        printf("Invalid choice. Try again.\n");
        displayMenu();
    }
}

void playGame() {
    displayIntroduction();

    int choice;

    do {
        printf("\nChoose a scenario:\n");
        printf("1. Scenario 1\n");
        printf("2. Scenario 2\n");
        printf("3. Save Game\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");

        // Check the return value of scanf and handle any errors
        if (scanf("%d", &choice) != 1) {
            printf("Error reading input. Exiting...\n");
            exit(EXIT_FAILURE);
        }

        switch (choice) {
        case 1:
            scenario1();
            break;
        case 2:
            scenario2();
            break;
        case 3:
            saveGame();
            break;
        case 4:
            gameOver();
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    } while (choice != 4);
}

void displayIntroduction() {
    printf("\nWelcome to the Text Adventure Game!\n");

    // Get player's name
    printf("Enter your name: ");

    // Check the return value of fgets and handle any errors
    if (fgets(player.name, sizeof(player.name), stdin) == NULL) {
        printf("Error reading input. Exiting...\n");
        exit(EXIT_FAILURE);
    }

    // Remove the newline character from the end of the name
    player.name[strcspn(player.name, "\n")] = '\0';

    // Set initial player health
    player.health = 100;

    printf("\nHello, %s! You have %d health.\n", player.name, player.health);
}

void scenario1() {
    printf("\nYou find a magic sword in the cave. Do you want to pick it up?\n");
    printf("1. Yes\n");
    printf("2. No\n");

    int choice;
    if (scanf("%d", &choice) != 1) {
        printf("Error reading input. Exiting...\n");
        exit(EXIT_FAILURE);
    }

    if (choice == 1) {
        printf("\nYou pick up the magic sword! Congratulations, you gain +20 health!\n");
        player.health += 20;
    }
    else {
        printf("\nYou decide not to pick up the sword.\n");
    }
}

void scenario2() {
    printf("\nYou encounter a group of friendly creatures offering you a healing potion. Do you accept?\n");
    printf("1. Yes\n");
    printf("2. No\n");

    int choice;
    if (scanf("%d", &choice) != 1) {
        printf("Error reading input. Exiting...\n");
        exit(EXIT_FAILURE);
    }

    if (choice == 1) {
        printf("\nYou accept the healing potion! Your health is restored to full.\n");
        player.health = 100;
    }
    else {
        printf("\nYou decline the healing potion.\n");
    }
}

void gameOver() {
    printf("\nGame over. Thanks for playing, %s!\n", player.name);
    exit(EXIT_SUCCESS);
}

void saveGame() {
    FILE* file;

    // Check the return value of fopen_s and handle any errors
    if (fopen_s(&file, "savegame.txt", "w") != 0) {
        printf("Error saving game. Please try again.\n");
        exit(EXIT_FAILURE);
    }

    // Check the return value of fprintf and handle any errors
    if (fprintf(file, "%s %d", player.name, player.health) < 0) {
        printf("Error writing to file. Exiting...\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);
    printf("Game saved successfully!\n");
}

void loadGame() {
    FILE* file;

    // Check the return value of fopen_s and handle any errors
    if (fopen_s(&file, "savegame.txt", "r") != 0) {
        printf("No saved game found.\n");
        return; // No saved game, just return
    }

    // Check the return value of fscanf and handle any errors
    if (fscanf(file, "%s %d", player.name, &player.health) != 2) {
        printf("Error loading game. Please try again.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fclose(file);
    printf("Game loaded. Welcome back, %s!\n", player.name);
    printf("Your current health: %d\n", player.health);
}
