%[1993]-"A New Strategy for Multifunction Myoelectric Control" (3)

function ZC = jZeroCrossing(X,opts)
% Parameter
thres = 0.01;    % threshold

if isfield(opts,'thres'), thres = opts.thres; end

N  = length(X); if(opts.plot) figure, plot(X); end
ZC = 0;
for k = 1 : N - 1
  if ((X(k) > 0  &&  X(k+1) < 0)  ||  (X(k) < 0  &&  X(k+1) > 0)) ...
      && (abs(X(k) - X(k+1)) >= thres)
    
    ZC = ZC + 1;
    if(opts.plot) hold on; plot(k,X(k),'r*'); end
  end
end
end

