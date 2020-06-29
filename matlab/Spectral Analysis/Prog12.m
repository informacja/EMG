% Prog. 12 - Digital adaptive filters
clear all; close all;

% Control parameters
itask = 1; % 1/2: 1 = adapt corr cancel, 2 = adapt line/signal enhancement
isig  = 2; % 1/2: 1 = synthetic, 2 = real
idisp = 0; % 0/1 filter display inside adaptation loop

% Signals
if( isig==1 ) % Synthetic signal
  fs = 8000;
  Nx = fs;
  dt = 1/fs; t=dt*(0:Nx-1);
 %s = exp(-50*(t-0.5).^2 ) .* sin(2*pi*(0*t + 0.5*250*t.^2));
 %s = exp(-50*(t-0.5).^2 ) .* sin(2*pi*50*t);
  s = sin(2*pi*50*t);
end 
if( isig==2 ) % Speech
  [s,fs] = audioread('goodbye.wav');
  s=s'; Nx = length(s); dt = 1/fs; t=dt*(0:Nx-1);
end    

c = sin( 2*pi*500*t );  % cross-talk, interference

figure
subplot(211); plot(t,s); xlabel('t [s]'); title('s(n)'); grid;
subplot(212); plot(t,c); xlabel('t [s]'); title('c(n)'); grid; pause

if( itask==1 ) % Scenario #1 - adaptive interference/correlation canceling
  d = s + c;
  x = 0.1 * [ 0 0 c(1:Nx-2)];
end
if( itask==2)  % Scenario #2 - adaptive line/signal enhncement
  d = s + 0.5*randn(1,Nx);
  x = [ 0 d(1:Nx-1)];
end
figure
subplot(211); plot(t,d); xlabel('t [s]'); title('d(n)'); grid;
subplot(212); plot(t,x); xlabel('t [s]'); title('x(n)'); grid; pause

% FIR adaptive filtering
M = 25; mi = 0.05;                % filter length, adapt. speed coeff.
h = zeros(1,M); bx = zeros(1,M);
y = zeros(1,Nx); e = y; hhist = y;
if( idisp==1 ) figure; f = 0 : (fs/2)/1000 : fs/2; end
for n = 1 : Nx
    bx = [ x(n) bx(1:M-1) ];        % input buffer actualization
    y(n) = sum( bx .* h );          % filtering
    e(n) = d(n) - y(n);             % eeror signal
  h = h + mi*e(n)*bx;             % #1 LMS: filter weights adaptation              
%     h = h + mi*e(n)*bx / (bx*bx'+0.00001);  % #2 NLMS: filter weights adaptation
    if( idisp == 1 )
        subplot(211); stem( h ); title('h(m)');
        subplot(212); plot(f,20*log10( abs( freqz(h,1,f,fs)))); xlabel('f [Hz]'); title('|H(f)| [dB]'); pause
    end
    hhist(n) = h(3);
end

% Results presentation

figure 
plot(t,hhist); xlabel('t [s]'); title('hNR(n)'); grid; pause

figure
subplot(211); plot(t,e); xlabel('t [s]'); title('e(n)'); grid;
subplot(212); plot(t,y); xlabel('t [s]'); title('y(n)'); grid; pause

disp('Playing d(n)'); soundsc(d,fs); pause
disp('Playing y(n)'); soundsc(y,fs); pause
disp('Playing e(n)'); soundsc(e,fs); pause