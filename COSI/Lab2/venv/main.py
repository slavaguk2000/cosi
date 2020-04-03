from scipy.linalg import hadamard
from numpy import zeros
from numpy import log2
from rademaher import rademaher
from walsh import walsh
import services as serv
N = 8
serv.check_pow_2(N)

had = hadamard(N)
rad = rademaher(N)
wal = walsh(N)
#print(wal)