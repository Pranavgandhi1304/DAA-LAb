#include <stdio.h>
#include <float.h>

#define MAX 50   // maximum keys

double OptimalBST(double p[], double q[], int n) {
    double E[MAX][MAX], W[MAX][MAX];
    int i, j, k, d;

    // Step 1: Initialization
    for (i = 0; i <= n; i++) {
        E[i][i] = q[i];
        W[i][i] = q[i];
    }

    // Step 2: Compute values for increasing interval lengths
    for (d = 1; d <= n; d++) {
        for (i = 0; i <= n - d; i++) {
            j = i + d;
            E[i][j] = DBL_MAX;   // Infinity
            W[i][j] = W[i][j - 1] + p[j] + q[j];

            // Try all possible roots
            for (k = i + 1; k <= j; k++) {
                double cost = E[i][k - 1] + E[k][j] + W[i][j];
                if (cost < E[i][j]) {
                    E[i][j] = cost;
                }
            }
        }
    }
    return E[0][n];  // minimum expected cost
}

int main() {
    int n, i;
    int keys[MAX];   // not actually used in cost computation, but read for format
    double p[MAX], q[MAX];

    // Input
    scanf("%d", &n);
    for (i = 1; i <= n; i++) scanf("%d", &keys[i]);
    for (i = 1; i <= n; i++) scanf("%lf", &p[i]);
    for (i = 0; i <= n; i++) scanf("%lf", &q[i]);

    double minCost = OptimalBST(p, q, n);

    printf("%.4f\n", minCost);
    return 0;
}
