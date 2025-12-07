#include <stdio.h>

int is_array_sorted_opt(int arr_nums[], int total_len) {
    for (int loop_idx = 1; loop_idx < total_len; loop_idx++) {
        if (arr_nums[loop_idx] < arr_nums[loop_idx - 1]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int total_len;
    scanf("%d", &total_len);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    printf("%s\n", is_array_sorted_opt(arr_nums, total_len) ? "True" : "False");
    return 0;
}
