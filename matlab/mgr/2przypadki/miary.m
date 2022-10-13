
filename = "MVA_000.wav";
y = importdata(filename);
plot(v.data)

Fs = v.fs;

% mplitude measurement Average peak-to-peak
% amplitude
% Amplitude after full-wave
% rectification and
% low-pass filtering RMS amplitude
% Integrated electrical activity
% Frequency analysis Power spectrum
% Spike counting No. of spikes
% per time unit

% No. of zero crossings per time unit 

winLength = 4096;
overlap = 512*2;
y = y.data(:,1);
[yB,~] = buffer(y,winLength,overlap,"nodelay");

init = winLength - overlap;
state = 0;
zcr = [];
for i = 1:size(yB,2)
    zcr = [zcr;zerocrossrate(yB(:,i),InitialState=state)];
    state = yB(init,i);
end

figure
yyaxis left
x = 0:1/Fs:(numel(y)-1)/Fs;
plot(x',y)
xlabel("Seconds")
ylabel("Amplitude")
yyaxis right
xx = (1:size(yB,2))*((winLength-overlap)/Fs);
plot(xx',zcr)
ylabel("Zero-crossing rate")

% No. of turns
% per time unit
% Motor unit firing rate Decomposition
% 

% avg = mean(y.data(:,1))
% [aa,count] = zerocrossrate(y.data,Level=avg)
