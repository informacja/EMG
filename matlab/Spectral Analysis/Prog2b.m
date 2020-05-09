% Prog2b.m
close all

figure, ribbon(X); title("Tak reprezetuj¹c dodatkow¹ powierzchni¹ sygna³y, dobrze widaæ kiedy miêsieñ mia³ wysoki potencja³ napiêcia w czasie"); ylabel("Czas"), xlabel("Kana³y")

[X, fpr] = audioread('oneTwo.wav')
x = X(:, 1); % First chanel only

figure, subplot(311), plot(x); title("Raw signal"); xlabel("Time"), ylabel("Voltage")
subplot(312), plot(diff(x),'g');   title("Derivative");
subplot(313), plot(diff(diff(x)), 'b'); title(" Second derivative");

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

figure, Nwin = 2048;
subplot(221), spectrogram(filtsig, Nwin, Nwin - k, Nfft, fpr / 2); title("Filtered 10-500 Hz, window = " + num2str(Nwin)); Nwin = Nwin/2;
subplot(222), spectrogram(filtsig, Nwin, Nwin - k, Nfft, fpr / 2); title("Filtered 10-500 Hz, window = " + num2str(Nwin)); Nwin = Nwin/2;
subplot(223), spectrogram(filtsig, Nwin, Nwin - k, Nfft, fpr / 2); title("Filtered 10-500 Hz, window = " + num2str(Nwin));  Nwin = Nwin/2;
subplot(224), spectrogram(filtsig, Nwin, Nwin - k, Nfft, fpr / 2); title("Filtered 10-500 Hz, window = " + num2str(Nwin))


Signal = x; Windowing = 256; Overlap = Windowing-16; Zeropadding = 0;
% emg_rms = rms_gbiomech(Signal, Windowing, Overlap, Zeropadding);

d = mean(x) - mean(filtsig);
figure, 
subplot(411), plot(x - d); title("Raw / Butter bandpass (10-500 Hz) [Time]"); axis tight; hold on; plot(filtsig); hold off;
subplot(412), W = 64; plot(rms_gbiomech(x, W, W - 16, Zeropadding)); title("RMS window = " + num2str(W)); axis tight;
subplot(413), W = 128; plot(rms_gbiomech(x, W, W - 16, Zeropadding)); title("RMS window = " + num2str(W)); axis tight;
subplot(414), W = 256; plot(rms_gbiomech(x, W, W - 16, Zeropadding)); title("RMS window = " + num2str(W));axis tight;

% soundsc(x, fpr*2);
soundsc(x, fpr);
