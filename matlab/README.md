> Czy sygnału miograficznego można słuchać, tak jak dzwięku? Cisnienie akustyczne to różnica ciśnienia atmosferycznego. Wobec tego "mowa" mięśni to różnica od "masy" potencjału elektrycznego ciała?

 **Tak, powiem więcej, warto nawet przeskalować(resampling) do pasma słyszalnego przez ludzi** *~TZ*

>[Analiza one&two.wav
![aMi](docs/512w.png)](https://htmlpreview.github.io/?https://raw.githubusercontent.com/informacja/EMG/master/matlab/Spectral%20Analysis/Prog2b.html)

## Matlab Editor VS Code 

> Wtyczka wsparcia *lint, snippets, run* dla języka [Matlab do edytora VS Code
![Snippets](docs/mSnippets.png)](https://marketplace.visualstudio.com/items?itemName=bat67.matlab-extension-pack#review-details)
<!-- 
>[alternative Matlab ide
![aMi](docs/aMi.png)](https://marketplace.visualstudio.com/items?itemName=marmottet.ami)  
-->

 
### Zapis do pliku \*.png o nazwie m-pliku
```matlab
[a,fname,c] = fileparts( mfilename('fullpath')); 
print( strcat(fname,'.png'),'-dpng');
```

 
### Zapis do pliku z numerem figury
```matlab
[a,fname,c] = fileparts( mfilename('fullpath'));                   % get current m-file name
print( strcat(fname, '_', num2str(get(gcf,'Number')), '.png'),'-dpng'); % save file CurrentMFile-lastFigureNumber.png

```

https://stijournal.pl/resources/html/article/details?id=204954#233202
