#define Base2 0xB000
#define Base 0x8000

void PrintBorder();
void Clr();
void PrintMessage(char* Word,int Size);

void main()
{
	char* Word="Hello World";
	int Size=11;
	
	//Clear Console
	Clr();
	
	//border
	PrintBorder();

	//print Hello World 
	PrintMessage(Word,Size);

	while(1==1)
	{}
	
}

void PrintBorder()
{
	int i,j;
	
	for(i=0;i<30;i++)
	{
		for(j=0;j<160;j++)
		{
			if(!(j>3 && j<156 && i>0 && i<24))
			{
				putInMemory(Base2, Base+(j)+(i*80*2), '*');
				putInMemory(Base2, Base+1+(j)+(i*80*2), 0x42);
			}
		}
	}	
}

void Clr()
{
	int i,j;

	for(i=0;i<80;i++)
	{
		for(j=0;j<160;j++)
		{
			putInMemory(Base2, Base+(j)+(i*80*2), 0x0);
			putInMemory(Base2, Base+1+(j)+(i*80*2), 0x5);
		}
	}
}

void PrintMessage(char* Word,int Size)
{
	int i,w;
	int base=Base;
	int PosY=0x0;

	for(i=0;i<16;i++)
	{
		PosY=(((i+4)*80)*2)+70; // +6  es normal
		for(w=0;w<Size;w++)
		{
			putInMemory(Base2, base+PosY, Word[w]);
			putInMemory(Base2, base+1+PosY, i+128); //+128  es para que parpadee.
			
			base+=2;
		}
		base-=Size*2;
	}	
}


