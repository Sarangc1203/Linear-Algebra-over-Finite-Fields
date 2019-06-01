n:=1;
p:=211;
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
for i in [1,2..p^n-1] do
	for j in [1,2..p^n-1] do
		for k in [1,2..p^n-1] do
			red:=0;
   			A:=[Z(p^n)^i,Z(p^n)^j,Z(p^n)^k];
			if (A[2]^2-4*A[1]*A[3])=0*Z(p^n) then
				red:=1;
			fi;
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
								Print("False\n");
							fi;
						fi;
					fi;
				fi; 
			od; 
    		od;   
	od;
od;
