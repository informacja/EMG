function RMS = rms_gbiomech(sinal, janelamento, overlap, zeropad)

% Signal = your Raw Signal preferably treated previously with a pass band of 20 to 500 Hz.
% Windowing = the analysis window size in number of samples.
% Overlap = overlap size in number of samples.
% Zeropadding = fill the difference between the raw signal and the RMS signal with zeros, where value "0" is disabled and value "1" is enabled. The default value is "0".

    delta = janelamento - overlap;

    indices = 1:delta:length(sinal);

    if length(sinal) - indices(end) + 1 < janelamento

        if zeropad
            sinal(end + 1:indices(end) + janelamento - 1) = 0;
        else
            indices = indices(1:find(indices + janelamento - 1 <= length(sinal), 1, 'last'));
        end

    end

    RMS = zeros(1, length(indices));

    sinal = sinal.^2;

    index = 0;

    for i = indices
        index = index + 1;
        RMS(index) = sqrt(mean(sinal(i:i + janelamento - 1)));
    end

end
