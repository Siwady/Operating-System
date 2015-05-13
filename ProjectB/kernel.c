#define Base2 0xB000
#define Base 0x8000

void Clr();
void printString(char Word[]);
void readString(char cha[]);
void pressReturn();
void PrintBorder();
void delay(int delay);

void main()
{
	char buffer[512];
	char word[80];
	changePage(2);
	
	moveCursor(0,2,2);
	readSector(buffer, 30);
	printString(buffer);

	moveCursor(5,10,2);
	printString("Write a message: ");
	readString(word);
	moveCursor(5,11,2);
	printString("Your message was: ");
	printString(word);

	delay(20000);

	changePage(3);
	makeInterrupt21();
	loadProgram();

	

}

void delay(int delay)
{
	int i;
	for(i=0;i<delay;i++)
	{
		
	}
}


void Clr()
{
	int i,j;

	for(i=0;i<17;i++)
	{
		for(j=0;j<160;j++)
		{
			putInMemory(Base2, Base+(j)+(i*160), 0x0);
			putInMemory(Base2, Base+1+(j)+(i*160), 0x0);
		}
	}
}

void printString(char Word[])
{
	int i=0;
	for(i=0;i<80;i++)
	{	
		if(Word[i]!='\0')
			printChar(Word[i]);
		else
			i=80;
	}
}

void readString(char cha[])
{
	int cont=0;
	char character;		
	
	while(character!=0xd)
	{
		character=readChar();
		
		if(character==0x8 && cont>0)
		{
			printChar(character);
			printChar(0x0);
			printChar(character);
			cont=cont-1;
			cha[cont]=0x0;
		}else if(cont<=80 && character!=0x8 && character!=0xd)
		{
			cha[cont]=character;
			printChar(cha[cont]);
			cont++;
		}
	}
	pressReturn();
	
	for(cont=cont+1;cont<80;cont++)
		cha[cont]=0x0;
				
}

void pressReturn()
{
	int i;
	printChar('\n');
	for(i=0;i<80;i++)
	{
		printChar(0x8);	
	} 
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


