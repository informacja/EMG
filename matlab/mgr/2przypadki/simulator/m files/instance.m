function instanceArr=instance(arr)
countArr=ones(1,max(arr));
instanceArr=zeros(1,length(arr));
for i=1:length(arr)
	instanceArr(i)=countArr(arr(i));
	countArr(arr(i))=countArr(arr(i))+1;
end


