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

#define ADMIN_DASHBOARD 1
#define TECHNICIAN_DASHBOARD 2
#define CS_AGENT_DASHBOARD 3

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

typedef struct {
    char email[50];
    char role[25];
    char password[50];
} PasswordRecord;

typedef struct {
    char serviceName[50];
    float price;
} ServicePrice;

typedef struct {
    float taxRate;
} TaxSettings;

typedef struct {
    char vehicleMake[50];
    char vehicleModel[50];
    char vehicleYear[5];
    char licensePlate[20];
    char vehicleColor[30];
    char mileage[15];
    char customerName[50];
    char customerPhone[15];
    char serviceType[100];
    char problemDescription[500];
    char urgencyLevel[20];
    char status[20];
    char timestamp[20];
    char notes[1000];
    char partsUsed[500];
    float partsCost;
    char lastUpdated[20];
} VehicleRecord;

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
void loginMenuHelp(void);
void adminDashboard(void);
void technicianDashboard(void);
void customerServiceAgentDashboard(void);
void viewActiveRepairs(void);
void viewRepairHistory(int callerDashboard);
void updateCarRepairStatus(int callerDashboard);
void viewServiceRequests(void);
void logVehicle(void);
void generateBill(void);
void managePricing(void);
void initializeDefaultPricing(void);
float getServicePrice(const char* serviceType);
void updateServicePrice(const char* serviceName, float newPrice);
float getTaxRate(void);
void updateTaxRate(float newTaxRate);
void initializeDefaultTaxRate(void);
void aboutApp(void);
void clearInputBuffer(void);
char* getEventTime(void);
int findLatestVehicleRecordByPlate(const char *plate, VehicleRecord *outRecord);
int updateVehicleRecord(const char *licensePlate, const char *newStatus, const char *notes, const char *partsUsed, float partsCost);
void displayVehicleForUpdate(VehicleRecord *record, int index);
void returnToDashboard(int callerDashboard);

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
    char role[] = "Admin";

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

    FILE *adminDb = fopen("users.csv", "r");
    if (adminDb == NULL) {
        adminDb = fopen("users.csv", "w");
        fprintf(adminDb, "Name,Role,Email,Phone,Date Of Birth,Timestamp\n");
        fprintf(adminDb, "%s,%s,%s,%s,%s,%s\n", admin.name, role, admin.email, admin.phone, admin.dateOfBirth, getEventTime());
        fclose(adminDb);   
    } else {
        fclose(adminDb);
        adminDb = fopen("users.csv", "a");
        fprintf(adminDb, "%s,%s,%s,%s,%s,%s\n", admin.name, role, admin.email, admin.phone, admin.dateOfBirth, getEventTime());
        fclose(adminDb);
    }

    FILE *adminPwd = fopen("sysdb.pwd", "rb");
    if (adminPwd == NULL) {
        adminPwd = fopen("sysdb.pwd", "wb");
        PasswordRecord record;
        strcpy(record.email, admin.email);
        strcpy(record.role, role);
        strcpy(record.password, admin.password);
        fwrite(&record, sizeof(PasswordRecord), 1, adminPwd);
        fclose(adminPwd);   
    } else {
        fclose(adminPwd);
        adminPwd = fopen("sysdb.pwd", "ab");
        PasswordRecord record;
        strcpy(record.email, admin.email);
        strcpy(record.role, role);
        strcpy(record.password, admin.password);
        fwrite(&record, sizeof(PasswordRecord), 1, adminPwd);
        fclose(adminPwd);
    }

    clearInputBuffer();
    printf("Press " YELLOW "Enter" RESET " to return to the main menu." HIDE_CURSOR);
    getchar();
    SET_STATE(SHOW_CURSOR);
    mainMenu(); 
}

void registerAsTechnician(void) {
    char role[] = "Technician";

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

    FILE *technicianDb = fopen("users.csv", "r");
    if (technicianDb == NULL) {
        technicianDb = fopen("users.csv", "w");
        fprintf(technicianDb, "Name,Role,Email,Phone,Date Of Birth,Timestamp\n");
        fprintf(technicianDb, "%s,%s,%s,%s,%s,%s\n", technician.name, role, technician.email, technician.phone, technician.dateOfBirth, getEventTime());
        fclose(technicianDb);   
    } 

    else {
        fclose(technicianDb);
        technicianDb = fopen("users.csv", "a");
        fprintf(technicianDb, "%s,%s,%s,%s,%s,%s\n", technician.name, role, technician.email, technician.phone, technician.dateOfBirth, getEventTime());
        fclose(technicianDb);
    }

    FILE *technicianPwd = fopen("sysdb.pwd", "rb");
    if (technicianPwd == NULL) {
        technicianPwd = fopen("sysdb.pwd", "wb");
        PasswordRecord record;
        strcpy(record.email, technician.email);
        strcpy(record.role, role);
        strcpy(record.password, technician.password);
        fwrite(&record, sizeof(PasswordRecord), 1, technicianPwd);
        fclose(technicianPwd);   
    } 

    else {
        fclose(technicianPwd);
        technicianPwd = fopen("sysdb.pwd", "ab");
        PasswordRecord record;
        strcpy(record.email, technician.email);
        strcpy(record.role, role);
        strcpy(record.password, technician.password);
        fwrite(&record, sizeof(PasswordRecord), 1, technicianPwd);
        fclose(technicianPwd);
    }

    clearInputBuffer();
    printf("Press " YELLOW "Enter" RESET " to return to the main menu." HIDE_CURSOR);
    getchar();
    SET_STATE(SHOW_CURSOR);
    mainMenu(); 
}

void registerAsCustomerServiceAgent(void) {
    char role[] = "Customer Service Agent";

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

    FILE *csagentDb = fopen("users.csv", "r");
    if (csagentDb == NULL) {
        csagentDb = fopen("users.csv", "w");
        fprintf(csagentDb, "Name,Role,Email,Phone,Date Of Birth,Timestamp\n");
        fprintf(csagentDb, "%s,%s,%s,%s,%s,%s\n", csagent.name, role, csagent.email, csagent.phone, csagent.dateOfBirth, getEventTime());
        fclose(csagentDb);   
    } 

    else {
        fclose(csagentDb);
        csagentDb = fopen("users.csv", "a");
        fprintf(csagentDb, "%s,%s,%s,%s,%s,%s\n", csagent.name, role, csagent.email, csagent.phone, csagent.dateOfBirth, getEventTime());
        fclose(csagentDb);
    }

    FILE *csagentPwd = fopen("sysdb.pwd", "rb");
    if (csagentPwd == NULL) {
        csagentPwd = fopen("sysdb.pwd", "wb");
        PasswordRecord record;
        strcpy(record.email, csagent.email);
        strcpy(record.role, role);
        strcpy(record.password, csagent.password);
        fwrite(&record, sizeof(PasswordRecord), 1, csagentPwd);
        fclose(csagentPwd);   
    } 

    else {
        fclose(csagentPwd);
        csagentPwd = fopen("sysdb.pwd", "ab");
        PasswordRecord record;
        strcpy(record.email, csagent.email);
        strcpy(record.role, role);
        strcpy(record.password, csagent.password);
        fwrite(&record, sizeof(PasswordRecord), 1, csagentPwd);
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
            loginAsCustomerServiceAgent();
            break;
        case 4:
            loginMenuHelp();
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
            loginMenu();
    }

}

void loginAsAdmin(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+-------------+\n" RESET);
    printf(BRIGHT_BLUE "| Admin Login |\n" RESET);
    printf(BRIGHT_BLUE "+-------------+\n" RESET);

    char email[50];
    char password[50];
    char line[150];
    int loginSuccess = 0;

    printf(YELLOW "Email: " RESET);
    getchar();
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = '\0';

    printf(YELLOW "Password: " RESET);
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    FILE *pwdFile = fopen("sysdb.pwd", "rb");
    if (pwdFile == NULL) {
        printf(RED "No user database found. Please register first.\n" RESET);
        clearInputBuffer();
        printf("Press " YELLOW "Enter" RESET " to return to login menu." HIDE_CURSOR);
        getchar();
        SET_STATE(SHOW_CURSOR);
        loginMenu();
        return;
    }

    PasswordRecord record;
    while (fread(&record, sizeof(PasswordRecord), 1, pwdFile) == 1) {
        if (strcmp(email, record.email) == 0 && strcmp(password, record.password) == 0 && strcmp(record.role, "Admin") == 0) {
            loginSuccess = 1;
            break;
        }
    }
    fclose(pwdFile);

    if (loginSuccess) {
        
        FILE *userFile = fopen("users.csv", "r");
        if (userFile != NULL) {
            char userName[50], userRole[50], userEmail[50], userPhone[15], userDOB[11], timestamp[20];
            

            fgets(line, sizeof(line), userFile);
            
            while (fgets(line, sizeof(line), userFile)) {
                if (sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%s", 
                          userName, userRole, userEmail, userPhone, userDOB, timestamp) == 6) {
                    if (strcmp(email, userEmail) == 0 && strcmp(userRole, "Admin") == 0) {
                        printf(GREEN "Login successful! Welcome, Admin %s\n" RESET, userName);
                        fclose(userFile);
                        
                        clearInputBuffer();
                        printf("Press " YELLOW "Enter" RESET " to continue to dashboard..." HIDE_CURSOR);
                        getchar();
                        SET_STATE(SHOW_CURSOR);
                        adminDashboard();
                        return;
                    }
                }
            }
            fclose(userFile);
        }
        
        printf(RED "Access denied. You are not registered as an Admin.\n" RESET);
    } else {
        printf(RED "Invalid email or password. Please try again.\n" RESET);
    }

    clearInputBuffer();
    printf("Press " YELLOW "Enter" RESET " to return to login menu." HIDE_CURSOR);
    getchar();
    SET_STATE(SHOW_CURSOR);
    loginMenu();
}

void loginAsTechnician(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+------------------+\n" RESET);
    printf(BRIGHT_BLUE "| Technician Login |\n" RESET);
    printf(BRIGHT_BLUE "+------------------+\n" RESET);

    char email[50];
    char password[50];
    char line[150];
    int loginSuccess = 0;

    printf(YELLOW "Email: " RESET);
    getchar(); 
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = '\0'; 

    printf(YELLOW "Password: " RESET);
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    FILE *pwdFile = fopen("sysdb.pwd", "rb");
    if (pwdFile == NULL) {
        printf(RED "No user database found. Please register first.\n" RESET);
        clearInputBuffer();
        printf("Press " YELLOW "Enter" RESET " to return to login menu." HIDE_CURSOR);
        getchar();
        SET_STATE(SHOW_CURSOR);
        loginMenu();
        return;
    }

    PasswordRecord record;
    while (fread(&record, sizeof(PasswordRecord), 1, pwdFile) == 1) {
        if (strcmp(email, record.email) == 0 && strcmp(password, record.password) == 0 && strcmp(record.role, "Technician") == 0) {
            loginSuccess = 1;
            break;
        }
    }
    fclose(pwdFile);

    if (loginSuccess) {
    
        FILE *userFile = fopen("users.csv", "r");
        if (userFile != NULL) {
            char userName[50], userRole[50], userEmail[50], userPhone[15], userDOB[11], timestamp[20];
            
        
            fgets(line, sizeof(line), userFile);
            
            while (fgets(line, sizeof(line), userFile)) {
                if (sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%s", 
                          userName, userRole, userEmail, userPhone, userDOB, timestamp) == 6) {
                    if (strcmp(email, userEmail) == 0 && strcmp(userRole, "Technician") == 0) {
                        printf(GREEN "Login successful! Welcome, Technician %s\n" RESET, userName);
                        fclose(userFile);
                        
                        clearInputBuffer();
                        printf("Press " YELLOW "Enter" RESET " to continue to dashboard..." HIDE_CURSOR);
                        getchar();
                        SET_STATE(SHOW_CURSOR);
                        technicianDashboard();
                        return;
                    }
                }
            }
            fclose(userFile);
        }
        

        printf(RED "Access denied. You are not registered as a Technician.\n" RESET);
    } else {
        printf(RED "Invalid email or password. Please try again.\n" RESET);
    }

    clearInputBuffer();
    printf("Press " YELLOW "Enter" RESET " to return to login menu." HIDE_CURSOR);
    getchar();
    SET_STATE(SHOW_CURSOR);
    loginMenu();
}

void loginAsCustomerServiceAgent(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+------------------------------+\n" RESET);
    printf(BRIGHT_BLUE "| Customer Service Agent Login |\n" RESET);
    printf(BRIGHT_BLUE "+------------------------------+\n" RESET);

    char email[50];
    char password[50];
    char line[150];
    int loginSuccess = 0;

    printf(YELLOW "Email: " RESET);
    getchar(); 
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = '\0'; 

    printf(YELLOW "Password: " RESET);
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    FILE *pwdFile = fopen("sysdb.pwd", "rb");
    if (pwdFile == NULL) {
        printf(RED "No user database found. Please register first.\n" RESET);
        clearInputBuffer();
        printf("Press " YELLOW "Enter" RESET " to return to login menu." HIDE_CURSOR);
        getchar();
        SET_STATE(SHOW_CURSOR);
        loginMenu();
        return;
    }

    PasswordRecord record;
    while (fread(&record, sizeof(PasswordRecord), 1, pwdFile) == 1) {
        if (strcmp(email, record.email) == 0 && strcmp(password, record.password) == 0 && strcmp(record.role, "Customer Service Agent") == 0) {
            loginSuccess = 1;
            break;
        }
    }
    fclose(pwdFile);

    if (loginSuccess) {

        FILE *userFile = fopen("users.csv", "r");
        if (userFile != NULL) {
            char userName[50], userRole[50], userEmail[50], userPhone[15], userDOB[11], timestamp[20];
            
            fgets(line, sizeof(line), userFile);
            
            while (fgets(line, sizeof(line), userFile)) {
                if (sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%s", 
                          userName, userRole, userEmail, userPhone, userDOB, timestamp) == 6) {
                    if (strcmp(email, userEmail) == 0 && strcmp(userRole, "Customer Service Agent") == 0) {
                        printf(GREEN "Login successful! Welcome, Customer Service Agent %s\n" RESET, userName);
                        fclose(userFile);
                
                        clearInputBuffer();
                        printf("Press " YELLOW "Enter" RESET " to continue to dashboard..." HIDE_CURSOR);
                        getchar();
                        SET_STATE(SHOW_CURSOR);
                        customerServiceAgentDashboard();
                        return;
                    }
                }
            }
            fclose(userFile);
        }
        
        printf(RED "Access denied. You are not registered as a Customer Service Agent.\n" RESET);
    } else {
        printf(RED "Invalid email or password. Please try again.\n" RESET);
    }

    clearInputBuffer();
    printf("Press " YELLOW "Enter" RESET " to return to login menu." HIDE_CURSOR);
    getchar();
    SET_STATE(SHOW_CURSOR);
    loginMenu();
}

void loginMenuHelp(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+-----------------+\n" RESET);
    printf(BRIGHT_BLUE "| Login Menu Help |\n" RESET);
    printf(BRIGHT_BLUE "+-----------------+\n" RESET);
    printf(GREEN "1. Admin: Login as an administrator.\n" RESET);
    printf(GREEN "2. Technician: Login as a technician.\n" RESET);
    printf(GREEN "3. Customer Service Agent: Login as a customer service agent.\n" RESET);
    printf(GREEN "4. Help: Shows this menu.\n" RESET);
    printf(GREEN "5. Return to Main Menu.\n" RESET);

    clearInputBuffer();
    printf("Press " YELLOW "Enter" RESET " to return to the login menu." HIDE_CURSOR);
    getchar();
    SET_STATE(SHOW_CURSOR);
    loginMenu();
}

void adminDashboard(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+-----------------+\n" RESET);
    printf(BRIGHT_BLUE "| Admin Dashboard |\n" RESET);
    printf(BRIGHT_BLUE "+-----------------+\n" RESET);

    printf(GREEN "[" YELLOW "1" GREEN "] Active Repairs\n" RESET);
    printf(GREEN "[" YELLOW "2" GREEN "] View Repair History\n" RESET);
    printf(GREEN "[" YELLOW "3" GREEN "] Update Repair Status\n" RESET);
    printf(GREEN "[" YELLOW "4" GREEN "] Manage Pricing\n" RESET);
    printf(GREEN "[" YELLOW "5" GREEN "] Logout\n" RESET);
    printf(YELLOW "Enter your choice: " RESET);
    
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            viewActiveRepairs();
            break;
        case 2:
            viewRepairHistory(ADMIN_DASHBOARD);
            break;
        case 3:
            updateCarRepairStatus(ADMIN_DASHBOARD);
            break;
        case 4:
            managePricing();
            break;
        case 5:
            printf(GREEN "Logged out successfully.\n" RESET);
            clearInputBuffer();
            printf("Press " YELLOW "Enter" RESET " to return to main menu." HIDE_CURSOR);
            getchar();
            SET_STATE(SHOW_CURSOR);
            mainMenu();
            return;
        default:
            printf(RED "Invalid input. Please try again.\n" RESET);
            clearInputBuffer();
            printf("Press " YELLOW "Enter" RESET " to continue..." HIDE_CURSOR);
            getchar();
            SET_STATE(SHOW_CURSOR);
            adminDashboard();
    }

}

void technicianDashboard(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+----------------------+\n" RESET);
    printf(BRIGHT_BLUE "| Technician Dashboard |\n" RESET);
    printf(BRIGHT_BLUE "+----------------------+\n" RESET);

    printf(GREEN "[" YELLOW "1" GREEN "] View Service Requests\n" RESET);
    printf(GREEN "[" YELLOW "2" GREEN "] Update Repair Status\n" RESET);
    printf(GREEN "[" YELLOW "3" GREEN "] View Repair History\n" RESET);
    printf(GREEN "[" YELLOW "4" GREEN "] Logout\n" RESET);
    printf(YELLOW "Enter your choice: " RESET);
    
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            viewServiceRequests();
            break;
        case 2:
            updateCarRepairStatus(TECHNICIAN_DASHBOARD);
            break;
        case 3:
            viewRepairHistory(TECHNICIAN_DASHBOARD);
            break;
        case 4:
            printf(GREEN "Logged out successfully.\n" RESET);
            clearInputBuffer();
            printf("Press " YELLOW "Enter" RESET " to return to main menu." HIDE_CURSOR);
            getchar();
            SET_STATE(SHOW_CURSOR);
            mainMenu();
            return;
        default:
            printf(RED "Invalid input. Please try again.\n" RESET);
            clearInputBuffer();
            printf("Press " YELLOW "Enter" RESET " to continue..." HIDE_CURSOR);
            getchar();
            SET_STATE(SHOW_CURSOR);
            technicianDashboard();
        
    }
  
}

void customerServiceAgentDashboard(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+----------------------------------+\n" RESET);
    printf(BRIGHT_BLUE "| Customer Service Agent Dashboard |\n" RESET);
    printf(BRIGHT_BLUE "+----------------------------------+\n" RESET);
    
    printf(GREEN "[" YELLOW "1" GREEN "] View Repair History\n" RESET);
    printf(GREEN "[" YELLOW "2" GREEN "] Log Vehicle\n" RESET);
    printf(GREEN "[" YELLOW "3" GREEN "] Generate Bill\n" RESET);
    printf(GREEN "[" YELLOW "4" GREEN "] Logout\n" RESET);
    printf(YELLOW "Enter your choice: " RESET);
    
    int choice;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            viewRepairHistory(CS_AGENT_DASHBOARD);
            break;
        case 2:
            logVehicle();
            break;
        case 3:
            generateBill();
            break;
        case 4:
            printf(GREEN "Logged out successfully.\n" RESET);
            clearInputBuffer();
            printf("Press " YELLOW "Enter" RESET " to return to main menu." HIDE_CURSOR);
            getchar();
            SET_STATE(SHOW_CURSOR);
            mainMenu();
            return;
        default:
            printf(RED "Invalid input. Please try again.\n" RESET);
            clearInputBuffer();
            printf("Press " YELLOW "Enter" RESET " to continue..." HIDE_CURSOR);
            getchar();
            SET_STATE(SHOW_CURSOR);
            customerServiceAgentDashboard();
    }

}

void viewActiveRepairs(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+---------------------+\n" RESET);
    printf(BRIGHT_BLUE "| Active Repairs List |\n" RESET);
    printf(BRIGHT_BLUE "+---------------------+\n" RESET);

    FILE *vehicleDb = fopen("vehicles.dat", "rb");
    if (vehicleDb == NULL) {
        printf(RED "No vehicle records found. No active repairs available.\n" RESET);
    } else {
        VehicleRecord record;
        int recordCount = 0;
        
        printf(CYAN "%-15s %-15s %-12s %-20s %-10s %-20s\n" RESET, 
               "Vehicle", "Customer", "Phone", "Service Type", "Urgency", "Status");
        printf(CYAN "%-15s %-15s %-12s %-20s %-10s %-20s\n" RESET,
               "-------", "--------", "-----", "------------", "-------", "------");
        
        while (fread(&record, sizeof(VehicleRecord), 1, vehicleDb) == 1) {
            if (strcmp(record.status, "Pending") == 0 || strcmp(record.status, "In Progress") == 0) {
                char vehicleInfo[30];
                snprintf(vehicleInfo, sizeof(vehicleInfo), "%s %s", record.vehicleMake, record.vehicleModel);
                
                printf("%-15s %-15s %-12s %-20s %-10s %-20s\n",
                       vehicleInfo, record.customerName, record.customerPhone, record.serviceType, record.urgencyLevel, record.status);
                recordCount++;
            }
        }
        fclose(vehicleDb);
        
        if (recordCount == 0) {
            printf(YELLOW "No active repairs found.\n" RESET);
        } else {
            printf(GREEN "\nTotal active repairs: %d\n" RESET, recordCount);
        }
    }

    clearInputBuffer();
    printf("Press " YELLOW "Enter" RESET " to return to the dashboard." HIDE_CURSOR);
    getchar();
    SET_STATE(SHOW_CURSOR);
    adminDashboard();
}

void viewRepairHistory(int callerDashboard) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+------------------------+\n" RESET);
    printf(BRIGHT_BLUE "| Vehicle Repair History |\n" RESET);
    printf(BRIGHT_BLUE "+------------------------+\n" RESET);

    char licensePlate[20];
    printf(YELLOW "Enter car license plate number: " RESET);
    clearInputBuffer();
    fgets(licensePlate, sizeof(licensePlate), stdin);
    licensePlate[strcspn(licensePlate, "\n")] = '\0';

    if (strlen(licensePlate) == 0) {
        printf(RED "Invalid license plate number.\n" RESET);
        clearInputBuffer();
        printf("Press " YELLOW "Enter" RESET " to return to the dashboard." HIDE_CURSOR);
        getchar();
        SET_STATE(SHOW_CURSOR);
        
        switch(callerDashboard) {
            case ADMIN_DASHBOARD:
                adminDashboard();
                break;
            case TECHNICIAN_DASHBOARD:
                technicianDashboard();
                break;
            case CS_AGENT_DASHBOARD:
                customerServiceAgentDashboard();
                break;
            default:
                mainMenu();
                break;
        }
        return;
    }

    FILE *vehicleDb = fopen("vehicles.dat", "rb");
    if (vehicleDb == NULL) {
        printf(RED "No vehicle records found. No repair history available.\n" RESET);
    } else {
        VehicleRecord record;
        int recordCount = 0;
        int vehicleFound = 0;
        char vehicleInfo[100] = "";
        char customerInfo[100] = "";
        
        while (fread(&record, sizeof(VehicleRecord), 1, vehicleDb) == 1) {
            if (strcmp(record.licensePlate, licensePlate) == 0) {
                vehicleFound = 1;
                if (strlen(vehicleInfo) == 0) {
                    snprintf(vehicleInfo, sizeof(vehicleInfo), "%s %s %s (%s)", 
                             record.vehicleMake, record.vehicleModel, record.vehicleYear, record.vehicleColor);
                    snprintf(customerInfo, sizeof(customerInfo), "%s (%s)", 
                             record.customerName, record.customerPhone);
                }
                break;
            }
        }
        
        if (!vehicleFound) {
            printf(RED "No vehicle found with license plate: %s\n" RESET, licensePlate);
            fclose(vehicleDb);
        } else {
            printf(BRIGHT_GREEN "\n=== VEHICLE INFORMATION ===\n" RESET);
            printf(CYAN "License Plate: %s\n" RESET, licensePlate);
            printf(CYAN "Vehicle: %s\n" RESET, vehicleInfo);
            printf(CYAN "Owner: %s\n" RESET, customerInfo);
            
            rewind(vehicleDb);
            printf(BRIGHT_GREEN "\n=== SERVICE HISTORY ===\n" RESET);
            printf(CYAN "%-12s %-20s %-15s %-12s %-20s %-10s\n" RESET, 
                   "Date", "Service Type", "Status", "Urgency", "Parts Used", "Cost");
            printf(CYAN "%-12s %-20s %-15s %-12s %-20s %-10s\n" RESET,
                   "----", "------------", "------", "--------", "----------", "----");
            
            while (fread(&record, sizeof(VehicleRecord), 1, vehicleDb) == 1) {
                if (strcmp(record.licensePlate, licensePlate) == 0) {
                    char date[11];
                    strncpy(date, record.timestamp, 10);
                    date[10] = '\0';
                    
                    char partsInfo[21];
                    if (strlen(record.partsUsed) > 0) {
                        if (strlen(record.partsUsed) > 20) {
                            strncpy(partsInfo, record.partsUsed, 17);
                            partsInfo[17] = '.';
                            partsInfo[18] = '.';
                            partsInfo[19] = '.';
                            partsInfo[20] = '\0';
                        } else {
                            strcpy(partsInfo, record.partsUsed);
                        }
                    } else {
                        strcpy(partsInfo, "None");
                    }
                    
                    char costStr[11];
                    if (record.partsCost > 0) {
                        snprintf(costStr, sizeof(costStr), "TK%.2f", record.partsCost);
                    } else {
                        strcpy(costStr, "TK0.00");
                    }

                    printf("%-12s %-20s %-15s %-12s %-20s %-10s\n",
                           date, record.serviceType, record.status, record.urgencyLevel, partsInfo, costStr);
                    
                    if (strlen(record.problemDescription) > 0) {
                        printf(BRIGHT_BLACK "  Problem: %s\n" RESET, record.problemDescription);
                    }
                    if (strlen(record.notes) > 0) {
                        printf(BRIGHT_BLACK "  Notes: %s\n" RESET, record.notes);
                    }
                    if (strlen(record.lastUpdated) > 0) {
                        printf(BRIGHT_BLACK "  Last Updated: %s\n" RESET, record.lastUpdated);
                    }
                    printf("\n");
                    recordCount++;
                }
            }
            fclose(vehicleDb);
            
            if (recordCount == 0) {
                printf(YELLOW "No service history found for this vehicle.\n" RESET);
            } else {
                printf(GREEN "Total service records: %d\n" RESET, recordCount);
            }
        }
    }

    clearInputBuffer();
    printf("Press " YELLOW "Enter" RESET " to return to the dashboard." HIDE_CURSOR);
    getchar();
    SET_STATE(SHOW_CURSOR);
    
    switch(callerDashboard) {
        case ADMIN_DASHBOARD:
            adminDashboard();
            break;
        case TECHNICIAN_DASHBOARD:
            technicianDashboard();
            break;
        case CS_AGENT_DASHBOARD:
            customerServiceAgentDashboard();
            break;
        default:
            mainMenu();
            break;
    }
}

void updateCarRepairStatus(int callerDashboard) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+--------------------------+\n" RESET);
    printf(BRIGHT_BLUE "| Update Car Repair Status |\n" RESET);
    printf(BRIGHT_BLUE "+--------------------------+\n" RESET);

    FILE *fp = fopen("vehicles.dat", "rb");
    if (!fp) {
        printf(RED "No vehicle records found.\n" RESET);
        clearInputBuffer();
        printf("Press " YELLOW "Enter" RESET " to return to the dashboard." HIDE_CURSOR);
        getchar();
        SET_STATE(SHOW_CURSOR);
        returnToDashboard(callerDashboard);
        return;
    }

    VehicleRecord records[1000];
    int count = 0;
    VehicleRecord temp;
    
    printf(CYAN "Available vehicles for status update:\n" RESET);
    printf(CYAN "%-4s %-15s %-15s %-20s %-12s %-15s\n" RESET, 
           "ID", "License Plate", "Vehicle", "Customer", "Status", "Service Type");
    printf(CYAN "%-4s %-15s %-15s %-20s %-12s %-15s\n" RESET,
           "--", "-------------", "-------", "--------", "------", "------------");
    
    while (fread(&temp, sizeof(VehicleRecord), 1, fp) == 1 && count < 1000) {
        if (strcmp(temp.status, "Completed") != 0) {
            records[count] = temp;
            char vehicleInfo[100];
            snprintf(vehicleInfo, sizeof(vehicleInfo), "%s %s", temp.vehicleMake, temp.vehicleModel);
            printf("%-4d %-15s %-15s %-20s %-12s %-15s\n", 
                   count + 1, temp.licensePlate, vehicleInfo, temp.customerName, 
                   temp.status, temp.serviceType);
            count++;
        }
    }
    fclose(fp);

    if (count == 0) {
        printf(YELLOW "No vehicles available for status update.\n" RESET);
        clearInputBuffer();
        printf("Press " YELLOW "Enter" RESET " to return to the dashboard." HIDE_CURSOR);
        getchar();
        SET_STATE(SHOW_CURSOR);
        returnToDashboard(callerDashboard);
        return;
    }

    printf(YELLOW "\nEnter vehicle ID to update (1-%d) or 0 to cancel: " RESET, count);
    int choice;
    if (scanf("%d", &choice) != 1) {
        printf(RED "Invalid input. Please enter a number.\n" RESET);
        clearInputBuffer();
        printf("Press " YELLOW "Enter" RESET " to return to the dashboard." HIDE_CURSOR);
        getchar();
        SET_STATE(SHOW_CURSOR);
        returnToDashboard(callerDashboard);
        return;
    }

    if (choice == 0) {
        clearInputBuffer();
        returnToDashboard(callerDashboard);
        return;
    }

    if (choice < 1 || choice > count) {
        printf(RED "Invalid selection.\n" RESET);
        clearInputBuffer();
        printf("Press " YELLOW "Enter" RESET " to return to the dashboard." HIDE_CURSOR);
        getchar();
        SET_STATE(SHOW_CURSOR);
        returnToDashboard(callerDashboard);
        return;
    }

    VehicleRecord *selected = &records[choice - 1];
    
    if (selected == NULL || choice - 1 < 0 || choice - 1 >= count) {
        printf(RED "Error: Invalid vehicle selection.\n" RESET);
        clearInputBuffer();
        printf("Press " YELLOW "Enter" RESET " to return to the dashboard." HIDE_CURSOR);
        getchar();
        SET_STATE(SHOW_CURSOR);
        returnToDashboard(callerDashboard);
        return;
    }
    
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+--------------------------+\n" RESET);
    printf(BRIGHT_BLUE "| Update Car Repair Status |\n" RESET);
    printf(BRIGHT_BLUE "+--------------------------+\n" RESET);
    
    displayVehicleForUpdate(selected, choice - 1);

    printf(YELLOW "\nAvailable status options:\n" RESET);
    printf(GREEN "[1]" RESET " Pending\n");
    printf(GREEN "[2]" RESET " In Progress\n");
    printf(GREEN "[3]" RESET " Completed\n");
    printf(GREEN "[4]" RESET " On Hold\n");
    printf(YELLOW "Enter new status (1-4): " RESET);
    
    int statusChoice;
    if (scanf("%d", &statusChoice) != 1) {
        printf(RED "Invalid input. Please enter a number.\n" RESET);
        clearInputBuffer();
        printf("Press " YELLOW "Enter" RESET " to return to the dashboard." HIDE_CURSOR);
        getchar();
        SET_STATE(SHOW_CURSOR);
        returnToDashboard(callerDashboard);
        return;
    }
    
    char newStatus[20];
    switch (statusChoice) {
        case 1: 
            strcpy(newStatus, "Pending"); 
            break;
        case 2: 
            strcpy(newStatus, "In Progress"); 
            break;
        case 3: 
            strcpy(newStatus, "Completed"); 
            break;
        case 4: 
            strcpy(newStatus, "On Hold"); 
            break;
        default:
            printf(RED "Invalid status selection.\n" RESET);
            clearInputBuffer();
            printf("Press " YELLOW "Enter" RESET " to return to the dashboard." HIDE_CURSOR);
            getchar();
            SET_STATE(SHOW_CURSOR);
            returnToDashboard(callerDashboard);
            return;
    }

    clearInputBuffer();
    char notes[1000];
    printf(YELLOW "Add notes (optional, press Enter to skip): " RESET);
    fgets(notes, sizeof(notes), stdin);
    notes[strcspn(notes, "\n")] = '\0';

    char partsUsed[500];
    printf(YELLOW "Parts used (optional, press Enter to skip): " RESET);
    fgets(partsUsed, sizeof(partsUsed), stdin);
    partsUsed[strcspn(partsUsed, "\n")] = '\0';

    float partsCost = 0.0;
    if (strlen(partsUsed) > 0) {
        printf(YELLOW "Parts cost (enter 0 if no cost): TK" RESET);
        if (scanf("%f", &partsCost) != 1) {
            printf(RED "Invalid input for parts cost. Setting to 0.\n" RESET);
            partsCost = 0.0;
        }
        clearInputBuffer();
    }

    if (updateVehicleRecord(selected->licensePlate, newStatus, notes, partsUsed, partsCost)) {
        printf(GREEN "\nVehicle status updated successfully!\n" RESET);
        printf(CYAN "License Plate: %s\n" RESET, selected->licensePlate);
        printf(CYAN "New Status: %s\n" RESET, newStatus);
        if (strlen(notes) > 0) {
            printf(CYAN "Notes: %s\n" RESET, notes);
        }
        if (strlen(partsUsed) > 0) {
            printf(CYAN "Parts Used: %s\n" RESET, partsUsed);
            printf(CYAN "Parts Cost: TK%.2f\n" RESET, partsCost);
        }
    } else {
        printf(RED "Failed to update vehicle status.\n" RESET);
    }

    clearInputBuffer();
    printf("Press " YELLOW "Enter" RESET " to return to the dashboard." HIDE_CURSOR);
    getchar();
    SET_STATE(SHOW_CURSOR);
    returnToDashboard(callerDashboard);
}

void viewServiceRequests(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+-----------------------+\n" RESET);
    printf(BRIGHT_BLUE "| View Service Requests |\n" RESET);
    printf(BRIGHT_BLUE "+-----------------------+\n" RESET);

    FILE *fp = fopen("vehicles.dat", "rb");
    if (!fp) {
        printf(RED "No service requests found.\n" RESET);
        clearInputBuffer();
        printf("Press " YELLOW "Enter" RESET " to return to the dashboard." HIDE_CURSOR);
        getchar();
        SET_STATE(SHOW_CURSOR);
        technicianDashboard();
        return;
    }

    VehicleRecord records[100];
    int count = 0;
    VehicleRecord temp;
    
    printf(CYAN "Current service requests:\n" RESET);
    printf(CYAN "%-4s %-15s %-15s %-20s %-12s %-10s %-15s\n" RESET, 
           "ID", "License Plate", "Vehicle", "Customer", "Status", "Urgency", "Service Type");
    printf(CYAN "%-4s %-15s %-15s %-20s %-12s %-10s %-15s\n" RESET,
           "--", "-------------", "-------", "--------", "------", "-------", "------------");
    
    while (fread(&temp, sizeof(VehicleRecord), 1, fp) == 1 && count < 100) {
        if (strcmp(temp.status, "Completed") != 0) {
            records[count] = temp;
            char vehicleInfo[30];
            snprintf(vehicleInfo, sizeof(vehicleInfo), "%s %s", temp.vehicleMake, temp.vehicleModel);
            printf("%-4d %-15s %-15s %-20s %-12s %-10s %-15s\n", 
                   count + 1, temp.licensePlate, vehicleInfo, temp.customerName, 
                   temp.status, temp.urgencyLevel, temp.serviceType);
            count++;
        }
    }
    fclose(fp);

    if (count == 0) {
        printf(YELLOW "No pending service requests found.\n" RESET);
    } else {
        printf(GREEN "\nTotal service requests: %d\n" RESET, count);
        
        printf(YELLOW "\nEnter request ID to view details (1-%d) or 0 to return: " RESET, count);
        int choice;
        scanf("%d", &choice);
        
        if (choice >= 1 && choice <= count) {
            system(CLEAR_SCREEN);
            printf(BRIGHT_BLUE "+------------------------+\n" RESET);
            printf(BRIGHT_BLUE "| Service Request Detail |\n" RESET);
            printf(BRIGHT_BLUE "+------------------------+\n" RESET);
            
            VehicleRecord *selected = &records[choice - 1];
            
            printf(CYAN "License Plate: %s\n" RESET, selected->licensePlate);
            printf(CYAN "Vehicle: %s %s (%s)\n" RESET, selected->vehicleMake, selected->vehicleModel, selected->vehicleYear);
            printf(CYAN "Color: %s\n" RESET, selected->vehicleColor);
            printf(CYAN "Mileage: %s\n" RESET, selected->mileage);
            printf(CYAN "Customer: %s (%s)\n" RESET, selected->customerName, selected->customerPhone);
            printf(CYAN "Service Type: %s\n" RESET, selected->serviceType);
            printf(CYAN "Problem Description:\n" RESET);
            printf("%s\n", selected->problemDescription);
            printf(CYAN "Urgency Level: %s\n" RESET, selected->urgencyLevel);
            printf(CYAN "Current Status: %s\n" RESET, selected->status);
            printf(CYAN "Created: %s\n" RESET, selected->timestamp);
            
            if (strlen(selected->notes) > 0) {
                printf(CYAN "Notes: %s\n" RESET, selected->notes);
            }
            
            if (strlen(selected->partsUsed) > 0) {
                printf(CYAN "Parts Used: %s\n" RESET, selected->partsUsed);
                printf(CYAN "Parts Cost: TK%.2f\n" RESET, selected->partsCost);
            }
            
            if (strlen(selected->lastUpdated) > 0) {
                printf(CYAN "Last Updated: %s\n" RESET, selected->lastUpdated);
            }
            
            printf(GREEN "\n[1] Update Status\n" RESET);
            printf(GREEN "[2] Return to Service Requests\n" RESET);
            printf(YELLOW "Enter your choice: " RESET);
            
            int detailChoice;
            scanf("%d", &detailChoice);
            
            if (detailChoice == 1) {
                updateCarRepairStatus(TECHNICIAN_DASHBOARD);
                return;
            }
            
            viewServiceRequests();
            return;
        }
    }

    clearInputBuffer();
    printf("\nPress " YELLOW "Enter" RESET " to return to the dashboard." HIDE_CURSOR);
    getchar();
    SET_STATE(SHOW_CURSOR);
    technicianDashboard();
}

void logVehicle(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+-------------+\n" RESET);
    printf(BRIGHT_BLUE "| Log Vehicle |\n" RESET);
    printf(BRIGHT_BLUE "+-------------+\n" RESET);

    VehicleRecord record;
    memset(&record, 0, sizeof(record));

    printf(YELLOW "License Plate: " RESET);
    clearInputBuffer();
    fgets(record.licensePlate, sizeof(record.licensePlate), stdin);
    record.licensePlate[strcspn(record.licensePlate, "\n")] = '\0';

    VehicleRecord previous;
    int hasPrevious = findLatestVehicleRecordByPlate(record.licensePlate, &previous);

    if (hasPrevious) {
        strcpy(record.vehicleMake, previous.vehicleMake);
        strcpy(record.vehicleModel, previous.vehicleModel);
        strcpy(record.vehicleYear, previous.vehicleYear);
        strcpy(record.vehicleColor, previous.vehicleColor);
        strcpy(record.mileage, previous.mileage);
        strcpy(record.customerName, previous.customerName);
        strcpy(record.customerPhone, previous.customerPhone);
        printf(GREEN "\nPrevious record found for this license plate.\n" RESET);
        printf(CYAN "Make/Model: %s %s | Year: %s | Color: %s | Mileage(last): %s\n" RESET,
               record.vehicleMake, record.vehicleModel, record.vehicleYear, record.vehicleColor, record.mileage);
        printf(CYAN "Customer: %s | Phone: %s\n" RESET, record.customerName, record.customerPhone);
        printf(YELLOW "Reuse previous details? (Y/n): " RESET);
        char ans[8]; fgets(ans, sizeof(ans), stdin);
        if (ans[0] == 'n' || ans[0] == 'N') {
            hasPrevious = 0;
        }
    }

    if (!hasPrevious) {
        printf(YELLOW "Vehicle Make: " RESET);
        fgets(record.vehicleMake, sizeof(record.vehicleMake), stdin);
        record.vehicleMake[strcspn(record.vehicleMake, "\n")] = '\0';
        
        printf(YELLOW "Vehicle Model: " RESET);
        fgets(record.vehicleModel, sizeof(record.vehicleModel), stdin);
        record.vehicleModel[strcspn(record.vehicleModel, "\n")] = '\0';
        
        printf(YELLOW "Vehicle Year: " RESET);
        fgets(record.vehicleYear, sizeof(record.vehicleYear), stdin);
        record.vehicleYear[strcspn(record.vehicleYear, "\n")] = '\0';
        
        printf(YELLOW "Vehicle Color: " RESET);
        fgets(record.vehicleColor, sizeof(record.vehicleColor), stdin);
        record.vehicleColor[strcspn(record.vehicleColor, "\n")] = '\0';
        
        printf(YELLOW "Mileage: " RESET);
        fgets(record.mileage, sizeof(record.mileage), stdin);
        record.mileage[strcspn(record.mileage, "\n")] = '\0';

        printf(YELLOW "Customer Name: " RESET);
        fgets(record.customerName, sizeof(record.customerName), stdin);
        record.customerName[strcspn(record.customerName, "\n")] = '\0';
        
        printf(YELLOW "Customer Phone: " RESET);
        fgets(record.customerPhone, sizeof(record.customerPhone), stdin);
        record.customerPhone[strcspn(record.customerPhone, "\n")] = '\0';
    } 
    else {
        printf(YELLOW "Update mileage (leave blank to keep %s): " RESET, record.mileage);
        char buf[32];
        fgets(buf, sizeof(buf), stdin);
        if (buf[0] != '\n') {
            buf[strcspn(buf, "\n")] = '\0';
            strncpy(record.mileage, buf, sizeof(record.mileage));
        }
    }

    printf(YELLOW "Service Type (e.g., Oil Change, Brake Repair, Engine Check): " RESET);
    fgets(record.serviceType, sizeof(record.serviceType), stdin); record.serviceType[strcspn(record.serviceType, "\n")] = '\0';
    printf(YELLOW "Problem Description: " RESET);
    fgets(record.problemDescription, sizeof(record.problemDescription), stdin); record.problemDescription[strcspn(record.problemDescription, "\n")] = '\0';
    printf(YELLOW "Urgency Level (Low/Medium/High/Emergency): " RESET);
    fgets(record.urgencyLevel, sizeof(record.urgencyLevel), stdin); record.urgencyLevel[strcspn(record.urgencyLevel, "\n")] = '\0';

    strcpy(record.status, "Pending");
    strncpy(record.timestamp, getEventTime(), sizeof(record.timestamp));
    record.timestamp[sizeof(record.timestamp)-1] = '\0';

    FILE *fp = fopen("vehicles.dat", "ab");
    if (!fp) {
        printf(RED "Failed to open vehicle database file." RESET "\n");
    } else {
        fwrite(&record, sizeof(VehicleRecord), 1, fp);
        fclose(fp);
        printf(GREEN "\nVehicle logged successfully!\n" RESET);
        printf(CYAN "Status: %s\n" RESET, record.status);
    }

    clearInputBuffer();
    printf("\nPress " YELLOW "Enter" RESET " to return to the dashboard." HIDE_CURSOR);
    getchar();
    SET_STATE(SHOW_CURSOR);
    customerServiceAgentDashboard();
}

int findLatestVehicleRecordByPlate(const char *plate, VehicleRecord *outRecord) {
    FILE *fp = fopen("vehicles.dat", "rb");
    if (!fp) return 0;
    VehicleRecord temp;
    int found = 0;
    while (fread(&temp, sizeof(VehicleRecord), 1, fp) == 1) {
        if (strcmp(temp.licensePlate, plate) == 0) {
            *outRecord = temp; 
            found = 1;
        }
    }
    fclose(fp);
    return found;
}

void displayVehicleForUpdate(VehicleRecord *record, int index) {
    printf(CYAN "\nSelected Vehicle Details:\n" RESET);
    printf(CYAN "License Plate: %s\n" RESET, record->licensePlate);
    printf(CYAN "Vehicle: %s %s (%s)\n" RESET, record->vehicleMake, record->vehicleModel, record->vehicleYear);
    printf(CYAN "Customer: %s (%s)\n" RESET, record->customerName, record->customerPhone);
    printf(CYAN "Service Type: %s\n" RESET, record->serviceType);
    printf(CYAN "Current Status: %s\n" RESET, record->status);
    printf(CYAN "Urgency: %s\n" RESET, record->urgencyLevel);
    
    if (strlen(record->notes) > 0) {
        printf(CYAN "Current Notes: %s\n" RESET, record->notes);
    }
    
    if (strlen(record->partsUsed) > 0) {
        printf(CYAN "Parts Used: %s\n" RESET, record->partsUsed);
        printf(CYAN "Parts Cost: TK%.2f\n" RESET, record->partsCost);
    }
    
    printf(CYAN "Problem: %s\n" RESET, record->problemDescription);
    printf(CYAN "Created: %s\n" RESET, record->timestamp);
    
    if (strlen(record->lastUpdated) > 0) {
        printf(CYAN "Last Updated: %s\n" RESET, record->lastUpdated);
    }
}

int updateVehicleRecord(const char *licensePlate, const char *newStatus, const char *notes, const char *partsUsed, float partsCost) {
    FILE *fp = fopen("vehicles.dat", "rb");
    if (!fp) return 0;
    
    VehicleRecord records[1000];
    int count = 0;
    int updated = 0;
    
    while (fread(&records[count], sizeof(VehicleRecord), 1, fp) == 1 && count < 1000) {
        count++;
    }
    fclose(fp);
    
    for (int i = count - 1; i >= 0; i--) {
        if (strcmp(records[i].licensePlate, licensePlate) == 0) {
            strcpy(records[i].status, newStatus);
            strcpy(records[i].lastUpdated, getEventTime());
            
            if (strlen(notes) > 0) {
                if (strlen(records[i].notes) > 0) {
                    size_t availableSpace = sizeof(records[i].notes) - strlen(records[i].notes) - 1;
                    if (availableSpace > 3 + strlen(notes)) {
                        strcat(records[i].notes, " | ");
                        strncat(records[i].notes, notes, availableSpace - 3);
                    }
                } else {
                    strncpy(records[i].notes, notes, sizeof(records[i].notes) - 1);
                    records[i].notes[sizeof(records[i].notes) - 1] = '\0';
                }
            }
            
            if (strlen(partsUsed) > 0) {
                if (strlen(records[i].partsUsed) > 0) {
                    size_t availableSpace = sizeof(records[i].partsUsed) - strlen(records[i].partsUsed) - 1;
                    if (availableSpace > 2 + strlen(partsUsed)) {
                        strcat(records[i].partsUsed, ", ");
                        strncat(records[i].partsUsed, partsUsed, availableSpace - 2);
                    }
                } else {
                    strncpy(records[i].partsUsed, partsUsed, sizeof(records[i].partsUsed) - 1);
                    records[i].partsUsed[sizeof(records[i].partsUsed) - 1] = '\0';
                }
                records[i].partsCost += partsCost;
            }
            
            updated = 1;
            break;
        }
    }
    
    if (updated) {
        fp = fopen("vehicles.dat", "wb");
        if (fp) {
            fwrite(records, sizeof(VehicleRecord), count, fp);
            fclose(fp);
            return 1;
        }
    }
    
    return 0;
}

void generateBill(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+---------------+\n" RESET);
    printf(BRIGHT_BLUE "| Generate Bill |\n" RESET);
    printf(BRIGHT_BLUE "+---------------+\n" RESET);

    char licensePlate[20];
    printf(YELLOW "Enter License Plate: " RESET);
    clearInputBuffer();
    fgets(licensePlate, sizeof(licensePlate), stdin);
    licensePlate[strcspn(licensePlate, "\n")] = '\0';

    FILE *fp = fopen("vehicles.dat", "rb");
    if (!fp) {
        printf(RED "No vehicle records found.\n" RESET);
        clearInputBuffer();
        printf("Press " YELLOW "Enter" RESET " to return to the dashboard." HIDE_CURSOR);
        getchar();
        SET_STATE(SHOW_CURSOR);
        customerServiceAgentDashboard();
        return;
    }

    VehicleRecord record;
    VehicleRecord latestRecord;
    int found = 0;
    
    while (fread(&record, sizeof(VehicleRecord), 1, fp) == 1) {
        if (strcmp(record.licensePlate, licensePlate) == 0) {
            latestRecord = record;
            found = 1;
        }
    }
    fclose(fp);

    if (!found) {
        printf(RED "No records found for license plate: %s\n" RESET, licensePlate);
        clearInputBuffer();
        printf("Press " YELLOW "Enter" RESET " to return to the dashboard." HIDE_CURSOR);
        getchar();
        SET_STATE(SHOW_CURSOR);
        customerServiceAgentDashboard();
        return;
    }

    float baseFee = getServicePrice(latestRecord.serviceType);

    float partsCost = latestRecord.partsCost;
    float subtotal = baseFee + partsCost;
    float taxRate = getTaxRate();
    float taxAmount = subtotal * taxRate;
    float totalAmount = subtotal + taxAmount;

    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+------------------------------------------------+\n" RESET);
    printf(BRIGHT_BLUE "|                 SERVICE BILL                   |\n" RESET);
    printf(BRIGHT_BLUE "+------------------------------------------------+\n" RESET);
    printf(CYAN "Bill Generated: %s\n" RESET, getEventTime());
    printf(CYAN "License Plate: %s\n" RESET, latestRecord.licensePlate);
    printf(CYAN "Vehicle: %s %s (%s)\n" RESET, latestRecord.vehicleMake, latestRecord.vehicleModel, latestRecord.vehicleYear);
    printf(CYAN "Customer: %s\n" RESET, latestRecord.customerName);
    printf(CYAN "Phone: %s\n" RESET, latestRecord.customerPhone);
    printf(CYAN "Service Date: %s\n" RESET, latestRecord.timestamp);
    printf(CYAN "Current Status: %s\n" RESET, latestRecord.status);

    printf(BRIGHT_BLUE "+------------------------------------------------+\n" RESET);
    printf(CYAN "Service Type: %s\n" RESET, latestRecord.serviceType);
    
    if (strlen(latestRecord.problemDescription) > 0) {
        printf(CYAN "Problem Description: %s\n" RESET, latestRecord.problemDescription);
    }
    
    if (strlen(latestRecord.partsUsed) > 0) {
        printf(CYAN "Parts Used: %s\n" RESET, latestRecord.partsUsed);
    }
    
    if (strlen(latestRecord.notes) > 0) {
        printf(CYAN "Notes: %s\n" RESET, latestRecord.notes);
    }

    printf(BRIGHT_BLUE "+------------------------------------------------+\n" RESET);
    printf(YELLOW "COST BREAKDOWN:\n" RESET);
    printf(CYAN "Base Service Fee:        TK%8.2f\n" RESET, baseFee);
    printf(CYAN "Parts Cost:              TK%8.2f\n" RESET, partsCost);
    printf(CYAN "                         ----------\n" RESET);
    printf(CYAN "Subtotal:                TK%8.2f\n" RESET, subtotal);
    printf(CYAN "Tax (%.1f%%):              TK%8.2f\n" RESET, taxRate * 100, taxAmount);
    printf(CYAN "                         ----------\n" RESET);
    printf(GREEN "TOTAL AMOUNT:            TK%8.2f\n" RESET, totalAmount);
    printf(BRIGHT_BLUE "+------------------------------------------------+\n" RESET);

    FILE *billFile = fopen("bills.txt", "a");
    if (billFile != NULL) {
        fprintf(billFile, "+--------------+\n");
        fprintf(billFile, "| SERVICE BILL |\n");
        fprintf(billFile, "+--------------+\n");
        fprintf(billFile, "Date: %s\n", getEventTime());
        fprintf(billFile, "License Plate: %s\n", latestRecord.licensePlate);
        fprintf(billFile, "Vehicle: %s %s (%s)\n", latestRecord.vehicleMake, latestRecord.vehicleModel, latestRecord.vehicleYear);
        fprintf(billFile, "Customer: %s (%s)\n", latestRecord.customerName, latestRecord.customerPhone);
        fprintf(billFile, "Service: %s\n", latestRecord.serviceType);
        fprintf(billFile, "Base Fee: TK%.2f\n", baseFee);
        fprintf(billFile, "Parts Cost: TK%.2f\n", partsCost);
        fprintf(billFile, "Tax (%.1f%%): TK%.2f\n", taxRate * 100, taxAmount);
        fprintf(billFile, "Total: TK%.2f\n", totalAmount);
        fprintf(billFile, "Status: %s\n", latestRecord.status);
        fprintf(billFile, "------------------------\n\n");
        fclose(billFile);
        printf(GREEN "\nBill saved to bills.txt\n" RESET);
    }

    clearInputBuffer();
    printf("\nPress " YELLOW "Enter" RESET " to return to the dashboard." HIDE_CURSOR);
    getchar();
    SET_STATE(SHOW_CURSOR);
    customerServiceAgentDashboard();
}

void initializeDefaultPricing(void) {
    FILE *fp = fopen("pricing.dat", "wb");
    if (fp) {
        ServicePrice defaultPrices[] = {
            {"Oil Change", 500.00},
            {"Brake Repair", 3500.00},
            {"Engine Check", 2000.00},
            {"Transmission", 3000.00},
            {"Tire Services", 3000.00},
            {"Battery", 2500.00},
            {"Air Filter", 1000.00},
            {"Inspection", 1000.00},
            {"Default Service", 2500.00}
        };
        
        int count = sizeof(defaultPrices) / sizeof(ServicePrice);
        fwrite(defaultPrices, sizeof(ServicePrice), count, fp);
        fclose(fp);
    }
    
    initializeDefaultTaxRate();
}

float getServicePrice(const char* serviceType) {
    FILE *fp = fopen("pricing.dat", "rb");
    if (!fp) {
        initializeDefaultPricing();
        fp = fopen("pricing.dat", "rb");
        if (!fp) return 2500.00;
    }
    
    ServicePrice price;
    while (fread(&price, sizeof(ServicePrice), 1, fp) == 1) {
        if (strstr(serviceType, price.serviceName) != NULL) {
            fclose(fp);
            return price.price;
        }
    }
    fclose(fp);
    
    fp = fopen("pricing.dat", "rb");
    if (fp) {
        while (fread(&price, sizeof(ServicePrice), 1, fp) == 1) {
            if (strcmp(price.serviceName, "Default Service") == 0) {
                fclose(fp);
                return price.price;
            }
        }
        fclose(fp);
    }
    
    return 2500.00;
}

void updateServicePrice(const char* serviceName, float newPrice) {
    FILE *fp = fopen("pricing.dat", "rb");
    if (!fp) {
        initializeDefaultPricing();
        fp = fopen("pricing.dat", "rb");
        if (!fp) return;
    }
    
    ServicePrice prices[20];
    int count = 0;
    int updated = 0;
    
    while (fread(&prices[count], sizeof(ServicePrice), 1, fp) == 1 && count < 20) {
        if (strcmp(prices[count].serviceName, serviceName) == 0) {
            prices[count].price = newPrice;
            updated = 1;
        }
        count++;
    }
    fclose(fp);
    
    if (updated) {
        fp = fopen("pricing.dat", "wb");
        if (fp) {
            fwrite(prices, sizeof(ServicePrice), count, fp);
            fclose(fp);
        }
    }
}

void initializeDefaultTaxRate(void) {
    FILE *fp = fopen("tax.dat", "wb");
    if (fp) {
        TaxSettings defaultTax = {0.08};
        fwrite(&defaultTax, sizeof(TaxSettings), 1, fp);
        fclose(fp);
    }
}

float getTaxRate(void) {
    FILE *fp = fopen("tax.dat", "rb");
    if (!fp) {
        initializeDefaultTaxRate();
        fp = fopen("tax.dat", "rb");
        if (!fp) return 0.08;
    }
    
    TaxSettings tax;
    if (fread(&tax, sizeof(TaxSettings), 1, fp) == 1) {
        fclose(fp);
        return tax.taxRate;
    }
    fclose(fp);

    return 0.08;
}

void updateTaxRate(float newTaxRate) {
    FILE *fp = fopen("tax.dat", "wb");
    if (fp) {
        TaxSettings tax = {newTaxRate};
        fwrite(&tax, sizeof(TaxSettings), 1, fp);
        fclose(fp);
    }
}

void managePricing(void) {
    system(CLEAR_SCREEN);
    printf(BRIGHT_BLUE "+----------------+\n" RESET);
    printf(BRIGHT_BLUE "| Manage Pricing |\n" RESET);
    printf(BRIGHT_BLUE "+----------------+\n" RESET);
    
    FILE *fp = fopen("pricing.dat", "rb");
    if (!fp) {
        initializeDefaultPricing();
        fp = fopen("pricing.dat", "rb");
    }
    
    if (!fp) {
        printf(RED "Error: Cannot access pricing data.\n" RESET);
        clearInputBuffer();
        printf("Press " YELLOW "Enter" RESET " to return to dashboard." HIDE_CURSOR);
        getchar();
        SET_STATE(SHOW_CURSOR);
        adminDashboard();
        return;
    }
    
    ServicePrice prices[20];
    int count = 0;
    
    printf(CYAN "Current Service Pricing:\n" RESET);
    printf(CYAN "%-4s %-20s %-15s\n" RESET, "ID", "Service Name", "Price (TK)");
    printf(CYAN "%-4s %-20s %-15s\n" RESET, "--", "------------", "----------");
    
    while (fread(&prices[count], sizeof(ServicePrice), 1, fp) == 1 && count < 20) {
        printf("%-4d %-20s TK%10.2f\n", count + 1, prices[count].serviceName, prices[count].price);
        count++;
    }
    fclose(fp);
    
    float currentTaxRate = getTaxRate();
    printf(CYAN "\nCurrent Tax Rate: %.1f%%\n" RESET, currentTaxRate * 100);
    
    printf(GREEN "\n[1] Update a service price\n" RESET);
    printf(GREEN "[2] Update tax rate\n" RESET);
    printf(GREEN "[3] Reset to default prices\n" RESET);
    printf(GREEN "[4] Return to dashboard\n" RESET);
    printf(YELLOW "Enter your choice: " RESET);
    
    int choice;
    scanf("%d", &choice);
    
    switch (choice) {
        case 1: {
            printf(YELLOW "Enter service ID to update (1-%d): " RESET, count);
            int serviceId;
            scanf("%d", &serviceId);
            
            if (serviceId >= 1 && serviceId <= count) {
                printf(YELLOW "Current price for %s: TK%.2f\n" RESET, 
                       prices[serviceId - 1].serviceName, prices[serviceId - 1].price);
                printf(YELLOW "Enter new price (TK): " RESET);
                float newPrice;
                scanf("%f", &newPrice);
                
                if (newPrice > 0) {
                    updateServicePrice(prices[serviceId - 1].serviceName, newPrice);
                    printf(GREEN "Price updated successfully!\n" RESET);
                    printf(CYAN "%s: TK%.2f -> TK%.2f\n" RESET, 
                           prices[serviceId - 1].serviceName, prices[serviceId - 1].price, newPrice);
                } else {
                    printf(RED "Invalid price. Price must be greater than 0.\n" RESET);
                }
            } else {
                printf(RED "Invalid service ID.\n" RESET);
            }
            break;
        }
        case 2: {
            float currentTaxRate = getTaxRate();
            printf(YELLOW "Current tax rate: %.1f%%\n" RESET, currentTaxRate * 100);
            printf(YELLOW "Enter new tax rate (as percentage, e.g., 8.5 for 8.5%%): " RESET);
            float newTaxPercent;
            scanf("%f", &newTaxPercent);
            
            if (newTaxPercent >= 0 && newTaxPercent <= 100) {
                float newTaxRate = newTaxPercent / 100.0;
                updateTaxRate(newTaxRate);
                printf(GREEN "Tax rate updated successfully!\n" RESET);
                printf(CYAN "Tax rate: %.1f%% -> %.1f%%\n" RESET, 
                       currentTaxRate * 100, newTaxRate * 100);
            } else {
                printf(RED "Invalid tax rate. Must be between 0 and 100.\n" RESET);
            }
            break;
        }
        case 3: {
            printf(YELLOW "Are you sure you want to reset all prices and tax rate to default? (y/N): " RESET);
            clearInputBuffer();
            char confirm;
            scanf("%c", &confirm);
            if (confirm == 'y' || confirm == 'Y') {
                initializeDefaultPricing();
                printf(GREEN "All prices and tax rate have been reset to default values.\n" RESET);
            } else {
                printf(CYAN "Reset cancelled.\n" RESET);
            }
            break;
        }
        case 4:
            adminDashboard();
            return;
        default:
            printf(RED "Invalid choice.\n" RESET);
            break;
    }
    
    clearInputBuffer();
    printf("\nPress " YELLOW "Enter" RESET " to continue..." HIDE_CURSOR);
    getchar();
    SET_STATE(SHOW_CURSOR);
    managePricing();
}

void aboutApp(void) {
    system(CLEAR_SCREEN);
    mainHeader();

    printf(BRIGHT_BLUE "+----------------------------------------------------+\n" RESET);
    printf(BRIGHT_BLUE "|                                                    |\n" RESET);
    printf(BRIGHT_BLUE "|" GREEN "  Garage Service Management System                  " BRIGHT_BLUE "|\n" RESET);
    printf(BRIGHT_BLUE "|" GREEN "  Version: 1.0.1                                    " BRIGHT_BLUE "|\n" RESET);
    printf(BRIGHT_BLUE "|" GREEN "  License: MIT                                      " BRIGHT_BLUE "|\n" RESET);
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

void returnToDashboard(int callerDashboard) {
    switch(callerDashboard) {
        case ADMIN_DASHBOARD:
            adminDashboard();
            break;
        case TECHNICIAN_DASHBOARD:
            technicianDashboard();
            break;
        default:
            mainMenu();
            break;
    }
}
