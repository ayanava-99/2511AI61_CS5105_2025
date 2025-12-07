#include <stdio.h>

void rotate_matrix_90_opt(int matrix_vals[][3], int matrix_size) {
    for (int row_idx = 0; row_idx < matrix_size; row_idx++) {
        for (int col_idx = row_idx + 1; col_idx < matrix_size; col_idx++) {
            int temp_swap = matrix_vals[row_idx][col_idx];
            matrix_vals[row_idx][col_idx] = matrix_vals[col_idx][row_idx];
            matrix_vals[col_idx][row_idx] = temp_swap;
        }
    }

    for (int row_idx = 0; row_idx < matrix_size; row_idx++) {
        int left_ptr = 0, right_ptr = matrix_size - 1;
        while (left_ptr < right_ptr) {
            int temp_swap = matrix_vals[row_idx][left_ptr];
            matrix_vals[row_idx][left_ptr] = matrix_vals[row_idx][right_ptr];
            matrix_vals[row_idx][right_ptr] = temp_swap;
            left_ptr++;
            right_ptr--;
        }
    }
}

int main() {
    int matrix_vals[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    rotate_matrix_90_opt(matrix_vals, 3);
    for (int row_idx = 0; row_idx < 3; row_idx++) {
        for (int col_idx = 0; col_idx < 3; col_idx++) {
            printf("%d ", matrix_vals[row_idx][col_idx]);
        }
        printf("\n");
    }
    return 0;
}
