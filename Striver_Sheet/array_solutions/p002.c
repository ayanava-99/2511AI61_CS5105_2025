#include <stdio.h>

void find_second_minmax_opt(int arr_nums[], int total_len) {
    int min_elem = arr_nums[0];
    int max_elem = arr_nums[0];

    for (int loop_idx = 1; loop_idx < total_len; loop_idx++) {
        if (arr_nums[loop_idx] < min_elem) min_elem = arr_nums[loop_idx];
        if (arr_nums[loop_idx] > max_elem) max_elem = arr_nums[loop_idx];
    }

    int second_min = -1, second_max = -1;
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        if (arr_nums[loop_idx] != min_elem && (second_min == -1 || arr_nums[loop_idx] < second_min)) {
            second_min = arr_nums[loop_idx];
        }
        if (arr_nums[loop_idx] != max_elem && (second_max == -1 || arr_nums[loop_idx] > second_max)) {
            second_max = arr_nums[loop_idx];
        }
    }
    printf("%d %d\n", second_min, second_max);
}

int main() {
    int total_len;
    scanf("%d", &total_len);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    find_second_minmax_opt(arr_nums, total_len);
    return 0;
}
