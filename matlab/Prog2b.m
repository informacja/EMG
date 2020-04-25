% Prog2b.m

[x, fpr] = audioread('one&two.wav');
x = x(:, 1)
plot(x);
soundsc(x, fpr);
spectrogram(x, 256, 256 - 16, 512, fpr);
