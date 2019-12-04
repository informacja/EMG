clear all;

filename = 'out30.wav'; % first electrode chanel (P0_11) at 2 chanel in waterfall() 
% filename = 'out31.wav';
% filename = 'noConnected.wav';
filename = 'out35.wav'; % test time*4

info = audioinfo(filename)
[data, fs] = audioread(filename);

figure(1); subplot(111); waterfall(data'); xlabel('Time'); ylabel('Channel'); 
% title(filename); axis([1 inf 1 info.NumChannels ]) 
% axis manual %[xmin xmax ymin ymax zmin zmax cmin cmax] — Also set the color limits. cmin is the data value that corresponds to the first color in the colormap. cmax is the data value that corresponds to the last color in the colormap.

figure(2);
for i = 1:info.Duration    
    shift = [ info.SampleRate*(i-1)+1, info.SampleRate*i];
    d = data( shift(1) : shift(2))';
    subplot(111); plot(d); title('Raw signal EMG');
    xlabel(sprintf( 'd - signal frame nr %.3i Time [ms]', i) );
    ylabel('[mV]');
end
