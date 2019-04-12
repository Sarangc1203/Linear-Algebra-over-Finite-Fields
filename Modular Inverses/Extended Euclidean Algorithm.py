a = int(input("a?"))
b = int(input("b?"))
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
if len(l) != 0:
    if l[0][2] >= 0 > l[0][1]:
        print(str(l[0][0]) + "(" + str(a) + ") + " + str(-l[0][1]) + "(" + str(b) + ") = " + str(l[0][2]))
    elif l[0][2] >= 0 and l[0][1] >= 0:
        print(str(l[0][0]) + "(" + str(a) + ") - " + str(l[0][1]) + "(" + str(b) + ") = " + str(l[0][2]))
    elif l[0][2] < 0 and l[0][0] < 0:
        print(str(l[0][1]) + "(" + str(b) + ") + " + str(-l[0][0]) + "(" + str(a) + ") = " + str(-l[0][2]))
    else:
        print(str(l[0][1]) + "(" + str(b) + ") - " + str(l[0][0]) + "(" + str(a) + ") = " + str(-l[0][2]))
else:
    print(str(a) + " - " + str(a // b) + "(" + str(b) + ") = 0")
