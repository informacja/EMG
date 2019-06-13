import os,io,sys

try:
  import numpy as np
  import matplotlib.pyplot as plt
  import scipy.fftpack
except:
  print("Uruchom inst.bat")
  sys.exit(1)


if len(sys.argv)<2: print("Wywol~anie:  python draw.py NAZWA_Pliku.csv")
#sys.exit(1)

def fx(x):
  return float(x)


L=[]
with io.open(sys.argv[1]) as F:				
  for l in [l.strip('\n\r,') for l in F.readlines()]:
    A=list(map(lambda x:fx(x),l.split(',')))
    L+=[A]

for l in L:
  N=len(l)
  x=np.linspace(0.0, N, N)
  y=l

  fig, ax = plt.subplots()
  ax.plot(x,y)
  plt.show()

  T=0.01

  yf = scipy.fftpack.fft(y)
  xf = np.linspace(0.0, 1.0/(2.0*T), N/2)
  fig, ax = plt.subplots()
  ax.plot(xf[1:],np.abs(yf[1:N//2]))
  plt.show()

# Number of samplepoints
N = 800
## sample spacing
T = 1.0 / 100.0
x = np.linspace(0.0, N*T, N)
y = 2*np.sin(50.0 * 2.0*np.pi*x) + 5*np.sin(80.0 * 2.0*np.pi*x)-8*np.sin(132.0*2.0*np.pi*x)
y=0
for n in range(1,600):
 k=2*n-1
##  if k>1200:continue # filtr dolnoprzep dla fg=120
 y+=4./(np.pi*k)*np.sin(k * 2.0*np.pi*x)
yf = scipy.fftpack.fft(y)
xf = np.linspace(0.0, 1.0/(2.0*T), N/2)

f1,a1=plt.subplots()
a1.plot(x,y)

yf = scipy.fftpack.fft(y)
xf = np.linspace(0.0, 1.0/(2.0*T), N/2)
fig, ax = plt.subplots()
ax.plot(xf, 2.0/N * np.abs(yf[:N//2]))
plt.show()
