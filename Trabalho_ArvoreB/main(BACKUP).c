#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX_KEYS 4

typedef struct TreeNode {
    char* keys[MAX_KEYS];
    struct TreeNode* children[MAX_KEYS + 1];
    int key_count;
    bool leaf;
} TreeNode;

typedef struct BTree {
    TreeNode* root;
} BTree;

BTree* initializeBTree() {
    BTree* tree = (BTree*)malloc(sizeof(BTree));
    if (tree) {
        TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
        if (root) {
            root->key_count = 0;
            root->leaf = true;
            tree->root = root;
        }
    }
    return tree;
}

void split_child(TreeNode* parent, int index, TreeNode* child) {
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->leaf = child->leaf;
    new_node->key_count = MAX_KEYS - 1;

    for (int i = 0; i < MAX_KEYS - 1; i++) {
        new_node->keys[i] = child->keys[i + MAX_KEYS];
        new_node->children[i] = child->children[i + MAX_KEYS];
    }
    new_node->children[MAX_KEYS - 1] = child->children[MAX_KEYS];

    for (int i = parent->key_count; i > index; i--) {
        parent->keys[i] = parent->keys[i - 1];
        parent->children[i + 1] = parent->children[i];
    }
    parent->keys[index] = child->keys[MAX_KEYS - 1];
    parent->children[index + 1] = new_node;
    parent->key_count++;

    for (int i = MAX_KEYS - 1; i < 2 * MAX_KEYS - 1; i++) {
        child->keys[i] = NULL;
        child->children[i + 1] = NULL;
    }
    child->key_count = MAX_KEYS;
    child->children[MAX_KEYS] = new_node;
}

void insert_non_full(TreeNode* node, char* filename) {
    int i = node->key_count - 1;
    if (node->leaf) {
        while (i >= 0 && strcmp(filename, node->keys[i]) < 0) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = strdup(filename);
        node->key_count++;
    } else {
        while (i >= 0 && strcmp(filename, node->keys[i]) < 0) {
            i--;
        }
        i++;
        if (node->children[i]->key_count == MAX_KEYS) {
            split_child(node, i, node->children[i]);
            if (strcmp(filename, node->keys[i]) > 0) {
                i++;
            }
        }
        insert_non_full(node->children[i], filename);
    }
}

void insert(BTree* tree, char* filename) {
    TreeNode* root = tree->root;
    if (root->key_count == MAX_KEYS) {
        TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
        new_node->children[0] = root;
        tree->root = new_node;
        split_child(new_node, 0, root);
        insert_non_full(new_node, filename);
    } else {
        insert_non_full(root, filename);
    }
}

void displayFileInfo(TreeNode* node, char* filename) {
    for (int i = 0; i < node->key_count; i++) {
        if (strcmp(filename, node->keys[i]) == 0) {
            printf("File %s found!\n", filename);
            return;
        }
    }

    if (!node->leaf) {
        int i = 0;
        while (i < node->key_count && strcmp(filename, node->keys[i]) > 0) {
            i++;
        }
        displayFileInfo(node->children[i], filename);
    } else {
        printf("File %s not found.\n", filename);
    }
}

void searchAndDisplay(BTree* tree, char* filename) {
    displayFileInfo(tree->root, filename);
}

int main() {
    DIR* dir = opendir("C:\\");
    struct dirent* entry;

    if (dir) {
        BTree* tree = initializeBTree();
        int fileCount = 0;  // Adicionamos uma contagem de arquivos para verificar

        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_REG) {  // Verifique se é um arquivo regular
                char* filename = strdup(entry->d_name);
                insert(tree, filename);
                fileCount++;
            } else if (entry->d_type == DT_DIR) {  // Verifique se é um diretório
                // Processar diretório (adicionar lógica apropriada aqui, se necessário)
                char* dirname = strdup(entry->d_name);
                // Por enquanto, apenas imprima o nome do diretório
                printf("Directory: %s\n", dirname);
            }
        }

        printf("\n\nList of files read:\n");
        TreeNode* current = tree->root;
        while (!current->leaf) {
            current = current->children[0];
        }
        while (current != NULL) {
            for (int i = 0; i < current->key_count; i++) {
                printf("- %s\n", current->keys[i]);
            }
            current = current->children[MAX_KEYS];
        }

        closedir(dir);

        if (fileCount > 0) {
            printf("\n\nDirectory was read successfully. Found %d files.\n", fileCount);
        } else {
            printf("No regular files found in the directory.\n");
        }

        // Exemplo de busca e exibição de informações sobre um arquivo
        char* search_filename = "AiOLog.txt";
        searchAndDisplay(tree, search_filename);

        // Agora, sua árvore B está preenchida com os nomes dos arquivos do diretório.
        // Você pode realizar buscas e exibir informações conforme necessário.
    } else {
        printf("Failed to open the directory.\n");
    }

    return 0;
}