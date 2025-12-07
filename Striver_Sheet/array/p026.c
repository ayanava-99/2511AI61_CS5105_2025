#include <stdio.h>

void set_matrix_zeroes_opt(int matrix_vals[][4], int rows_count, int cols_count) {
    int first_row_zero = 0, first_col_zero = 0;

    for (int col_idx = 0; col_idx < cols_count; col_idx++) {
        if (matrix_vals[0][col_idx] == 0) {
            first_row_zero = 1;
            break;
        }
    }
    for (int row_idx = 0; row_idx < rows_count; row_idx++) {
        if (matrix_vals[row_idx][0] == 0) {
            first_col_zero = 1;
            break;
        }
    }

    for (int row_idx = 1; row_idx < rows_count; row_idx++) {
        for (int col_idx = 1; col_idx < cols_count; col_idx++) {
            if (matrix_vals[row_idx][col_idx] == 0) {
                matrix_vals[row_idx][0] = 0;
                matrix_vals[0][col_idx] = 0;
            }
        }
    }

    for (int row_idx = 1; row_idx < rows_count; row_idx++) {
        for (int col_idx = 1; col_idx < cols_count; col_idx++) {
            if (matrix_vals[row_idx][0] == 0 || matrix_vals[0][col_idx] == 0) {
                matrix_vals[row_idx][col_idx] = 0;
            }
        }
    }

    if (first_row_zero) {
        for (int col_idx = 0; col_idx < cols_count; col_idx++) {
            matrix_vals[0][col_idx] = 0;
        }
    }
    if (first_col_zero) {
        for (int row_idx = 0; row_idx < rows_count; row_idx++) {
            matrix_vals[row_idx][0] = 0;
        }
    }
}

int main() {
    int matrix_vals[3][4] = {{1,1,1},{1,0,1},{1,1,1}};
    set_matrix_zeroes_opt(matrix_vals, 3, 4);
    for (int row_idx = 0; row_idx < 3; row_idx++) {
        for (int col_idx = 0; col_idx < 4; col_idx++) {
            printf("%d ", matrix_vals[row_idx][col_idx]);
        }
        printf("\n");
    }
    return 0;
}
