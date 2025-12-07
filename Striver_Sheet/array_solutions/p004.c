#include <stdio.h>

int remove_dup_sorted_opt(int arr_nums[], int total_len) {
    if (total_len == 0) return 0;
    int write_pos = 1;
    for (int loop_idx = 1; loop_idx < total_len; loop_idx++) {
        if (arr_nums[loop_idx] != arr_nums[loop_idx - 1]) {
            arr_nums[write_pos++] = arr_nums[loop_idx];
        }
    }
    return write_pos;
}

int main() {
    int total_len;
    scanf("%d", &total_len);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    int unique_count = remove_dup_sorted_opt(arr_nums, total_len);
    printf("%d\n", unique_count);
    return 0;
}
