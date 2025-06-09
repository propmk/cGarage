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
void registerMenu(void);
void registerAsAdmin(void);
void registerAsTechnician(void);
void registerMenuHelp(void);
void loginMenu(void);
void loginAsAdmin(void);
void loginAsTechnician(void);
void loginAsGuest(void);
void loginMenuHelp(void);
void aboutApp(void);

int main(void) {

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
    printf(CLEAR_SCREEN);
    mainHeader();
    
    printf(GREEN "[" YELLOW "1" GREEN "] Register\n" RESET);
    printf(GREEN "[" YELLOW "2" GREEN "] Login\n" RESET);
    printf(GREEN "[" YELLOW "3" GREEN "] About\n" RESET);
    printf(GREEN "[" YELLOW "4" GREEN "] Exit\n" RESET);
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
            aboutApp();
            break;
        case 4:
            printf(GREEN "Exiting the system. Goodbye!\n" RESET);
            exit(0);
        default:
            printf(RED "Invalid choice. Please try again.\n" RESET);
            mainMenu();
    }
}

void registerMenu(void) {
    printf(CLEAR_SCREEN);
    printf(BLUE "+---------------+\n" RESET);
    printf(BLUE "| Register Menu |\n" RESET);
    printf(BLUE "+---------------+\n" RESET);
    printf(GREEN "[" YELLOW "1" GREEN "] Admin\n" RESET);
    printf(GREEN "[" YELLOW "2" GREEN "] Technician\n" RESET);
    printf(GREEN "[" YELLOW "3" GREEN "] Help\n" RESET);
    printf(GREEN "[" YELLOW "4" GREEN "] Return to Main Menu\n" RESET);
    printf(YELLOW "Enter your choice: " RESET);

    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            registerAsAdmin();
            break;
        case 2:
            registerAsTechnician();
            break;
        case 3:
            registerMenuHelp();
            break;
        case 4:
            mainMenu();
            break;
        default:
            printf(RED "Invalid choice. Please try again.\n" RESET);
            registerMenu();
    }
}

void registerAsAdmin(void) {
    printf(CLEAR_SCREEN);
    printf(BLUE "+--------------------+\n" RESET);
    printf(BLUE "| Admin Registration |\n" RESET);
    printf(BLUE "+--------------------+\n" RESET);

    getchar(); 
}

void registerAsTechnician(void) {
    printf(CLEAR_SCREEN);
    printf(BLUE "+-------------------------+\n" RESET);
    printf(BLUE "| Technician Registration |\n" RESET);
    printf(BLUE "+-------------------------+\n" RESET);

    getchar();
}

void registerMenuHelp(void) {
    printf(CLEAR_SCREEN);
    printf(BLUE "+---------------------+\n" RESET);
    printf(BLUE "| Register Menu Help  |\n" RESET);
    printf(BLUE "+---------------------+\n" RESET);
    printf(GREEN "1. Admin: Register as an administrator.\n" RESET);
    printf(GREEN "2. Technician: Register as a technician.\n" RESET);
    printf(GREEN "3. Help: Shows this menu.\n" RESET);
    printf(GREEN "4. Return to Main Menu.\n" RESET);

    getchar();
}

void loginMenu(void) {
    printf(CLEAR_SCREEN);
    printf(BLUE "+------------+\n" RESET);
    printf(BLUE "| Login Menu |\n" RESET);
    printf(BLUE "+------------+\n" RESET);
    printf(GREEN "[" YELLOW "1" GREEN "] Admin\n" RESET);
    printf(GREEN "[" YELLOW "2" GREEN "] Technician\n" RESET);
    printf(GREEN "[" YELLOW "3" GREEN "] Guest\n" RESET);
    printf(GREEN "[" YELLOW "4" GREEN "] Help\n" RESET);
    printf(GREEN "[" YELLOW "5" GREEN "] Return to Main Menu\n" RESET);
    printf(YELLOW "Enter your choice: " RESET);

    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            loginAsAdmin();
            break;
        case 2:
            loginAsTechnician();
            break;
        case 3:
            loginAsGuest();
            break;
        case 4:
            loginMenuHelp();
            break;
        case 5:
            mainMenu();
            break;
        default:
            printf(RED "Invalid choice. Please try again.\n" RESET);
            loginMenu();
    }

}

void loginAsAdmin(void) {
    printf(CLEAR_SCREEN);
    printf(BLUE "+-------------+\n" RESET);
    printf(BLUE "| Admin Login |\n" RESET);
    printf(BLUE "+-------------+\n" RESET);

    getchar();
}

void loginAsTechnician(void) {
    printf(CLEAR_SCREEN);
    printf(BLUE "+------------------+\n" RESET);
    printf(BLUE "| Technician Login |\n" RESET);
    printf(BLUE "+------------------+\n" RESET);

    getchar();
}

void loginAsGuest(void) {
    printf(CLEAR_SCREEN);
    printf(BLUE "+-------------+\n" RESET);
    printf(BLUE "| Guest Login |\n" RESET);
    printf(BLUE "+-------------+\n" RESET);

    getchar();
}

void loginMenuHelp(void) {
    printf(CLEAR_SCREEN);
    printf(BLUE "+------------------+\n" RESET);
    printf(BLUE "| Login Menu Help  |\n" RESET);
    printf(BLUE "+------------------+\n" RESET);
    printf(GREEN "1. Admin: Login as an administrator.\n" RESET);
    printf(GREEN "2. Technician: Login as a technician.\n" RESET);
    printf(GREEN "3. Guest: Login as a guest user.\n" RESET);
    printf(GREEN "4. Help: Shows this menu.\n" RESET);
    printf(GREEN "5. Return to Main Menu.\n" RESET);

    getchar();
}

void aboutApp(void) {
    printf(CLEAR_SCREEN);
    printf(BLUE "+-------+\n" RESET);
    printf(BLUE "| About |\n" RESET);
    printf(BLUE "+-------+\n" RESET);
    printf(GREEN "Garage Service Management System\n" RESET);
    printf(GREEN "Version: 0.0.0\n" RESET);
    printf(GREEN "Github Repository:" CYAN "https://github.com/Propmk/cGarage\n" RESET);

    getchar();
}
