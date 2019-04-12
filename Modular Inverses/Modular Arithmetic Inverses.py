import time
import random


def modArthInv(a, b):
    if b > a:
        a, b = b, a
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
        print(l[0][1] % a)
    else:
        print((-l[0][1]) % a)


def naive():
    for i in range(1, m):
        if i*n % m == 1:
            print(i)
            break


# m = int(input("mod?"))
# n = int(input("n?"))
m = 1009
n = 11
# m = 10009
# n = 0
start = time.time()
#
modArthInv(m, n)
# for i in range(10000):
#     modArthInv(m, n)
end = time.time()
print((end-start)*1000)
# print("")
# start = time.time()
# naive()
# end = time.time()
# print((end-start)*1000)
