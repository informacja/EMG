% Prog2b.m
close all

[X, fpr] = audioread('one&two.wav')
x = X(:, 1);
plot(x);
% soundsc(x, fpr);
spectrogram(x, 256, 256 - 16, 4096, fpr);
figure, ribbon(X); title("Tak reprezetuj¹c sygna³y, dobrze widaæ kiedy w czasie sygna³ ma du¿e napiêcie")
ylabel("Czas"),xlabel("Kana³y")



% [x,y] = meshgrid(-3:.5:3,-3:.1:3);
% z = peaks(x,y);
% figure;ribbon(y,z)