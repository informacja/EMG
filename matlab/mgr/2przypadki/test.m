filename = "MVA_000.wav";
v = audioread(filename);
zci = @(v) find(diff(sign(v)));
zeros = zci(v);
figure(1), plot(v), hold on
plot(zeros, 1, '*r')
zerNaSekunde = length(zeros)/audioinfo(filename).Duration

% test Matlab Windows
newData1 = importdata('MVA_000.vma');
figure(2), plot(newData1.data)
fs = newData1.fs