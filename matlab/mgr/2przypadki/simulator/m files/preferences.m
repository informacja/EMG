function preferences

parentf=gcbf;
userData=get(parentf,'UserData');
simulatormfc=userData.simulatormfc;
preferences=userData.preferences;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Get the screen size
screenSize=get(0,'ScreenSize');
screenHeight=screenSize(4);
screenWidth=screenSize(3);

%figure height and width
figureWidth=475;
figureHeight=300;
backGroundColor=[0.98,0.98,0.98];
%margin
margin=0.01;

%Main figure
f=figure(...
	'Name','Advanced Preferences',...
	'NumberTitle','off',...
	'MenuBar','none',...
	'Units','pix',...
	'Resize','off',...
	'Color',backGroundColor,...
	'defaultaxesxtick', [], ...
	'defaultaxesytick', [], ...
	'defaultuicontrolcallback',@checkValue,...
	'pos',[(screenWidth-figureWidth)/2,(screenHeight-figureHeight)/2,figureWidth,figureHeight]);


figureData= struct(...
	'simulatormfc',simulatormfc,...
	'preferences', preferences);

set(f,'UserData',figureData);

%----------------------------Main Panel ----------------------------------------

panelHeight=0.98;
generalRowHeight=panelHeight/13;
leftPanelMargin=0.05;
editBoxPosX=0.30;
textBoxWidth=0.35;
browseField=0.50;
editBoxWidth=0.35;
checkBoxPosX=0.05;
editBoxStartY=panelHeight+margin;

%%%%%%%%%%%%%%%%%%%%%%%%UICONTROLS%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%----------------------ROW 1--------------------------------------------
editBoxY=2.5*generalRowHeight;
h=uicontrol(...
	'style','text',...
	'String','Tip uptake:',...
	'Units','norm',...
	'BackgroundColor',backGroundColor,...
	'horizontalAlignment','left',...
	'pos',[leftPanelMargin,editBoxStartY-editBoxY-0.25*generalRowHeight,editBoxWidth,generalRowHeight]);
defaultFontName= get(h,'FontName');
defaultFontSize= get(h,'FontSize');

%--------Set default font and Size--------------
set(f,...
	'defaultuicontrolFontName',defaultFontName,...
	'defaultuicontrolFontSize',defaultFontSize);
%---------------------------------------------

uicontrol(...
	'style','edit',...
	'Tag','tipUptakeDistance',...
	'Units','norm',...
	'horizontalAlignment','right',...
	'BackgroundColor',backGroundColor,...
	'UserData',f,...
	'pos',[1-leftPanelMargin-browseField/2,editBoxStartY-editBoxY,browseField/2,generalRowHeight]);



%----------------------ROW 2--------------------------------------------
editBoxY=editBoxY+2.5*generalRowHeight;
uicontrol(...
	'style','text',...
	'String','Cannula uptake:',...
	'Units','norm',...
	'BackgroundColor',backGroundColor,...
	'horizontalAlignment','left',...
	'pos',[leftPanelMargin,editBoxStartY-editBoxY-0.25*generalRowHeight,editBoxWidth,generalRowHeight]);

uicontrol(...
	'style','edit',...
	'Tag','canUptakeDistance',...
	'Units','norm',...
	'horizontalAlignment','right',...
	'BackgroundColor',backGroundColor,...
	'String','',...
	'UserData',f,...
	'pos',[1-leftPanelMargin-browseField/2,editBoxStartY-editBoxY,browseField/2,generalRowHeight]);
%----------------------ROW 3--------------------------------------------
editBoxY=editBoxY+2.5*generalRowHeight;
uicontrol(...
	'style','text',...
	'String','Internal interp factor for jitter:',...
	'Units','norm',...
	'BackgroundColor',backGroundColor,...
	'horizontalAlignment','left',...
	'pos',[leftPanelMargin,editBoxStartY-editBoxY-0.25*generalRowHeight,editBoxWidth,generalRowHeight]);

uicontrol(...
	'style','edit',...
	'Tag','jitterInterpExp',...
	'Units','norm',...
	'horizontalAlignment','right',...
	'BackgroundColor',backGroundColor,...
	'String','',...
	'UserData',f,...
	'pos',[1-leftPanelMargin-browseField/2,editBoxStartY-editBoxY,browseField/2,generalRowHeight]);
%----------------------ROW 4--------------------------------------------
editBoxY=editBoxY+2.5*generalRowHeight;
uicontrol(...
	'style','checkbox',...
	'String','Filter',...
	'Tag','filter_raw_signal',...
	'Units','norm',...
	'BackgroundColor',backGroundColor,...
	'horizontalAlignment','left',...
	'UserData',f,...
	'pos',[leftPanelMargin,editBoxStartY-editBoxY-0.25*generalRowHeight,editBoxWidth,generalRowHeight]);

uicontrol(...
	'style','checkbox',...
	'String','Include all units.',...
	'Tag','allUnits',...
	'Units','norm',...
	'BackgroundColor',backGroundColor,...
	'horizontalAlignment','left',...
	'Value',str2num(preferences.allUnits),...
	'UserData',f,...
	'pos',[1-leftPanelMargin-browseField/2,editBoxStartY-editBoxY-0.25*generalRowHeight,browseField/2,generalRowHeight]);

%----------------------ROW 7--------------------------------------------
editBoxY=editBoxY+2.5*generalRowHeight;

uicontrol(...
	'style','pushButton',...
	'Units','norm',...
	'String','OK',...
	'Callback',@saveChanges,...
	'UserData',parentf,...
	'pos',[leftPanelMargin,editBoxStartY-editBoxY,browseField/2,generalRowHeight]);


uicontrol(...
	'style','pushButton',...
	'Tag','electrode_type',...
	'Units','norm',...
	'String','Cancel',...
	'Callback',@cancel,...
	'UserData',f,...
	'pos',[1-leftPanelMargin-browseField/2,editBoxStartY-editBoxY,browseField/2,generalRowHeight]);
fillIn(f,f);
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%SAVECHANGES
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function saveChanges(src,evnt)
f=gcbf;
updateCFG(f,f);
figureUserData=get(f,'UserData');
simulatormfc=figureUserData.simulatormfc;
parentf=get(gcbo,'UserData');
userData=get(parentf,'UserData');
userData.simulatormfc=simulatormfc;
h=findobj(f,'Tag','allUnits');
if(ishandle(h))
	userData.preferences.allUnits=num2str(get(h,'Value'));
end
set(parentf,'UserData',userData);

delete(f);

%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%FUNCTIONS%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%FILLIN
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function fillIn(f,parentf)

figureUserData=get(parentf,'UserData');
% get the simulatormfc structure
simulatormfc=figureUserData.simulatormfc;
h=findobj(f,'style','edit');
for i=1:length(h)
	field=get(h(i),'Tag');
	if(isfield(simulatormfc,field))
		value=getfield(simulatormfc,field);
		value=value.value;
		set(h(i),'String',value);
	end
end
h=findobj(f,'style','checkbox');
for i=1:length(h)
	field=get(h(i),'Tag');
	if(isfield(simulatormfc,field))
		value=getfield(simulatormfc,field);
		value=str2num(value.value);
		if(~isempty(value))
			set(h(i),'Value',value);
		end
	end
end
h=findobj(f,'style','popupmenu');
for i=1:length(h)
	field=get(h(i),'Tag');
	if(isfield(simulatormfc,field))
		value=getfield(simulatormfc,field);
		value=str2num(value.value);
		if(~isempty(value))
			set(h(i),'Value',value);
		end
	end
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%checkValue
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function checkValue(src,evnt)
simulator=get(gcbo,'UserData');
figureUserData=get(simulator,'UserData');
simulatormfc=figureUserData.simulatormfc;
field=get(gcbo,'Tag');
style=get(gcbo,'style');
if(isfield(simulatormfc,field))
	if(strcmp(style,'edit'))

		fieldStruct=getfield(simulatormfc,field);
		fieldStruct.value=get(gcbo,'String');
		if (isempty(fieldStruct.range))
		elseif(length(fieldStruct.range)<2)
			if(str2num(fieldStruct.value)< fieldStruct.range)
				message=['The value should be greater than ', num2str(fieldStruct.range),' !'];
				h=warndlg(message);
			end
		else
			if((str2num(fieldStruct.value)< fieldStruct.range(1))&(str2num(fieldStruct.value)>fieldStruct.range(2)))
				message=['The value should be between ', num2str(fieldStruct.range(1)),' and ',num2str(fieldStruct.range(2)),' !'];
				h=warndlg(message);
			end

		end


	end
end
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%updateCFG
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function updateCFG(f,parentf)

figureUserData=get(parentf,'UserData');
% get the simulatormfc structure
simulatormfc=figureUserData.simulatormfc;
h=findobj(f,'style','edit');
for i=1:length(h)
	field=get(h(i),'Tag');
	if(isfield(simulatormfc,field))
		value=get(h(i),'String');
		fieldStruct=getfield(simulatormfc,field);
	    fieldStruct.value=value;
	    simulatormfc=setfield(simulatormfc,field,fieldStruct);
		
	end
end
h=findobj(f,'style','checkbox');
for i=1:length(h)
	field=get(h(i),'Tag');
	if(isfield(simulatormfc,field))
		value=get(h(i),'Value');
		fieldStruct=getfield(simulatormfc,field);
	    fieldStruct.value=num2str(value);
	    simulatormfc=setfield(simulatormfc,field,fieldStruct);
		
	end
end
h=findobj(f,'style','popupmenu');
for i=1:length(h)
	field=get(h(i),'Tag');
	if(isfield(simulatormfc,field))
		value=get(h(i),'Value');
		fieldStruct=getfield(simulatormfc,field);
	    fieldStruct.value=num2str(value);
	    simulatormfc=setfield(simulatormfc,field,fieldStruct);
		
	end
end
figureUserData.simulatormfc=simulatormfc;
set(parentf,'UserData',figureUserData);
%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%Cancel
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function cancel(src,evnt)
delete(gcbf);