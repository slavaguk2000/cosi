import numpy as np
import ft
from matplotlib import pyplot as plt

def drawPlot(fun, transmition, xlabel, ylabel):
   x = np.linspace(0, 14, ft.N)
   ax  = plt.gca()
   ax.axhline(y = 0, color = 'k')
   ax.set_xlabel(xlabel)
   ax.set_ylabel(ylabel)
   plt.plot(x, fun(x, transmition))
   plt.show()