#include <stdio.h>
#include <stdlib.h>

int compare_opt(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int three_sum_closest_opt(int arr_nums[], int total_len, int target_val) {
    qsort(arr_nums, total_len, sizeof(int), compare_opt);
    int closest_sum = arr_nums[0] + arr_nums[1] + arr_nums[2];

    for (int loop_idx = 0; loop_idx < total_len - 2; loop_idx++) {
        int left_ptr = loop_idx + 1, right_ptr = total_len - 1;

        while (left_ptr < right_ptr) {
            int sum_now = arr_nums[loop_idx] + arr_nums[left_ptr] + arr_nums[right_ptr];

            if (sum_now == target_val) return sum_now;

            if (abs(sum_now - target_val) < abs(closest_sum - target_val)) {
                closest_sum = sum_now;
            }

            if (sum_now < target_val) {
                left_ptr++;
            } else {
                right_ptr--;
            }
        }
    }

    return closest_sum;
}

int main() {
    int arr_nums[] = {-1, 2, 1, -4};
    printf("%d\n", three_sum_closest_opt(arr_nums, 4, 1));
    return 0;
}
