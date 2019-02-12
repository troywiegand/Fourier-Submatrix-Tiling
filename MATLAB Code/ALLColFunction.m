function [ BigArray ] = ALLColFunction( JustRemoved,HowMany,R,ColRemoved,H,RemovedArray )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here


if ColRemoved==HowMany

    BigArray=ALLRowFunction( 0,HowMany,R,0,H,RemovedArray );
    
    
else
    
    %Might screw up here 
    BigArray=[];
    
    for j=JustRemoved+1:R-(HowMany-ColRemoved-1)-1
        J=H;
        J(:,R+1-j)=[];
      RemovedArray(1,ColRemoved+1)=R-j;%Start index at zero for output
      BigArray=[BigArray;ALLColFunction( j,HowMany,R,ColRemoved+1,J,RemovedArray )];
    
    end

end
        
end

