#include <stdio.h> // Library untuk input-output standar
#include <stdlib.h> // Library untuk fungsi-fungsi umum
#include <string.h> // Library untuk manipulasi string
#include <stdbool.h> // Library untuk tipe data boolean
#include "search.h"
#include "login.h"
#define ALPHABET_SIZE 26 // Ukuran abjad Inggris

// Fungsi untuk menginisialisasi sebuah node Trie
struct TrieNode *getNode() {
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode)); // Mengalokasikan memori untuk sebuah node baru
    node->isEndOfWord = false; 													// Mengeset nilai awal isEndOfWord menjadi false
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL; 												// Mengeset semua pointer anak-anak menjadi NULL
    return node; 																// Mengembalikan node yang telah diinisialisasi
}

// Fungsi untuk memasukkan sebuah kata ke dalam Trie
void insert(struct TrieNode *root, char *word) {
    struct TrieNode *current = root; 											// Pointer yang menunjuk ke node saat ini dimulai dari root
    int index;
    for (int i = 0; i < strlen(word); i++) {
        index = word[i] - 'a'; 													// Menghitung indeks berdasarkan huruf
        if (!current->children[index])
            current->children[index] = getNode(); 								// Jika anak dengan indeks tersebut belum ada, alokasikan memori untuk node tersebut
        current = current->children[index]; 									// Pindah ke node anak yang sesuai
    }
    current->isEndOfWord = true; 												// Menandai bahwa kata telah selesai dimasukkan
}

// Fungsi rekursif untuk menelusuri Trie dan mencetak semua kata dengan awalan yang diberikan
void traverseTrie(struct TrieNode *node, char *prefix) {
    if (node->isEndOfWord)
        printf("%s\n", prefix); 									// Jika node saat ini adalah akhir dari sebuah kata, cetak prefiks yang terkumpul

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i]) {
            char *newPrefix = (char *)malloc(strlen(prefix) + 2); 	// Mengalokasikan memori untuk prefiks baru
            strcpy(newPrefix, prefix);								// Menyalin prefiks yang ada ke prefiks baru
            newPrefix[strlen(prefix)] = i + 'a';					// Menambahkan huruf baru ke prefiks baru
            newPrefix[strlen(prefix) + 1] = '\0'; 					// Mengakhiri prefiks baru dengan null terminator
            traverseTrie(node->children[i], newPrefix);				// Rekursif untuk menelusuri node anak
            free(newPrefix); 										// Membebaskan memori yang dialokasikan untuk prefiks baru
        }
    }
}

// Fungsi untuk mencari kata-kata dalam Trie berdasarkan awalan yang diberikan
void search(struct TrieNode *root, char *prefix) {
    struct TrieNode *current = root; 								// Pointer yang menunjuk ke node saat ini dimulai dari root
    int index;
    int length = strlen(prefix);
    for (int i = 0; i < length; i++) {
        index = prefix[i] - 'a'; 									// Menghitung indeks berdasarkan huruf
        if (!current->children[index]) {
            printf("No words found with prefix \"%s\"\n", prefix); 	// Jika tidak ada anak dengan indeks tersebut, cetak pesan bahwa tidak ada kata yang ditemukan
            return;
        }
        current = current->children[index];							// Pindah ke node anak yang sesuai
    }
    // Jika prefiks ditemukan, telusuri Trie untuk mencetak semua kata dengan prefiks tersebut
    traverseTrie(current, prefix);
}

// Fungsi untuk menampilkan opsi menu
void displayMenuUser() {
	printf("==========================================================================\n");
	printf("|                            WELCOME USER                                |\n");
	printf("==========================================================================\n");
    printf("|                             Trie Shop                                  |\n");
    printf("==========================================================================\n");
    printf("| 1. Masukan Barang \t\t\t\t\t\t\t |\n");
    printf("| 2. Mencari Barang menggunakan prefix\t\t\t\t\t |\n");
    printf("| 3. Keluar\t\t\t\t\t\t\t\t |\n");
    printf("==========================================================================\n");
    printf("==========================================================================\n");
}

void displayMenuAdmin() {
	printf("==========================================================================\n");
	printf("|                           WELCOME ADMIN                                |\n");
	printf("==========================================================================\n");
    printf("|                             Trie Shop                                  |\n");
    printf("==========================================================================\n");
    printf("| 1. Masukan Barang \t\t\t\t\t\t\t |\n");
    printf("| 2. Mencari Barang menggunakan prefix\t\t\t\t\t |\n");
    printf("| 3. Keluar\t\t\t\t\t\t\t\t |\n");
    printf("==========================================================================\n");
    printf("==========================================================================\n");
}

int maintrieuser() {
    struct TrieNode *root = getNode(); 		// Inisialisasi root Trie

    int choice;
    char word[100], prefix[100];

    do {
    	system("cls");
        displayMenuUser(); 						// Menampilkan menu
        printf("Masukan pilihan (1/2/3): ");
        scanf("%d", &choice); 				// Membaca pilihan dari pengguna
        getchar();							// Membersihkan buffer masukan

        switch (choice) {
            case 1:
                char pilih;
                do {
                    printf("Masukan barang : ");
                    fgets(word, sizeof(word), stdin); 	// Membaca kata yang akan dimasukkan
                    word[strcspn(word, "\n")] = '\0'; 	// Menghapus karakter newline jika ada
                    insert(root, word); 				// Memasukkan kata ke dalam Trie

                    printf("Masukan Barang lain?(Y/N):");
                    scanf(" %c", &pilih); 					// Membaca pilihan untuk memasukkan kata lagi
                    getchar(); 								// Membersihkan buffer masukan
                } while (pilih == 'Y' || pilih == 'y'); 	// Melanjutkan loop jika pengguna memilih 'Y' atau 'y'
                system("CLS"); 								// Membersihkan layar
                break;
            case 2:
                printf("Masukan barang yang ingin dicari (Prefix): ");
                fgets(prefix, sizeof(prefix), stdin); 					// Membaca prefiks yang akan dicari
                prefix[strcspn(prefix, "\n")] = '\0'; 					// Menghapus karakter newline jika ada
                printf("Barang dengan prefix \"%s\":\n", prefix);
                search(root, prefix); 									// Mencari kata-kata dengan prefiks yang diberikan
                system("pause");
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n"); // Pesan untuk pilihan yang tidak valid
        }
    } while (choice != 3); // Melanjutkan loop hingga pengguna memilih untuk keluar

    return 0;
}

int maintrieadmin() {
    struct TrieNode *root = getNode(); 		// Inisialisasi root Trie

    int choice;
    char word[100], prefix[100];

    do {
    	system("cls");
        displayMenuAdmin(); 						// Menampilkan menu
        printf("Masukan pilihan (1/2/3): ");
        scanf("%d", &choice); 				// Membaca pilihan dari pengguna
        getchar();							// Membersihkan buffer masukan

        switch (choice) {
            case 1:
                char pilih;
                do {
                    printf("Masukan barang : ");
                    fgets(word, sizeof(word), stdin); 	// Membaca kata yang akan dimasukkan
                    word[strcspn(word, "\n")] = '\0'; 	// Menghapus karakter newline jika ada
                    insert(root, word); 				// Memasukkan kata ke dalam Trie

                    printf("Masukan Barang lain?(Y/N):");
                    scanf(" %c", &pilih); 					// Membaca pilihan untuk memasukkan kata lagi
                    getchar(); 								// Membersihkan buffer masukan
                } while (pilih == 'Y' || pilih == 'y'); 	// Melanjutkan loop jika pengguna memilih 'Y' atau 'y'
                system("CLS"); 								// Membersihkan layar
                break;
            case 2:
                printf("Masukan barang yang ingin dicari (Prefix): ");
                fgets(prefix, sizeof(prefix), stdin); 					// Membaca prefiks yang akan dicari
                prefix[strcspn(prefix, "\n")] = '\0'; 					// Menghapus karakter newline jika ada
                printf("Barang dengan prefix \"%s\":\n", prefix);
                search(root, prefix); 									// Mencari kata-kata dengan prefiks yang diberikan
                system("pause");
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a valid option.\n"); // Pesan untuk pilihan yang tidak valid
        }
    } while (choice != 3); // Melanjutkan loop hingga pengguna memilih untuk keluar

    return 0;
}
