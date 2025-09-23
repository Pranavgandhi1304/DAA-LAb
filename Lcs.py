X = "AGCCCTAAGGGCTACCTAGCTT"
Y = "GACAGCCTACAAGCGTTAGCTTG"
def lcs(X, Y):
    m, n = len(X), len(Y)
    dp = [[0]*(n+1) for _ in range(m+1)]
    direction = [['']*(n+1) for _ in range(m+1)]

    # Fill dp and direction matrices
    for i in range(1, m+1):
        for j in range(1, n+1):
            if X[i-1] == Y[j-1]:
                dp[i][j] = dp[i-1][j-1] + 1
                direction[i][j] = 'D'
            elif dp[i-1][j] >= dp[i][j-1]:
                dp[i][j] = dp[i-1][j]
                direction[i][j] = 'U'
            else:
                dp[i][j] = dp[i][j-1]
                direction[i][j] = 'S'

    # Print cost matrix with directions
    print("Cost Matrix (dp):")
    for i in range(m+1):
        row = []
        for j in range(n+1):
            row.append(f"{dp[i][j]}{direction[i][j] if direction[i][j] else ' '}")
        print(' '.join(row))
    print()

    # Backtrack to find LCS
    lcs_seq = []
    i, j = m, n
    while i > 0 and j > 0:
        if direction[i][j] == 'D':
            lcs_seq.append(X[i-1])
            i -= 1
            j -= 1
        elif direction[i][j] == 'U':
            i -= 1
        else:
            j -= 1
    lcs_seq.reverse()
    lcs_str = ''.join(lcs_seq)

    print(f"Length of LCS = {dp[m][n]}")
    print(f"LCS = {lcs_str}")

lcs(X, Y)
