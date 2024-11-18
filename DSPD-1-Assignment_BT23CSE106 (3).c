#include <stdio.h>
#include <string.h>

#define max_transaction 1000
#define max_sellers 500
#define max_buyers 500
#define MAX_MONTHS 12

struct transaction {
    int transaction_id;
    int seller_id;
    int buyer_id;
    float energy;
    float price;
    char time[20]; 
};

struct seller_revenue {
    int seller_id;
    float total_revenue;
};

struct buyer_energy {
    int buyer_id;
    float total_energy_bought;
};

struct pair_count {
    int seller_id;
    int buyer_id;
    int transaction_count;
};

struct pair_revenue {
    int seller_id;
    int buyer_id;
    float total_revenue;
};


void add_transaction(struct transaction transactions[], int *count);
void display_transactions(struct transaction transactions[], int count);
void list_of_sellers(struct transaction transactions[], int count);
void list_of_buyers(struct transaction transactions[], int count);
void list_of_transactions_in_time_period(struct transaction transactions[], int count);
void max_month(struct transaction transactions[], int count);
void revenue_by_seller(struct transaction transactions[], int count);
void sort_sellers_by_revenue(struct transaction transactions[], int count);

void add_transaction(struct transaction transactions[], int *count) {
    if (*count >= max_transaction) {
        printf("Error: Maximum number of transactions reached.\n");
        return;
    }

    struct transaction newTransaction;

    printf("Enter Transaction ID: ");
    scanf("%d", &newTransaction.transaction_id);
    printf("Enter Buyer ID: ");
    scanf("%d", &newTransaction.buyer_id);
    printf("Enter Seller ID: ");
    scanf("%d", &newTransaction.seller_id);
    printf("Enter Energy Amount (kWh): ");
    scanf("%f", &newTransaction.energy);
    printf("Enter Price per kWh: ");
    scanf("%f", &newTransaction.price);
    getchar(); 
    printf("Enter Timestamp (YYYY-MM-DD HH:MM:SS): ");
    fgets(newTransaction.time, sizeof(newTransaction.time), stdin);

    size_t len = strlen(newTransaction.time);
    if (len > 0 && newTransaction.time[len - 1] == '\n') {
        newTransaction.time[len - 1] = '\0';
    }

    transactions[*count] = newTransaction;
    (*count)++;

    printf("Transaction added successfully.\n");
}

void display_transactions(struct transaction transactions[], int count) {
    if (count == 0) {
        printf("NO TRANSACTIONS AVAILABLE\n");
        return;
    }

    printf("Displaying All Transactions\n");
    for (int i = 0; i < count; i++) {
        printf("Transaction ID: %d | Seller ID: %d | Buyer ID: %d | Energy: %.2f kWh | Price: %.2f | Timestamp: %s\n", 
               transactions[i].transaction_id, transactions[i].seller_id, 
               transactions[i].buyer_id, transactions[i].energy, 
               transactions[i].price, transactions[i].time);
    }
}

void list_of_sellers(struct transaction transactions[], int count) {
    int foundSellers[max_sellers] = {0}; 

    for (int i = 0; i < count; i++) {
        int sellerId = transactions[i].seller_id;

        if (!foundSellers[sellerId]) {
            printf("Transactions for Seller ID %d:\n", sellerId);
            foundSellers[sellerId] = 1; 

            for (int j = 0; j < count; j++) {
                if (transactions[j].seller_id == sellerId) {
                    printf("Transaction ID: %d, Buyer ID: %d, Energy: %.2f kWh, Price: %.2f, Time: %s\n",
                           transactions[j].transaction_id,
                           transactions[j].buyer_id,
                           transactions[j].energy,
                           transactions[j].price,
                           transactions[j].time);
                }
            }
        }
    }
}

void list_of_buyers(struct transaction transactions[], int count) {
    int foundBuyers[max_buyers] = {0};

    for (int i = 0; i < count; i++) {
        int buyerId = transactions[i].buyer_id;

        if (!foundBuyers[buyerId]) {
            printf("Transactions for Buyer ID %d:\n", buyerId);
            foundBuyers[buyerId] = 1; 

            for (int j = 0; j < count; j++) {
                if (transactions[j].buyer_id == buyerId) {
                    printf("Transaction ID: %d, Seller ID: %d, Energy: %.2f kWh, Price: %.2f, Time: %s\n",
                           transactions[j].transaction_id,
                           transactions[j].seller_id,
                           transactions[j].energy,
                           transactions[j].price,
                           transactions[j].time);
                }
            }
        }
    }
}

void list_of_transactions_in_time_period(struct transaction transactions[], int count) {
    char start_time[20], end_time[20];
    int found = 0;  

    
    printf("Enter the starting time (YYYY-MM-DD HH:MM:SS): ");
    fgets(start_time, sizeof(start_time), stdin);
    
    
    size_t len = strlen(start_time);
    if (len > 0 && start_time[len - 1] == '\n') {
        start_time[len - 1] = '\0'; 
    }

    
    if (len < 19) {
        printf("Error: Starting time format is incorrect. Please follow YYYY-MM-DD HH:MM:SS.\n");
        return;
    }

    printf("Enter the ending time (YYYY-MM-DD HH:MM:SS): ");
    fgets(end_time, sizeof(end_time), stdin);
    

    len = strlen(end_time);
    if (len > 0 && end_time[len - 1] == '\n') {
        end_time[len - 1] = '\0'; 
    }

    
    if (len < 19) {
        printf("Error: Ending time format is incorrect. Please follow YYYY-MM-DD HH:MM:SS.\n");
        return;
    }

    
    printf("Transactions between %s and %s:\n", start_time, end_time);
    for (int i = 0; i < count; i++) {
        if (strcmp(transactions[i].time, start_time) >= 0 && strcmp(transactions[i].time, end_time) <= 0) {
            printf("Transaction ID: %d, Seller ID: %d, Buyer ID: %d, Energy: %.2f kWh, Price: %.2f, Time: %s\n", 
                   transactions[i].transaction_id, 
                   transactions[i].seller_id, 
                   transactions[i].buyer_id, 
                   transactions[i].energy, 
                   transactions[i].price, 
                   transactions[i].time);
            found = 1; 
        }
    }

    if (!found) {
        printf("No transactions found within the given time period.\n");
    }
}



void max_month(struct transaction transactions[], int count) {
    int month_count[MAX_MONTHS] = {0}; 

    for (int i = 0; i < count; i++) {
        char month_str[3];
        strncpy(month_str, &transactions[i].time[5], 2);
        month_str[2] = '\0'; 

        if (month_str[0] == '0') {
            month_count[month_str[1] - '1']++; 
        } else if (month_str[0] == '1') {
            if (month_str[1] == '0') {
                month_count[9]++; 
            } else {
                month_count[10]++;
            }
        } else if (month_str[0] == '2' && month_str[1] == '0') {
            month_count[11]++; 
        }
    }

    int max_transactions = 0;
    int max_month_index = -1;
    for (int i = 0; i < MAX_MONTHS; i++) {
        if (month_count[i] > max_transactions) {
            max_transactions = month_count[i];
            max_month_index = i;
        }
    }

    const char *month_names[MAX_MONTHS] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    if (max_month_index != -1) {
        printf("Month with maximum transactions: %s (%d transactions)\n", 
               month_names[max_month_index], 
               max_transactions);
    } else {
        printf("No transactions found.\n");
    }
}

void revenue_by_seller(struct transaction transactions[], int count) {
    int seller_id;
    float total_revenue = 0.0;

    printf("Enter Seller ID to calculate total revenue: ");
    scanf("%d", &seller_id);

    for (int i = 0; i < count; i++) {
        if (transactions[i].seller_id == seller_id) {
            total_revenue += transactions[i].energy * transactions[i].price;
        }
    }

    printf("Total revenue generated by Seller ID %d: %.2f\n", seller_id, total_revenue);
}

void sort_sellers_by_revenue(struct transaction transactions[], int count) {
    struct seller_revenue sellers[max_sellers]; 
    int seller_count = 0;

    
    for (int i = 0; i < count; i++) {
        int found = 0;
        for (int j = 0; j < seller_count; j++) {
            if (sellers[j].seller_id == transactions[i].seller_id) {
                sellers[j].total_revenue += transactions[i].energy * transactions[i].price;
                found = 1; 
            }
        }
        
        if (!found) {
            sellers[seller_count].seller_id = transactions[i].seller_id;
            sellers[seller_count].total_revenue = transactions[i].energy * transactions[i].price;
            seller_count++;
        }
    }

    
    for (int i = 0; i < seller_count - 1; i++) {
        for (int j = i + 1; j < seller_count; j++) {
            if (sellers[i].total_revenue < sellers[j].total_revenue) {
                struct seller_revenue temp = sellers[i];
                sellers[i] = sellers[j];
                sellers[j] = temp;
            }
        }
    }

    
    printf("Sellers sorted by revenue (from highest to lowest):\n");
    for (int i = 0; i < seller_count; i++) {
        printf("Seller ID: %d, Total Revenue: %.2f\n", sellers[i].seller_id, sellers[i].total_revenue);
    }
}


void highest_energy_amount(struct transaction transactions[], int count) {
    if (count == 0) {
        printf("No transactions available to display.\n");
        return;
    }

    struct transaction max_energy_transaction = transactions[0];

    for (int i = 1; i < count; i++) {
        if (transactions[i].energy > max_energy_transaction.energy) {
            max_energy_transaction = transactions[i];
        }
    }

    printf("Transaction with the highest energy amount traded:\n");
    printf("Transaction ID: %d | Seller ID: %d | Buyer ID: %d | Energy: %.2f kWh | Price: %.2f | Timestamp: %s\n",
           max_energy_transaction.transaction_id,
           max_energy_transaction.seller_id,
           max_energy_transaction.buyer_id,
           max_energy_transaction.energy,
           max_energy_transaction.price,
           max_energy_transaction.time);
}

void sort_transactions_by_energy(struct transaction transactions[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (transactions[i].energy < transactions[j].energy) {
                struct transaction temp = transactions[i];
                transactions[i] = transactions[j];
                transactions[j] = temp;
            }
        }
    }
    
    printf("Transactions sorted by energy amount traded (from highest to lowest):\n");
    for (int i = 0; i < count; i++) {
        printf("Transaction ID: %d | Seller ID: %d | Buyer ID: %d | Energy: %.2f kWh | Price: %.2f | Timestamp: %s\n", 
               transactions[i].transaction_id, 
               transactions[i].seller_id, 
               transactions[i].buyer_id, 
               transactions[i].energy, 
               transactions[i].price, 
               transactions[i].time);
    }
}

void sort_buyers_by_energy(struct transaction transactions[], int count) {
    struct buyer_energy buyers[max_buyers];
    int buyer_count = 0;

    
    for (int i = 0; i < count; i++) {
        int found = 0;
        for (int j = 0; j < buyer_count; j++) {
            if (buyers[j].buyer_id == transactions[i].buyer_id) {
                buyers[j].total_energy_bought += transactions[i].energy;
                found = 1;
                break;
            }
        }
        if (!found) {
            buyers[buyer_count].buyer_id = transactions[i].buyer_id;
            buyers[buyer_count].total_energy_bought = transactions[i].energy;
            buyer_count++;
        }
    }

    
    for (int i = 0; i < buyer_count - 1; i++) {
        for (int j = i + 1; j < buyer_count; j++) {
            if (buyers[i].total_energy_bought < buyers[j].total_energy_bought) {
                struct buyer_energy temp = buyers[i];
                buyers[i] = buyers[j];
                buyers[j] = temp;
            }
        }
    }

    
    printf("Buyers sorted by energy bought (from highest to lowest):\n");
    for (int i = 0; i < buyer_count; i++) {
        printf("Buyer ID: %d, Total Energy Bought: %.2f kWh\n", buyers[i].buyer_id, buyers[i].total_energy_bought);
    }
}


void find_max_transaction_pair(struct transaction transactions[], int count) {
    struct pair_count pairs[max_transaction];
    int pair_count = 0;

    
    for (int i = 0; i < count; i++) {
        int seller_id = transactions[i].seller_id;
        int buyer_id = transactions[i].buyer_id;

        int found = 0;
        
        for (int j = 0; j < pair_count; j++) {
            if (pairs[j].seller_id == seller_id && pairs[j].buyer_id == buyer_id) {
                pairs[j].transaction_count++;
                found = 1;
                break;
            }
        }

        
        if (!found) {
            pairs[pair_count].seller_id = seller_id;
            pairs[pair_count].buyer_id = buyer_id;
            pairs[pair_count].transaction_count = 1;
            pair_count++;
        }
    }


    int max_transactions = 0;
    int max_index = -1;
    for (int i = 0; i < pair_count; i++) {
        if (pairs[i].transaction_count > max_transactions) {
            max_transactions = pairs[i].transaction_count;
            max_index = i;
        }
    }

    
    if (max_index != -1) {
        printf("Seller ID %d and Buyer ID %d are involved in the maximum number of transactions: %d transactions.\n", 
               pairs[max_index].seller_id, pairs[max_index].buyer_id, 
               pairs[max_index].transaction_count);
    } else {
        printf("No transactions found.\n");
    }
}

void sort_seller_buyer_pairs_by_transactions(struct transaction transactions[], int count) {
    struct pair_count pairs[max_transaction];
    int pair_count = 0;

    for (int i = 0; i < count; i++) {
        int seller_id = transactions[i].seller_id;
        int buyer_id = transactions[i].buyer_id;

        int found = 0;
        
        for (int j = 0; j < pair_count; j++) {
            if (pairs[j].seller_id == seller_id && pairs[j].buyer_id == buyer_id) {
                pairs[j].transaction_count++;
                found = 1;
                break;
            }
        }

    
        if (!found) {
            pairs[pair_count].seller_id = seller_id;
            pairs[pair_count].buyer_id = buyer_id;
            pairs[pair_count].transaction_count = 1;
            pair_count++;
        }
    }

    
    for (int i = 0; i < pair_count - 1; i++) {
        for (int j = i + 1; j < pair_count; j++) {
            if (pairs[i].transaction_count < pairs[j].transaction_count) {
                
                struct pair_count temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }


    printf("Seller-Buyer pairs sorted by the number of transactions (from highest to lowest):\n");
    for (int i = 0; i < pair_count; i++) {
        printf("Seller ID: %d, Buyer ID: %d, Number of Transactions: %d\n", 
               pairs[i].seller_id, pairs[i].buyer_id, pairs[i].transaction_count);
    }
}

void sort_seller_buyer_pairs_by_revenue(struct transaction transactions[], int count) {
    struct pair_revenue pairs[max_transaction];
    int pair_count = 0;

    
    for (int i = 0; i < count; i++) {
        int seller_id = transactions[i].seller_id;
        int buyer_id = transactions[i].buyer_id;
        float revenue = transactions[i].energy * transactions[i].price;

        int found = 0;
        
        for (int j = 0; j < pair_count; j++) {
            if (pairs[j].seller_id == seller_id && pairs[j].buyer_id == buyer_id) {
                pairs[j].total_revenue += revenue; 
                found = 1;
                break;
            }
        }

        
        if (!found) {
            pairs[pair_count].seller_id = seller_id;
            pairs[pair_count].buyer_id = buyer_id;
            pairs[pair_count].total_revenue = revenue;
            pair_count++;
        }
    }

    
    for (int i = 0; i < pair_count - 1; i++) {
        for (int j = i + 1; j < pair_count; j++) {
            if (pairs[i].total_revenue < pairs[j].total_revenue) {
                
                struct pair_revenue temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }

    
    printf("Seller-Buyer pairs sorted by total revenue exchanged (from highest to lowest):\n");
    for (int i = 0; i < pair_count; i++) {
        printf("Seller ID: %d, Buyer ID: %d, Total Revenue: %.2f\n", 
               pairs[i].seller_id, pairs[i].buyer_id, pairs[i].total_revenue);
    }
}


int main() {
    struct transaction transactions[max_transaction];

    int count = 15;
    int n;
    int flag = 0;
    
    struct transaction initial_transactions[15] = {
        {1, 101, 201, 100.5, 2.5, "2024-01-10 10:00:00"},
        {2, 102, 202, 150.0, 3.0, "2024-02-15 12:30:00"},
        {3, 103, 203, 120.5, 2.8, "2024-03-05 14:45:00"},
        {4, 101, 204, 200.0, 2.2, "2024-01-20 16:10:00"},
        {5, 105, 202, 180.0, 3.1, "2024-04-12 18:25:00"},
        {6, 104, 205, 110.5, 2.6, "2024-05-20 09:50:00"},
        {7, 101, 201, 140.0, 2.4, "2024-06-22 20:15:00"},
        {8, 106, 206, 170.5, 2.7, "2024-07-30 22:40:00"},
        {9, 107, 207, 160.0, 3.2, "2024-08-18 08:05:00"},
        {10, 103, 203, 190.0, 2.9, "2024-09-10 11:30:00"},
        {11, 108, 208, 130.5, 2.3, "2024-10-02 13:55:00"},
        {12, 102, 202, 125.0, 2.1, "2024-11-08 15:20:00"},
        {13, 104, 209, 195.0, 3.0, "2024-12-12 17:35:00"},
        {14, 106, 210, 175.5, 3.5, "2024-02-22 19:50:00"},
        {15, 101, 205, 185.0, 2.6, "2024-03-14 21:05:00"}
    };

    
    for (int i = 0; i < 15; i++) {
        transactions[i] = initial_transactions[i];
    }

    while (flag == 0) {
        printf("Welcome to Energy Trading Record Management System\n");
        printf("1. Add new transaction\n");
        printf("2. Display all transactions\n");
        printf("3. Create a list of transactions for every seller\n");
        printf("4. Create a list of transactions for every buyer\n");
        printf("5. List of transactions in a certain time period\n");
        printf("6. Month in which maximum transactions took place\n");
        printf("7. Calculate total revenue by Seller\n");
        printf("8. Sort list of sellers based on their revenue generated\n");
        printf("9. Find transaction with highest energy amount\n");
        printf("10. Sort transactions based on amount of energy traded\n");
        printf("11. Sort buyers based on energy bought\n");
        printf("12. Pair of seller/buyer involved in maximum number of transactions\n");
        printf("13. Sort all seller/buyer pairs in decreasing order of transactions between themn\n");
        printf("14. Sort all pairs in decreasing order of total revenue exchanged between them\n");
        printf("15. Exit\n");
        printf("Please choose one option to continue: ");
        scanf("%d", &n);

        switch (n) {
            case 1:
                add_transaction(transactions, &count);
                break;
            case 2:
                display_transactions(transactions, count);
                break;
            case 3:
                list_of_sellers(transactions, count);
                break;
            case 4:
                list_of_buyers(transactions, count);
                break; 
            case 5:
                list_of_transactions_in_time_period(transactions, count);
                break;
            case 6:
                max_month(transactions, count);
                break;
            case 7:
                revenue_by_seller(transactions, count);
                break;
            case 8: 
                sort_sellers_by_revenue(transactions, count);
                break;
            case 9:
                highest_energy_amount(transactions,count);
                break;
            case 10:
                sort_transactions_by_energy(transactions,count);
                break;
            case 11:
                sort_buyers_by_energy(transactions,count);
                break;
            case 12:
                find_max_transaction_pair(transactions,count);
                break;
            case 13:
                sort_seller_buyer_pairs_by_transactions(transactions,count);
                break;
            case 14:
                sort_seller_buyer_pairs_by_revenue(transactions,count);
                break;
            case 15:
                printf("Exiting the program.\n");
                flag = 1;
                break;
            default:
                printf("INVALID INPUT\n");
        }
    }

    return 0;
}