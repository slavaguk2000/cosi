import numpy as np

N = 16

def init_res(x):
    return np.zeros(x.shape[0], dtype=np.complex64)

def furie_transmition(x, is_direct, fun_values):
   res = init_res(x)
   for k in range(N):
      for m in range(N):
         res[k] += fun_values[m] * (np.e)**(-1j*2*np.pi/N*k*m*(1 if is_direct else -1))
   if(is_direct):
      res /= N
   return res

def fust_furie_transmition(x, is_direct, fun_values):
    if len(fun_values) == 1:
        return fun_values
    b_even = fust_furie_transmition(x, is_direct, fun_values[::2])
    b_odd = fust_furie_transmition(x, is_direct, fun_values[1::2])
    N = len(fun_values)
    Wn = np.e ** (2 * np.pi * 1j / N)
    w = 1
    res = init_res(x)
    for i in range(int(N / 2)):
        res[i] = b_even[i] + w * b_odd[i]
        res[int(i + N / 2)] = b_even[i] - w * b_odd[i]
        w *= Wn
    return res

