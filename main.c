#include <stdio.h>
#include <stdlib.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"
#define BLINK "\033[5m"
#define REVERSE "\033[7m"
#define HIGHLIGHT "\033[7m"
#define CLEAR_SCREEN "\033[2J\033[H"
#define CLEAR_LINE "\033[K"
#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"
#define SET_COLOR(color) printf("%s", color)
#define RESET_COLOR() printf(RESET)

void mainHeader(void);
void mainMenu(void);
void loginMenu(void);
void registerMenu(void);

int main(void) {

    mainHeader();
    mainMenu();
    





    getchar();

    return 0;
}

void mainHeader(void) {
    SET_COLOR(BLUE);
    printf("+----------------------------------------------------+\n");
    printf("|   ____            ____                             |\n");
    printf("|  / ___|          / ___| __ _ _ __ __ _  __ _  ___  |\n");
    printf("| | |      _____  | |  _ / _` | '__/ _` |/ _` |/ _ \\ |\n");
    printf("| | |___  |_____| | |_| | (_| | | | (_| | (_| |  __/ |\n");
    printf("|  \\____|          \\____|\\__,_|_|  \\__,_|\\__, |\\___| |\n");
    printf("|                                        |___/       |\n");
    printf("+----------------------------------------------------+\n");     
    RESET_COLOR();
}

void mainMenu(void) {
    printf(GREEN "[" YELLOW "1" GREEN "] Register\n" RESET);
    printf(GREEN "[" YELLOW "2" GREEN "] Login\n" RESET);
    printf(GREEN "[" YELLOW "3" GREEN "] Exit\n" RESET);
    printf(YELLOW "Enter your choice: " RESET);

    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            registerMenu();
            break;
        case 2:
            loginMenu();
            break;
        case 3:
            printf(GREEN "Exiting the system. Goodbye!\n" RESET);
            exit(0);
        default:
            printf(RED "Invalid choice. Please try again.\n" RESET);
            mainMenu();
    }
}

void loginMenu(void) {
    printf(CLEAR_SCREEN);
    printf(BLUE "+------------+\n" RESET);
    printf(BLUE "| Login Menu |\n" RESET);
    printf(BLUE "+------------+\n" RESET);
    printf(GREEN "[" YELLOW "1" GREEN "] Admin\n" RESET);
    printf(GREEN "[" YELLOW "2" GREEN "] Technician\n" RESET);
    printf(GREEN "[" YELLOW "3" GREEN "] Guest\n" RESET);
    printf(GREEN "[" YELLOW "3" GREEN "] Login Menu Help\n" RESET);
    printf(GREEN "[" YELLOW "4" GREEN "] Back to Main Menu\n" RESET);
}

void registerMenu(void) {
    printf(CLEAR_SCREEN);
    printf(BLUE "+---------------+\n" RESET);
    printf(BLUE "| Register Menu |\n" RESET);
    printf(BLUE "+---------------+\n" RESET);
    printf(GREEN "[" YELLOW "1" GREEN "] Admin\n" RESET);
    printf(GREEN "[" YELLOW "2" GREEN "] Technician\n" RESET);
    printf(GREEN "[" YELLOW "3" GREEN "] Register Menu Help\n" RESET);
    printf(GREEN "[" YELLOW "4" GREEN "] Back to Main Menu\n" RESET);
}