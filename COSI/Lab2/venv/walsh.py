from rademaher import rademaher
from bitarray import bitarray
from numpy import ndarray, log2, zeros
from copy import copy
import services as serv

def fwt(x):
    N = len(x)
    res = zeros(N)
    count = N
    while (count > 1):
        count = int(count/2)
        butterfly = int(N/count/2)
        for j in range(butterfly):
            for i in range(count):
                offset = count*2*j
                res[i + offset] = x[i + offset] + x[i + count + offset];
                res[i + count + offset] = x[i + offset] - x[i + count + offset]
            x = copy(res)
    return res/8


def walsh(N):
    serv.check_pow_2(N)
    rad = rademaher(N)
    wal = ndarray((N, N))
    wal.fill(1)
    for i in range(N):
        r = int(log2(N))
        bin_i = ('0'*r+bin(i)[2:])[-r-1:]
        for k in range(1, r+1):
            wal[i] *= rad[k]**(int(bin_i[r-k+1])^int(bin_i[r-k]))
    return wal