% [Y, FS]=audioread(FILENAME, [START END], DATATYPE);
function [x] = wav_emg(filename)

filename = 'sample/50hz.wav';
filename = 'sample/noise.wav';
filename = 'sample/hand.wav';

filename = 'sample/a.wav';
filename = 'sample/b.wav';
filename = 'sample/c.wav'; % 4*bps
% filename = 'sample/d.wav'; % hand

shift = [1, 2048*2]

info = audioinfo(filename)

[data, fs] = audioread(filename, shift);

d(info.SampleRate) = data(info.SampleRate);

% d
% wyswietlanie kilku klatek
%      data_fft = fft(data); % data
%  size(data_fft)
%    plot(abs(data_fft(:,1)));
%   return;
for i = 1:info.Duration
    
shift = [ info.SampleRate*(i-1)+1, info.SampleRate*i]

 if shift(1) == 0
     shift(1) = 1;
 end

%     for i = 1:info.SampleRate
%         d(i) = data(i+shift(1));
%         
        d = data( shift(1) : shift(2))';
        size(d)
%     end
    
 data_fft = fft(d)/info.SampleRate;% data
 data_fft = data_fft';
 plot(abs(data_fft(:,1)),'r');

    pause(0.111);         
%     fprintf('Pr�bka nr: %d', i); input('');
end
%  data_fft = fft(data) ;% data
%  plot(abs(data_fft(:,1)));
 return;
 
 
[y,fs] = audioread(filename);

 whos y
ydft = fft(y);
% I'll assume y has even length
ydft = ydft(1:length(y)/2+1);
% create a frequency vector
freq = 0:fs/length(y):fs/2;
% plot magnitude
subplot(211);
plot(freq,abs(ydft));
% plot phase
subplot(212);
plot(freq,unwrap(angle(ydft))); 
xlabel('Hz');

return;
% below from csv-------------------------------------------------------------------------

Fs=FS;
samples = [1,2*Fs];
[Y, FS] =  audioinfo(filename, samples)

n = info.Duration
whos Y

t = 0:seconds(1/Fs):seconds(info.Duration);
t = t(1:info.TotalSamples);
size(t)
size(Y)
plot(t,Y)
xlabel('Time')
ylabel('Audio Signal')

L = length(Y)-1; 

T = 1/FS; 
t = (0:L-1)*T;                                      % Time vector
Fn = FS/2;                                          % Nyquist Frequency
Fv = linspace(0, 1, fix(L/2)+1)*Fn;                 % Frequency Vector
Iv = 1:size(Fv,2);
%     
%  for i = 1:1
    
%     X=Y(i,:); 
X = Y;
    FX = fft(X)/L;                                      % Fourier Transform
    
%     plot(Fv, abs(FX(Iv))*2); figure(1); grid; 
% end
end