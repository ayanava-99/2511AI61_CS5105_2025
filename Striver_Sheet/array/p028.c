#include <stdio.h>

void spiral_matrix_opt(int matrix_vals[][4], int rows_m, int cols_n) {
    int top_row = 0, bottom_row = rows_m - 1, left_col = 0, right_col = cols_n - 1;

    while (top_row <= bottom_row && left_col <= right_col) {
        for (int col_idx = left_col; col_idx <= right_col; col_idx++) {
            printf("%d ", matrix_vals[top_row][col_idx]);
        }
        top_row++;

        for (int row_idx = top_row; row_idx <= bottom_row; row_idx++) {
            printf("%d ", matrix_vals[row_idx][right_col]);
        }
        right_col--;

        if (top_row <= bottom_row) {
            for (int col_idx = right_col; col_idx >= left_col; col_idx--) {
                printf("%d ", matrix_vals[bottom_row][col_idx]);
            }
            bottom_row--;
        }

        if (left_col <= right_col) {
            for (int row_idx = bottom_row; row_idx >= top_row; row_idx--) {
                printf("%d ", matrix_vals[row_idx][left_col]);
            }
            left_col++;
        }
    }
    printf("\n");
}

int main() {
    int matrix_vals[3][4] = {{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    spiral_matrix_opt(matrix_vals, 3, 4);
    return 0;
}
