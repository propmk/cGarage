#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BLACK "\033[30m"
#define BRIGHT_BLACK "\033[90m"
#define RED "\033[31m"
#define BRIGHT_RED "\033[91m"
#define GREEN "\033[32m"
#define BRIGHT_GREEN "\033[92m"
#define YELLOW "\033[33m"
#define BRIGHT_YELLOW "\033[93m"
#define BLUE "\033[34m"
#define BRIGHT_BLUE "\033[94m"
#define MAGENTA "\033[35m"
#define BRIGHT_MAGENTA "\033[95m"
#define CYAN "\033[36m"
#define BRIGHT_CYAN "\033[96m"
#define WHITE "\033[37m"
#define BRIGHT_WHITE "\033[97m"
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"
#define HIGHLIGHT "\033[7m"
#define CLEAR_LINE "\033[K"
#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"
#define SET_STATE(state) printf("%s", state)
#define RESET_STATE() printf(RESET)

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

typedef struct {
    char name[50];
    char email[50];
    char phone[15];
    char dateOfBirth[11];
    char password[50];
} Employee;

void mainHeader(void);
void mainMenu(void);
void registerMenu(void);
void registerAsAdmin(void);
void registerAsTechnician(void);
void registerAsCustomerServiceAgent(void);
void registerMenuHelp(void);
void loginMenu(void);
void loginAsAdmin(void);
void loginAsTechnician(void);
void loginAsCustomerServiceAgent(void);
void loginAsGuest(void);
void loginMenuHelp(void);
void aboutApp(void);
void clearInputBuffer(void);
char* getEventTime(void);

int main(void) {

    mainMenu();

    return 0;
}

void mainHeader(void) {
    SET_STATE(BRIGHT_BLUE);
    printf("+----------------------------------------------------+\n");
    printf("|   ____            ____                             |\n");
    printf("|  / ___|          / ___| __ _ _ __ __ _  __ _  ___  |\n");
    printf("| | |      _____  | |  _ / _` | '__/ _` |/ _` |/ _ \\ |\n");
    printf("| | |___  |_____| | |_| | (_| | | | (_| | (_| |  __/ |\n");
    printf("|  \\____|          \\____|\\__,_|_|  \\__,_|\\__, |\\___| |\n");
    printf("|                                        |___/       |\n");
    printf("+----------------------------------------------------+\n");     
    RESET_STATE();
}

void mainMenu(void) {
    system(CLEAR_SCREEN);
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
            printf(RED "Invalid input. Please try again.\n" RESET);
            clearInputBuffer();
            printf("Press "  YELLOW "Enter" RESET " to continue..." HIDE_CURSOR);
            getchar();
            SET_STATE(SHOW_CURSOR);
            mainMenu();
    }
}

void registerMenu(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+---------------+\n" RESET);
    printf(BRIGHT_BLUE "| Register Menu |\n" RESET);
    printf(BRIGHT_BLUE "+---------------+\n" RESET);
    printf(GREEN "[" YELLOW "1" GREEN "] Admin\n" RESET);
    printf(GREEN "[" YELLOW "2" GREEN "] Technician\n" RESET);
    printf(GREEN "[" YELLOW "3" GREEN "] Customer Service Agent\n" RESET);
    printf(GREEN "[" YELLOW "4" GREEN "] Help\n" RESET);
    printf(GREEN "[" YELLOW "5" GREEN "] Return to Main Menu\n" RESET);
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
            registerAsCustomerServiceAgent();
            break;
        case 4:
            registerMenuHelp();
            break;
        case 5:
            mainMenu();
            break;
        default:
            printf(RED "Invalid input. Please try again.\n" RESET);
            clearInputBuffer();
            printf("Press " YELLOW "Enter" RESET " to continue..." HIDE_CURSOR);
            getchar();
            SET_STATE(SHOW_CURSOR);
            registerMenu();
    }
}

void registerAsAdmin(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+--------------------+\n" RESET);
    printf(BRIGHT_BLUE "| Admin Registration |\n" RESET);
    printf(BRIGHT_BLUE "+--------------------+\n" RESET);

    printf(GREEN "Enter your details:\n" RESET);
    Employee admin;
    printf(YELLOW "Name: " RESET);
    getchar();
    fgets(admin.name, sizeof(admin.name), stdin);
    printf(YELLOW "Email: " RESET);
    fgets(admin.email, sizeof(admin.email), stdin);
    printf(YELLOW "Phone: " RESET);
    fgets(admin.phone, sizeof(admin.phone), stdin);
    printf(YELLOW "Date of Birth (YYYY-MM-DD): " RESET);
    fgets(admin.dateOfBirth, sizeof(admin.dateOfBirth), stdin);
    printf(YELLOW "Password: " RESET);
    getchar();
    fgets(admin.password, sizeof(admin.password), stdin);
    
    admin.name[strcspn(admin.name, "\n")] = '\0';
    admin.email[strcspn(admin.email, "\n")] = '\0';
    admin.phone[strcspn(admin.phone, "\n")] = '\0';
    admin.dateOfBirth[strcspn(admin.dateOfBirth, "\n")] = '\0';
    admin.password[strcspn(admin.password, "\n")] = '\0';
    
    printf(GREEN "Registration successful for Admin: %s\n" RESET, admin.name);

    FILE *adminDb = fopen("admins.csv", "r");
    if (adminDb == NULL) {
        adminDb = fopen("admins.csv", "w");
        fprintf(adminDb, "Name,Email,Phone,Date Of Birth,Timestamp\n");
        fprintf(adminDb, "%s,%s,%s,%s,%s\n", admin.name, admin.email, admin.phone, admin.dateOfBirth, getEventTime());
        fclose(adminDb);   
    } 

    else {
        fclose(adminDb);
        adminDb = fopen("admins.csv", "a");
        fprintf(adminDb, "%s,%s,%s,%s,%s\n", admin.name, admin.email, admin.phone, admin.dateOfBirth, getEventTime());
        fclose(adminDb);
    }

    FILE *adminPwd = fopen("admins.pwd", "r");
    if (adminPwd == NULL) {
        adminPwd = fopen("admins.pwd", "w");
        fprintf(adminPwd, "Email,Password\n");
        fprintf(adminPwd, "%s,%s\n", admin.email, admin.password);
        fclose(adminPwd);   
    } 

    else {
        fclose(adminPwd);
        adminPwd = fopen("admins.pwd", "a");
        fprintf(adminPwd, "%s,%s\n", admin.email, admin.password);
        fclose(adminPwd);
    }

    


    clearInputBuffer();
    printf("Press " YELLOW "Enter" RESET " to return to the main menu." HIDE_CURSOR);
    getchar();
    SET_STATE(SHOW_CURSOR);
    mainMenu(); 
}

void registerAsTechnician(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+-------------------------+\n" RESET);
    printf(BRIGHT_BLUE "| Technician Registration |\n" RESET);
    printf(BRIGHT_BLUE "+-------------------------+\n" RESET);

    printf(GREEN "Enter your details:\n" RESET);
    Employee technician;
    printf(YELLOW "Name: " RESET);
    getchar();
    fgets(technician.name, sizeof(technician.name), stdin);
    printf(YELLOW "Email: " RESET);
    fgets(technician.email, sizeof(technician.email), stdin);
    printf(YELLOW "Phone: " RESET);
    fgets(technician.phone, sizeof(technician.phone), stdin);
    printf(YELLOW "Date of Birth (YYYY-MM-DD): " RESET);
    fgets(technician.dateOfBirth, sizeof(technician.dateOfBirth), stdin);
    printf(YELLOW "Password: " RESET);
    getchar();
    fgets(technician.password, sizeof(technician.password), stdin);
    
    technician.name[strcspn(technician.name, "\n")] = '\0';
    technician.email[strcspn(technician.email, "\n")] = '\0';
    technician.phone[strcspn(technician.phone, "\n")] = '\0';
    technician.dateOfBirth[strcspn(technician.dateOfBirth, "\n")] = '\0';
    technician.password[strcspn(technician.password, "\n")] = '\0';
    
    printf(GREEN "Registration successful for Technician: %s\n" RESET, technician.name);

    FILE *technicianDb = fopen("technicians.csv", "r");
    if (technicianDb == NULL) {
        technicianDb = fopen("technicians.csv", "w");
        fprintf(technicianDb, "Name,Email,Phone,Date Of Birth,Timestamp\n");
        fprintf(technicianDb, "%s,%s,%s,%s,%s\n", technician.name, technician.email, technician.phone, technician.dateOfBirth, getEventTime());
        fclose(technicianDb);   
    } 

    else {
        fclose(technicianDb);
        technicianDb = fopen("technicians.csv", "a");
        fprintf(technicianDb, "%s,%s,%s,%s,%s\n", technician.name, technician.email, technician.phone, technician.dateOfBirth, getEventTime());
        fclose(technicianDb);
    }

    FILE *technicianPwd = fopen("technicians.pwd", "r");
    if (technicianPwd == NULL) {
        technicianPwd = fopen("technicians.pwd", "w");
        fprintf(technicianPwd, "Email,Password\n");
        fprintf(technicianPwd, "%s,%s\n", technician.email, technician.password);
        fclose(technicianPwd);   
    } 

    else {
        fclose(technicianPwd);
        technicianPwd = fopen("technicians.pwd", "a");
        fprintf(technicianPwd, "%s,%s\n", technician.email, technician.password);
        fclose(technicianPwd);
    }

    


    clearInputBuffer();
    printf("Press " YELLOW "Enter" RESET " to return to the main menu." HIDE_CURSOR);
    getchar();
    SET_STATE(SHOW_CURSOR);
    mainMenu(); 
}

void registerAsCustomerServiceAgent(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+-------------------------------------+\n" RESET);
    printf(BRIGHT_BLUE "| Customer Service Agent Registration |\n" RESET);
    printf(BRIGHT_BLUE "+-------------------------------------+\n" RESET);

    printf(GREEN "Enter your details:\n" RESET);
    Employee csagent;
    printf(YELLOW "Name: " RESET);
    getchar();
    fgets(csagent.name, sizeof(csagent.name), stdin);
    printf(YELLOW "Email: " RESET);
    fgets(csagent.email, sizeof(csagent.email), stdin);
    printf(YELLOW "Phone: " RESET);
    fgets(csagent.phone, sizeof(csagent.phone), stdin);
    printf(YELLOW "Date of Birth (YYYY-MM-DD): " RESET);
    fgets(csagent.dateOfBirth, sizeof(csagent.dateOfBirth), stdin);
    printf(YELLOW "Password: " RESET);
    getchar();
    fgets(csagent.password, sizeof(csagent.password), stdin);
    
    csagent.name[strcspn(csagent.name, "\n")] = '\0';
    csagent.email[strcspn(csagent.email, "\n")] = '\0';
    csagent.phone[strcspn(csagent.phone, "\n")] = '\0';
    csagent.dateOfBirth[strcspn(csagent.dateOfBirth, "\n")] = '\0';
    csagent.password[strcspn(csagent.password, "\n")] = '\0';
    
    printf(GREEN "Registration successful for Customer Service Agent: %s\n" RESET, csagent.name);

    FILE *csagentDb = fopen("csagents.csv", "r");
    if (csagentDb == NULL) {
        csagentDb = fopen("csagents.csv", "w");
        fprintf(csagentDb, "Name,Email,Phone,Date Of Birth,Timestamp\n");
        fprintf(csagentDb, "%s,%s,%s,%s,%s\n", csagent.name, csagent.email, csagent.phone, csagent.dateOfBirth, getEventTime());
        fclose(csagentDb);   
    } 

    else {
        fclose(csagentDb);
        csagentDb = fopen("csagents.csv", "a");
        fprintf(csagentDb, "%s,%s,%s,%s,%s\n", csagent.name, csagent.email, csagent.phone, csagent.dateOfBirth, getEventTime());
        fclose(csagentDb);
    }

    FILE *csagentPwd = fopen("csagents.pwd", "r");
    if (csagentPwd == NULL) {
        csagentPwd = fopen("csagents.pwd", "w");
        fprintf(csagentPwd, "Email,Password\n");
        fprintf(csagentPwd, "%s,%s\n", csagent.email, csagent.password);
        fclose(csagentPwd);   
    } 

    else {
        fclose(csagentPwd);
        csagentPwd = fopen("csagents.pwd", "a");
        fprintf(csagentPwd, "%s,%s\n", csagent.email, csagent.password);
        fclose(csagentPwd);
    }

    


    clearInputBuffer();
    printf("Press " YELLOW "Enter" RESET " to return to the main menu." HIDE_CURSOR);
    getchar();
    SET_STATE(SHOW_CURSOR);
    mainMenu(); 
}

void registerMenuHelp(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+----------------------+\n" RESET);
    printf(BRIGHT_BLUE "|  Register Menu Help  |\n" RESET);
    printf(BRIGHT_BLUE "+----------------------+\n" RESET);
    printf(GREEN "1. Admin: Register as an administrator.\n" RESET);
    printf(GREEN "2. Technician: Register as a technician.\n" RESET);
    printf(GREEN "3. Customer Service Agent: Register as a customer service agent.\n" RESET);
    printf(GREEN "4. Help: Shows this menu.\n" RESET);
    printf(GREEN "5. Return to Main Menu.\n" RESET);

    clearInputBuffer();
    printf("Press " YELLOW "Enter" RESET " to return to the register menu." HIDE_CURSOR);
    getchar();
    SET_STATE(SHOW_CURSOR);
    registerMenu();
}

void loginMenu(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+------------+\n" RESET);
    printf(BRIGHT_BLUE "| Login Menu |\n" RESET);
    printf(BRIGHT_BLUE "+------------+\n" RESET);
    printf(GREEN "[" YELLOW "1" GREEN "] Admin\n" RESET);
    printf(GREEN "[" YELLOW "2" GREEN "] Technician\n" RESET);
    printf(GREEN "[" YELLOW "3" GREEN "] Customer Service Agent\n" RESET);
    printf(GREEN "[" YELLOW "4" GREEN "] Guest\n" RESET);
    printf(GREEN "[" YELLOW "5" GREEN "] Help\n" RESET);
    printf(GREEN "[" YELLOW "6" GREEN "] Return to Main Menu\n" RESET);
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
            loginAsCustomerServiceAgent();
            break;
        case 4:
            loginAsGuest();
            break;
        case 5:
            loginMenuHelp();
            break;
        case 6:
            mainMenu();
            break;
        default:
            printf(RED "Invalid input. Please try again.\n" RESET);
            clearInputBuffer();
            printf("Press " YELLOW "Enter" RESET " to continue..." HIDE_CURSOR);
            getchar();
            SET_STATE(SHOW_CURSOR);
            loginMenu();
    }

}

void loginAsAdmin(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+-------------+\n" RESET);
    printf(BRIGHT_BLUE "| Admin Login |\n" RESET);
    printf(BRIGHT_BLUE "+-------------+\n" RESET);

    getchar();
}

void loginAsTechnician(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+------------------+\n" RESET);
    printf(BRIGHT_BLUE "| Technician Login |\n" RESET);
    printf(BRIGHT_BLUE "+------------------+\n" RESET);

    getchar();
}

void loginAsCustomerServiceAgent(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+------------------------------+\n" RESET);
    printf(BRIGHT_BLUE "| Customer Service Agent Login |\n" RESET);
    printf(BRIGHT_BLUE "+------------------------------+\n" RESET);

    getchar();
}

void loginAsGuest(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+-------------+\n" RESET);
    printf(BRIGHT_BLUE "| Guest Login |\n" RESET);
    printf(BRIGHT_BLUE "+-------------+\n" RESET);

    getchar();
}

void loginMenuHelp(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+------------------+\n" RESET);
    printf(BRIGHT_BLUE "| Login Menu Help  |\n" RESET);
    printf(BRIGHT_BLUE "+------------------+\n" RESET);
    printf(GREEN "1. Admin: Login as an administrator.\n" RESET);
    printf(GREEN "2. Technician: Login as a technician.\n" RESET);
    printf(GREEN "3. Customer Service Agent: Login as a customer service agent.\n" RESET);
    printf(GREEN "3. Guest: Login as a guest user.\n" RESET);
    printf(GREEN "4. Help: Shows this menu.\n" RESET);
    printf(GREEN "5. Return to Main Menu.\n" RESET);

    clearInputBuffer();
    printf("Press " YELLOW "Enter" RESET " to return to the login menu." HIDE_CURSOR);
    getchar();
    SET_STATE(SHOW_CURSOR);
    loginMenu();
}

void aboutApp(void) {
    system(CLEAR_SCREEN);
    mainHeader();

    printf(BRIGHT_BLUE "+----------------------------------------------------+\n" RESET);
    printf(BRIGHT_BLUE "|                                                    |\n" RESET);
    printf(BRIGHT_BLUE "|" GREEN "  Garage Service Management System                  " BRIGHT_BLUE "|\n" RESET);
    printf(BRIGHT_BLUE "|" GREEN "  Version: 0.0.0                                    " BRIGHT_BLUE "|\n" RESET);
    printf(BRIGHT_BLUE "|" GREEN "  License: GPLv3                                    " BRIGHT_BLUE "|\n" RESET);
    printf(BRIGHT_BLUE "|" GREEN "  Github Repo: " CYAN "https://github.com/Propmk/cGarage    " BRIGHT_BLUE "|\n" RESET);
    printf(BRIGHT_BLUE "|                                                    |\n" RESET);
    printf(BRIGHT_BLUE "+----------------------------------------------------+\n" RESET);
    
    clearInputBuffer();
    printf("Press " YELLOW "Enter" RESET " to return to the main menu." HIDE_CURSOR);
    getchar();
    SET_STATE(SHOW_CURSOR);
    mainMenu();
}

void clearInputBuffer(void) {
    while (getchar() != '\n');
}

char* getEventTime(void) {
    static char timeBuffer[20];
    time_t now = time(NULL);
    struct tm *localTime = localtime(&now);
    strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", localTime);
    return timeBuffer;
}