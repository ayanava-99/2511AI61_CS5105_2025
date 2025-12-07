#include <stdio.h>
#include <stdlib.h>

int compare_opt(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int longest_consecutive_opt(int arr_nums[], int total_len) {
    if (total_len == 0) return 0;
    qsort(arr_nums, total_len, sizeof(int), compare_opt);

    int max_streak = 1, current_streak = 1;
    for (int loop_idx = 1; loop_idx < total_len; loop_idx++) {
        if (arr_nums[loop_idx] == arr_nums[loop_idx - 1]) continue;
        if (arr_nums[loop_idx] == arr_nums[loop_idx - 1] + 1) {
            current_streak++;
        } else {
            if (current_streak > max_streak) max_streak = current_streak;
            current_streak = 1;
        }
    }
    if (current_streak > max_streak) max_streak = current_streak;
    return max_streak;
}

int main() {
    int total_len;
    scanf("%d", &total_len);
    int arr_nums[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_nums[loop_idx]);
    }
    printf("%d\n", longest_consecutive_opt(arr_nums, total_len));
    return 0;
}
