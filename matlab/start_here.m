clear all;
filename = 'Mario62/out1.wav';
filename = 'Mario62/out2.wav';
filename = '../matlab/generated/out27.wav';

info = audioinfo(filename)

[data, fs] = audioread(filename,'float');
 
for i = 1:info.Duration
    
 shift = [ info.SampleRate*(i-1)+1, info.SampleRate*i];
 d = data( shift(1) : shift(2))';
 subplot(211); plot(d); title('Sygna³');
 xlabel(sprintf( 'd - signal frame nr %.3i [t]', i) );
 
 subplot(212);
 data_fft = fft(d)'/info.SampleRate;                                       % values from 0 to 1 
 plot(abs(data_fft(:,1)),'r');
 w1 = data_fft(1:length(data_fft)/2);                                      % half of symetric spectrum
% w2 = data_fft(length(data_fft)/2:length(data_fft));

 plot(abs(w1(:,1)),'r'); title(filename);  
 xlabel(sprintf( 'w1 - frame nr %.3i/%i [Hz]', i, info.Duration) );
  
%  ylim([-0.01 0.3])
%  axis([0 info.SampleRate/2 -0.01 0.3])

 tab = []; 
 m1 = w1(2:length(w1));
 tab = [ tab abs(max(m1)) ]; 
 axis([0 info.SampleRate/2 -0.00 max(tab)])
      pause(0.00000000000001);
%    fprintf('Okno (klatka) nr: %d/%d (Enter)', i, info.Duration); input('');
end

 