# Compiler_Bhaskara_Analyzer

C Program that analyzes and calculate expressions with addition, subtraction, multiplication, division, sign change and square root.

Grammar: 
<pre>
E -> T E1		{E1.h = Tptr} E1 {Eptr = E1.s}
E1 -> + T E2	{E2.h = geranodo('+',E1h,Tptr)} E2 {E1.s = E2.s}
E1 -> - T E2	{E2.h = geranodo('-',E1h,Tptr)} E2 {E1.s = E2.s}
E1 -> vazio		{E1s = E1h}

T -> F {T1.h = Fptr} T1 {Tptr = T1s}
T1 -> * F {T2.h = geranodo('*',T1h,Fptr)} T2 {T1.s = T2.s}
T1 -> / F {T2.h = geranodo('/',T1h,Fptr)} T2 {T1.s = T2.s}
T1 -> vazio		{T1s = T1h}

F -> ( E ) {Fptr = Eptr}
F -> raiz(E) {Fptr = geranodo('raiz', Eptr, 1);
F -> - F {Fptr = geranodo(*,-1,F1ptr)}
F -> id {gerafolha}
F -> num {gerafolha}

</pre>
