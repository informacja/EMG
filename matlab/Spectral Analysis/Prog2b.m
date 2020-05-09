% Prog2b.m
close all

[X, fpr] = audioread('oneTwo.wav')
x = X(:, 1); % First chanel only
figure, subplot(311), plot(x); title("Raw signal"); xlabel("Time"), ylabel("Voltage")
subplot(312), plot(diff(x),'g');   title("Derivative");
subplot(313), plot(diff(diff(x)), 'b'); title(" Second derivative");

figure, subplot(311), plot(rms(x,10)); title("RMS");
subplot(312), plot(diff(rms(x,500)));   title("Derivative");
subplot(313), plot(rms(x,128)); title(" Second derivative");

% soundsc(x, fpr*2);
% soundsc(x, fpr);
% spectrogram(x, 256, 256 - 16, 4096, fpr);'
 
figure
Nwin = 512;
Nfft = 2048;
k    = 16;
subplot(221), spectrogram(x, Nwin, Nwin - k, Nfft, fpr / 2, 'yaxis');
% Nwin = 256;
Nfft = 2048 * 2;
subplot(222), spectrogram(x, Nwin, Nwin - k, Nfft, fpr / 2, 'yaxis');
% Nwin = 512;
Nfft = 2048/2;
subplot(223), spectrogram(x, Nwin, Nwin - k, Nfft, fpr / 2, 'yaxis');
% Nwin = 1024;
Nfft = 2048 * 4;
subplot(224), spectrogram(x, Nwin, Nwin - k, Nfft, fpr / 2, 'yaxis');
%  , pokrycie,
figure, ribbon(X); title("Tak reprezetuj¹c wiêksz¹ powierzchni¹ sygna³y, dobrze widaæ kiedy miêsieñ mia³ wysoki potencja³ napiêcia w czasie"); ylabel("Czas"), xlabel("Kana³y")

% Periodogram ??
% dtmf diff() energia ? LIczymy ca³kê

% [x,y] = meshgrid(-3:.5:3,-3:.1:3);
% z = peaks(x,y);
% figure;ribbon(y,z)
