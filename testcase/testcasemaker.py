#This makes test case for comparing both heaps. Given below test case contains 50 heaps each with 200 elements in them and union is appplied on these heaps.

with open("INSERT_UNION_FIB.txt",'w') as f:
    f.write('50\n')
    for q in range(50):
        f.write(f'{q}\n')
        for i in range(200):
            f.write('1\n')
            f.write(f'{q*200+i}\n')
        for i in range(10):
            f.write('3\n')
        f.write("7\n")
    f.write("0\n")
    for q in range(1,50):
        f.write(f"2\n{q}\n")
    f.write("7\n")
    f.write("-1\n")


with open("INSERT_UNION_BINARY.txt",'w') as f:
    f.write('50\n')
    for q in range(50):
        f.write(f'{q}\n')
        for i in range(200):
            f.write('1\n')
            f.write(f'{q*200+i}\n')
        for i in range(10):
            f.write('3\n')
        f.write("8\n")
    f.write("0\n")
    for q in range(1,50):
        f.write(f"2\n{q}\n")
    f.write("8\n")
    f.write("-1\n")