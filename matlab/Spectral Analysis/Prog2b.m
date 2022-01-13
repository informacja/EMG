% Prog2b.m
close all


[X, fpr] = audioread('oneTwo.wav');
x = X(:, 1); % First chanel only
figure, ribbon(X); title("Tak reprezetuj¹c dodatkow¹ powierzchni¹ sygna³y, dobrze widaæ kiedy miêsieñ mia³ wysoki potencja³ napiêcia w czasie"); ylabel("Czas"), xlabel("Kana³y")

figure, subplot(311), plot(x); title("Raw signal"); xlabel("Time"), ylabel("Voltage")
subplot(312), plot(diff(x),'g');   title("Derivative");
subplot(313), plot(diff(diff(x)), 'b'); title(" Second derivative");

if(1) % for book
  figure; plot(x,'b-'); xlabel('t [s]'); title('x(t)'); axis([-2,2,-0.25,1.25]); grid;
  FigType=2; MyFigFile='DFT_time_RectPulse';    % FigType = 1=long, 2=short
  figPW;
  figure; plot(X,'b-'); xlabel('f [Hz]'); title('X(f)'); grid;
  FigType=2; MyFigFile='DFT_freq_RectPulse';    % FigType = 1=long, 2=short
  figPW;
end

fcutlow = 10; %low cut frequency in Hz
fcuthigh = 500; %high cut frequency in Hz
[b, a] = butter(2, [fcutlow, fcuthigh] / (fpr / 2), 'bandpass');
filtsig = filter(b, a, x); %filtered signal

figure
Nwin = 2048;
Nfft = 2048;
k    = 16;
subplot(221), spectrogram(x, Nwin, Nwin - k, Nfft, fpr / 2); title("Raw signal, window = " + num2str(Nwin)); Nwin = Nwin/2;
subplot(222), spectrogram(x, Nwin, Nwin - k, Nfft, fpr / 2); title("Raw signal, window = " + num2str(Nwin)); Nwin = Nwin/2;
subplot(223), spectrogram(x, Nwin, Nwin - k, Nfft, fpr / 2); title("Raw signal, window = " + num2str(Nwin)); Nwin = Nwin/2;
subplot(224), spectrogram(x, Nwin, Nwin - k, Nfft, fpr / 2); title("Raw signal, window = " + num2str(Nwin));
 figPW;
figure, Nwin = 2048;
subplot(221), spectrogram(filtsig, Nwin, Nwin - k, Nfft, fpr / 2); title("Filtered 10-500 Hz, window = " + num2str(Nwin)); Nwin = Nwin/2;
subplot(222), spectrogram(filtsig, Nwin, Nwin - k, Nfft, fpr / 2); title("Filtered 10-500 Hz, window = " + num2str(Nwin)); Nwin = Nwin/2;
subplot(223), spectrogram(filtsig, Nwin, Nwin - k, Nfft, fpr / 2); title("Filtered 10-500 Hz, window = " + num2str(Nwin));  Nwin = Nwin/2;
subplot(224), spectrogram(filtsig, Nwin, Nwin - k, Nfft, fpr / 2); title("Filtered 10-500 Hz, window = " + num2str(Nwin))
 figPW;

Signal = x; Windowing = 256; Overlap = Windowing-16; Zeropadding = 0;
% emg_rms = rms_gbiomech(Signal, Windowing, Overlap, Zeropadding);
 

d = mean(x) - mean(filtsig);
figure, 
subplot(411), plot(x - d); title("Raw / Butter bandpass (10-500 Hz) [Time]"); axis tight; hold on; plot(filtsig); hold off;
subplot(412), W = 64; plot(rms_gbiomech(x, W, W - 16, Zeropadding)); title("RMS window = " + num2str(W)); axis tight;
subplot(413), W = 128; plot(rms_gbiomech(x, W, W - 16, Zeropadding)); title("RMS window = " + num2str(W)); axis tight;
subplot(414), W = 256; plot(rms_gbiomech(x, W, W - 16, Zeropadding)); title("RMS window = " + num2str(W));axis tight;
 figPW;
% soundsc(x, fpr*2);
soundsc(x, fpr);
