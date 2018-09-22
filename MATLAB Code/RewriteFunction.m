function [ BigArray ] = RewriteFunction( H, j, R)

BigArray =[];
[a,b]=size(H);
for r = 1:a
     temp=zeros(1,b);
     m=b;
        newline=zeros(1,R-j);
     for item = 1:j
        for i=1:size(newline)
                    temp(m)=H(r,item);
                    m=m-1;
        end  
     end
   k=1; 
   t=1;
     for l=1:R
         test=temp(t);
          if l>test && t<j 
             t=t+1;
          end  
        if k<=b && ~(temp(1)==0 && temp(2)==0)
         if (l-1)~=test
           newline(k)=l-1;
           k=k+1;
            
             
         end
        else
            
        end
     end
        BigArray=[BigArray;newline];
        
end
