print("Please see the decrypt.py's output, and manually check the word.\nPlease input one of the plaintext and its No.")
plaintext = input("input the plaintext after check (eg. 'POST, GET, INPUT')\n")
No = input("the No. of the input plaintext.(begin from 1)\n")
#read the file 
def hex2list(a):
    b = []
    for i in range(int(len(a)/2)):
        b.append(int(a[2*i:2*i+2],16))
    return b

def xor(a,b):
    assert len(a) == len(b)
    c = []
    for i in range(len(a)):
        c.append(a[i]^b[i])
    return c

with open("captured_cipher","r") as f:
    lines = f.readlines()
    for line in lines:
        line = line.strip('\n')
        if line.isdigit():
            rows = int(line)
    #print(rows)
    lists = [[] for i in range(rows)]
    for line in lines:
        line = line.strip('\n')
        if line.isdigit():
            rows = int(line)
            continue
        lists[rows-1].append(hex2list(line))

plaintext1 = []
for i in range(len(plaintext)):
    plaintext1.append(ord(plaintext[i]))
key = xor(lists[No-1][0],plaintext1)
print("the key is :{}".format(key))