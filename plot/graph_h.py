import matplotlib.pyplot as plt
from random import *

def graph(list_1,list_2,NAME):
    layer_1 = 0
    layer_2 = 0
    e = 0
    M = list_1
    while e == 0:
        try:
            M = M[0]
            layer_1 += 1
            if M == M[0]:
                layer_1 -= 1

                e = 1
        except:
            e = 1
    e = 0
    M = list_2
    while e == 0:
        try:
            M = M[0]
            layer_2 += 1
            if M == M[0]:
                layer_2 -= 1
                e = 1
        except:
            e = 1
    if NAME == None:
        if layer_2 != 1:
            NAME = [None] * layer_2

    if layer_1 == 1 and layer_2 > 1 or layer_2 == layer_1 and layer_1 > 1 and layer_2 > 1:
            for i in range(len(list_2)):
                if layer_2 != layer_1:
                    simple_graph(list_1,list_2[i],NAME[i])
                else:
                    simple_graph(list_1[i],list_2[i],NAME[i])

    else:
        simple_graph(list_1,list_2,NAME)

    plt.grid()
    plt.show()
def simple_graph(list_1,list_2,NAME):
    if list_1 != None and str(list_1[0]) == list_1[0]:
        N = []
        for i in range(len(list_1)):
            N.append(i)
        plt.xticks(N, list_1)
        list_1 = None
    if list_2 != None and str(list_2[0]) == list_2[0]:
        N = []
        for i in range(len(list_2)):
            N.append(i)
        plt.xticks(N, list_2)
        list_2 = None
    if NAME != [] and NAME != None:
        if list_1 != None and list_2 != None:
            plt.plot(list_1,list_2,label=NAME)
        elif list_2 != None:
            plt.plot(list_2,label=NAME)
        else:
            plt.plot(list_1,label=NAME)
        plt.legend(bbox_to_anchor=(0.7, 1.14), loc=2, borderaxespad=0)
    else:
        if list_1 != None and list_2 != None:
            plt.plot(list_1,list_2)
        elif list_2 != None:
            plt.plot(list_2)
        else:
            plt.plot(list_1)

f = open("/home/daniel/.ann/func", "r")
L = []
for e in f.read().split():
  L.append(float(e))
f.close()

s = []
for i in range(100):
  s.append(i/100)

x = [s]
fx = [L]

crs = open("/home/daniel/.ann/crs", "r")
dts = crs.read().split()
crs.close()

i = 0
ex = []
efx = []
b = []
while i < len(dts):
  a = float(dts[i])
  i += 1
  o = float(dts[i])
  i += 1
  b.append((a,o))

b.sort()

for (a,o) in b:
  ex.append(a)
  efx.append(o)

x.append(ex)
fx.append(efx)

graph(x, fx, None) #FILL LISTS WITH VALUES [x] [f(x)]
