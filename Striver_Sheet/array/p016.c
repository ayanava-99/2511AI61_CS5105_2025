#include <stdio.h>

int max_product_opt(int arr_nums[], int total_len) {
    if (total_len == 0) return 0;
    int max_prod = arr_nums[0], min_prod = arr_nums[0], result = arr_nums[0];

    for (int loop_idx = 1; loop_idx < total_len; loop_idx++) {
        if (arr_nums[loop_idx] < 0) {
            int temp = max_prod;
            max_prod = min_prod;
            min_prod = temp;
        }
        max_prod = (arr_nums[loop_idx] > max_prod * arr_nums[loop_idx]) ? arr_nums[loop_idx] : max_prod * arr_nums[loop_idx];
        min_prod = (arr_nums[loop_idx] < min_prod * arr_nums[loop_idx]) ? arr_nums[loop_idx] : min_prod * arr_nums[loop_idx];
        if (max_prod > result) result = max_prod;
    }
    return result;
}

int main() {
    int total_len;
    scanf("%d", &total_len);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    printf("%d\n", max_product_opt(arr_nums, total_len));
    return 0;
}
