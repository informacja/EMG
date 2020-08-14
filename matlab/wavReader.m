clear all;

filename =  'incrementUint16_t.wav'; % W aplikacji nagrywającej zapisywałem inkrementuącą się zmienną, sam nie wiem jak to zinterpretowć :)
filename =  'noConnected.wav'; % Elektroda nie jest podpięta do płytki LPC 1347 widać szum z ADC
filename =  'one&two.wav'; % 2 elektrody podpięte do prawej i lewej dłoni, zaciskanych naprzemiennie, 3-ci kanał ma przesłuchy (amplituda jest niesymetryczna)
% filename = "M:\Elektryczne Gitary & Kuba Sienkiewicz-Antologia\8-Nie Jestem Z Miasta - 1997\2-Wlosy.mp3"
info = audioinfo(filename)

[data, fs] = audioread(filename);

figure(1); subplot(111); waterfall(data'); xlabel('Time [ms]'); ylabel('Channel nr'); zlabel('Amplitude [mV]'); title(filename);
set(gca,  'ytick', [1:info.NumChannels]);
% axis([0 info.TotalSamples 1 info.NumChannels]) % change displayed resolution
% axis([1 inf 1 info.NumChannels ]) % axis manual %[xmin xmax ymin ymax zmin zmax cmin cmax] � Also set the color limits. cmin is the data value that corresponds to the first color in the colormap. cmax is the data value that corresponds to the last color in the colormap.

figure(2);
w = hanning(info.SampleRate)'; 

for i = 1:info.Duration
    shift = [info.SampleRate * (i - 1) + 1, info.SampleRate * i]; % k
    d = data(shift(1):shift(2))';
    subplot(111); plot(d); title('Raw signal EMG');
    xlabel(sprintf( 'Time [ms]\nsignal frame nr %.3i/%.3d ', i, info.Duration)); ylabel('Amplitude [mV]');

    if( 1 ) % show fft() windowed part of signal
        d = d .* w; 
        X = fft(d) / info.SampleRate; %% Dlaczego taka normalizacja, a nie dzielenie przez N ?? code from PSD
        X = 2*fft(d) / sum(w); %% Dlaczego taka normalizacja, a nie dzielenie przez N ?? code from PSD
        f0 = 1 / info.SampleRate; % 1 sekunda / 2048 próbek
        f = f0 * (0:info.SampleRate - 1);
        k = 1:info.SampleRate / 2 + 1;
        % f = f0 * (0:N - 1);
        % f = 0:1:info.SampleRate / 2;
        % plot(f(shift), 20 * log10(abs(X(shift))), 'b.-');
        plot(f(k), 20 * log10(abs(X(k))), 'g'); %% TO DO ERROR in log10 -> k
        % axis([0 info.SampleRate/2 -0.00 max(d)])
        pause(0.00000000000001);
        fprintf('Okno (klatka) nr: %d/%d (Enter)', i, info.Duration); input('');
    end
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
