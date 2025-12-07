#include <stdio.h>

int max_consecutive_opt(int arr_nums[], int total_len) {
    int max_count = 0, current_count = 0;
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        if (arr_nums[loop_idx] == 1) {
            current_count++;
            if (current_count > max_count) max_count = current_count;
        } else {
            current_count = 0;
        }
    }
    return max_count;
}

int main() {
    int total_len;
    scanf("%d", &total_len);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    printf("%d\n", max_consecutive_opt(arr_nums, total_len));
    return 0;
}
