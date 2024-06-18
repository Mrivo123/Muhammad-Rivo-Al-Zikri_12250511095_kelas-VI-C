#include <stdio.h>
#include <string.h>

struct Account {
    char username[50];
    char password[50];
    double balance;
};


int login(struct Account accounts[], int numAccounts) {
    char username[50], password[50];
    printf("Masukkan username: ");
    scanf("%s", username);
    printf("Masukkan password: ");
    scanf("%s", password);

    for (int i = 0; i < numAccounts; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0) {
            return i;
        }
    }
    return -1;  
}


void checkBalance(struct Account account) {
    printf("Saldo anda: %.2f\n", account.balance);
}


void transfer(struct Account *account, struct Account accounts[], int numAccounts) {
    char targetUsername[50];
    double amount;

    printf("Masukkan username tujuan: ");
    scanf("%s", targetUsername);
    printf("Masukkan jumlah yang akan ditransfer: ");
    scanf("%lf", &amount);

    if (amount > account->balance) {
        printf("Saldo tidak cukup.\n");
        return;
    }

    for (int i = 0; i < numAccounts; i++) {
        if (strcmp(accounts[i].username, targetUsername) == 0) {
            account->balance -= amount;
            accounts[i].balance += amount;
            printf("Transfer berhasil.\n");
            return;
        }
    }

    printf("Username tujuan tidak ditemukan.\n");
}


void withdraw(struct Account *account) {
    double amount;
    printf("Masukkan jumlah yang akan diambil (50.000 atau 100.000): ");
    scanf("%lf", &amount);

    if (amount != 50.000 && amount != 100.000) {
        printf("Jumlah tidak valid. Hanya bisa mengambil 50.000 atau 100.000.\n");
        return;
    }

    if (amount > account->balance) {
        printf("Saldo tidak cukup.\n");
        return;
    }

    account->balance -= amount;
    printf("Penarikan berhasil. Saldo anda sekarang: %.2f\n", account->balance);
}

int main() {
	printf("=====SELAMAT DATANG DI BANK HALAL=====\n\n");
	
    struct Account accounts[4] = {
        {"user1", "pass1", 1000.000},
        {"user2", "pass2", 1500.000},
        {"user3", "pass3", 2000.000},
        {"rivo", "rivo901",5000.000}  
    };

    int numAccounts = 4;
    int loggedInUserIndex = -1;

    while (loggedInUserIndex == -1) {
        loggedInUserIndex = login(accounts, numAccounts);
        if (loggedInUserIndex == -1) {
            printf("Login gagal. Coba lagi.\n");
        }
    }

    int choice;
    do {
        printf("\n1. Cek Saldo\n2. Transfer\n3. Tarik Tunai\n4. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkBalance(accounts[loggedInUserIndex]);
                break;
            case 2:
                transfer(&accounts[loggedInUserIndex], accounts, numAccounts);
                break;
            case 3:
                withdraw(&accounts[loggedInUserIndex]);
                break;
            case 4:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (choice != 4);

    return 0;
}
