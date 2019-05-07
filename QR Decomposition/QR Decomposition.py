import numpy
import random
import math


def modArthInv1(a, b):
    if b > a:
        a, b = b, a
    if b == 1:
        return 1
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

def QRDecomp():
    Q = mat[:, 0:n]
    for i in range(0, n):
        for j in range(0, i):
            Q[:, i] = Q[:, i] - (numpy.dot(Q[:, i], Q[:, j])*Q[:, j])/(sum(k**2 for k in Q[:, j]))
        Q[:, i] = Q[:, i] / math.sqrt(sum(k**2 for k in Q[:, i]))
    return Q

def ijmulttrans():
    B = mat[:, n]
    print(B)
    for i in range(0,n):
        for j in range(0,n):
            X[i] += Q[j][i]*B[j]
    print(X)

n = 4
m = 111
mat = numpy.zeros(shape=(n, n+1), dtype=numpy.float)
Q = numpy.zeros(shape=(n, n), dtype=numpy.float)
X = numpy.zeros(shape=(n,1), dtype=numpy.float)

for i1 in range(0, n):
    for j1 in range(0, n+1):
        mat[i1][j1] = random.randint(0, m-1)
# mat = numpy.array([[1.0, 2.0, 3.0, 4.0], [-1.0, 1.0, 1.0, 2.0], [1.0, 1.0, 1.0, 1.0], [1.0, 1.0, 1.0, 3.0]])
print(mat)
Q = QRDecomp()
ijmulttrans()

