#define Base2 0xB000
#define Base 0x8000

void Clr();

void main()
{
	//Clear Console
	Clr();
	printChar('H');
	printChar('O');
	printChar('L');
	printChar('A');
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
