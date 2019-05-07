import numpy
from random import randint
import time
import math


def nextpow(n1):
    a = 1
    n = n1
    while n // 2:
        a *= 2
        n = n//2
    if a != n1:
        a *= 2
    return a


def StrassenMult(M, N, n):
    # print(M)
    a = M[0:n//2][:, 0:n//2]
    b = M[0:n//2][:, n//2:n]
    c = M[n//2:n][:, 0:n//2]
    d = M[n//2:n][:, n//2:n]
    # print("a"+str(a))

    e = N[0:n // 2][:, 0:n // 2]
    f = N[0:n // 2][:, n // 2:n]
    g = N[n // 2:n][:, 0:n // 2]
    h = N[n // 2:n][:, n // 2:n]

    t1 = f-h
    t2 = a+b
    t3 = c+d
    t4 = g-e
    t5 = a+d
    t6 = e+h
    t7 = b-d
    t8 = g+h
    t9 = a-c
    t10 = e+f

    if n//2 <= leaf_size:
        # print(n//2)
        p1 = ikjMult(a, t1, n//2)
        # print(p1)
        p2 = ikjMult(t2, h, n//2)
        p3 = ikjMult(t3, e, n//2)
        p4 = ikjMult(d, t4, n//2)
        p5 = ikjMult(t5, t6, n//2)
        p6 = ikjMult(t7, t8, n//2)
        p7 = ikjMult(t9, t10, n//2)
    else:
        # print("Str"+str(n//2))
        p1 = StrassenMult(a, t1, n//2)
        p2 = StrassenMult(t2, h, n//2)
        p3 = StrassenMult(t3, e, n//2)
        p4 = StrassenMult(d, t4, n//2)
        p5 = StrassenMult(t5, t6, n//2)
        p6 = StrassenMult(t7, t8, n//2)
        p7 = StrassenMult(t9, t10, n//2)

    t11 = p5+p4-p2+p6
    t12 = p1+p2
    t21 = p3+p4
    t22 = p1+p5-p3-p7
    # print(t11)
    # print(t21)

    t31 = numpy.concatenate((t11, t21))
    t41 = numpy.concatenate((t12, t22))
    return numpy.concatenate((t31, t41), axis=1)


def ikjMult(M, N, n):
    a = numpy.zeros(shape=(n, n), dtype=numpy.int64)
    for i in range(0, n):
        for k in range(0, n):
            t = M[i][k]
            for j in range(0, n):
                a[i][j] += t*N[k][j]
    return a


leaf_size = 2
m = 128
m1 = nextpow(m)
A = numpy.zeros(shape=(m1, m1), dtype=numpy.int64)
B = numpy.zeros(shape=(m1, m1), dtype=numpy.int64)
for i in range(0, m1):
    for j in range(0, m1):
        if i < m and j < m:
            A[i][j] = randint(0, m-1)
            B[i][j] = randint(0, m-1)
        else:
            A[i][j] = 0
            B[i][j] = 0
# print(A)
# print(B)
start = time.time()
ikjMult(A, B, m)
end = time.time()
print((end-start)*1000)

start = time.time()
StrassenMult(A, B, m1)
end = time.time()
print((end-start)*1000)
