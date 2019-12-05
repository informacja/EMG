clear all;

filename = 'incrementUint16_t.wav'; 
filename = 'one&two.wav';
filename = 'out56.wav';

info = audioinfo(filename)
[data, fs] = audioread(filename);

figure(1); subplot(111); waterfall(data'); xlabel('Time [ms]'); ylabel('Channel nr'); zlabel('Amplitude [mV]'); title(filename); 
set(gca,'ytick',[1:info.NumChannels]); 
% axis([0 info.TotalSamples 1 info.NumChannels]) % change displayed resolution
% axis([1 inf 1 info.NumChannels ]) % axis manual %[xmin xmax ymin ymax zmin zmax cmin cmax] — Also set the color limits. cmin is the data value that corresponds to the first color in the colormap. cmax is the data value that corresponds to the last color in the colormap.

figure(2);
for i = 1:info.Duration    
    shift = [ info.SampleRate*(i-1)+1, info.SampleRate*i];
    d = data( shift(1) : shift(2))';
    subplot(111); plot(d); title('Raw signal EMG');
    xlabel(sprintf( 'Time [ms]\nsignal frame nr %.3i/%.3d ', i, info.Duration) ); ylabel('Amplitude [mV]');
       
%  tab = []; 
%  m1 = w1(2:length(w1));
%  tab = [ tab abs(max(m1)) ]; 
%  axis([0 info.SampleRate/2 -0.00 max(tab)])
%      pause(0.00000000000001);
%    fprintf('Okno (klatka) nr: %d/%d (Enter)', i, info.Duration); input('');
end
% 
% load handel.mat
% 
% filename = 'handel.wav';
% audiowrite(filename,y,Fs);
% clear y Fs
% 
% [y,Fs] = audioread(filename);
%   audiowrite(FILENAME,Y,FS,Name1,Value1,Name2,Value2, ...) 
%     Specifies optional comma-separated pairs of Name,Value arguments, 
%     where Name is the argument name and Value is the corresponding value. 
%     Name must appear inside single quotes (' '). You can specify several 
%     name and value pair arguments in any order as Name1,Value1,...,NameN,
%     ValueN.  Valid Name,Value arguments are as follows:
%  
%     'BitsPerSample' 