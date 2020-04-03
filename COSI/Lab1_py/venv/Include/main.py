import numpy as np
import drawer as dw
import ft
import scipy.fft as fff

def source_fun(x, transmition):
   return np.sin(3 * x) + np.cos(x)
def test():
   x = np.linspace(0, 14, ft.N)
   print(fff.fft(source_fun(x, 1)))
   print(ft.fast_furie_transmition_freq(True, source_fun(x,1)))
   print(ft.furie_transmition(True, source_fun(x,1)))
   exit(0)

def ift_fun(x, transmition):
   source = source_fun(x, transmition)
   values = transmition(True, source)
   return transmition(False, values).real

def amplitude(x, transmition):
   return abs(transmition(True, source_fun(x, transmition)))

def phase(x, transmition):
   complex_ar = transmition(True, source_fun(x, transmition))
   return np.arctan(complex_ar.imag / complex_ar.real)

dw.drawPlot(source_fun, ft.furie_transmition, "X", "Amplitude")
dw.drawPlot(amplitude, ft.furie_transmition, "Frequince", "Amplitude")
dw.drawPlot(ift_fun, ft.furie_transmition, "X", "Amplitude")
dw.drawPlot(amplitude, ft.fast_furie_transmition_time, "Frequince", "Amplitude")
dw.drawPlot(ift_fun, ft.fast_furie_transmition_time, "X", "Amplitude")
dw.drawPlot(amplitude, ft.fast_furie_transmition_freq, "Frequince", "Amplitude")
dw.drawPlot(ift_fun, ft.fast_furie_transmition_freq, "X", "Amplitude")

exit(0)
dw.drawPlot(phase, ft.furie_transmition, "Frequince", "Phase")
dw.drawPlot(ift_fun, ft.furie_transmition, "X", "Amplitude")
dw.drawPlot(amplitude, ft.fust_furie_transmition_time, "Frequince", "Amplitude")
dw.drawPlot(phase, ft.fust_furie_transmition_time, "Frequince", "Phase")

# dw.drawPlot(amplitude, ft.fust_furie_transmition_freq, "Frequince", "Amplitude")
# dw.drawPlot(phase, ft.fust_furie_transmition_freq, "Frequince", "Phase")


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