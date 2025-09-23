#include <stdio.h>
#include <limits.h>
int maxCrossingSum(int arr[], int l, int m, int h, int constraint, int *bestStart, int *bestEnd) {
    int sum = 0;
    int left_sum = INT_MIN, max_left = m;
    for (int i = m; i >= l; i--) {
        sum += arr[i];
        if (sum > left_sum && sum <= constraint) {
            left_sum = sum;
            max_left = i;
        }
    }
    sum = 0;
    int right_sum = INT_MIN, max_right = m + 1;
    for (int j = m + 1; j <= h; j++) {
        sum += arr[j];
        if (sum > right_sum && (left_sum + sum) <= constraint) {
            right_sum = sum;
            max_right = j;
        }
    }
    if (left_sum == INT_MIN) left_sum = 0;
    if (right_sum == INT_MIN) right_sum = 0;
    *bestStart = max_left;
    *bestEnd = max_right;
    return left_sum + right_sum;
}
int maxSubArraySum(int arr[], int l, int h, int constraint, int *startIdx, int *endIdx) {
    if (l == h) {
        if (arr[l] <= constraint) {
            *startIdx = *endIdx = l;
            return arr[l];
        } else {
            return INT_MIN;
        }
    }
    int m = (l + h) / 2;
    int leftStart, leftEnd, rightStart, rightEnd, crossStart, crossEnd;
    int left_sum = maxSubArraySum(arr, l, m, constraint, &leftStart, &leftEnd);
    int right_sum = maxSubArraySum(arr, m + 1, h, constraint, &rightStart, &rightEnd);
    int cross_sum = maxCrossingSum(arr, l, m, h, constraint, &crossStart, &crossEnd);
    if (left_sum >= right_sum && left_sum >= cross_sum) {
        *startIdx = leftStart; *endIdx = leftEnd;
        return left_sum;
    } else if (right_sum >= left_sum && right_sum >= cross_sum) {
        *startIdx = rightStart; *endIdx = rightEnd;
        return right_sum;
    } else {
        *startIdx = crossStart; *endIdx = crossEnd;
        return cross_sum;
    }
}
int main() {
    int n, constraint;
    printf("Enter number of tasks: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter resources required for each task:\n");
    for (int i = 0; i < n; i++) 
    scanf("%d", &arr[i]);
    printf("Enter resource constraint: ");
    scanf("%d", &constraint);
    if (n == 0 || constraint <= 0) {
        printf("No feasible subarray.\n");
        return 0;
    }
    int startIdx = -1, endIdx = -1;
    int max_sum = maxSubArraySum(arr, 0, n - 1, constraint, &startIdx, &endIdx);
    if (max_sum == INT_MIN) {
        printf("No feasible subarray.\n");
    } else {
        printf("Maximum resource utilization = %d\n", max_sum);
        printf("Best subarray: [ ");
        for (int i = startIdx; i <= endIdx; i++) {
            printf("%d ", arr[i]);
        }
        printf("]\n");
    }
    return 0;
}
