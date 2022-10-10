
% function [outputArg1,outputArg2] = (saveAs, OverwrieProtection)
function figPW(nrPliku, nrKol, ext, katalog, wariantNazw, FigsTZ, FigType)
% figPW(nrPliku = 1, nrKol=1, ext='png', katalog='figury/', wariantNazw=1, FigsTZ=1, FigType=1)
% figPW(1, 1, 'png', 'figury', 1, 1,3)
if(nargin==1) fprintf('%s\n%s', "figPW(nrPliku = 1, nrKol=1, ext='png', katalog='figury/', wariantNazw=1, FigsTZ=1)","figPW(1, 1, 'png', 'figury/', 1, 1, 3)" ); end;  
% if (exist('FigsTZ','var'))
%     FigsTZ = 1; 
%     nrPliku = get(gcf,'Number');
%     nrKol = get(gcf,'Tag');
% end;
if(nargin<6) FigsTZ=0; end;  
if(nargin<5) wariantNazw=1; end;
if(nargin<4 || nargin == 1 ) katalog='figury/'; end; if ~exist(katalog, 'dir') mkdir (katalog); end;
if(nargin<3) ext ='fig'; end;
    
    if(nargin<2) % jeœli jeden parametr    
        if(nargin == 1 && isstr(nrPliku)) 
            fTitle = nrPliku; % string parametr
        else fTitle = '_'; end% do zapisywanej nazwy pliku
        nrName = get( get(gcf,'Number'), 'Name' );
        if(nargin > 1 && nrPliku < 0 )
            h1=get(gca,'title');
            title=get(h1,'string');
            if( isempty(title) )
                title( datestr(now,'yyyy-mm-dd HH.MM.ss') ); % default timestamp title
                title=get(h1,'string');
            else
                fTitle = ['_' title '_' ];
            end
        end
    % title([{'Dziedzina czasu'},{'Cha-ka skokowa'}]);  
    % xlabel('Oœ rzeczywista'); ylabel('Oœ urojona'); 
    % legend(str{:}); 
        [path, filename, Fext] = fileparts( mfilename('.')); [~, folderName] = fileparts(pwd()); if(nargin == 1) folderName = katalog; nrName=''; end;                     % nazwa TEGO *.m-pliku
        print( strcat(folderName, fTitle, nrName, num2str(get(gcf,'Number')), '.png'),'-dpng', '-r300'); % Zapisz jako tenMPlik_nrOstatniejFigury.png 
        fprintf("\t*%s\n", strcat("Zapisano: ", folderName, fTitle, nrName, num2str(get(gcf,'Number')), '.png'));
        return % jeœli bez parametrów
    end 

h=gcf;
set(h,'PaperOrientation','Landscape');
%set(h,'Units','centimeters');
%set(h,'OuterPosition',[1, 1, 29 21]);
% set(h,'Position',2*get(h,'Position'));

if(wariantNazw==1) % PIG
    filename=sprintf('%sFig_P%dK%d',katalog,nrPliku,nrKol);
end;

if(wariantNazw==2) % 2017
    % tutaj nrPliku jest nazwa
    filename=sprintf('%sFig_%sK%d',katalog,nrPliku,nrKol);
end;
% fn = nextname(filename, int2str(nrKol), "") to do
saveas(h,filename,ext);
saveas(h,filename,'png'); 
fprintf(1,'\n\t*Zapisano rysunek "%s.%s +.png"',filename,ext);

%             zapiszFig(nrPliku, nrKol, 'fig');
%             zapiszFig(nrPliku, nrKol, 'pdf');
%             zapiszFig(nrPliku, nrKol, 'emf'); %!
%             zapiszFig(nrPliku, nrKol, 'eps');
%             zapiszFig(nrPliku, nrKol, 'tif');
%             zapiszFig(nrPliku, nrKol, 'pcx');
%             zapiszFig(nrPliku, nrKol, 'jpg');
%             zapiszFig(nrPliku, nrKol, 'pbm');
%             zapiszFig(nrPliku, nrKol, 'pgm');
%             zapiszFig(nrPliku, nrKol, 'png');
%             zapiszFig(nrPliku, nrKol, 'ppm');

% Figure Pretty & Write
%  if(narg  < 1)
%      saveAs
%  end 

%EXAMPLE USE
%[y, x, t] = impulse(licz, mian);
%figure(2), plot(t, y); 
%MyFigFile = '1impulse'; FigsTZ;
%function FigsTZ( FigType, MyFigFile, h )
 if(FigsTZ)
    if( ~exist('FigType', 'var') ) FigType = 1; end;
    LineWidth = 0.75;  % by³o 0.5
    GridAlpha = 0.75;  % procentowo
    %LineStyle=['-'];
    MarkerSize = 3;
    FontSizeTitle = 9;
    FontSizeLabels = 9;
    FontSizeTicks = 8;
    FontSizeLegend = 8;%FontSizeLegend = 16;
    Resolution = 1200;           % 150, 300, 600, 1200
    
    FigX0 = 2; FigY0 = 2;        % (left,down) corner of the window
    FigWidthShort = 5.75;        % window X size (in centimeters) - all = fig + text
    FigWidthLong = 2*5.75;       % window X size (in centimeters) - all = fig + text
    FigHeight = 4.25;            % window Y size 4.25
    PosFigLong  = [.18/2 .2 .89  .690];   % Dell  % PosFigLong  = [.095 .20 .87  .68];   % Asus
    %PosFigShort = [.175  .2 .775 .690];   % Dell  % [.175  .2 .775 .725];   % Dell PosFigShort = [.195 .205 .775 .68];  % Asus
     PosFigShort = [.175  .195 .775 .690];   % Dell  % [.175  .2 .775 .725];   % Dell PosFigShort = [.195 .205 .775 .68];  % Asus
    %PosFigShort = [.15   .2 .775 .690];   % Dell  % [.175  .2 .775 .725];   % Dell PosFigShort = [.195 .205 .775 .68];  % Asus
    font = 'Times'; % 'Times';
    if( FigType==1 ) % 1 long figure
       FigWidth = FigWidthLong; PosFig = PosFigLong; 
    end
    if( FigType==2 ) % 2 short figures, side by side
       FigWidth = FigWidthShort; PosFig = PosFigShort; 
    end
    if( FigType==3 ) % 2 as is on monitor
       set(gcf,'Units','centimeters')
       PosFig = get(gcf,'Position'); FigWidth = PosFig(3);
%        set(gcf,'Units','normalized'); PosFig = get(gcf,'Position');;
%        FigWidth = FigWidthLong; PosFig = PosFigLong*2; 
       PosFig = get(gca,'Position');
    end
%     figure('Units','centimeters',...
    %'Position',[FigX0 FigY0 FigWidth FigHeight],...
    %'PaperPositionMode','auto');
    
    set(0,'defaultLineLineWidth', LineWidth);         % set the default line width to lw
    set(0,'defaultLineMarkerSize',MarkerSize);        % set the default line marker size to msz
    %set(0,'defaultLineStyle',LineStyle);             % set default line style
    set(0,'DefaultFigurePaperPositionMode','auto');   % automatyczna wielkoœæ rysunku
    %set(0,'DefaultAxesColorOrder',[0,0,0]);           % czarna linia
    
    %set(h,'markers',MarkerSize);
    
    %set(0,...
    %'LineStyle',LineStyle,...
    %'LineWidth',LineWidth,...
    %'MarkerSize',MarkerSize);
    
    set(gcf,'DefaultLineLineWidth',LineWidth);             % gruboœæ linii wykresów
    %set(gcf,'DefaultMarkerSize',MarkerSize);                % wielkoœæ markera                    
    set(gcf,'Units','centimeters');                        % jednostka wymiarowania okna
    set(gcf,'Position', [FigX0 FigY0 FigWidth FigHeight]); % wymiary okna: (x,y,dx,dy), (x,y)- lewy dolny
    set(gcf,'PaperPositionMode','auto');
%     PosFig = get(gcf,'Position');
    %set(gca,'Units','centimeters'); %JB
    set(gca,...                   % axis features
     'Units','normalized',...
     'LineWidth',LineWidth,...
     'GridLineStyle',':', ...
     'GridAlpha',GridAlpha, ...
     'Position',PosFig,...   % (left,bottom) (width,hight) - relative, inside the window
     'FontUnits','points',...
     'FontWeight','normal',...
     'FontSize',FontSizeTicks,...
     'FontName',font);
    set(get(gca,'Xlabel'),...
      'FontUnits','points',...
      'FontWeight','normal',...
      'FontSize',FontSizeLabels,...
      'Interpreter','tex',...
      'FontName',font);
    set(get(gca,'Ylabel'),...
      'FontUnits','points',...
      'FontWeight','normal',...
      'FontSize',FontSizeLabels,...
      'Interpreter','tex',...
      'FontName',font);
    set(get(gca,'Title'),...
      'FontUnits','points',...
      'FontWeight','normal',...
      'FontSize',FontSizeTitle,...
      'Interpreter','tex',...
      'FontName',font);
    set(get(gca,'Legend'),...
      'FontUnits','points',...
      'FontSize',FontSizeLegend,...
      'Interpreter','tex',...
      'Location','NorthEast',...
      'FontName',font);
    % Legenda
    child = get( gcf, 'Children' );
    for i = 1:length( child )
        tag = get( child(i), 'Tag' );
        if( 1 == strcmp( tag, 'legend' ) )
            set( child(i),'FontSize',FontSizeLegend,'LineWidth',LineWidth);
            break;
        end
    end
    % MyFigFile = fn
    print( strcat(filename,'.png'),'-dpng', '-r600');
    % print( strcat(MyFigFile,'.eps'),'-depsc', '-r600');
 end
end


 function [name,val] = nextname(bnm,sfx,ext,otp) %#ok<*ISMAT>
% Return the next unused filename, incrementing a numbered suffix if required.
%
% (c) 2017-2021 Stephen Cobeldick
%
%% Examples %%
%
%%% Current directory contains files 'A1.m', 'A2.m', and 'A4.m':
%
% >> nextname('A','1','.m')
% ans = 'A3.m'
%
% >> nextname('A','001','.m')
% ans = 'A003.m'
%
%%% Subdirectory 'HTML' contains folders 'B(1)', 'B(2)', and 'B(4)':
%
% >> nextname('HTML\B','(1)','')
% ans = 'B(3)'
%
% >> nextname('HTML\B','(001)','')
% ans = 'B(003)'
%
% >> nextname('HTML\B','(1)','',false) % default = name only.
% ans = 'B(3)'
% >> nextname('HTML\B','(1)','',true) % prepend same path as the input name.
% ans = 'HTML\B(3)'
%
%% Inputs and Outputs %%
%
%%% Input Arguments (**==default):
% bnm = CharVector or StringScalar giving the base filename or folder name,
%       with an absolute or relative file path if required.
% sfx = CharVector or StringScalar of the suffix to append, contains exactly
%       one integer number (use leading zeros to specify the number of digits).
% ext = CharVector or StringScalar of the file extension, if any. For folder
%       names or files without extensions use ''.
% otp = LogicalScalar, true/false** -> output with same path as input name / name only. 
%
%% Input Wrangling %%
%
bnm = nn1s2c(bnm);
sfx = nn1s2c(sfx);
ext = nn1s2c(ext);
%
msg = 'Input <%s> must be a 1xN char vector or a scalar string.';
assert(ischar(bnm)&&ndims(bnm)==2&&size(bnm,1)==1,'SC.nextname:bnm:NotText',msg,'bnm')
assert(ischar(sfx)&&ndims(sfx)==2&&size(sfx,1)==1,'SC:nextname:sfx:NotText',msg,'sfx')
assert(ischar(ext)&&ndims(ext)==2&&size(ext,1)<=1,'SC:nextname:ext:NotText',msg,'ext')
%
tkn = regexp(sfx,'\d+','match');
val = sscanf(sprintf(' %s',tkn{:}),'%lu'); % faster than STR2DOUBLE.
assert(numel(val)==1,'SC:nextname:sfx:NotOneInteger',...
	'The suffix must contain exactly one integer value (any number of digits).')
wid = numel(tkn{1});
%
%% Get Existing File / Folder Names %%
%
[inpth,fnm,tmp] = fileparts(bnm);
fnm = [fnm,tmp];
%
% Find files/subfolders on that path:
raw = dir(fullfile(inpth,[fnm,regexprep(sfx,'\d+','*'),ext]));
%
% Special case of exactly one matching subfolder (Octave):
if ~all(strncmp({raw.name},fnm,numel(fnm)))
	raw = dir(fullfile(inpth,'*'));
end
%
% Generate regular expression:
rgx = regexprep(regexptranslate('escape',sfx),'\d+','(\\d+)');
rgx = ['^',regexptranslate('escape',fnm),rgx,regexptranslate('escape',ext),'$'];
%
% Extract numbers from names:
tkn = regexpi({raw.name},rgx,'tokens','once');
tkn = [tkn{:}];
%
%% Identify First Unused Name %%
%
if numel(tkn)
	% For speed these values must be converted before the WHILE loop:
	vec = sscanf(sprintf(' %s',tkn{:}),'%lu');  % faster than STR2DOUBLE.
	%
	% Find the first unused name, starting from the provided value:
	while any(val==vec)
		val = val+1;
	end
end
%
name = [fnm,regexprep(sfx,'\d+',sprintf('%0*u',wid,val)),ext];
%
if nargin>3
    assert(islogical(otp)&&isscalar(otp),'SC:nextname:otp:NotLogicalScalar',...
		'Input <otp> must be a scalar logical (i.e. true or false).')
    if otp
        name = fullfile(inpth,name);
    end
end
%
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%nextname
function arr = nn1s2c(arr)
% If scalar string then extract the character vector, otherwise data is unchanged.
if isa(arr,'string') && isscalar(arr)
	arr = arr{1};
end
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%nn1s2c

%% make new figure with one subplot of from old fig
% nFig = 6;
% for i=14
%     figure(nFig); ncol = i;
%     subplot(4,4,ncol);
%     ax1=gca;
%     
%     figure;
%     tcl=tiledlayout(1,1);
%     ax1.Parent=tcl;
%     ax1.Layout.Tile=1;
% %     ax1.XLabel = tcl.XLabel      
% %     ax1.YLabel = tcl.YLabel
%     
%     figPW(nFig, ncol, 'png', 'figury/', 1, 1, 3)
% end