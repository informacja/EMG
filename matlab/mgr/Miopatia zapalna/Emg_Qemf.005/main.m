[y fs] = audioread("MVA_000.mp3");
[z fs] = audioread("MVA_000.wav");

figure(1)
subplot(211);plot(y);
subplot(212);plot(z);
isequal(y,z)

figure(2)
% diff(y,z)
% codegen writeAudio -args {readfilename,writefilename}
readfilename = coder.typeof('a',[1 500],[0 1]);
writefilename = coder.typeof('b',[1 500],[0 1])

/Applications/ffmpeg -i "/Users/puler/Documents/GitHub/EMG/matlab/mgr/Miopatia zapalna/Emg_Qemf.005/MVA_000.wav" -acodec libmp3lame -ab 256k 001.mp
