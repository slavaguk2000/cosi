from numpy import log2

def check_pow_2(N):
    if (log2(N) != int(log2(N))):
        raise Exception("N should be a power of 2")
