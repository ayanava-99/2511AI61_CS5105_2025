#include <stdio.h>

int linear_search_opt(int arr_nums[], int total_len, int target_val) {
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        if (arr_nums[loop_idx] == target_val) {
            return loop_idx;
        }
    }
    return -1;
}

int main() {
    int total_len, target_val;
    scanf("%d %d", &total_len, &target_val);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    printf("%d\n", linear_search_opt(arr_nums, total_len, target_val));
    return 0;
}
