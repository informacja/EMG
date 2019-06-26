% [Y, FS]=audioread(FILENAME, [START END], DATATYPE);
function [x] = wav_emg(filename)

filename = 'sample/thumb/out2.wav';
% filename = 'out.wav';

[Y, FS]=audioread(filename)

L = length(Y)-1; 

T = 1/FS; 
t = (0:L-1)*T;                                      % Time vector
Fn = FS/2;                                          % Nyquist Frequency
Fv = linspace(0, 1, fix(L/2)+1)*Fn;                 % Frequency Vector
Iv = 1:size(Fv,2);
    
% for i = 1:n
    
%     X=M(i,:);   
    FX = fft(Y)/L;                                      % Fourier Transform
    
    plot(Fv, abs(FX(Iv))*2); figure(1); grid; 

% end
end