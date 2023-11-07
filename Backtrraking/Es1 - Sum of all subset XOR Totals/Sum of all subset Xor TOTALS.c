//coplessitá O(2^n)

#include <stdio.h>

int xorTotal(int* nums, int numsSize, int idx, int currentXor) {
    if (idx == numsSize) {
        return currentXor;
    }
    
    // Calcola la XOR totale senza includere l'elemento corrente
    int totalWithoutCurrent = xorTotal(nums, numsSize, idx + 1, currentXor);
    
    // Calcola la XOR totale includendo l'elemento corrente
    int totalWithCurrent = xorTotal(nums, numsSize, idx + 1, currentXor ^ nums[idx]);
    
    return totalWithoutCurrent + totalWithCurrent;
}

int subsetXORSum(int* nums, int numsSize) {
    return xorTotal(nums, numsSize, 0, 0);
}

int main() {
    int nums[] = {2, 5, 6};
    int numsSize = 3;
    int result = subsetXORSum(nums, numsSize);
    printf("Il risultato è: %d\n", result);
    return 0;
}
