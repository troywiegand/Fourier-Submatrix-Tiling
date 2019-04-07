function [ BigArray ] = RowFunction( JustRemoved,HowMany,R,RowRemoved,H,RemovedArray)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here


if RowRemoved==HowMany

    if 1==1
        %BigArray=RemovedArray ;
        BigArray=[RemovedArray;zeros(1,length(RemovedArray))]
        dlmwrite('allR8a3.txt',RewriteFunction(BigArray,HowMany,R),'-append','delimiter',' ')
        %,'roffset',1
    else
        BigArray=[];  
    end
else
 BigArray=[];   
for j=JustRemoved+1:R-(HowMany-RowRemoved-1)-1
    J=H;
    J(R+1-j,:)=[];
    RemovedArray(2,RowRemoved+1)=R-j;%Start index at zero for output
    BigArray=[BigArray; RowFunction( j,HowMany,R,RowRemoved+1,J,RemovedArray)];
       

end

end
