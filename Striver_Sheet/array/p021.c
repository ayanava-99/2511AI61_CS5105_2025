#include <stdio.h>
#include <stdlib.h>

int compare_opt(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void two_sum_opt(int arr_nums[], int total_len, int target_val) {
    qsort(arr_nums, total_len, sizeof(int), compare_opt);
    int left_ptr = 0, right_ptr = total_len - 1;
    while (left_ptr < right_ptr) {
        int sum_now = arr_nums[left_ptr] + arr_nums[right_ptr];
        if (sum_now == target_val) {
            printf("%d %d\n", left_ptr, right_ptr);
            return;
        } else if (sum_now < target_val) {
            left_ptr++;
        } else {
            right_ptr--;
        }
    }
}

int main() {
    int total_len, target_val;
    scanf("%d %d", &total_len, &target_val);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    two_sum_opt(arr_nums, total_len, target_val);
    return 0;
}
