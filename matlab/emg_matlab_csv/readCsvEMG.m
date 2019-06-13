function [m] = readCsvEMG(filename)

% Do komentowania u¿ywamy skrótu Ctrl + R

filename = 'zacisk_slaby.csv';          
filename = 'bezczynnosc.csv';           % bardzo ma³y pik przy 50 Hz (w pierwszym kwadracie wykresu)
filename = 'zacisk silny.csv';          % ma³a amplituda mo¿e byæ spowodowana s³abym przyleganiem do cia³a
% filename = '50Hz.csv';                  % gdy nic nie jest podpiête do elektrody, widzimy harmoniczne

%% Wczytywanie danych
M = csvread(filename);

% n - zapisanych próbek (jedna na wiersz)
[n,length] = size(M);
L = length-1; 

% wartoœc Fs jest z internetu :) nie znam prawdziwej 
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
%     fprintf('Próbka nr: %d', i); input('');
end

    title( sprintf('Fourier Transform Of Original Signal ‘X’ \t\t %s', filename))
    xlabel('Frequency 0-1024 (Hz) ') % nie wiem jak poprwanie ustawiæ podpis osi 
    ylabel('Amplitude')

end