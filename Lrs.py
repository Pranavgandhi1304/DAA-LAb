def LRS(a: str) -> str:
    n = len(a)
    b = a 

    c = [[0 for _ in range(n + 1)] for _ in range(n + 1)]

    for i in range(1, n + 1):
        for j in range(1, n + 1):
            if a[i - 1] == b[j - 1] and i != j:
                c[i][j] = 1 + c[i - 1][j - 1] 
            else:
  
                c[i][j] = max(c[i - 1][j], c[i][j - 1])   
 
    
    i, j = n, n
    seq = []
    while i > 0 and j > 0:
        if a[i - 1] == b[j - 1] and i != j:
            seq.append(a[i - 1])
            i -= 1
            j -= 1
        elif c[i - 1][j] > c[i][j - 1]:
            i -= 1
        else:
            j -= 1
    seq.reverse()
    return "".join(seq)

s = "AABEBCDD"
print("Input String:", s)
print("Longest Repeating Subsequence:", LRS(s))
