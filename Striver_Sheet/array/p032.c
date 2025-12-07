#include <stdio.h>
#include <stdlib.h>

int compare_intervals_opt(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void merge_intervals_opt(int intervals[][2], int total_len) {
    qsort(intervals, total_len, sizeof(intervals[0]), compare_intervals_opt);

    int merged_count = 1;
    for (int loop_idx = 1; loop_idx < total_len; loop_idx++) {
        if (intervals[loop_idx][0] <= intervals[merged_count - 1][1]) {
            if (intervals[loop_idx][1] > intervals[merged_count - 1][1]) {
                intervals[merged_count - 1][1] = intervals[loop_idx][1];
            }
        } else {
            intervals[merged_count][0] = intervals[loop_idx][0];
            intervals[merged_count][1] = intervals[loop_idx][1];
            merged_count++;
        }
    }

    for (int loop_idx = 0; loop_idx < merged_count; loop_idx++) {
        printf("[%d, %d] ", intervals[loop_idx][0], intervals[loop_idx][1]);
    }
    printf("\n");
}

int main() {
    int intervals[][2] = {{1,5},{3,6},{8,10},{15,18}};
    merge_intervals_opt(intervals, 4);
    return 0;
}
