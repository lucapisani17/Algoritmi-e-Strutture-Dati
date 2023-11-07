LETTURA DA FILE
FILE* file = fopen("input.txt", "r"); // Apri il file in modalità di lettura

    if (!file) {
        fprintf(stderr, "Impossibile aprire il file input.txt\n");
        return 1;
    }


//COMUNI AL BACKTRACKING
// Definizione della struttura del nodo dell'albero
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};
// Funzione di utilità per stampare un percorso
void printPath(int* path, int pathLength) {
    for (int i = 0; i < pathLength; i++) {
        printf("%d", path[i]);
        if (i < pathLength - 1) {
            printf("->");
        }
    }
    printf("\n");
}
// Funzione di backtracking per trovare tutti i percorsi radice-foglia
void findPaths(struct TreeNode* node, int* path, int pathLength) {
    if (node == NULL) {
        return;
    }

    path[pathLength] = node->val;
    pathLength++;

    if (node->left == NULL && node->right == NULL) {
        printPath(path, pathLength);
    } else {
        findPaths(node->left, path, pathLength);
        findPaths(node->right, path, pathLength);
    }
}
// Funzione principale per trovare tutti i percorsi radice-foglia
void rootToLeafPaths(struct TreeNode* root) {
    int* path = (int*)malloc(1000 * sizeof(int)); // Allocazione di memoria per il percorso
    findPaths(root, path, 0);
    free(path); // Libera la memoria allocata per il percorso
}
int main() {
    // Creazione dell'albero di esempio
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = 1;
    root->left = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left->val = 2;
    root->left->left = NULL;
    root->left->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->left->right->val = 5;
    root->left->right->left = NULL;
    root->left->right->right = NULL;
    root->right = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->right->val = 3;
    root->right->left = NULL;
    root->right->right = NULL;

    // Trova e stampa tutti i percorsi radice-foglia
    rootToLeafPaths(root);

    // Libera la memoria allocata per l'albero
    free(root->left->right);
    free(root->left);
    free(root->right);
    free(root);

    return 0;
}


//tutti i percorsi dalla fonte al target
void backtrack(int** graph, int graphSize, int* graphColSize, int current, int target, int* path, int pathSize, int*** result, int* resultSize, int** resultColSize) {
    if (current == target) { // Se siamo arrivati al nodo di destinazione, abbiamo trovato un percorso
        *resultSize += 1; // Aumentiamo il conteggio dei percorsi trovati
        *result = (int**)realloc(*result, (*resultSize) * sizeof(int*)); // Riallochiamo la memoria per contenere il nuovo percorso
        (*resultColSize) = (int*)realloc(*resultColSize, (*resultSize) * sizeof(int)); // Riallochiamo la memoria per contenere la dimensione del nuovo percorso
        (*resultColSize)[*resultSize - 1] = pathSize; // Memorizziamo la dimensione del percorso corrente
        (*result)[*resultSize - 1] = (int*)malloc(pathSize * sizeof(int)); // Allochiamo la memoria per il percorso corrente

        // Copiamo il percorso corrente nel risultato
        for (int i = 0; i < pathSize; i++) {
            (*result)[*resultSize - 1][i] = path[i];
        }
        return;
    }

    // Altrimenti, esploriamo i nodi successivi
    for (int i = 0; i < graphColSize[current]; i++) {
        path[pathSize] = graph[current][i]; // Aggiungiamo il nodo corrente al percorso
        backtrack(graph, graphSize, graphColSize, graph[current][i], target, path, pathSize + 1, result, resultSize, resultColSize); // Chiamata ricorsiva per esplorare il nodo successivo
    }
}
int** allPathsSourceTarget(int** graph, int graphSize, int* graphColSize, int* returnSize, int** returnColumnSizes) {
    int** result = (int**)malloc(sizeof(int*)); // Allochiamo la memoria per contenere i percorsi
    *returnSize = 0; // Inizializziamo il numero di percorsi trovati
    *returnColumnSizes = (int*)malloc(sizeof(int)); // Allochiamo la memoria per contenere le dimensioni dei percorsi

    int* path = (int*)malloc(graphSize * sizeof(int)); // Allochiamo la memoria per contenere il percorso corrente
    path[0] = 0; // Il percorso inizia dal nodo 0
    int pathSize = 1; // La dimensione iniziale del percorso è 1

    backtrack(graph, graphSize, graphColSize, 0, graphSize - 1, path, pathSize, &result, returnSize, returnColumnSizes); // Chiamata iniziale alla funzione di backtracking

    free(path); // Liberiamo la memoria allocata per il percorso
    return result; // Restituiamo i percorsi trovati
}
int main() {
    int graphSize = 4;
    int* graphColSize = (int*)malloc(4 * sizeof(int));
    graphColSize[0] = 2; graphColSize[1] = 1; graphColSize[2] = 1; graphColSize[3] = 0;
    int* graph[4];
    int row1[] = {1, 2};
    int row2[] = {3};
    int row3[] = {3};
    int row4[] = {};
    graph[0] = row1;
    graph[1] = row2;
    graph[2] = row3;
    graph[3] = row4;

    int returnSize;
    int* returnColumnSizes;

    int** result = allPathsSourceTarget(graph, graphSize, graphColSize, &returnSize, &returnColumnSizes);

    printf("Output:\n");
    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
        free(result[i]);
    }

    free(graphColSize);
    free(result);
    free(returnColumnSizes);

    return 0;
}


//permutazioni: tutte le possibili permutazioni da un array di interi distinti
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void backtrack(int* nums, int numsSize, int** result, int* resultSize, int* path, int pathSize, int* used) {
    if (pathSize == numsSize) { // Se abbiamo completato un percorso, lo aggiungiamo al risultato
        *resultSize += 1; // Aumentiamo il conteggio dei risultati
        *result = (int**)realloc(*result, (*resultSize) * sizeof(int*)); // Riallochiamo la memoria per contenere il nuovo percorso
        (*result)[*resultSize - 1] = (int*)malloc(numsSize * sizeof(int)); // Allochiamo la memoria per il nuovo percorso

        // Copiamo il percorso corrente nel risultato
        for (int i = 0; i < numsSize; i++) {
            (*result)[*resultSize - 1][i] = path[i];
        }
        return;
    }

    for (int i = 0; i < numsSize; i++) {
        if (!used[i]) { // Se l'elemento non è stato ancora utilizzato
            path[pathSize] = nums[i]; // Aggiungiamo l'elemento al percorso
            used[i] = 1; // Contrassegniamo l'elemento come utilizzato
            backtrack(nums, numsSize, result, resultSize, path, pathSize + 1, used); // Chiamata ricorsiva per esplorare il prossimo elemento
            used[i] = 0; // Ripristiniamo l'elemento come non utilizzato
        }
    }
}
int** permute(int* nums, int numsSize, int* returnSize) {
    int** result = (int**)malloc(sizeof(int*)); // Allochiamo la memoria per contenere i risultati
    *returnSize = 0; // Inizializziamo il numero di risultati trovati

    int* path = (int*)malloc(numsSize * sizeof(int)); // Allochiamo la memoria per contenere il percorso corrente
    int* used = (int*)calloc(numsSize, sizeof(int)); // Allochiamo la memoria per tenere traccia degli elementi utilizzati

    backtrack(nums, numsSize, &result, returnSize, path, 0, used); // Chiamata iniziale alla funzione di backtracking

    free(path); // Liberiamo la memoria allocata per il percorso
    free(used); // Liberiamo la memoria allocata per l'array di controllo

    return result; // Restituiamo i risultati trovati
}
int main() {
    int nums[] = {1, 2, 3};
    int numsSize = 3;
    int returnSize;

    int** result = permute(nums, numsSize, &returnSize);

    printf("Output:\n");
    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < numsSize; j++) {
            printf("%d ", result[i][j]);
            free(result[i]);
        }
        printf("\n");
    }

    free(result);

    return 0;
}


//Maximum bitwise or
int maxBitwiseOR(int* nums, int numsSize, int currentOR, int index) {
    if (index >= numsSize) {
        return currentOR; // Restituiamo il risultato corrente
    }
    
    int includeCurrent = maxBitwiseOR(nums, numsSize, currentOR | nums[index], index + 1); // Calcoliamo l'OR includendo l'elemento corrente
    int excludeCurrent = maxBitwiseOR(nums, numsSize, currentOR, index + 1); // Calcoliamo l'OR senza includere l'elemento corrente
    
    return includeCurrent > excludeCurrent ? includeCurrent : excludeCurrent; // Restituiamo il massimo tra i due
}
int countMaxBitwiseORSubsets(int* nums, int numsSize) {
    int maxOR = maxBitwiseOR(nums, numsSize, 0, 0); // Calcoliamo il massimo OR usando la funzione di backtracking
    int count = 0; // Inizializziamo il contatore

    // Contiamo quante volte il massimo OR appare nell'array
    for (int i = 0; i < numsSize; i++) {
        if ((nums[i] | maxOR) == maxOR) {
            count++;
        }
    }

    return count; // Restituiamo il numero di subset con il massimo OR
}
int main() {
    int nums[] = {3, 1};
    int numsSize = 2;

    int result = countMaxBitwiseORSubsets(nums, numsSize);

    printf("Output: %d\n", result);

    return 0;
}


//Subesets: tutti i possibili sottoinsiemi da un array di interi unici
void backtrack(int* nums, int numsSize, int start, int* path, int pathSize, int** result, int* resultSize, int** resultColSize) {
    // Aggiungiamo il percorso corrente al risultato
    (*result)[*resultSize] = (int*)malloc(pathSize * sizeof(int));
    (*resultColSize)[*resultSize] = pathSize;
    for (int i = 0; i < pathSize; i++) {
        (*result)[*resultSize][i] = path[i];
    }
    (*resultSize)++;

    for (int i = start; i < numsSize; i++) {
        path[pathSize] = nums[i]; // Aggiungiamo l'elemento corrente al percorso
        backtrack(nums, numsSize, i + 1, path, pathSize + 1, result, resultSize, resultColSize); // Chiamata ricorsiva per esplorare il prossimo elemento
    }
}
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    // Allochiamo la memoria per contenere i risultati
    int** result = (int**)malloc(1 * sizeof(int*));
    int* resultColSize = (int*)malloc(1 * sizeof(int));
    *returnSize = 0;

    int* path = (int*)malloc(numsSize * sizeof(int)); // Allochiamo la memoria per contenere il percorso corrente

    backtrack(nums, numsSize, 0, path, 0, &result, returnSize, &resultColSize); // Chiamata iniziale alla funzione di backtracking

    free(path); // Liberiamo la memoria allocata per il percorso

    // Ridimensioniamo i risultati al giusto numero di subset
    result = (int**)realloc(result, (*returnSize) * sizeof(int*));
    resultColSize = (int*)realloc(resultColSize, (*returnSize) * sizeof(int));

    *returnColumnSizes = resultColSize; // Assegnamo il puntatore alle dimensioni delle colonne

    return result; // Restituiamo i risultati trovati
}
int main() {
    int nums[] = {1, 2, 3};
    int numsSize = 3;
    int returnSize;
    int* returnColumnSizes;

    int** result = subsets(nums, numsSize, &returnSize, &returnColumnSizes);

    printf("Output:\n");
    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
        free(result[i]);
    }

    free(result);
    free(returnColumnSizes);

    return 0;
}


//You have n  tiles, where each tile has one letter tiles[i] printed on it.
//Return the number of possible non-empty sequences of letters you can make using the letters printed on those tiles.
void backtrack(char* tiles, int* visited, int* resultSize, int level) {
    if (level > 0) {
        (*resultSize)++; // Aumentiamo il conteggio dei risultati
    }

    for (int i = 0; i < strlen(tiles); i++) {
        if (visited[i] == 0) { // Se il carattere non è stato ancora utilizzato
            if (i > 0 && tiles[i] == tiles[i-1] && visited[i-1] == 0) {
                continue; // Evitiamo duplicati
            }
            visited[i] = 1; // Contrassegniamo il carattere come utilizzato
            backtrack(tiles, visited, resultSize, level + 1); // Chiamata ricorsiva per esplorare il prossimo carattere
            visited[i] = 0; // Ripristiniamo il carattere come non utilizzato
        }
    }
}
int numTilePossibilities(char* tiles) {
    int* visited = (int*)calloc(strlen(tiles), sizeof(int)); // Allochiamo la memoria per tenere traccia dei caratteri utilizzati
    int resultSize = 0;

    qsort(tiles, strlen(tiles), sizeof(char), strcmp); // Ordiniamo i caratteri per evitare duplicati

    backtrack(tiles, visited, &resultSize, 0); // Chiamata iniziale alla funzione di backtracking

    free(visited); // Liberiamo la memoria allocata per l'array di controllo

    return resultSize; // Restituiamo il numero di sequenze possibili
}
int main() {
    char tiles[] = "AAB";
    int result = numTilePossibilities(tiles);

    printf("Output: %d\n", result);

    return 0;
}


//Letter case permutation: Given a string s, you can transform every letter individually to be lowercase or uppercase to create another string.
void backtrack(char* s, int index, char* path, char** result, int* resultSize) {
    if (index == strlen(s)) {
        char* copy = (char*)malloc((strlen(s) + 1) * sizeof(char)); // Allocazione di memoria per una copia del percorso
        strcpy(copy, path); // Copia il percorso in copy
        result[*resultSize] = copy; // Aggiungi copy ai risultati
        (*resultSize)++;
        return;
    }

    // Prova a trasformare il carattere corrente in minuscolo
    path[index] = tolower(s[index]);
    backtrack(s, index + 1, path, result, resultSize);

    // Prova a trasformare il carattere corrente in maiuscolo
    path[index] = toupper(s[index]);
    backtrack(s, index + 1, path, result, resultSize);
}
char** letterCasePermutation(char* s, int* returnSize) {
    int resultSize = 0;
    char** result = (char**)malloc(1 * sizeof(char*));
    char* path = (char*)malloc((strlen(s) + 1) * sizeof(char)); // Allocazione di memoria per il percorso
    strcpy(path, s);

    backtrack(s, 0, path, result, &resultSize); // Chiamata iniziale alla funzione di backtracking

    free(path); // Libera la memoria allocata per il percorso

    *returnSize = resultSize;
    return result; // Restituisce i risultati trovati
}
int main() {
    char s[] = "a1b2";
    int returnSize;
    char** result = letterCasePermutation(s, &returnSize);

    printf("Output:\n");
    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }

    free(result);

    return 0;
}


//Happy String
// Funzione per generare le stringhe felici
void generateHappyStrings(char* result, int n, int* k, int index, char prevChar) {
    if (*k == 0) {
        return; // Abbiamo già trovato la k-esima stringa felice
    }
    
    if (index == n) {
        (*k)--;
        if (*k == 0) {
            printf("%s\n", result); // Abbiamo trovato la k-esima stringa felice
        }
        return;
    }

    for (char c = 'a'; c <= 'c'; c++) {
        if (c != prevChar) {
            result[index] = c;
            generateHappyStrings(result, n, k, index + 1, c);
        }
    }
}
// Funzione principale che restituisce la k-esima stringa felice di lunghezza n
char* kthHappyString(int n, int k) {
    char* result = (char*)malloc((n + 1) * sizeof(char));
    result[n] = '\0';
    
    int count = 0; // Contatore per tener traccia del numero di stringhe felici trovate
    
    // Genera le stringhe felici a partire dalla prima lettera
    for (char c = 'a'; c <= 'c'; c++) {
        result[0] = c;
        generateHappyStrings(result, n, &k, 1, c);
    }
    
    if (k == 0) {
        return result;
    } else {
        return ""; // Non ci sono abbastanza stringhe felici di lunghezza n
    }
}
int main() {
    int n = 1;
    int k = 3;
    char* result = kthHappyString(n, k);
    printf("Output: %s\n", result);
    free(result);
    return 0;
}


//LABIRITNO FATTO IN CLASSE
#include <stdio.h>
#define N 4 // Dimensione del labirinto
void stampa_soluzione(int soluzione[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", soluzione[i][j]);
        }
        printf("\n");
    }
}
int is_valid_move(int labirinto[N][N], int x, int y, int soluzione[N][N]) {
    return (x >= 0 && y >= 0 && x < N && y < N && labirinto[x][y] == 1 && soluzione[x][y] == 0);
}
int risolvi_labirinto(int labirinto[N][N], int x, int y, int soluzione[N][N]) {
    if (x == N-1 && y == N-1) {
        soluzione[x][y] = 1;
        return 1;
    }

    if (is_valid_move(labirinto, x, y, soluzione)) {
        soluzione[x][y] = 1;

        if (risolvi_labirinto(labirinto, x+1, y, soluzione) || risolvi_labirinto(labirinto, x, y+1, soluzione)) {
            return 1;
        }

        soluzione[x][y] = 0;
    }

    return 0;
}
int main() {
    int labirinto[N][N] = {
        {1, 0, 1, 1},
        {1, 1, 1, 0},
        {0, 0, 1, 1},
        {0, 0, 1, 1}
    };

    int soluzione[N][N] = {0};

    if (risolvi_labirinto(labirinto, 0, 0, soluzione)) {
        stampa_soluzione(soluzione);
    } else {
        printf("Non esiste un percorso valido nel labirinto.\n");
    }

    return 0;
}


