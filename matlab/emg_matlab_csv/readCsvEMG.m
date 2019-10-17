function [m] = readCsvEMG(filename)

% Do komentowania u�ywamy skr�tu Ctrl + R


% filename = 'zacisk_slaby.csv';          
% filename = 'bezczynnosc.csv';           % bardzo ma�y pik przy 50 Hz (w pierwszym kwadracie wykresu)
% filename = 'zacisk silny.csv';          % ma�a amplituda mo�e by� spowodowana s�abym przyleganiem do cia�a
filename = '50Hz.csv';                  % gdy nic nie jest podpi�te do elektrody, widzimy harmoniczne
%  filename = 'sample/peak.csv';                  % gdy nic nie jest podpi�te do elektrody, widzimy harmoniczne
%% Wczytywanie danych
M = csvread(filename);

% n - zapisanych pr�bek (jedna na wiersz)
[n,length] = size(M);
L = length-1; 

% warto�c Fs jest z internetu :) nie znam prawdziwej 
Fs = 0.00378;                                       % Sampling frequency
T = 1/Fs; 
t = (0:L-1)*T;                                      % Time vector
Fn = Fs/2;                                          % Nyquist Frequency
Fv = linspace(0, 1, fix(L/2)+1)*Fn;                 % Frequency Vector
Iv = 1:size(Fv,2);
    
%%    hold on; 
    
for i = 1:n
    
    X=M(i,:);   
    FX = fft(X)/L;                                      % Fourier Transform
    
    plot(Fv, abs(FX(Iv))*2); figure(1); grid; 
    pause(.111);         
%     fprintf('Pr�bka nr: %d', i); input('');
end

    title( sprintf('Fourier Transform Of Original Signal �X� \t\t %s', filename))
    xlabel('Frequency 0-1024 (Hz) ') % nie wiem jak poprwanie ustawi� podpis osi 
    ylabel('Amplitude')

end