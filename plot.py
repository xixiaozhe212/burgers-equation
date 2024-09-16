import numpy as np
import matplotlib.pyplot as plt

x = np.linspace(0, 2.0, 100)

plt.ion()

for n in range(0, 81, 10):
    data = np.loadtxt(str(n)+".dat")
    plt.clf()
    plt.plot(x, data, ".-")
    plt.xlabel("x")
    plt.ylabel("u")
    plt.xlim([0.0, 2.0])
    # plt.ylim([-0.1,1.3])
    plt.pause(0.2)
    plt.ioff()