## Pytania

> Czy sygnału miograficznego można słuchać, tak jak dzwięku? Cisnienie akustyczne jest to różnica od ciśnienia atmosferycznego. Wobec tego "mowa" mięśni to różnica od "masy" potencjału elektrycznego ciała?

## Prototypy

>[Analiza one&two.wav
![aMi](../docs/512w.png)](https://htmlpreview.github.io/?https://raw.githubusercontent.com/informacja/EMG/master/matlab/Spectral%20Analysis/Prog2b.html)

## Matlab Editor VS Code 

> Wtyczka wsparcia *lint, snippets, run* dla języka [Matlab do edytora VS Code
![Snippets](../docs/mSnippets.png)](https://marketplace.visualstudio.com/items?itemName=bat67.matlab-extension-pack#review-details)

>[alternative Matlab ide
![aMi](../docs/aMi.png)](https://marketplace.visualstudio.com/items?itemName=marmottet.ami) 

### Trzy kanały (pierwszy jest w środku)
<img src="../docs/matlabWaterfall.png">
 
### Zapis do pliku png
```matlab
[a,fname,c] = fileparts( mfilename('fullpath')); 
print( strcat(fname,'.png'),'-dpng');
```
