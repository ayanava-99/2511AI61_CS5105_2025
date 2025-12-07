#include <stdio.h>

int single_number_opt(int arr_nums[], int total_len) {
    int xor_result = 0;
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        xor_result ^= arr_nums[loop_idx];
    }
    return xor_result;
}

int main() {
    int total_len;
    scanf("%d", &total_len);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    printf("%d\n", single_number_opt(arr_nums, total_len));
    return 0;
}
