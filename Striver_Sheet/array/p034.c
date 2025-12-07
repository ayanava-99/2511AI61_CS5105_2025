#include <stdio.h>
#include <stdlib.h>

int compare_opt(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void four_sum_opt(int arr_nums[], int total_len, int target_sum) {
    qsort(arr_nums, total_len, sizeof(int), compare_opt);

    for (int i_idx = 0; i_idx < total_len - 3; i_idx++) {
        if (i_idx > 0 && arr_nums[i_idx] == arr_nums[i_idx - 1]) continue;

        for (int j_idx = i_idx + 1; j_idx < total_len - 2; j_idx++) {
            if (j_idx > i_idx + 1 && arr_nums[j_idx] == arr_nums[j_idx - 1]) continue;

            int left_ptr = j_idx + 1, right_ptr = total_len - 1;
            while (left_ptr < right_ptr) {
                int sum_now = arr_nums[i_idx] + arr_nums[j_idx] + arr_nums[left_ptr] + arr_nums[right_ptr];
                if (sum_now == target_sum) {
                    printf("[%d, %d, %d, %d]\n", arr_nums[i_idx], arr_nums[j_idx], arr_nums[left_ptr], arr_nums[right_ptr]);
                    left_ptr++;
                    right_ptr--;
                } else if (sum_now < target_sum) {
                    left_ptr++;
                } else {
                    right_ptr--;
                }
            }
        }
    }
}

int main() {
    int arr_nums[] = {1, -2, 3, 5, 7, 9};
    four_sum_opt(arr_nums, 6, 7);
    return 0;
}
