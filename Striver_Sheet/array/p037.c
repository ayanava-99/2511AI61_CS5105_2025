#include <stdio.h>

int first_greater_element_opt(int arr_nums[], int total_len, int target_val) {
    int left_ptr = 0, right_ptr = total_len - 1, result_idx = -1;

    while (left_ptr <= right_ptr) {
        int mid_idx = (left_ptr + right_ptr) / 2;
        if (arr_nums[mid_idx] > target_val) {
            result_idx = mid_idx;
            right_ptr = mid_idx - 1;
        } else {
            left_ptr = mid_idx + 1;
        }
    }

    return result_idx;
}

int main() {
    int arr_nums[] = {1, 3, 5, 7, 9, 11};
    printf("%d\n", first_greater_element_opt(arr_nums, 6, 5));
    return 0;
}
