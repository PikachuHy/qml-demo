import numpy as np

data = np.load('/home/pikachu/Documents/pose.npz')
a = data['arr_0']
print(a.shape)
b = a[0]
print(len(b))
c = b[0]
print(len(c))
d = c[0]
# print(d,len(d))
# print(c[1],len(c[1]))
print(c)
