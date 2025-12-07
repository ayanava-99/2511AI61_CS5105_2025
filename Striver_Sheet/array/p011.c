#include <stdio.h>

int kadane_max_sum_opt(int arr_nums[], int total_len) {
    int max_sum = arr_nums[0], current_sum = arr_nums[0];
    for (int loop_idx = 1; loop_idx < total_len; loop_idx++) {
        if (current_sum < 0) {
            current_sum = arr_nums[loop_idx];
        } else {
            current_sum += arr_nums[loop_idx];
        }
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
    }
    return max_sum;
}

int main() {
    int total_len;
    scanf("%d", &total_len);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    printf("%d\n", kadane_max_sum_opt(arr_nums, total_len));
    return 0;
}
