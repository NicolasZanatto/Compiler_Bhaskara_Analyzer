#include <stdio.h>
#include <stdlib.h>
#include <math.h>

char expression[30]="(-b+r(b*b-4*a*c))/(2*a)";
int pos=0;

typedef struct tnodo {char tipo; 
	struct tnodo *fesq; 
	struct tnodo *fdir;
	int val;} tnodo; // tipo: 'I':identificador  
//       'C':constante

tnodo *gerafolha(char tipo, int val)
{
	tnodo *naux=(tnodo *)malloc(sizeof(tnodo));
	naux->val=val;
	naux->tipo=tipo;
	return naux; 
}

tnodo *geranodo(char tipo, tnodo *nesq, tnodo *ndir)
{
	tnodo *naux=(tnodo *)malloc(sizeof(tnodo));
	naux->tipo=tipo;
	naux->fesq=nesq;
	naux->fdir=ndir;
	return naux;
}

int F(tnodo **Fptr);

int T1(tnodo **T1s, tnodo *T1h);

int E1(tnodo **E1s, tnodo *E1h);

int T(tnodo **Tptr);

void Desaloca(tnodo *Raiz)
{
	if (Raiz->tipo=='C') free(Raiz);
	else
	{
		Desaloca(Raiz->fesq);
		Desaloca(Raiz->fdir);
	}
}

int E(tnodo **Eptr)
{
	tnodo *E1s,*E1h,*Tptr;
	if (T(&Tptr))
	{
		E1h=Tptr;
		if (E1(&E1s, E1h))
		{
			*Eptr=E1s;
			return 1;
		}
	}
	return 0;
}       

int E1(tnodo **E1s, tnodo *E1h)
{
	tnodo *Tptr,*E2h,*E2s;
	if (expression[pos]=='+')
	{
		pos++;
		if (T(&Tptr))
		{
			E2h=geranodo('+',E1h,Tptr);
			if (E1(&E2s,E2h))
			{
				*E1s=E2s;
				return 1;
			}
			else 
			{
				Desaloca(E2s);
				return 0;
			}
		}
		else return 0;
	}
	else if (expression[pos]=='-')
	{
		pos++;
		if (T(&Tptr))
		{
			E2h=geranodo('-',E1h,Tptr);
			if (E1(&E2s,E2h))
			{
				*E1s=E2s;
				return 1;
			}
			else 
			{
				Desaloca(E2s);
				return 0;
			}
		}
		else return 0;
	}
	
	else
	{
		*E1s=E1h;
		return 1;
	}    
}

int T(tnodo **Tptr)
{
	tnodo *T1s,*T1h,*Fptr;
	if (F(&Fptr))
	{
		T1h=Fptr;
		if (T1(&T1s, T1h))
		{
			*Tptr=T1s;
			return 1;
		}
	}
	return 0;
}     

int T1(tnodo **T1s, tnodo *T1h)
{
	tnodo *Fptr,*T2h,*T2s;
	if (expression[pos]=='*')
	{
		pos++;
		if (F(&Fptr))
		{
			T2h=geranodo('*',T1h,Fptr);
			if (T1(&T2s,T2h))
			{
				*T1s=T2s;
				return 1;
			}
			else 
			{
				Desaloca(T2s);
				return 0;
			}
		}
		else return 0;
	}
	else if (expression[pos]=='/')
	{
		pos++;
		if (F(&Fptr))
		{
			T2h=geranodo('/',T1h,Fptr);
			if (T1(&T2s,T2h))
			{
				*T1s=T2s;
				return 1;
			}
			else 
			{
				Desaloca(T2s);
				return 0;
			}
		}
		else return 0;
	}
	
	else
	{
		*T1s=T1h;
		return 1;
	}    
}

int F(tnodo **Fptr)
{
	tnodo *Eptr;
	if (expression[pos]=='(')
	{
		pos++;
		if (E(&Eptr))
		if (expression[pos]==')')
		{
			pos++;
			*Fptr=Eptr;
			return 1;
		}
		else return 0;
		else return 0;
	}
	else if (expression[pos]>='a' && expression[pos]<='z' && expression[pos] != 'r')
	{
		char id=expression[pos];
		int val = 0;
		
		switch(id){
			case 'a':
				val = 4;
				break;
			case 'b':
				val = 2;
				break;
			case 'c':
				val = -6;
				break;
		}
		
		pos++;
		*Fptr=gerafolha('I',val);
		return 1;
	}
	else if (expression[pos]>='0' && expression[pos]<='9')
	{
		int val=expression[pos]-'0';
		pos++;
		*Fptr=gerafolha('C',val);
		return 1;
	}
	else if(expression[pos] == '-'){
		tnodo *F1ptr, *sinalNodo;
		pos++;
		if (F(&F1ptr)){
			sinalNodo =gerafolha('C', -1);
			*Fptr = geranodo('*',sinalNodo, F1ptr);
			return 1;
		}
		else return 0;
	}
	else if(expression[pos] == 'r'){
		tnodo *Eptr, *nodoAuxiliar;
		pos++;
		if (expression[pos]=='(')
		{
			pos++;
			if (E(&Eptr)){
				if (expression[pos]==')')
				{
					pos++;
					nodoAuxiliar =gerafolha('C', 1);
					*Fptr = geranodo('R',Eptr, nodoAuxiliar);
					return 1;
				}
				else return 0;
			}
			else return 0;
		}	
	}
	else return 0;
}        

int avalia(tnodo *Eraiz)
{
	if (Eraiz->tipo=='C') return Eraiz->val;
	if (Eraiz->tipo=='I') return Eraiz->val;
	if (Eraiz->tipo=='+') return avalia(Eraiz->fesq)+avalia(Eraiz->fdir);
	if (Eraiz->tipo=='-') return avalia(Eraiz->fesq)-avalia(Eraiz->fdir);
	if (Eraiz->tipo=='*') return avalia(Eraiz->fesq)*avalia(Eraiz->fdir);
	if (Eraiz->tipo=='/') return avalia(Eraiz->fesq)/avalia(Eraiz->fdir);
	if (Eraiz->tipo=='R') return sqrt(avalia(Eraiz->fesq));
}

int main()
{
	//scanf("%s",expression);
	tnodo *Eraiz;
	if (E(&Eraiz))
	printf("O valor e %d\n",avalia(Eraiz));
	else printf("Erro!!!! pos=%d\n",pos);
	system("pause");
}
