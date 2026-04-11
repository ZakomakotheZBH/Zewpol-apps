#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

typedef struct App {
    int id;
    char name[50];
    float price;
    int is_pro;
    struct App* next;
} App;

App* store_head = NULL;
float balance = 50.00;
int has_pro = 0;
float PRO_COST = 5000.00;

void add_app(int id, const char* name, float price, int is_pro) {
    App* n = (App*)malloc(sizeof(App));
    n->id = id;
    strcpy(n->name, name);
    n->price = price;
    n->is_pro = is_pro;
    n->next = store_head;
    store_head = n;
}

// Generates 50 "Pro" apps for the catalog
void populate_pro_apps() {
    char name_buf[50];
    for (int i = 1; i <= 50; i++) {
        sprintf(name_buf, "Pro-Tool-%02d", i);
        add_app(1000 + i, name_buf, 99.99, 1);
    }
}

void scan_zcard() {
    char code[20];
    printf("\n[ Z-CAMERA ACTIVE ]\nInput 16-digit Zcard code: ");
    scanf("%s", code);
    
    printf("Verifying with Z-Bank...");
    fflush(stdout);
    sleep(1);

    if (strstr(code, "777") != NULL) {
        balance += 2500.00;
        printf("\n>> [GOLDEN CARD] $2,500.00 Added!\n");
    } else if (strlen(code) == 16) {
        balance += 100.00;
        printf("\n>> [STANDARD] $100.00 Added.\n");
    } else {
        printf("\n>> [ERROR] Invalid Code.\n");
    }
}

void upgrade_to_pro() {
    if (has_pro) {
        printf("\nYou are already a Zewpol PRO member!\n");
        return;
    }
    printf("\n--- ZEWPOL PRO UPGRADE ---\n");
    printf("Cost: $%.2f | Your Balance: $%.2f\n", PRO_COST, balance);
    printf("Benefits: Access to 50+ Elite Developer Tools.\n");
    printf("Upgrade? (1=Yes, 0=No): ");
    int choice; scanf("%d", &choice);
    
    if (choice == 1) {
        if (balance >= PRO_COST) {
            balance -= PRO_COST;
            has_pro = 1;
            printf(">> WELCOME TO PRO. Unlocking high-level binaries...\n");
        } else {
            printf(">> Insufficient funds. Scan more Zcards!\n");
        }
    }
}

void show_store() {
    printf("\n==================================\n");
    printf("     ZEWPOL GIGA-STORE v7.0\n");
    printf("     Status: %s | Wallet: $%.2f\n", has_pro ? "PRO" : "Standard", balance);
    printf("==================================\n");
    
    App* curr = store_head;
    while (curr) {
        if (curr->is_pro && !has_pro) {
            printf("[%d] %-15s | [PRO ONLY]\n", curr->id, curr->name);
        } else {
            printf("[%d] %-15s | $%.2f %s\n", curr->id, curr->name, curr->price, curr->is_pro ? "(PRO)" : "");
        }
        curr = curr->next;
    }
}

void install_app() {
    int id;
    printf("\nEnter App ID to Install: ");
    scanf("%d", &id);
    
    App* curr = store_head;
    while (curr) {
        if (curr->id == id) {
            if (curr->is_pro && !has_pro) {
                printf(">> BLOCKED: This app requires Zewpol PRO status.\n");
                return;
            }
            if (balance >= curr->price) {
                balance -= curr->price;
                printf(">> Installing %s...\n", curr->name);
                for(int i=0; i<10; i++) { printf("#"); fflush(stdout); usleep(100000); }
                printf(" 100%%\nDone!\n");
            } else {
                printf(">> Error: Not enough money.\n");
            }
            return;
        }
        curr = curr->next;
    }
    printf("App not found.\n");
}

int main() {
    srand(time(NULL));
    // Load Standard Apps
    add_app(501, "Zewpol Kernel", 0.00, 0);
    add_app(502, "Z-Chat", 0.00, 0);
    // Load 50 Pro Apps
    populate_pro_apps();

    int opt;
    while (1) {
        show_store();
        printf("\n1. Install App\n2. Scan Zcard\n3. Upgrade to PRO\n4. Exit\nSelection: ");
        if (scanf("%d", &opt) != 1) break;

        if (opt == 1) install_app();
        else if (opt == 2) scan_zcard();
        else if (opt == 3) upgrade_to_pro();
        else break;
    }
    return 0;
}
