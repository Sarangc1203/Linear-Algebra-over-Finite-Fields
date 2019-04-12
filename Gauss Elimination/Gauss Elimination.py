import numpy
from time import time
from random import randint
# from numba import vectorize


# def gcd(a, b):
#     if a == 0 or b == 0:
#         return 0
#     if a % b == 0:
#         return b
#     else:
#         return gcd(b, a%b)


def modArthInv(a, b):
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


# n = int(input("n?\n"))
# m = int(input("m?\n"))
n = 100
m = 101
mat = numpy.zeros(shape=(n, n+1), dtype=numpy.int64)
# for i in range(0, n):
#     print("next")
#     for j in range(0, n+1):
#         mat[i][j] = int(input("")) % m
# for i in range(0, n):
#     mat[i][i] = 1
#     mat[i][n] = 1
for i in range(0, n):
    for j in range(0, n+1):
        mat[i][j] = randint(0, m-1)

print(mat)
start = time()

for i in range(0, n):
    if mat[i][i] == 0:
        for k in range(i + 1, n):
            if mat[k][i] != 0:
                p = list(mat[k, :])
                mat[k, :] = mat[i, :]
                mat[i, :] = p
                break
    #print("i = "+str(i))
    #print(mat)

    #print(mat)

    if mat[i][i] == 0:
        print("No Solution")
        break
    else:
        if mat[i][i] != 1:
            mat[i, :] *= modArthInv(m, mat[i][i])
            mat[i, :] %= m
        #print(mat)
        # temp = mat[i, :]
        # mat -= temp
        # mat[i, :] = temp
        for j in range(0, n):
            if i != j and mat[j][i] != 0:
                mat[j, :] -= mat[j][i]*mat[i, :]
                mat[j, :] %= m
            # if mat[j][i] != 0:
            #     inv = modArthInv(m, mat[j][i])
            #     mat[j, :] *= inv
            #     mat[j, :] -= mat[i, :]
            #     mat[j, :] %= m
            #print(mat)

        #for j in range(i+1, n):
            #print(str(i)+" "+str(j))
            # g = gcd(m, mat[j][i])
            # if g > 1:
            #     mat[j, :] *= (m // g)
            # elif g == 1:
            #     inv = modArthInv(m, mat[j][i])
            #     mat[j, :] *= inv
            #     mat[j, :] -= mat[i, :]
            # mat[j, :] %= m
            #mat[j, :] -= mat[j][i] * mat[i, :]
            #mat[j, :] %= m
            # if mat[j][i] != 0:
            #     inv = modArthInv(m, mat[j][i])
            #     mat[j, :] *= inv
            #     mat[j, :] -= mat[i, :]
            #     mat[j, :] %= m

        #print(mat)

end = time()
print(mat[:, n])
print((end-start)*1000)
