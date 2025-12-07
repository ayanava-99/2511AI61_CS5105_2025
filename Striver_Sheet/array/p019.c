#include <stdio.h>

int longest_subarray_sum_opt(int arr_nums[], int total_len, int target_sum) {
    int left_ptr = 0, max_len = 0, current_sum = 0;
    for (int right_ptr = 0; right_ptr < total_len; right_ptr++) {
        current_sum += arr_nums[right_ptr];
        while (current_sum > target_sum && left_ptr <= right_ptr) {
            current_sum -= arr_nums[left_ptr];
            left_ptr++;
        }
        if (current_sum == target_sum) {
            int len_now = right_ptr - left_ptr + 1;
            if (len_now > max_len) max_len = len_now;
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
    printf("%d\n", longest_subarray_sum_opt(arr_nums, total_len, target_sum));
    return 0;
}
