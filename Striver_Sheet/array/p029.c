#include <stdio.h>

void majority_element_2_opt(int arr_nums[], int total_len) {
    int candidate1 = 0, candidate2 = 0, count1 = 0, count2 = 0;

    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        if (arr_nums[loop_idx] == candidate1) {
            count1++;
        } else if (arr_nums[loop_idx] == candidate2) {
            count2++;
        } else if (count1 == 0) {
            candidate1 = arr_nums[loop_idx];
            count1 = 1;
        } else if (count2 == 0) {
            candidate2 = arr_nums[loop_idx];
            count2 = 1;
        } else {
            count1--;
            count2--;
        }
    }

    count1 = 0;
    count2 = 0;
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        if (arr_nums[loop_idx] == candidate1) count1++;
        else if (arr_nums[loop_idx] == candidate2) count2++;
    }

    int threshold = total_len / 3;
    if (count1 > threshold) printf("%d ", candidate1);
    if (count2 > threshold) printf("%d", candidate2);
    printf("\n");
}

int main() {
    int total_len;
    scanf("%d", &total_len);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    majority_element_2_opt(arr_nums, total_len);
    return 0;
}
