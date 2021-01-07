result = []
first=['u','s','z','d']
second=['d','l','h','e']
key=['o','p','l','k']
for x in range(4):
    temp = ord(first[x]) ^ (ord(second[x]) ^ ord(key[x]))
    if temp>122:
        temp=temp-26
    if temp<97:
        temp = temp + 26
    result += chr(temp)
print(result)