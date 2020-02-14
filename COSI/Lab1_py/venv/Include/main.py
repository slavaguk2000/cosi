import numpy as np
import drawer as dw
import ft
# from scipy.fft import fft

def source_fun(x, transmition):
   return np.sin(3 * x) + np.cos(x)

def ift_fun(x, transmition):
   source = source_fun(x, transmition)
   values = transmition(x, True, source)
   return transmition(x, False, values).real

def amplitude(x, transmition):
   return abs(transmition(x, True, source_fun(x, transmition)))

def phase(x, transmition):
   complex_ar = transmition(x, True, source_fun(x, transmition))
   return np.arctan(complex_ar.imag / complex_ar.real)

dw.drawPlot(source_fun, ft.furie_transmition, "X", "Amplitude")
dw.drawPlot(amplitude, ft.furie_transmition, "Frequince", "Amplitude")
dw.drawPlot(phase, ft.furie_transmition, "Frequince", "Phase")
dw.drawPlot(ift_fun, ft.furie_transmition, "X", "Amplitude")
dw.drawPlot(amplitude, ft.fust_furie_transmition, "Frequince", "Amplitude")
dw.drawPlot(phase, ft.fust_furie_transmition, "Frequince", "Phase")


# исходная функция
# амплитуды от частоты
# фазы от частоты
# вернуть из исходной
# амплитуды от частоты fast
# фазы от частоты fast
# вернуть из исходной fast

# знать 3 свойства
# где применить
#
#