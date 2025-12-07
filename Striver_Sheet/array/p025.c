#include <stdio.h>

void reverse_arr_opt(int arr_nums[], int start_idx, int end_idx) {
    while (start_idx < end_idx) {
        int temp_swap = arr_nums[start_idx];
        arr_nums[start_idx] = arr_nums[end_idx];
        arr_nums[end_idx] = temp_swap;
        start_idx++;
        end_idx--;
    }
}

void next_permutation_opt(int arr_nums[], int total_len) {
    int pivot_idx = total_len - 2;
    while (pivot_idx >= 0 && arr_nums[pivot_idx] >= arr_nums[pivot_idx + 1]) {
        pivot_idx--;
    }

    if (pivot_idx < 0) {
        reverse_arr_opt(arr_nums, 0, total_len - 1);
        return;
    }

    int swap_idx = total_len - 1;
    while (swap_idx > pivot_idx && arr_nums[swap_idx] <= arr_nums[pivot_idx]) {
        swap_idx--;
    }

    int temp_swap = arr_nums[pivot_idx];
    arr_nums[pivot_idx] = arr_nums[swap_idx];
    arr_nums[swap_idx] = temp_swap;

    reverse_arr_opt(arr_nums, pivot_idx + 1, total_len - 1);
}

int main() {
    int total_len;
    scanf("%d", &total_len);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    next_permutation_opt(arr_nums, total_len);
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        printf("%d ", arr_nums[loop_idx]);
    }
    printf("\n");
    return 0;
}
