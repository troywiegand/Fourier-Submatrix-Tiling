

R=10;
F=zeros(R);

for j=1:R
    for k=1:R
        F(j,k)=exp(((2*pi*1i)/R)*(j-1)*(k-1));
    end
end

for j=ceil(R/2)
    
    H=ColFunction( 0,j,R,0,F,zeros(2,j) )
    NumberOfCombos=size (H,1)/3
    Q=RewriteFunction( H, j, R);
    
end

