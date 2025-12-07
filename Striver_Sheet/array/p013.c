#include <stdio.h>

void find_leaders_opt(int arr_nums[], int total_len) {
    int leaders[total_len], lead_count = 0;
    int max_right = arr_nums[total_len - 1];
    leaders[lead_count++] = max_right;

    for (int loop_idx = total_len - 2; loop_idx >= 0; loop_idx--) {
        if (arr_nums[loop_idx] > max_right) {
            leaders[lead_count++] = arr_nums[loop_idx];
            max_right = arr_nums[loop_idx];
        }
    }

    for (int loop_idx = lead_count - 1; loop_idx >= 0; loop_idx--) {
        printf("%d ", leaders[loop_idx]);
    }
    printf("\n");
}

int main() {
    int total_len;
    scanf("%d", &total_len);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    find_leaders_opt(arr_nums, total_len);
    return 0;
}
