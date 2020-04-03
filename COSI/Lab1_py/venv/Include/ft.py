import numpy as np
import scipy as sc
import copy
N = 16
def getW(N, is_direct):
    return (np.e)**(-1j*2*np.pi/N*(1 if is_direct else -1))

def init_res(N):
    return np.zeros(N, dtype=np.complex64)


def reverseBits(num, bitSize):
    binary = bin(num)
    reverse = binary[-1:1:-1]
    reverse = reverse + (bitSize - len(reverse)) * '0'
    return int(reverse, 2)

def furie_transmition(is_direct, fun_values):
    N = len(fun_values)
    res = init_res(N)
    w = getW(N, is_direct)
    for k in range(N):
        for m in range(N):
            res[k] += fun_values[m] * w**(k*m)
    if(not is_direct):
        res /= N
    return res


def fast_furie_transmition_time(is_direct, fun_values):
    N = len(fun_values)
    if is_direct:
        return sc.fft(fun_values)
    else:
        return sc.ifft(fun_values)
    if len(fun_values) == 1:
        return fun_values
    b_even = sc.fft(fun_values[::2])
    b_odd = sc.fft(fun_values[1::2])
    w = 1
    Wn = getW(N, is_direct)
    res = init_res(N)
    for i in range(int(N / 2)):
        res[i] = b_even[i] + w * b_odd[i]
        res[int(i + N / 2)] = b_even[i] - w * b_odd[i]
        w *= Wn
    return res

def fast_furie_transmition_freq(is_direct, fun_values):
    N = len(fun_values)
    log2N = int(np.log2(N))
    w = getW(N, is_direct)
    res = init_res(N)
    for i in range(N):
        res[i] = fun_values[i]
    k = N
    while (k > 1):
        k = int(k/2)
        for i in range(0, N, k*2):
            for j in range(i, int(i + k)):
                a = res[j]
                b = res[j+ k]
                res[j] =  a + b
                res[j + k] = (a - b) * w**((j - i)*(N/(k*2)))
    for i in range(N):
        j = reverseBits(i, log2N)
        (res[i], res[j]) = (res[j], res[i])
    if (not is_direct):
        res /= N
    return res