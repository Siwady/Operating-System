#define Base2 0xB000
#define Base 0x8000

void Clr();
void printString(char* Word);

void main()
{
	
	char* cha;
	int i=0;
	
	
	for(i=0;i<5;i++)
	{
		cha[i]=readChar();
		printChar(cha[i]);
	}

}

void Clr()
{
	int i,j;

	for(i=0;i<17;i++)
	{
		for(j=0;j<160;j++)
		{
			putInMemory(Base2, Base+(j)+(i*80*2), 0x0);
			putInMemory(Base2, Base+1+(j)+(i*80*2), 0x5);
		}
	}
}

void printString(char* Word)
{
	int i=0;
	for(i=0;i<80;i++)
	{
		if(Word[i]=='\0')
			i=80;
		else
			printChar(Word[i]);
	}
}
