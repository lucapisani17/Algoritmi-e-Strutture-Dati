LETTURA DA FILE
FILE* file = fopen("input.txt", "r"); // Apri il file in modalità di lettura

    if (!file) {
        fprintf(stderr, "Impossibile aprire il file input.txt\n");
        return 1;
    }


//COMUNI AL DIVIDE ET IMPERA

//ALBERI

// Definizione della struttura del nodo
 struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Funzione per creare un nuovo nodo
struct TreeNode* new_node(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Funzione per convertire l'array ordinato in un BST
struct TreeNode* sorted_array_to_bst(int* nums, int start, int end) {
    if (start > end)
        return NULL //verifico che l'array non sia nullo

    int mid = (start + end) / 2; //trovo il punto medio dell'array che sará la mia radice 
    struct TreeNode* root = new_node(nums[mid]);

    root->left = sorted_array_to_bst(nums, start, mid - 1); // attacco alla nuova radice i sottoalberi di destra e sinistra richiamando la funzione di conversione
    //lo start dell array di sinistrasará sempre il primo, mentre end sará l 'elemento prima di quello nel punto medio, quindi mid-1. Viceverse mid+1 sará 
    //lo start per l'array di destra
    root->right = sorted_array_to_bst(nums, mid + 1, end);

    return root;
}

//Funzione per eseguire una visita in ordine dell'albero non necessaria
void inorder_traversal(struct TreeNode* node) {
    if (node == NULL)
        return;

    inorder_traversal(node->left);
    printf("%d ", node->val);
    inorder_traversal(node->right);
}

//RICERCA BINARIA RICORSIVA
int onecounter_recursive(int array[], int start, int end) {
    if (start > end) {
        return 0;
    }

    if (start == end) {
        return (array[start] == 1) ? 1 : 0;
    }

    int mid = (start + end) / 2;

    int left_count = onecounter_recursive(array, start, mid);
    int right_count = onecounter_recursive(array, mid + 1, end);

    return left_count + right_count;
}

//RICERCA ELEMENTO MAJOR

int find_candidate(int array[], int dim) {
    int count = 1;
    int candidate = array[0];

    for (int i = 1; i < dim; i++) {
        if (array[i] == candidate) {
            count++;
        } else {
            count--;
        }

        if (count == 0) {
            candidate = array[i];
            count = 1;
        }
    }

    return candidate;
}

int is_majority(int array[], int dim, int candidate) {
    int count = 0;

    for (int i = 0; i < dim; i++) {
        if (array[i] == candidate) {
            count++;
        }
    }

    return (count > dim / 2);
}

int majority_element_divide_and_conquer(int array[], int start, int end) {
    if (start == end) {
        return array[start];
    }

    int mid = (start + end) / 2;

    int left_majority = majority_element_divide_and_conquer(array, start, mid);
    int right_majority = majority_element_divide_and_conquer(array, mid + 1, end);

    if (left_majority == right_majority) {
        return left_majority;
    }

    int left_majority_count = is_majority(array, end - start + 1, left_majority);
    int right_majority_count = is_majority(array, end - start + 1, right_majority);

    if (left_majority_count > (end - start + 1) / 2) {
        return left_majority;
    }

    if (right_majority_count > (end - start + 1) / 2) {
        return right_majority;
    }

    return -1; // Nessun elemento maggioritario
}

//// Funzione ricorsiva per costruire l'albero massimo
struct TreeNode* constructMaximumBinaryTree(int nums[], int start, int end) {
    if (start > end)
        return NULL;
    //mi trovo il max inex cioé l'elemento piú grande dell array con la funzione scritta sopra e lo uso per creare la radice attraverso la funzione di creazione del nodo
    int maxIndex = findMaxIndex(nums, start, end);
    struct TreeNode* root = newNode(nums[maxIndex]);

    // Avendo adesso un nuovo nodo radice che da struct ha un valore e un left e right nulli, procedo a richiamare ricorsivamente la funzione a destra e sinistra per costruire i due sottoalberi
    root->left = constructMaximumBinaryTree(nums, start, maxIndex - 1);
    root->right = constructMaximumBinaryTree(nums, maxIndex + 1, end);

    return root;
}

// Funzione per stampare l'albero (pre-order traversal)
void printTree(struct TreeNode* node) {
    if (node == NULL)
        return;

    printf("%d ", node->val);

    printTree(node->left);
    printTree(node->right);
}

//ALBERO MASSIMO BILANCIATO Mi calcolo il nodo radice partendo dall'input chealtro non é che un array di elementi. La radice la prendo sempre trovando il valore medio e poi richiamo la funzione ricorsivamente a destra e sinistra per i due sottoalberi
struct TreeNode* sortedArrayToBST(int* nums, int left, int right) {
    if (left > right) {
        return NULL;
    }

    int mid = (left + right) / 2;
    struct TreeNode* root = newNode(nums[mid]);

    root->left = sortedArrayToBST(nums, left, mid - 1);
    root->right = sortedArrayToBST(nums, mid + 1, right);

    return root;
}

//EXTRA-QUADTREE
// Definition for a Quad-Tree node
struct Node {
    bool val;
    bool isLeaf;
    struct Node* topLeft;
    struct Node* topRight;
    struct Node* bottomLeft;
    struct Node* bottomRight;
};

// Function to create a new Quad-Tree node
struct Node* newNode(bool val, bool isLeaf, struct Node* topLeft, struct Node* topRight, struct Node* bottomLeft, struct Node* bottomRight) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->val = val;
    node->isLeaf = isLeaf;
    node->topLeft = topLeft;
    node->topRight = topRight;
    node->bottomLeft = bottomLeft;
    node->bottomRight = bottomRight;
    return node;
}
struct Node* construct(int** grid, int gridSize, int* gridColSize) {
    return constructQuadTree(grid, 0, 0, gridSize, 0, gridColSize[0]);
}
struct Node* constructQuadTree(int** grid, int x, int y, int size, int offsetX, int offsetY) {
    if (size == 1) {
        return newNode(grid[x][y] == 1, true, NULL, NULL, NULL, NULL);
    }

    int newSize = size / 2;

    struct Node* topLeft = constructQuadTree(grid, x, y, newSize, offsetX, offsetY);
    struct Node* topRight = constructQuadTree(grid, x, y + newSize, newSize, offsetX, offsetY);
    struct Node* bottomLeft = constructQuadTree(grid, x + newSize, y, newSize, offsetX, offsetY);
    struct Node* bottomRight = constructQuadTree(grid, x + newSize, y + newSize, newSize, offsetX, offsetY);

    bool isLeaf = false;
    if (topLeft->isLeaf && topRight->isLeaf && bottomLeft->isLeaf && bottomRight->isLeaf) {
        if (topLeft->val == topRight->val && topRight->val == bottomLeft->val && bottomLeft->val == bottomRight->val) {
            isLeaf = true;
        }
    }

    if (isLeaf) {
        return newNode(topLeft->val, true, NULL, NULL, NULL, NULL);
    } else {
        return newNode(true, false, topLeft, topRight, bottomLeft, bottomRight);
    }
}


//K ESIMO elemento piú grande in un array non ordinato
int partition(int* nums, int left, int right) {
    int pivot = nums[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (nums[j] >= pivot) {
            i++;
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
        }
    }

    int temp = nums[i + 1];
    nums[i + 1] = nums[right];
    nums[right] = temp;

    return i + 1;
}
int findKthLargest(int* nums, int left, int right, int k) {
    if (left <= right) {
        int pivotIndex = partition(nums, left, right);

        if (pivotIndex == k - 1) {
            return nums[pivotIndex];
        } else if (pivotIndex < k - 1) {
            return findKthLargest(nums, pivotIndex + 1, right, k);
        } else {
            return findKthLargest(nums, left, pivotIndex - 1, k);
        }
    }

    return -1; // In caso di errore
}

//EXTRA - k punti  piú vicini all origine
// Definizione di una struttura per rappresentare un punto
struct Point {
    int x;
    int y;
};
// Funzione per calcolare la distanza euclidea tra due punti
double distance(struct Point p) {
    return sqrt(p.x * p.x + p.y * p.y);
}
// Funzione di partizione per l'algoritmo di selezione rapida
int partition(struct Point arr[], int left, int right) {
    struct Point pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (distance(arr[j]) <= distance(pivot)) {
            i++;
            struct Point temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    struct Point temp = arr[i + 1];
    arr[i + 1] = arr[right];
    arr[right] = temp;

    return i + 1;
}
// Algoritmo di selezione rapida per trovare il k-esimo punto più vicino all'origine
void quickSelect(struct Point arr[], int left, int right, int k) {
    if (left <= right) {
        int pivotIndex = partition(arr, left, right);

        if (pivotIndex == k) {
            return;
        } else if (pivotIndex < k) {
            quickSelect(arr, pivotIndex + 1, right, k);
        } else {
            quickSelect(arr, left, pivotIndex - 1, k);
        }
    }
}

//Beautiful
int* mergeArrays(int* arr1, int size1, int* arr2, int size2) {
    int* result = (int*)malloc((size1 + size2) * sizeof(int));

    int i = 0, j = 0, k = 0;

    while (i < size1 && j < size2) {
        result[k++] = arr1[i++];
        result[k++] = arr2[j++];
    }

    while (i < size1) {
        result[k++] = arr1[i++];
    }

    while (j < size2) {
        result[k++] = arr2[j++];
    }

    return result;
}
int* beautifulArray(int n, int* returnSize) {
    *returnSize = n;

    if (n == 1) {
        int* result = (int*)malloc(sizeof(int));
        result[0] = 1;
        return result;
    }

    int leftSize = (n + 1) / 2;
    int* left = beautifulArray(leftSize, returnSize);

    int rightSize = n / 2;
    int* right = beautifulArray(rightSize, returnSize);

    return mergeArrays(left, leftSize, right, rightSize);
}

//CONVERSIONE SORTED LIST TO BST
// Definizione per la struttura del nodo di una lista concatenata
struct ListNode {
    int val;
    struct ListNode* next;
};
// Definizione per la struttura del nodo di un albero binario
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};
// Funzione per creare un nuovo nodo della lista concatenata
struct ListNode* newListNode(int val) {
    struct ListNode* node = (struct ListNode*)malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}
// Funzione per creare un nuovo nodo dell'albero binario
struct TreeNode* newTreeNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}
// Funzione che converte una lista concatenata ordinata in un albero binario bilanciato
struct TreeNode* sortedListToBST(struct ListNode* head, int start, int end) {
    if (start > end) {
        return NULL;
    }

    int mid = (start + end) / 2;

    // Trova il nodo medio nella lista
    struct ListNode* current = head;
    for (int i = start; i < mid; i++) {
        current = current->next;
    }

    // Crea un nuovo nodo dell'albero con il valore del nodo medio
    struct TreeNode* root = newTreeNode(current->val);

    // Ricostruisci l'albero ricorsivamente per le sotto-liste sinistra e destra
    root->left = sortedListToBST(head, start, mid - 1);
    root->right = sortedListToBST(current->next, mid + 1, end);

    return root;
}
// Funzione per stampare l'albero in ordine
void printTree(struct TreeNode* root) {
    if (root == NULL) {
        return;
    }

    printTree(root->left);
    printf("%d ", root->val);
    printTree(root->right);
}


//Sort an array in ascending, dal piú piccolo al piú grande (Merge)
// Funzione per combinare due sottoarray ordinati
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int Left[n1], Right[n2];

    for (int i = 0; i < n1; i++)
        Left[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        Right[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (Left[i] <= Right[j]) {
            arr[k] = Left[i];
            i++;
        } else {
            arr[k] = Right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = Left[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = Right[j];
        j++;
        k++;
    }
}

// Funzione ricorsiva per dividere e ordinare l'array
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}


//Ricerca di un valore in unam atrice di interi ordinata
int searchMatrixRecursive(int** matrix, int startRow, int endRow, int startCol, int endCol, int target) {
    if (startRow > endRow || startCol > endCol) {
        return 0;
    }

    int midRow = (startRow + endRow) / 2;
    int midCol = (startCol + endCol) / 2;

    if (matrix[midRow][midCol] == target) {
        return 1;
    } else if (matrix[midRow][midCol] < target) {
        return searchMatrixRecursive(matrix, startRow, midRow, midCol + 1, endCol, target) ||
               searchMatrixRecursive(matrix, midRow + 1, endRow, startCol, midCol, target);
    } else {
        return searchMatrixRecursive(matrix, startRow, midRow - 1, startCol, endCol, target) ||
               searchMatrixRecursive(matrix, midRow, endRow, startCol, midCol - 1, target);
    }
}
int searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target) {
    if (matrixSize == 0 || *matrixColSize == 0) {
        return 0;
    }

    return searchMatrixRecursive(matrix, 0, matrixSize - 1, 0, *matrixColSize - 1, target);
}


//ricerca del sottoarray with the largest sum, and return its sum
int max(int a, int b) {
    return (a > b) ? a : b;
}
int maxCrossingSum(int* nums, int low, int mid, int high) {
    int leftSum = -9999;
    int sum = 0;
    for (int i = mid; i >= low; i--) {
        sum += nums[i];
        if (sum > leftSum) {
            leftSum = sum;
        }
    }

    int rightSum = -9999;
    sum = 0;
    for (int i = mid + 1; i <= high; i++) {
        sum += nums[i];
        if (sum > rightSum) {
            rightSum = sum;
        }
    }

    return leftSum + rightSum;
}
int maxSubArrayRecursive(int* nums, int low, int high) {
    if (low == high) {
        return nums[low];
    }

    int mid = (low + high) / 2;

    return max(max(maxSubArrayRecursive(nums, low, mid), maxSubArrayRecursive(nums, mid + 1, high)),
               maxCrossingSum(nums, low, mid, high));
}
int maxSubArray(int* nums, int numsSize) {
    return maxSubArrayRecursive(nums, 0, numsSize - 1);
}


//Merge K sorted list
// Definition for singly-linked list.
struct ListNode {
    int val;
    struct ListNode *next;
};
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    if (l1->val < l2->val) {
        l1->next = mergeTwoLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeTwoLists(l1, l2->next);
        return l2;
    }
}
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0) return NULL;
    if (listsSize == 1) return lists[0];
    if (listsSize == 2) return mergeTwoLists(lists[0], lists[1]);

    int mid = listsSize / 2;
    struct ListNode* left = mergeKLists(lists, mid);
    struct ListNode* right = mergeKLists(lists + mid, listsSize - mid);

    return mergeTwoLists(left, right);
}


//Skyline
// Struttura per rappresentare un punto
typedef struct {
    int x; // Coordinata x
    int y; // Altezza y
} Point;
// Struttura per rappresentare un edificio
typedef struct {
    int left;   // Coordinata x sinistra
    int right;  // Coordinata x destra
    int height; // Altezza
} Building;
// Funzione per unire due skyline in un nuovo skyline
Point* mergeSkyline(Point* leftSkyline, int leftSize, Point* rightSkyline, int rightSize, int* mergedSize) {
    int leftH = 0, rightH = 0;
    int i = 0, j = 0, h, maxH;

    *mergedSize = 0;
    Point* mergedSkyline = (Point*)malloc(sizeof(Point) * (leftSize + rightSize));

    while (i < leftSize && j < rightSize) {
        if (leftSkyline[i].x < rightSkyline[j].x) {
            h = leftSkyline[i].y;
            i++;
        } else if (leftSkyline[i].x > rightSkyline[j].x) {
            h = rightSkyline[j].y;
            j++;
        } else {
            h = leftSkyline[i].y > rightSkyline[j].y ? leftSkyline[i].y : rightSkyline[j].y;
            i++;
            j++;
        }

        if (*mergedSize == 0 || h != mergedSkyline[*mergedSize - 1].y) {
            mergedSkyline[*mergedSize].x = leftSkyline[i - 1].x;
            mergedSkyline[*mergedSize].y = h;
            (*mergedSize)++;
        }
    }

    while (i < leftSize) {
        mergedSkyline[*mergedSize] = leftSkyline[i];
        (*mergedSize)++;
        i++;
    }

    while (j < rightSize) {
        mergedSkyline[*mergedSize] = rightSkyline[j];
        (*mergedSize)++;
        j++;
    }

    free(leftSkyline);
    free(rightSkyline);

    return mergedSkyline;
}
// Funzione principale per risolvere il problema usando l'approccio "Divide and Conquer with Heap"
Point* skyline(Building* buildings, int left, int right, int* skylineSize) {
    if (left == right) {
        Point* result = (Point*)malloc(sizeof(Point) * 2);
        result[0].x = buildings[left].left;
        result[0].y = buildings[left].height;
        result[1].x = buildings[left].right;
        result[1].y = 0;
        *skylineSize = 2;
        return result;
    }

    int mid = left + (right - left) / 2;
    int leftSize, rightSize;

    Point* leftSkyline = skyline(buildings, left, mid, &leftSize);
    Point* rightSkyline = skyline(buildings, mid + 1, right, &rightSize);

    return mergeSkyline(leftSkyline, leftSize, rightSkyline, rightSize, skylineSize);
}


//Mediana di due array ordinati
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    if (nums1Size > nums2Size) {
        int* temp = nums1;
        nums1 = nums2;
        nums2 = temp;
        int tempSize = nums1Size;
        nums1Size = nums2Size;
        nums2Size = tempSize;
    }

    int m = nums1Size;
    int n = nums2Size;
    int imin = 0, imax = m, halfLen = (m + n + 1) / 2;

    while (imin <= imax) {
        int i = (imin + imax) / 2;
        int j = halfLen - i;

        if (i < m && nums2[j-1] > nums1[i]) {
            imin = i + 1;
        } else if (i > 0 && nums1[i-1] > nums2[j]) {
            imax = i - 1;
        } else {
            int maxLeft, minRight;

            if (i == 0) { maxLeft = nums2[j-1]; }
            else if (j == 0) { maxLeft = nums1[i-1]; }
            else { maxLeft = nums1[i-1] > nums2[j-1] ? nums1[i-1] : nums2[j-1]; }

            if ((m + n) % 2 == 1) { return maxLeft; }

            if (i == m) { minRight = nums2[j]; }
            else if (j == n) { minRight = nums1[i]; }
            else { minRight = nums1[i] < nums2[j] ? nums1[i] : nums2[j]; }

            return (maxLeft + minRight) / 2.0;
        }
    }

    return 0.0;
}


//Count Rage Sum
int countRangeSums(int* nums, int numsSize, int lower, int upper, int start, int end) {
    if (start == end) {
        return (nums[start] >= lower && nums[start] <= upper) ? 1 : 0;
    }

    int mid = (start + end) / 2;
    int count = 0;

    int* prefixSum = (int*)malloc((end - start + 1) * sizeof(int));
    prefixSum[0] = nums[start];
    for (int i = 1; i <= end - start; i++) {
        prefixSum[i] = prefixSum[i - 1] + nums[start + i];
    }

    for (int i = mid + 1; i <= end; i++) {
        for (int j = start; j <= mid; j++) {
            int sum = prefixSum[i - start] - (j > start ? prefixSum[j - 1 - start] : 0);
            if (sum >= lower && sum <= upper) {
                count++;
            }
        }
    }

    count += countRangeSums(nums, numsSize, lower, upper, start, mid);
    count += countRangeSums(nums, numsSize, lower, upper, mid + 1, end);

    free(prefixSum);

    return count;
}
int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    return countRangeSums(nums, numsSize, lower, upper, 0, numsSize - 1);
}


//SIGNOR ROSSI
// Funzione per calcolare la somma delle distanze minime
int minDistanceSum(int relatives[], int start, int end) {
    if (start >= end) {
        return 0;
    }

    int mid = (start + end) / 2;

    // Trova la mediana dei parenti
    int median = relatives[mid];

    // Calcola la somma delle distanze
    int sum = 0;
    for (int i = start; i <= end; i++) {
        sum += abs(relatives[i] - median);
    }

    // Dividi il problema in due sottoarray e somma le distanze
    int leftSum = minDistanceSum(relatives, start, mid - 1);
    int rightSum = minDistanceSum(relatives, mid + 1, end);

    return sum + leftSum + rightSum;
}
int main() {
    int numTests;
    scanf("%d", &numTests);

    for (int t = 0; t < numTests; t++) {
        int numRelatives;
        scanf("%d", &numRelatives);

        int relatives[numRelatives];
        for (int i = 0; i < numRelatives; i++) {
            scanf("%d", &relatives[i]);
        }

        // Ordina l'array dei parenti
        for (int i = 0; i < numRelatives - 1; i++) {
            for (int j = 0; j < numRelatives - i - 1; j++) {
                if (relatives[j] > relatives[j+1]) {
                    int temp = relatives[j];
                    relatives[j] = relatives[j+1];
                    relatives[j+1] = temp;
                }
            }
        }

        // Calcola la somma delle distanze minime
        int minSum = minDistanceSum(relatives, 0, numRelatives - 1);

        printf("%d\n", minSum);
    }

    return 0;
}



