#include <stdio.h>

int max_profit_opt(int arr_prices[], int total_len) {
    int min_price = arr_prices[0], max_profit = 0;
    for (int loop_idx = 1; loop_idx < total_len; loop_idx++) {
        int profit_now = arr_prices[loop_idx] - min_price;
        if (profit_now > max_profit) max_profit = profit_now;
        if (arr_prices[loop_idx] < min_price) min_price = arr_prices[loop_idx];
    }
    return max_profit;
}

int main() {
    int total_len;
    scanf("%d", &total_len);
    int arr_prices[total_len];
    for (int loop_idx = 0; loop_idx < total_len; loop_idx++) {
        scanf("%d", &arr_prices[loop_idx]);
    }
    printf("%d\n", max_profit_opt(arr_prices, total_len));
    return 0;
}
