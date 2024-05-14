#include <stdio.h> // Library untuk input-output standar
#include <stdlib.h> // Library untuk fungsi-fungsi umum
#include <string.h> // Library untuk manipulasi string
#include <stdbool.h> // Library untuk tipe data boolean
#include "search.h"
#include "login.h"
#define ALPHABET_SIZE 26 // Ukuran abjad Inggris


// Function to initialize a Trie node
struct TrieNode* CreateNode() {
    struct TrieNode* node = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    if (!node) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    node->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

// Function to insert a word into the Trie
void insert(struct TrieNode* root, char* word) {
    struct TrieNode* current = root;
    int index;
    for (int i = 0; i < strlen(word); i++) {
        index = word[i] - 'a';
        if (!current->children[index])
            current->children[index] = CreateNode();
        current = current->children[index];
    }
    current->isEndOfWord = true;
}

// Recursive function to traverse the Trie and print all words with the given prefix
void traverseTrie(struct TrieNode* node, char* prefix) {
    if (node->isEndOfWord)
        printf("%s\n", prefix);

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            char* newPrefix = (char*)malloc(strlen(prefix) + 2);
            if (!newPrefix) {
                printf("Memory allocation failed\n");
                exit(1);
            }
            strcpy(newPrefix, prefix);
            newPrefix[strlen(prefix)] = i + 'a';
            newPrefix[strlen(prefix) + 1] = '\0';
            traverseTrie(node->children[i], newPrefix);
            free(newPrefix);
        }
    }
}

void search(struct TrieNode* root, char* prefix) {
    struct TrieNode* current = root; // Pointer yang menunjuk ke node saat ini dimulai dari root
    int index;
    int length = strlen(prefix);
    for (int i = 0; i < length; i++) {
        index = prefix[i] - 'a'; // Menghitung indeks berdasarkan huruf
        if (!current->children[index]) {
            printf("No words found with prefix \"%s\"\n", prefix); // Jika tidak ada anak dengan indeks tersebut, cetak pesan bahwa tidak ada kata yang ditemukan
            return;
        }
        current = current->children[index]; // Pindah ke node anak yang sesuai
    }
    // Jika prefiks ditemukan, telusuri Trie untuk mencetak semua kata dengan prefiks tersebut
    traverseTrie(current, prefix);
}

// Function to display user menu
void displayMenuUser() {
    printf("==========================================================================\n");
    printf("|                            WELCOME USER                                |\n");
    printf("==========================================================================\n");
    printf("|                             Trie Shop                                  |\n");
    printf("==========================================================================\n");
    printf("| 1. Lihat Barang                                                        |\n");
    printf("| 2. Beli Barang (In Progress)                                           |\n");
    printf("| 3. Lihat Keranjang (In Progress)                                       |\n");
    printf("| 4. Kembali                                                             |\n");
    printf("==========================================================================\n");
    printf("==========================================================================\n");
}

void displayMenuAdmin() {
    printf("==========================================================================\n");
    printf("|                           WELCOME ADMIN                                |\n");
    printf("==========================================================================\n");
    printf("|                             Trie Shop                                  |\n");
    printf("==========================================================================\n");
    printf("| 1. Tambah Barang                                                       |\n");
    printf("| 2. Cari Barang                                                         |\n");
    printf("| 3. Daftar Barang                                                       |\n");
    printf("| 4. Kembali                                                             |\n");
    printf("==========================================================================\n");
    printf("==========================================================================\n");
}

// Function to add a new category
void addCategory(struct Category categories[], int* categoryCount) {
    printf("Buat Kategori: ");
    fgets(categories[*categoryCount].name, sizeof(categories[*categoryCount].name), stdin);
    categories[*categoryCount].name[strcspn(categories[*categoryCount].name, "\n")] = '\0';
    categories[*categoryCount].trie = CreateNode();
    (*categoryCount)++;
}

// Function to select a category
int selectCategory(struct Category categories[], int categoryCount) {
    printf("Pilih Kategori:\n");
    for (int i = 0; i < categoryCount; i++) {
        printf("%d. %s\n", i + 1, categories[i].name);
    }
    int choice;
    printf("Masukan Pilihan: ");
    scanf("%d", &choice);
    getchar();
    return choice - 1;
}

// Function to display all items in a category
void displayItems(struct TrieNode* root) {
    printf("Barang pada kategori:\n");
    char prefix[1] = ""; // Start with an empty prefix
    traverseTrie(root, prefix); // Traverse the Trie and print all words
    printf("\n");
}

// Function to display all items in all categories
void displayAllItems(struct Category categories[], int categoryCount) {
    for (int i = 0; i < categoryCount; i++) {
        printf("Kategori: %s\n", categories[i].name);
        displayItems(categories[i].trie); // Display items for each category
    }
}

int maintrieuser() {
    struct TrieNode* root = CreateNode();
    struct Category categories[100];
    int categoryCount = 0;

    int choice;
    char word[100], prefix[100];
    int selectedCategory;

    do {
        system("cls");
        displayMenuUser(); 						// Menampilkan menu
        printf("Masukan pilihan (1/2/3): ");
        scanf("%d", &choice); 				// Membaca pilihan dari pengguna
        getchar();							// Membersihkan buffer masukan

        switch (choice) {
        case 1:
            if (categoryCount == 0) {
                printf("Belum ada Barang. Tambahkan barang terlebih dahulu.\n");
                system("pause");
                break;
            }
            displayAllItems(categories, categoryCount);
            system("pause");
            break;
        case 2:
            system("CLS");
            printf("\n==========================================================================\n");
            printf("|                      Terima Kasih Pelanggan                            |\n");
            printf("|                      Sampai Bertemu Kembali                            |\n");
            printf("==========================================================================\n");
            menulogin();
        case 3:
            system("CLS");
            printf("\n==========================================================================\n");
            printf("|                      Terima Kasih Pelanggan                            |\n");
            printf("|                      Sampai Bertemu Kembali                            |\n");
            printf("==========================================================================\n");
            menulogin();
        case 4:
            menulogin();
        default:
            printf("Invalid choice");
            system("pause");
        }
    } while (choice != 3); // Melanjutkan loop hingga pengguna memilih untuk keluar

    return 0;
}

int maintrieadmin() {
    struct TrieNode* root = CreateNode();
    struct Category categories[100];
    int categoryCount = 0;

    int choice;
    char word[100], prefix[100];
    int selectedCategory;

    do {
        system("CLS");
        displayMenuAdmin();
        printf("Masukan pilihan pada menu: (1/2/3/4: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            char pilih;
            do {
                addCategory(categories, &categoryCount);

                printf("\nApakah sudah selesai menambah kategori? (Y/N): ");
                scanf(" %c", &pilih);
                getchar(); // Membersihkan buffer masukan
            } while (pilih != 'Y' && pilih != 'y');

            if (categoryCount == 0) {
                printf("Belum ada Barang. Tambahkan barang terlebih dahulu.\n");
                system("pause");
                break;
            }

            char tambahBarang;
            do {
                selectedCategory = selectCategory(categories, categoryCount);
                do {
                    printf("Masukan Barang pada kategori %s: ", categories[selectedCategory].name);
                    fgets(word, sizeof(word), stdin);
                    word[strcspn(word, "\n")] = '\0';
                    insert(categories[selectedCategory].trie, word);

                    printf("Tambahkan barang lain? (Y/N): ");
                    scanf(" %c", &tambahBarang);
                    getchar(); // Membersihkan buffer masukan
                } while (tambahBarang == 'Y' || tambahBarang == 'y');

                printf("\nTambah item untuk kategori lain? (Y/N): ");
                scanf(" %c", &pilih);
                getchar(); // Membersihkan buffer masukan
            } while (pilih == 'Y' || pilih == 'y');
            system("CLS");
            break;

        case 2:
            if (categoryCount == 0) {
                printf("Belum ada Barang. Tambahkan barang terlebih dahulu.\n");
                system("pause");
                break;
            }
            selectedCategory = selectCategory(categories, categoryCount);
            printf("Cari Barang berdasarkan nama: ");
            fgets(prefix, sizeof(prefix), stdin);
            prefix[strcspn(prefix, "\n")] = '\0';
            printf("Barang \"%s\" ada pada kategori %s:\n", prefix, categories[selectedCategory].name);
            search(categories[selectedCategory].trie, prefix);
            system("pause");
            break;

        case 3:
            if (categoryCount == 0) {
                printf("Belum ada Barang. Tambahkan barang terlebih dahulu.\n");
                system("pause");
                break;
            }
            displayAllItems(categories, categoryCount);
            system("pause");
            break;

        case 4:
            system("CLS");
            printf("\n==========================================================================\n");
            printf("|                      Thank You for Shopping                             |\n");
            printf("|                           See You Again!                                |\n");
            printf("==========================================================================\n");
            menulogin();

        default:
            printf("Invalid choice");
            system("pause");
        }
    } while (choice != 4); // Melanjutkan loop hingga pengguna memilih untuk keluar

    return 0;
}
