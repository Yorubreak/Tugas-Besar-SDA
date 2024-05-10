#ifndef SEARCH_H
#define SEARCH_H
#include <stdio.h> // Library untuk input-output standar
#include <stdlib.h> // Library untuk fungsi-fungsi umum
#include <string.h> // Library untuk manipulasi string
#include <stdbool.h> // Library untuk tipe data boolean
#include "login.h"

#define ALPHABET_SIZE 26 // Ukuran abjad Inggris

// Node structure untuk Trie
struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE]; 	// Anak-anak dari sebuah node, sesuai dengan setiap huruf dalam abjad
    bool isEndOfWord; 							// Menyatakan apakah sebuah node adalah akhir dari sebuah kata
};

// Fungsi untuk menginisialisasi sebuah node Trie// Function to initialize a Trie node
struct TrieNode *getNode();

// Fungsi untuk memasukkan sebuah kata ke dalam Trie
void insert(struct TrieNode *root, char *word);

// Fungsi rekursif untuk menelusuri Trie dan mencetak semua kata dengan awalan yang diberikan
void traverseTrie(struct TrieNode *node, char *prefix);

// Fungsi untuk mencari kata-kata dalam Trie berdasarkan awalan yang diberikan
void search(struct TrieNode *root, char *prefix);

// Fungsi untuk menampilkan opsi menu
void displayMenuUser();
void displayMenuAdmin();
int maintrieuser();
int maintrieadmin(); 
#endif /* TRIE_H */

