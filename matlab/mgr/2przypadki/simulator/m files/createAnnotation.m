function ann = createAnnotation(ann)
% time: 
% unit: 
% uncertainty:
% chan: 

%get the maximum unit number 
maximumUnit=max(ann.unit);

%unit unigue numbers
uniqueUnits=unique(ann.unit);

%initialize index array
indexArray=zeros(1,maximumUnit);

%tempIndex Array
tempIndexArray=[1:length(uniqueUnits)];
indexArray(uniqueUnits)=tempIndexArray(tempIndexArray);

ann.unit=indexArray(ann.unit);






