import time
import sys
sys.setrecursionlimit(50000)

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


def modArthInv2(a):
    def power(x, n):
        if n == 0:
            return 1
        p = power(x, n / 2) % m
        p = (p * p) % m
        if n % 2 == 0:
            return p
        else:
            return (x * p) % m
    return power(a, m-2)


m = 7919
start = time.time()
for j in range(1, m):
    modArthInv1(j, m)
end = time.time()
print(end-start)

start = time.time()
for j in range(1, m):
    modArthInv2(j)
end = time.time()
print(end-start)
