#include <stdio.h>

int max_subarray_sum_opt(int arr_nums[], int total_len) {
    int max_sum_track = arr_nums[0], current_sum = arr_nums[0];
    for (int loop_idx = 1; loop_idx < total_len; loop_idx++) {
        current_sum = (arr_nums[loop_idx] > current_sum + arr_nums[loop_idx]) ? arr_nums[loop_idx] : current_sum + arr_nums[loop_idx];
        max_sum_track = (current_sum > max_sum_track) ? current_sum : max_sum_track;
    }
    return max_sum_track;
}

int main() {
    int total_len;
    scanf("%d", &total_len);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    printf("%d\n", max_subarray_sum_opt(arr_nums, total_len));
    return 0;
}
