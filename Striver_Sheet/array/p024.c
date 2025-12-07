#include <stdio.h>

void rearrange_by_sign_opt(int arr_nums[], int total_len) {
    int pos_arr[total_len], neg_arr[total_len];
    int pos_cnt = 0, neg_cnt = 0;

    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        if (arr_nums[loop_idx] > 0) {
            pos_arr[pos_cnt++] = arr_nums[loop_idx];
        } else {
            neg_arr[neg_cnt++] = arr_nums[loop_idx];
        }
    }

    int result_idx = 0;
    for (int loop_idx = 0; loop_idx < pos_cnt; loop_idx++) {
        arr_nums[result_idx++] = pos_arr[loop_idx];
        if (loop_idx < neg_cnt) arr_nums[result_idx++] = neg_arr[loop_idx];
    }
}

int main() {
    int total_len;
    scanf("%d", &total_len);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    rearrange_by_sign_opt(arr_nums, total_len);
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        printf("%d ", arr_nums[loop_idx]);
    }
    printf("\n");
    return 0;
}
