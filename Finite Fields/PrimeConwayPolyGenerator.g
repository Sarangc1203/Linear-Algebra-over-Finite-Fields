OutputLogTo("otp");
for n in [2..8] do
	Print(n,"\n\n");
	for p in Primes do
		if p^n <= 10000 then
			if p <> 2 then
				Print(p," ",n,"\n");
				Print(ConwayPolynomial(p,n),"\n");
			fi;
		else
			break;
		fi;
	od;
	Print("\n");
od;