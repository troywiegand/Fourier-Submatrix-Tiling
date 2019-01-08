

R=22;
F=zeros(R);

for j=1:R
    for k=1:R
        F(j,k)=exp(((2*pi*1i)/R)*(j-1)*(k-1));
    end
end

for j=11
    
    fileID = fopen('R22a11.txt','a');
    
    something=R-j
    
    fprintf(fileID, '%d' ,something);
    fprintf(fileID, ' \n');
    H=ColFunction( 0,j,R,0,F,zeros(2,j) )
    NumberOfCombos=size (H,1)/3
    Q=RewriteFunction( H, j, R)
    
    fprintf(fileID, 'VICTORY!! \n\n');
    
end

