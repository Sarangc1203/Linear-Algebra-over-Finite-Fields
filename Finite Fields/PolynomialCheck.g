n:=1;
p:=2;
S:=[];
F:=GF(p,n);
rd:=0;

P:=[];
x:=X(GF(p^n),"x");;
for e in F do
	if(Order(e)=p^(n)-1) then
       Add(P,e);
    fi;
od;
N:=Size(P);
foundA:=0;
for i in [1,2..p^(n)-1] do
	for j in [1,2..p^(n)-1] do
		for k in [1,2..p^(n)-1] do
			red:=0;
   			A:=[Z(p^n)^i,Z(p^n)^j,Z(p^n)^k];
      		for b in F do
       			if ((A[1]*b^2+A[2]*b+A[3])=0*Z(p)) then
                	red:=1; 
              		break;
            	fi;
            od;
            Count:=0;
            foundP:=0;
            for a in P do
            	Count:=Count+1;
                if(foundP = 0) then
               		if (red = 0) then
                    	if (Order(A[1]*a^2+A[2]*a+A[3])=(p^(n)-1)) then
                        	foundP:=1;
                        else
                        	if (Count=N) then
                            	Print(A);
                           		Print(",");
                           	fi;
                      	fi;
                   	fi;
               	fi; 
         	od; 
    	od;   
	od;
od;
