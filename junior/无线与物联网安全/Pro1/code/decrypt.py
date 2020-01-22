
# read the file
def hex2list(a):
    b = []
    for i in range(int(len(a)/2)):
        b.append(int(a[2*i:2*i+2],16))
    return b

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
    #print(lists)


#I know the plaintext has HTTP POST GET INPUT OUTPUT
# H T P O S G E I N U , SPACE
# generate the dictionary
char = ['H','T','P','O','S','G','E','I','N','U',',',' ']
dictionary = {}
for i in range(len(char)):
    for j in range(i+1,len(char)):
        if (ord(char[i]) ^ ord(char[j])) in dictionary.keys():
            dictionary[ord(char[i]) ^ ord(char[j])] += char[i]+char[j]
        else:
            dictionary[ord(char[i]) ^ ord(char[j])] = char[i]+char[j]
dictionary[0] = ''
#print(len(dictionary))


#begin to decrypt the key(when Nonce = 0)
def xor(a,b):
    assert len(a) == len(b)
    c = []
    for i in range(len(a)):
        c.append(a[i]^b[i])
    return c

plaintext = [['' for j in range((16))] for i in range(len(lists))]
afterxor  = [[] for i in range(len(lists))]
for i in range(0,len(lists)):
    for j in range(0,len(lists)):
        if i == j : 
            continue
        afterxor[i].append(xor(lists[i][0],lists[j][0]))

for i in range(len(afterxor)):
    for j in afterxor[i]:
        for k in range(len(j)):
            plaintext[i][k] += dictionary[j[k]]

def max_letter_count(n):
    list4 = []
    list1 = []
    list2 = []
    for i in n:
        list3 = []
        count_max = n.count(i)
        list3.append(i)
        list3.append(count_max)
        list1.append(list3)
        list2.append(count_max)
    num=max(list2)
    for i in range(len(list2)):
        if list2[i] == num:
            list4.append(list1[i][0])
    tmp = list(set(list4))
    ans = ''
    for i in tmp:
        ans += i
    return ans

print("The possible plaintext:\n(one character means this byte is definite \nwhile more than one characters means these are possible characters of the byte.)\n")
for i in range(len(plaintext)):
    for j in range(len(plaintext[i])):
        plaintext[i][j] = max_letter_count(plaintext[i][j])
    print(plaintext[i])      

print("The output may need manually check, Please run the GetKey.py now.")
# may need manually check the word
