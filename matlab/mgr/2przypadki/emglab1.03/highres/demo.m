%DEMO  High-resolution toolbox.% This is a stand alone program that demonstrates the functions in the% High Resolution toolbox.  Read the comments in the m-file for an% explanation.% Copyright (c) 2006-2009. Kevin C. McGill and others.% Part of EMGlab version 1.0.% This work is licensed under the Aladdin free public license.% For copying permissions see license.txt.% email: emglab@emglab.net% Here are four templates:clear xx(:,1) = [-0.1;1.2;1.6;3.7;2.9;1.7;6.1;8;3.7;-1;-2.9;-3.1;-3.3;0.8;...-0.8;-0.6;-1.8;2.3;-0.5;-0.2;-2.5;-4.4;-13.3;-22.4;-40.8;-49.5;-79;...-42.3;32.4;71.5;98.4;82.1;59.1;16.6;-0;-7.6;-7.5;-11.8;-12.8;-14.4;...-15.2;-12.3;-8.5;-8.3;-6.7;-7.9;-5;-1.7;1.2;-0.9;-0.1;-0.1;0.8;0.9;0.9];x(:,2) = [0.2;-0.7;-1.3;-0.8;-3.3;-5.8;-12.5;-20.7;-18.1;-2.3;4.6;...14.2;17.9;16.9;15.6;11.5;8.7;9.5;9.7;10.4;7.8;5.2;1.4;0.3;-17.6;-54;...-83.6;-113;-44.9;57.5;101;64.2;22.4;20;35;35.4;21.1;1.7;-9.1;-10.9;...-11.5;-10.4;-12.2;-9.6;-9;-8.1;-6.8;-6;-5.9;-4.3;-4.5;-2.1;-1;-0.1;-0.7];x(:,3) = [-0.4;0.3;-0.4;-0.4;-2.6;-5.4;-8.8;-1.6;7.3;10;6.1;0.4;1.2;...0.7;0.5;2.8;2.6;2.3;-1.9;0.6;0.4;6;7.4;11.5;9.4;9.4;-7.5;-55.3;-145;...-44;53.7;27.5;34;29.4;32;24.6;16.7;7.6;4.6;1.2;2.8;-2.7;-4;-5.9;-3.2;...-4.6;-3.6;-4.3;-2.6;-4.9;-3.6;-2.6;-1.2;-1.7;2];x(:,4) = [-5.7;-9.1;-17.6;-27.2;-11.6;12.7;19.1;18.8;19.5;9.4;9;9.5;...9;8.2;2.3;-5.4;-5.1;-2.8;-4.2;-8.9;-10.3;-10.5;-12.7;-4.1;3.3;2.7;-28.3;...-79.9;-98.1;45.6;137;89.6;31.9;12.2;6.7;-3.7;-5.4;-6.6;-7.5;-10.1;-9.1;...-10.6;-7.1;-6.5;-6.6;-4.7;-4.1;-3.2;-2.5;-2.6;-1.1;-1;0.1;-1;-0.6];x = [zeros(20,4); x; zeros(25,4)];subplot (3,2,1);plot (x);title ('Four templates')% Use RTP and IRTP to convert back and forth from the time domain% to real trigonometric polynomials.  Use HR_SHIFT to time-shift % signals in the RTP domain. xp = rtp (x);	% TRP representations of the templates.xps = hr_shift (xp, [-30, -10, 10, 30]);	% Spread them outsubplot (3,2,2);plot (irtp(xps, 5)); 		% Plot them, interpolating by 5.title ('Spread out and interpolated');% Simulate an occurrence of unit 4 that is out of alignment with% the template by a fraction of a sampling interval. xp4 = xp(:,4);			% template 4.d0 = rand - 0.5;		% Pick a random occurrence time in [-.5, .5].n = 2*randn(size(xp4));	% White gaussian noise.		yp4 = shift (xp4, d0)+n;	% yp4 is a shifted, noisy version of template 4.subplot (3,2,3);plot (irtp([xp4, yp4, xp4-yp4])); % Plot waveform, template, differencetitle ('Time-quantization error');% Use rptALIGN to align the template to the waveform.[b,d] = hr_align (xp4, yp4);	% Estimate the occurrence time. disp ('Time-quantization.');disp ('    actual   estimated');disp([d0, d]);			% Print the actual and estimate times.XP4 = shift(xp4, d);		% Shift the template into alignment.subplot (3,2,4);plot (irtp([yp4, XP4, yp4-XP4]));	% Plot waveform, aligned template, difference.title ('Optimal alignment')% Simulate a superimposition of all four units.d0 = rand (4,1) * 20 - 10; 	% Pick random occurrence times for the units.n = 2*randn(size(xp4));	% White gaussian noise.yp = comp(xp,d0)+n;	% xd is a noisy sum of the shifted templates.subplot (3,2,5);plot (irtp(yp));title ('Superimposition');% Use RESOLVE to find the optimal alignment.d = resolve (yp, xp);	% Estimate the occurrence times.disp ('Superimposition.');disp ('    actual   estimated');disp([d0, d]);			% Print the actual and estimated times.XP = comp(xp,d);		% Compute the reconstruction.subplot (3,2,6);plot (irtp([yp, XP, yp-XP]));	% Plot waveform, reconstruction, difference.title ('Optimal Resolution');