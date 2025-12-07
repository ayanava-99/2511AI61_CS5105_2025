#include <stdio.h>

int count_subarray_sum_opt(int arr_nums[], int total_len, int target_sum) {
    int count_subarrays = 0, prefix_sum = 0;
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        prefix_sum += arr_nums[loop_idx];
        if (prefix_sum == target_sum) count_subarrays++;
        for (int inner_idx = 0; inner_idx < loop_idx; inner_idx++) {
            int slice_sum = 0;
            for (int k_idx = inner_idx; k_idx <= loop_idx; k_idx++) {
                slice_sum += arr_nums[k_idx];
                if (slice_sum == target_sum) count_subarrays++;
            }
        }
    }
    return count_subarrays;
}

int main() {
    int total_len, target_sum;
    scanf("%d %d", &total_len, &target_sum);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    printf("%d\n", count_subarray_sum_opt(arr_nums, total_len, target_sum));
    return 0;
}
