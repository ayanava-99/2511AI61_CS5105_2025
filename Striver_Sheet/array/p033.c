#include <stdio.h>

void merge_sorted_opt(int arr1[], int len1, int arr2[], int len2) {
    int ptr1 = len1 - 1, ptr2 = len2 - 1, ptr_merge = len1 + len2 - 1;

    while (ptr1 >= 0 && ptr2 >= 0) {
        if (arr1[ptr1] > arr2[ptr2]) {
            arr1[ptr_merge] = arr1[ptr1];
            ptr1--;
        } else {
            arr1[ptr_merge] = arr2[ptr2];
            ptr2--;
        }
        ptr_merge--;
    }

    while (ptr2 >= 0) {
        arr1[ptr_merge] = arr2[ptr2];
        ptr2--;
        ptr_merge--;
    }
}

int main() {
    int len1 = 3, len2 = 2;
    int arr1[5] = {1, 3, 5, 0, 0};
    int arr2[2] = {2, 4};
    merge_sorted_opt(arr1, len1, arr2, len2);
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr1[i]);
    }
    printf("\n");
    return 0;
}
