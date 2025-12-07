#include <stdio.h>
#include <stdlib.h>

int compare_opt(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void three_sum_opt(int arr_nums[], int total_len) {
    qsort(arr_nums, total_len, sizeof(int), compare_opt);

    for (int loop_idx = 0; loop_idx < total_len - 2; loop_idx++) {
        if (loop_idx > 0 && arr_nums[loop_idx] == arr_nums[loop_idx - 1]) continue;

        int left_ptr = loop_idx + 1, right_ptr = total_len - 1;
        while (left_ptr < right_ptr) {
            int sum_now = arr_nums[loop_idx] + arr_nums[left_ptr] + arr_nums[right_ptr];
            if (sum_now == 0) {
                printf("[%d, %d, %d]\n", arr_nums[loop_idx], arr_nums[left_ptr], arr_nums[right_ptr]);
                left_ptr++;
                right_ptr--;
                while (left_ptr < right_ptr && arr_nums[left_ptr] == arr_nums[left_ptr - 1]) left_ptr++;
                while (left_ptr < right_ptr && arr_nums[right_ptr] == arr_nums[right_ptr + 1]) right_ptr--;
            } else if (sum_now < 0) {
                left_ptr++;
            } else {
                right_ptr--;
            }
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
    three_sum_opt(arr_nums, total_len);
    return 0;
}
