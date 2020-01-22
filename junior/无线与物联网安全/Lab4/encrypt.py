
def xor(a, b):
	ans = []
	#assert len(a) != len(b)
	ans.append(hex(a[0]^b[0]))
	for i in range(1,min(len(b),len(a))):
		ans.append(hex(b[i] ^ a[i]))
	return ans
	
	
def getICV(a):
	ans = []
	ans.append(a[0])
	for i in range(1,len(a)):
		ans[0] = ans[0] ^ a[i]
	return ans
	
a = input("输入最多三个16进制数作为明文，用','分开：")
b = input("输入比明文多1个16进制数，用','分开：")
plaintext = a.split(",")
plaintext = [int(plaintext[i],16) for i in range(len(plaintext))]
ICV = (getICV(plaintext))
print("The ICV is:{}".format(hex(ICV[0])))
plaintext = plaintext + ICV
keystream = b.split(",")
keystream = [int(keystream[i],16) for i in range(len(keystream))]
ciphertext = xor(plaintext,keystream)
print(ciphertext) #'0xf7', '0xf1', '0xde', '0xda'