#include <stdio.h>

int find_max_element_opt(int arr_nums[], int total_len) {
    int max_tracked = arr_nums[0];
    for (int loop_idx = 1; loop_idx < total_len; loop_idx++) {
        if (arr_nums[loop_idx] > max_tracked) {
            max_tracked = arr_nums[loop_idx];
        }
    }
    return max_tracked;
}

int main() {
    int total_len;
    scanf("%d", &total_len);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    printf("%d\n", find_max_element_opt(arr_nums, total_len));
    return 0;
}
