#include <stdio.h>

int largest_sum_zero_opt(int arr_nums[], int total_len) {
    int max_len_found = 0, prefix_sum = 0;

    for (int start_idx = 0; start_idx < total_len; start_idx++) {
        prefix_sum = 0;
        for (int end_idx = start_idx; end_idx < total_len; end_idx++) {
            prefix_sum += arr_nums[end_idx];
            if (prefix_sum == 0) {
                int len_now = end_idx - start_idx + 1;
                if (len_now > max_len_found) max_len_found = len_now;
            }
        }
    }

    return max_len_found;
}

int main() {
    int total_len;
    scanf("%d", &total_len);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    printf("%d\n", largest_sum_zero_opt(arr_nums, total_len));
    return 0;
}
