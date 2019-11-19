# Finger_EMG 
Aplikacja przetwarzająca sygnał elektromiograficzny napięcia mięśni <br> 

##### Specyfikacja sprzętowa:
	 LPC1347 32-bit ARM Cortex-M3 mikrokontroler
	 DFRobot Gravity - analogowy czujnik EMG

## Elektrody podpinamy kolejno zacznąc od pinu P0_11 (obecnie 3 kanały)
<img src="docs/LPC1347.jpg">

## Elektroda wykrywając pracę mięśni palca środkowego i serdecznego  
<img src="docs/spider.gif">

## Widmo charakterystyczne EMG, zaciśnięta dłoń (0-512Hz)  
<img src="docs/now.png">

## Linux VBox  
<img src="docs/Centos8Vbox.png">

### Matlab wave fft
<img src="docs/works.gif">

### Start_here.m script 
<img src="docs/matlsig.png">

### Hann window (red)
<img src="docs/hann.png">

#### FS 256
<img src="docs/256.png">

#### FS 1024
<img src="docs/1024.png">

# Instrukcja obsługi aplikacji 
### Nawigacja 

>Zalecaną metodą obsługi jest używanie skrótów klawiaturowych
	
> <kbhit>Ctrl</kbhit> + <kbhit>Tab</kbhit> zmiana karty 
		
> Wszystkie ustawienia przłączalne (toggle) można ustawiać  <kbhit>Ctrl</kbhit> + <kbhit>numer</kbhit> 
		
> Aby rozpocząć nagrywanie, upewniamy się, że aktualna zakładka to **zapis** naciskamy <kbhit>Enter</kbhit> pasek postępu zacznie się wypełniać
		
### Zapis 
> Open tab "Save" and just press <kbhit> Enter </kbhit>, progress bar should fill in.

# ButterWorth
## Bez filtracji
<img src="docs/no.png">

## Po wycięciu 50Hz

<img src="docs/filtered.png">

## Band Stop

<img src="docs/bandStop.gif">

## High Pass
<img src="docs/highPass.gif">

### Asymptota szumu (zielony)
Widmo jest symetryczne, tu widzimy lewą połowę widma, oś symetrii jest na krawędzi obrazu
<img src="docs/noise.png">

