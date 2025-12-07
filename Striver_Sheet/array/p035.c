#include <stdio.h>

int count_xor_subarrays_opt(int arr_nums[], int total_len, int target_xor) {
    int count_subarray = 0;

    for (int start_idx = 0; start_idx < total_len; start_idx++) {
        int xor_val = 0;
        for (int end_idx = start_idx; end_idx < total_len; end_idx++) {
            xor_val ^= arr_nums[end_idx];
            if (xor_val == target_xor) {
                count_subarray++;
            }
        }
    }

    return count_subarray;
}

int main() {
    int arr_nums[] = {4, 2, 2, 6, 4};
    printf("%d\n", count_xor_subarrays_opt(arr_nums, 5, 6));
    return 0;
}
