% Prog 11: filtry cyfrowe FIR (finite impulse response), nierekursywny
%          przesuwnik fazowy Hilberta (-pi/2 rad), f. rï¿½niczkujï¿½cy
clear all; close all;

fpr = 2000;  % cz. prï¿½bkowania [Hz]

[X, fpr] = audioread('oneTwo.wav');
x = X(:, 1); % First chanel only

% Projekt filtra: Hilbetra, Differential
M = 100; N = 2*M+1;
n = -M : 1 : M;
hH = (1 - cos(pi*n)) ./ (pi*n); hH( M+1 ) = 0;
hD = cos( pi*n ) ./ n; hD( M+1 ) = 0;

% M = 100; N = 2*M+1;
% n = -M : 1 : M;
% 
% hH = x; hH( M+1 ) = 0;
% hD
b = hH; 

% ###########
% SPRAWDZENIE
figure
subplot(311); stem( n, b); title('b(n) = h(n)'); grid;   
w = chebwin(N,100)';
subplot(312); stem( n, w); title('w(n)'); grid;   
b = b .* w;
subplot(313); stem( n, b); title('bw(n) = hw(n)'); grid;    
z = roots(b);

% SPRAWDZENIE Z & P
alfa = 0 : 2*pi/1000 : 2*pi;
c = cos(alfa); s = sin( alfa );
figure; plot(real(z),imag(z),'bo',c,s,'k-');
grid; title('Z & P'); 

% H(z) --> H(f)
f = -fpr/2 : (fpr/2)/2001 : fpr/2;
z = exp( -j*2*pi*f/fpr );
H = exp( j*2*pi*f/fpr*M ) .* polyval( b(end:-1:1) , z) ;  % chka czï¿½stotliwoï¿½ciowa
%H = freqz(b,a,f);               %5 to samo
% figure; plot(f,abs(H)); xlabel('f [Hz]'); grid; title('|H(f)|'); pause
% figure; plot(f,20*log10(abs(H))); xlabel('f [Hz]'); grid; title('|H(f)| [dB]'); pause
% figure; semilogx(f,20*log10(abs(H))); xlabel('f [Hz]'); grid; title('|H(f)| [dB]'); pause
% figure; plot(f,angle(H)); xlabel('f [Hz]'); grid; title('angle(H(f)) [rad]'); pause
% figure; plot(f,unwrap(angle(H))); xlabel('f [Hz]'); grid; title('angle((H(f)) [rad]'); pause

% Uï¿½YCIE FILTRA
% SYGNAï¿½
% Nx = 2000; 
% dt = 1/fpr; t = dt*(0:Nx-1);
% AM = 10*(1+0.5*sin(2*pi*1*t));
% fn = 100; df = 50;  FM = sin( 2*pi*2*t );
%   x = AM .* cos( 2*pi*( fn*t + df * cumsum( FM )*dt ) );

Nx = size(x,1); 
dt = 1/fpr; t = dt*(0:Nx-1);
% nie mogê tego zakomentowaæ bo nie widzi w 88 lini
AM = 10*(1+0.5*sin(2*pi*1*t));
fn = 100; df = 50;  FM = sin( 2*pi*2*t );
% x = AM .* cos( 2*pi*( fn*t + df * cumsum( FM )*dt ) );
% x = cos( 2*pi*50*t );
figure;
plot(t,x); xlabel('t [s]'); title('x(t)')

% ZASTOSOWANIE
% y=conv(x,b); y = y(1:Nx);
% y=filter(b,1,x);
Nb = length( b );
bx = zeros( 1, Nb );
for n = 1 : Nx
    bx = [ x(n) bx(1:Nb-1) ];
    y(n) = sum( bx .* b );
end
figure;
subplot(121); plot(x);
subplot(122); plot(y); pause
n = Nx/2+1 : Nx;
f = fpr/(Nx/2)*(0:Nx/2-1);
figure;
subplot(121); plot(f, 20*log10( abs( fft(x(n)) /(Nx/2) ) ) );
subplot(122); plot(f, 20*log10( abs( fft(y(n)) /(Nx/2) ) ) ); 

% Tylko dla filtra Hilberta
x = x( M+1 : Nx-M );
y = y( 2*M+1 : Nx );
AM = AM( M+1 : Nx-M );
FM = FM( M+1 : Nx-M );
t = t( M+1 : Nx-M );

figure
Nwin = 1024;
Nfft = 2048;
k    = 16;

figure; plot( x, y ); title('Okrag?'); pause
figure; plot( t,x,'b-',t,y,'r-'); xlabel('t [s]'); title('x(t), y(t)'); pause

subplot(211), spectrogram(x, Nwin, Nwin - k, Nfft, fpr / 2); title("Raw signal, window = " + num2str(Nwin)); 
subplot(212), spectrogram(y, Nwin, Nwin - k, Nfft, fpr / 2); title("Hilbert filtered signal, window = " + num2str(Nwin)); 
 
return;
%xa = hilbert(x);   % to samo funkcjï¿½ Matlaba
xa = x + j*y;

AMest = abs( xa );

dfi = xa(2:end) .* conj( xa(1:end-1) );
FMest = (1/(2*pi)) * angle(dfi) / dt;  % Fest = fn + df*FM
FMest = (FMest - fn) / df;    % 

figure;
subplot(211); plot(t,AM,'r-',t,AMest,'b-'); title('de-AM'); 
subplot(212); plot(t,FM,'r-',t(2:end),FMest,'b-'); title('de-FM');
pause
