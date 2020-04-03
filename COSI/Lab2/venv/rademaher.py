from numpy import ndarray
from numpy import log2
import services as serv


def rademaher(N):
    serv.check_pow_2(N)
    rad = ndarray((int(log2(N)+1), N), int)
    for i in range(len(rad)):
        for j in range (len(rad[i])):
            rad[i][j] = 1 if j%(N/2**(i-1)) < (N/2**i) else -1
    return rad