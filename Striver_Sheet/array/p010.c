#include <stdio.h>

int majority_element_opt(int arr_nums[], int total_len) {
    int candidate = 0, count = 0;
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        if (count == 0) {
            candidate = arr_nums[loop_idx];
            count = 1;
        } else if (arr_nums[loop_idx] == candidate) {
            count++;
        } else {
            count--;
        }
    }
    return candidate;
}

int main() {
    int total_len;
    scanf("%d", &total_len);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    printf("%d\n", majority_element_opt(arr_nums, total_len));
    return 0;
}
