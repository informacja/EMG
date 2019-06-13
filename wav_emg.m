% [Y, FS]=audioread(FILENAME, [START END], DATATYPE);
function [x] = wav_emg(filename)

filename = 'jon.wav';
% filename = 'out.wav';

[Y, FS]=audioread(filename)

end