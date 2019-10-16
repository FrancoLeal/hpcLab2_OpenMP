import numpy as np
from matplotlib import pyplot as plt

t_p = [5.118,3.619,3.136,2.944,2.327,2.492,2.209,2.410,2.183,2.262,2.240,2.225,2.153,2.202,2.190,2.110,2.184,2.152,2.162,2.144,2.157,2.197,2.135,2.115]
t_s = 5.124
speedup = []
x = []
for i in range(0,24):
    x = np.append(x,i+1)
    speedup = np.append(speedup,t_s/t_p[i])
    print(x[i])
plt.xlabel("N° de hebras")
plt.ylabel("Speedup")
plt.title("Comportamiento speedup")
plt.plot(x,speedup)
plt.grid(color = 'lime',linestyle='--',linewidth=0.5)
plt.show()