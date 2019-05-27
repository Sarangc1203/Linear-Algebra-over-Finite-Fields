OutputLogTo("otp");
q1:= [];;
R1:= [];;
for p in [3, 5..19] do
  if (IsPrimeInt(p) = true) then
    K:=[1,2..20];
    B:=[0];;
    for k in K do
      D:=DivisorsInt(p^k-1);
      P:=PrimeDivisors(p^k-1);
      counts:=0;
      for l in D do 
        d:=1;
        count:=0;
        for m in P do 
          if ((l mod m =0) = false) then
            d:=d-2/m;
            count:=count+1;
          fi;
        od;
        if (d > 0) then
          dlt:=((2*count-1)/d)+2;
          e:=PrimeDivisors(l);
          f:=Size(e);
          if (p^Float(k/2) > Float(dlt)*Float(2*2^f*(2^f-Float(3/2))+(3*2^f)/(2*p^Float(k/2)))+1+ (3*2^f)/(2*p^Float(k/2)) and counts =0) then 
            del:=Float(dlt);
            UniteSet(B, [k]); 
            counts:=1;
          fi;
        fi;
      od;
    od;
    R:=K;;
    SubtractSet(R, B);
    if Size(R) > 0 then
      Add(q1,p);
      Add(R1,R);
    fi;
  fi;
od;

index:=1;;

for index in [1..Size(q1)] do
	q:=q1[index];
	for n1 in R1[index] do
    Print(q," ",n1,"\n");
    Print(ConwayPolynomial(q,n1));
    Print("\n");
  od;
od;
