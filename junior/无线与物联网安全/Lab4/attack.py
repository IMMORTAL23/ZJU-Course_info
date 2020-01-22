def xor(a, b):
	ans = []
	#assert len(a) != len(b)
	for i in range(1,min(len(b),len(a))):
		ans.append((b[i] ^ a[i]))
	return ans
	
def getICV(a):
	ans=0
	for i in range(0,len(a)-1):
		ans = ans ^ a[i]
	return ans
	
def check(s):
	flag = 0
	keystream = [0x5b,0x2a,0x3d,0x4e]
	plain = xor(s,keystream)
	ICV = getICV(plain)
	#print("Guess: {}, NewICV: {}.".format(hex(s[-1]),hex(plain[-1])))
	if ICV == plain[-1]:
		flag = 1;
	return flag

ciphertext = [0xf7,0xf1,0xde,0x90]
chop = [0xf7,0xf1]
chopchop = [0xf7]
S1=S2=0

for i in range(0,0x100):
	chop.append(i)
	if(check(chop)):
		S1 = i
		print("The S1 is "+hex(i))
		break
	del chop[2]

for i in range(0,0x100):
	chopchop.append(i)
	if(check(chopchop)):
		S2 = i
		print("The S2 is "+hex(i))
		break
	del chopchop[1]

print("The data3 is "+ hex(S1^S2^ciphertext[1]^ciphertext[2]))