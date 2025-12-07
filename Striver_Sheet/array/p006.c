#include <stdio.h>

void move_zero_end_opt(int arr_nums[], int total_len) {
    int pos_nonzero = 0;
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        if (arr_nums[loop_idx] != 0) {
            int temp_swap = arr_nums[pos_nonzero];
            arr_nums[pos_nonzero] = arr_nums[loop_idx];
            arr_nums[loop_idx] = temp_swap;
            pos_nonzero++;
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
    move_zero_end_opt(arr_nums, total_len);
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        printf("%d ", arr_nums[loop_idx]);
    }
    printf("\n");
    return 0;
}
