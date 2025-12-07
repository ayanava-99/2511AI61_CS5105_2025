#include <stdio.h>

int count_pairs_diff_opt(int arr_nums[], int total_len, int diff_k) {
    int count_pairs = 0;

    for (int outer_idx = 0; outer_idx < total_len; outer_idx++) {
        for (int inner_idx = outer_idx + 1; inner_idx < total_len; inner_idx++) {
            if (arr_nums[outer_idx] - arr_nums[inner_idx] == diff_k || 
                arr_nums[inner_idx] - arr_nums[outer_idx] == diff_k) {
                count_pairs++;
            }
        }
    }

    return count_pairs;
}

int main() {
    int arr_nums[] = {1, 5, 3, 4, 2};
    printf("%d\n", count_pairs_diff_opt(arr_nums, 5, 2));
    return 0;
}
