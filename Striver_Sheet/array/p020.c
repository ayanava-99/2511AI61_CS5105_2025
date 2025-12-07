#include <stdio.h>
#include <stdlib.h>

int longest_subarray_mixed_opt(int arr_nums[], int total_len, int target_sum) {
    int max_len = 0, prefix_sum = 0;
    for (int start_idx = 0; start_idx < total_len; start_idx++) {
        prefix_sum = 0;
        for (int end_idx = start_idx; end_idx < total_len; end_idx++) {
            prefix_sum += arr_nums[end_idx];
            if (prefix_sum == target_sum) {
                int len_now = end_idx - start_idx + 1;
                if (len_now > max_len) max_len = len_now;
            }
        }
    }
    return max_len;
}

int main() {
    int total_len, target_sum;
    scanf("%d %d", &total_len, &target_sum);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    printf("%d\n", longest_subarray_mixed_opt(arr_nums, total_len, target_sum));
    return 0;
}
