q1:= [];
R1:= [];
for p in [3,5..301] do
  if (IsPrimeInt(p) = true) then
    K:=[1];
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

index:=1;

for index in [1..Size(q1)] do
	q:=q1[index];
	for n1 in R1[index] do
		# Field F:
		F:=GF(q,n1);

		# Generator of Field:
		g:=Z(q^n1);

		# All possible values of odd unitary d are stored in dlist:
		dlist:=[];
		i:=1;
		while (i<=(q^n1-1)/2) do
			if (q^n1-1) mod i = 0 then
				if (Gcd(i,(q^n1-1)/i)=1) then
					Add(dlist,i);
				fi;
			fi;
			i:=i+2;
		od;

		# Generating the set P:
		P:=[];
		for i in [1..(q^n1-1)] do
			if (Gcd(i,(q^n1-1))=1) then
				Add(P,g^i);
			fi;
		od;

		dlist:=Reversed(dlist);
		flag:=0;

		for d in dlist do

			# Generating the set Ad:
			Ad:=[];
			e:=Product(Union(Factors((q^n1-1)/d),[]));
			for n in [0..e-1] do
				Add(Ad,g^(n*d));
			od;

			# All the factors of d are stored in dfacts: (Union is used to remove redundunt factors)
			dfacts:=Union(Factors(d),[]);
			s:=Size(dfacts);

			# R is the Rp set storing first half Field elements except 0:
			R:=[];
			i:=0;
			for i in [1..s] do
				Add(R,[1..(dfacts[i]-1)/2]);
			od;

			# Generating the values of all possible epsilons and storing it in epsilon:
			epsilon:=[];
			eps:=[-1,1];
			for i in [1..s] do
				Add(epsilon,eps);
			od;
			epsilon:=Cartesian(epsilon);

			# x will store the Xd(epsilon) for all possible epsilons:
			x:=[];

			# Loop for calculating all Xd(epsilon)
			for i in [1..Size(epsilon)] do
				xtemp:=List(Elements(F));

				# epsR is the set epsilon*Rp:
				epsR:=[];

				# Loop for checking x for all dfacts:
				for j in [1..s] do
					temp2:=[];
					Add(epsR,(epsilon[i][j]*R[j]) mod dfacts[j]);
					Add(epsR[j],0);

					# Loop for checking which element of field satisfies the condition:
					for k in [1..(q^n1-1)] do
						if (k mod dfacts[j]) in epsR[j] then
							Add(temp2,(g^k));
						fi;
					od;

					# Intersection as it should lie in all epsilon*Rp for dfacts:
					xtemp:=Intersection(xtemp,temp2);
				od;
				Add(x,xtemp);
			od;

			# Checking if the Union is equal to GF(q^n1) - {0}:
			y:=Union(x);
			Add(y,0*g);
			if IsEqualSet(y,Elements(F)) then
				Print("");
			else
				Print("");
			fi;


			# Loops for finding elements of A forall alpha, beta, xd (:= Xd(delta)), xe (:= Xd(epsilon)):
			for alpha in Ad do
				for beta in Ad do
					flag2:=0;
					flag3:=0;
					for xd in x do
						yrange:=Intersection(P,xd);
						for xe in x do
							flag2:=0;
							# A is used to store the values for first condition in Lemma 5:
							A:=Set([]);
							xrange:=Intersection(P,xe);
							for x1 in xrange do
								for y1 in yrange do
									AddSet(A, (alpha*x1+g^0)^2 - beta*y1);
								od;
							od;
							# Checking if A equal to GF(q^n1) - {0}:
							A:=Union(A,[]);
							Add(A,0*g);
							if IsEqualSet(A,Elements(F)) then
								flag2:=1;
								break;
								Print("");
							else
								Print("");
							fi;
						od;
						flag3:=0;
						# B is used to store the values for second condition in Lemma 5:
						B:=Set([]);
						for x1 in P do
							for y1 in yrange do
								AddSet(B, x1^2 - beta*y1);
							od;
						od;
						# Checking if B equal to GF(q^n1) - {0}:
						B:=Union(B,[]);
						Add(B,0*g);
						if IsEqualSet(B,Elements(F)) then
							flag3:=1;
							Print("");
						else
							Print("");
						fi;
						
						if (flag2=1 and flag3=1) then
							break;
						fi;
					od;
					if (flag2<> 1 or flag3<>1) then
						flag:=1;
						break;
					fi;
				od;
				if (flag=1) then
					break;
				fi;
			od;
			if flag = 0 then
				break;
			fi;
		od;
		if flag = 1 then
			Print(q, "^", n1, "\tException\n");
		else
			Print(q, "^", n1, "\tNot Exception\n");
		fi;
	od;
od;
