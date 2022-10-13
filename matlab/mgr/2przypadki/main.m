% run("EMG-Feature-Extraction-Toolbox-master/jfemg('zc', X, opts)")
addpath("EMG-Feature-Extraction-Toolbox-master")

X = audioread("MVA_000.wav");

opts.thres = 0.01; % 100mV
opts.plot = false;
f1 = jfemg('zc', X, opts); 
% figure, plot(X)
featNameShort = {
'fzc'     % jNewZeroCrossing
'ewl'     % EnhancedWaveLength;
'emav'    % EnhancedMeanAbsoluteValue;    
'asm'     % AbsoluteValueOfTheSummationOfExpRoot;
'ass'     % AbsoluteValueOfTheSummationOfSquareRoot;
'msr'     % MeanValueOfTheSquareRoot;
'ltkeo'   % LogTeagerKaiserEnergyOperator; 
'lcov'    % LogCoefficientOfVariation;
'card'    % Cardinality;   
'ldasdv'  % LogDifferenceAbsoluteStandardDeviationValue;
'ldamv'   % LogDifferenceAbsoluteMeanValue;
'dvarv'   % DifferenceVarianceValue;   
'mfl'     % MaximumFractalLength; 
'myop'    % MyopulsePercentageRate; 
'ssi'     % SimpleSquareIntegral;
'vo'      % VOrder; 
'tm'      % TemporalMoment; 
'aac'     % AverageAmplitudeChange;
'mmav'    % ModifiedMeanAbsoluteValue;
'mmav2'   % ModifiedMeanAbsoluteValue2;     
'iemg'    % IntegratedEMG;
'dasdv'   % DifferenceAbsoluteStandardDeviationValue;
'damv'    % DifferenceAbsoluteMeanValue;
'rms'     % RootMeanSquare; 
'vare'    % VarianceOfEMG; 
'wa'      % WillisonAmplitude; 
'ld'      % LogDetector;
'ar'      % AutoRegressiveModel;
'mav'     % MeanAbsoluteValue;
'zc'      % ZeroCrossing; 
'ssc'     % SlopeSignChange; 
'wl'      % WaveformLength;
'mad'     % MeanAbsoluteDeviation;
'iqr'     % InterquartileRange;       
'kurt'    % Kurtosis;
'skew'    % Skewness; 
'cov'     % CoefficientOfVariation;
'sd'      % StandardDeviation;
'var'     % Variance; 
'ae'      % AverageEnergy;
};

jFeat = [];
opts.thres = 0.01;
opts.plot = false;
% opts.order = 1;
for (i = 1:length(featNameShort))
    featNameShort{i}
    tmp = jfemg(featNameShort{i}, X, opts); 
    jFeat = [jFeat tmp];
end

plot(imag(jFeat))
