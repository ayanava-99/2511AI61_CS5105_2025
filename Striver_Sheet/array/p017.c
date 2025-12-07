#include <stdio.h>

void union_sorted_opt(int arr1[], int len1, int arr2[], int len2) {
    int ptr1 = 0, ptr2 = 0;
    printf("[");
    int first_elem = 1;
    while (ptr1 < len1 && ptr2 < len2) {
        if (arr1[ptr1] < arr2[ptr2]) {
            if (!first_elem) printf(", ");
            printf("%d", arr1[ptr1]);
            first_elem = 0;
            ptr1++;
        } else if (arr1[ptr1] > arr2[ptr2]) {
            if (!first_elem) printf(", ");
            printf("%d", arr2[ptr2]);
            first_elem = 0;
            ptr2++;
        } else {
            if (!first_elem) printf(", ");
            printf("%d", arr1[ptr1]);
            first_elem = 0;
            ptr1++;
            ptr2++;
        }
    }
    while (ptr1 < len1) {
        if (!first_elem) printf(", ");
        printf("%d", arr1[ptr1]);
        first_elem = 0;
        ptr1++;
    }
    while (ptr2 < len2) {
        if (!first_elem) printf(", ");
        printf("%d", arr2[ptr2]);
        first_elem = 0;
        ptr2++;
    }
    printf("]\n");
}

int main() {
    int len1, len2;
    scanf("%d %d", &len1, &len2);
    int arr1[len1], arr2[len2];
    for (int i = 0; i < len1; i++) scanf("%d", &arr1[i]);
    for (int i = 0; i < len2; i++) scanf("%d", &arr2[i]);
    union_sorted_opt(arr1, len1, arr2, len2);
    return 0;
}
