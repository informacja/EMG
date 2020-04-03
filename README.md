# EMG WaveApp
Aplikacja przetwarzająca sygnał elektromiograficzny napięcia mięśniowego <br> 

##### Specyfikacja sprzętowa:
	 LPC1347 32-bit ARM Cortex-M3 mikrokontroler
	 DFRobot Gravity - analogowy czujnik EMG

## Elektrody podpinamy kolejno zacznąc od pinu P0_11 (obecnie 3 kanały)
<img src="docs/LPC1347.jpg">

## Widmo charakterystyczne EMG, zaciśnięta dłoń (0-512Hz)  
<img src="docs/now.png">

## Elektroda wykrywając pracę mięśni palca środkowego i serdecznego (like Spiderman)
<img src="docs/spider.gif">

## Synał z trzech kanałów: pojedyncze zaciśnięcia dłoni, parami oraz niepodpięty kanał (ujemna amplituda niesymetryczna)
<img src="docs/out56.png">
