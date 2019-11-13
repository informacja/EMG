
filename = 'rect/out1.wav';

info = audioinfo(filename)

[data, fs] = audioread(filename,'double');
 
for i = 1:info.Duration
    
 shift = [ info.SampleRate*(i-1)+1, info.SampleRate*i];
 d = data( shift(1) : shift(2))';
 subplot(211); plot(d); title('sygna³');
  plot(abs(w1(:,1)),'r');   
  xlabel(sprintf( 'd - signal [Hz] frame nr %.3i', i) );
 data_fft = fft(d)'/info.SampleRate;                                       % values from 0 to 1 
%    plot(abs(data_fft(:,1)),'r');
%   figure(122)
 w1 = data_fft(1:length(data_fft)/2);
 w2 = data_fft(length(data_fft)/2:length(data_fft));
%   subplot(211);
subplot(212);
  plot(abs(w1(:,1)),'r');   
  xlabel(sprintf( 'w1 [Hz] frame nr %.3i', i) );
  2
%   ylim([-0.01 0.3])
%       axis([0 info.SampleRate/2 -0.01 0.3])
%   subplot(212); 
%    plot(abs(w2(:,1)),'r');    xlabel('w2 [Hz]');
   axis([0 info.SampleRate/2 -0.00 0.1])
   title(filename);
     
   fprintf('Okno (klatka) nr: %d/%d (Enter)', i, info.Duration); input('');
end

 