% [Y, FS]=audioread(FILENAME, [START END], DATATYPE);
% function [x] = wav_emg(filename)

% to do get current file path from csv log file (last file)

filename = 'sample/50hz.wav';
 filename = 'sample/noise.wav';
 filename = 'sample/hand.wav';

 filename = 'sample/noise4.wav';
 filename = 'sample/hand4.wav';
%  filename = 'sample/silence4.wav';
% 
% filename = 'sample/noise2.wav';
% filename = 'sample/hand2.wav';
% filename = 'sample/silence2.wav';

 % filename = 'sample/a.wav';
% filename = 'sample/b.wav';
% filename = 'sample/c.wav'; % 4*bps
% filename = 'sample/d.wav'; % hand
 
filename = 'rectangle/nothing.wav';

filename = 'sample/out18.wav';
filename = 'sample/out21.wav'; % 2048

filename = 'sample/out28.wav'; % 2048

filename = 'Mario62/out4.wav';

info = audioinfo(filename)
% info.SampleRate = info.SampleRate*4;

[data, fs] = audioread(filename,'double');
 
for i = 1:info.Duration
    
 shift = [ info.SampleRate*(i-1)+1, info.SampleRate*i];
 d = data( shift(1) : shift(2))';
    
 data_fft = fft(d)'/info.SampleRate;                                       % values from 0 to 1 
%    plot(abs(data_fft(:,1)),'r');
  figure(2)
 w1 = data_fft(1:length(data_fft)/2);
 w2 = data_fft(length(data_fft)/2:length(data_fft));
%   subplot(211);
  plot(abs(w1(:,1)),'r');     xlabel('w1 [Hz]');
%   ylim([-0.01 0.3])
%       axis([0 info.SampleRate/2 -0.01 0.3])
%   subplot(212); 
%    plot(abs(w2(:,1)),'r');    xlabel('w2 [Hz]');
   axis([0 info.SampleRate/2 -0.00 0.1])
   title(filename);
   
  figure(1)
    ydft = fft(d);
    % I'll assume y has even length
    ydft = ydft(1:length(d)/2+1);
    % create a frequency vector
    freq = 0:fs/length(d):fs/2;
    % plot magnitude
    subplot(211);
    plot(freq,abs(ydft));
%     axis([-5 5 -1.5 1.5])
    % plot phase
    subplot(212);
    plot(freq,unwrap(angle(ydft))); 
    xlabel('Hz');

 pause(0.111);         
%  fprintf('Okno (klatka) nr: %d/%d', i, info.Duration); input('');
%  end

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
freq(1) = 0;
plot(freq,abs(ydft));
% plot phase
subplot(212);
plot(freq,unwrap(angle(ydft))); 
xlabel('Hz');

return;
% below read from csv-------------------------------------------------------------------------
% deprecated %%
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