#include <stdio.h>

void sort_012_opt(int arr_nums[], int total_len) {
    int low_ptr = 0, mid_ptr = 0, high_ptr = total_len - 1;
    while (mid_ptr <= high_ptr) {
        if (arr_nums[mid_ptr] == 0) {
            int temp_swap = arr_nums[low_ptr];
            arr_nums[low_ptr] = arr_nums[mid_ptr];
            arr_nums[mid_ptr] = temp_swap;
            low_ptr++;
            mid_ptr++;
        } else if (arr_nums[mid_ptr] == 1) {
            mid_ptr++;
        } else {
            int temp_swap = arr_nums[mid_ptr];
            arr_nums[mid_ptr] = arr_nums[high_ptr];
            arr_nums[high_ptr] = temp_swap;
            high_ptr--;
        }
    }
}

int main() {
    int total_len;
    scanf("%d", &total_len);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    sort_012_opt(arr_nums, total_len);
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        printf("%d ", arr_nums[loop_idx]);
    }
    printf("\n");
    return 0;
}
