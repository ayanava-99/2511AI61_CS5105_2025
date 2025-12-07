#include <stdio.h>

int find_missing_opt(int arr_nums[], int total_len) {
    int total_sum = 0;
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        total_sum += arr_nums[loop_idx];
    }
    int expected_sum = (total_len * (total_len + 1)) / 2;
    return expected_sum - total_sum;
}

int main() {
    int total_len;
    scanf("%d", &total_len);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    printf("%d\n", find_missing_opt(arr_nums, total_len));
    return 0;
}
