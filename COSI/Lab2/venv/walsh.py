

import numpy as np
from matplotlib import pyplot as plt
import copy
N = 16
def source_fun(x):
   return np.sin(3 * x) + np.cos(x)

def simple_furie_core(res, fun_values, direct):
    for k in range(N):
        for m in range(N):
            res[k] += fun_values[m] * (np.e) ** (-1j * 2 * np.pi / N * k * m * (1 if direct else -1))
    return res

def getW(r, n, direct):
    return np.e ** (-2j*np.pi*r*(1 if direct else -1)/n)

def reverseBits(num, bitSize):
    binary = bin(num)
    reverse = binary[-1:1:-1]
    return int(reverse + (bitSize - len(reverse)) * '0', 2)

def fast_furie_core(res, values, direct):
    count = N
    while (count > 1):
        count = int(count/2)
        butterfly = int(N/count/2)
        for j in range(butterfly):
            for i in range(count):
                offset = count*2*j
                # res[i + offset] = "(" + values[i + offset] + "+" + values[i + count + offset] + ")"
                # res[i + count + offset] = "(" + values[i + offset] + "-" + values[i + count + offset] + ")" + "*" + "W" + str(i*butterfly);
                res[i + offset] = values[i + offset] + values[i + count + offset];
                res[i + count + offset] = (values[i + offset] + values[i + count + offset] * -1) * getW(i*butterfly, N, direct);
            values = copy.copy(res)
    bitCount = int(np.log2(N))
    for i in range(N):
        res[i] = values[reverseBits(i, bitCount)]
    return res

def transmition_core(direct, fun, x, furie_core):
    res = np.zeros(N, dtype=np.complex64)
    fun_values = fun(x)
    return furie_core(res, fun_values, direct)

def main_ft(x, furie_core):
    return transmition_core(True, source_fun, x, furie_core)

def main_ift(x, furie_core):
   return transmition_core(False, ft, x, furie_core)/N

def ft(x):
    return main_ft(x, simple_furie_core)

def fft(x):
    return main_ft(x, fast_furie_core)

def ift(x):
    return main_ift(x, simple_furie_core)

def ifft(x):
    return main_ift(x, fast_furie_core)

from rademaher import rademaher
from numpy import ndarray
from numpy import log2
import services as serv
def walsh(N):
    serv.check_pow_2(N)
    rad = rademaher(N)
    wal = ndarray((N, N))
    wal.fill(1)
    for i in range(N):
        bin_i = bin(i)
        r = int(log2(N))
        for k in range(1, r+1):
            wal[i] = rad[k]
            print(bin_i[k])
            #print(bin_i[r-k+1]^bin_i[r-k])
#            print(rad[k]**(bin_i[r-k+1]^bin_i[r-k]))
    return wal