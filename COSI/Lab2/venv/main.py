from scipy.linalg import hadamard
from numpy import zeros
from numpy import log2
from rademaher import rademaher
from walsh import walsh
from walsh import fwt
import services as serv
N = 8
num_fun_wal = 2
num_fun_had = 3

serv.check_pow_2(N)

had = hadamard(N)
wal = walsh(N)
print(fwt(wal[num_fun_wal]))
print(fwt(had[num_fun_had]))
