#include <stdio.h>

void left_rot_one_opt(int arr_nums[], int total_len) {
    if (total_len <= 1) return;
    int first_save = arr_nums[0];
    for (int loop_idx = 0; loop_idx < total_len - 1; loop_idx++) {
        arr_nums[loop_idx] = arr_nums[loop_idx + 1];
    }
    arr_nums[total_len - 1] = first_save;
}

int main() {
    int total_len;
    scanf("%d", &total_len);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    left_rot_one_opt(arr_nums, total_len);
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        printf("%d ", arr_nums[loop_idx]);
    }
    printf("\n");
    return 0;
}
