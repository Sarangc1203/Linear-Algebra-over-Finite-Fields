import numpy
import random
import time


def modArthInv(a, b):
    if b > a:
        a, b = b, a
    if b == 1:
        return 1
    if b == 0:
        return 0
    else:
        p = a
        q = b
        l = []
        while p % q != 0:
            l.append([1, p // q, p % q])
            p, q = q, (p % q)
        i = len(l) - 2
        while i >= 0:
            l[i][0] = l[i + 1][1]
            l[i][1] = l[i + 1][1] * l[i][1] + l[i + 1][0]
            l[i][2] = -l[i + 1][2]
            i -= 1
        if l[0][2] < 0:
            return l[0][1] % a
        else:
            return (-l[0][1]) % a


n = 1000
m = 1009
mat = numpy.zeros(shape=(n, n+1), dtype=numpy.int64)

for i1 in range(0, n):
    for j in range(0, n+1):
        mat[i1][j] = random.randint(0, m-1)

start = time.time()
for i1 in range(0, n):
    if mat[i1][i1] == 0:
        for k in range(i1 + 1, n):
            if mat[k][i1] != 0:
                p = list(mat[k, :])
                mat[k, :] = mat[i1, :]
                mat[i1, :] = p
                break
    if mat[i1][i1] == 0:
        print("No Solution")
# print("Mat")
# print(mat)
L = numpy.eye(n, dtype=int)
# U = numpy.zeros(n)
U = numpy.array(mat)

for i1 in range(0, n):
    for j in range(i1+1, n):
        # print(str(i1)+" - "+str(j))
        # print(mat[i1, i1])
        p = (modArthInv(m, U[i1][i1]) * U[j][i1]) % m
        L[j][i1] = p
        U[j, :] -= p * U[i1, :]
        U[j, :] %= m

end = time.time()
print(end - start)
print("\nL:")
print(L)
print("\nU:")
print(U)
print("\nDiff")
print((mat-numpy.dot(L, U)) % m)
