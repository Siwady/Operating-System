#define Base2 0xB000
#define Base 0x8000
#define COLUMN 0x5

void printString(char Word[]);
void readString(char cha[]);
void pressReturn();
void PrintBorder();


void main()
{
	char buffer[512];
	char word[80];
	
	Clr();	
	PrintBorder();	
	
	moveCursor(15,2,0);
	readSector(buffer, 30);
	printString(buffer);

	moveCursor(COLUMN,10,0);
	printString("Write a message: ");
	readString(word);
	
	moveCursor(COLUMN,11,0);
	printString("Your message was: ");
	printString(word);
	
	moveCursor(COLUMN,13,0);
	printString("Press any key to continue... ");
	readChar();
	
	Clr();
	PrintBorder();	
	makeInterrupt21();
	loadProgram();

	

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
			printChar(0x0);				//printCharC  con color
			printChar(character);
			cont=cont-1;
			cha[cont]=0x0;
		}else if(cont<=80 && character!=0x8 && character!=0xd)
		{
			cha[cont]=character;
			printCharC(cha[cont]);
			cont++;
		}
	}
	pressReturn();
	
	for(cont=cont+1;cont<80;cont++)
		cha[cont]=0x0;
				
}

void pressReturn()
{
	printChar('\n');
	printChar('\r');	
	
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
				putInMemory(Base2, Base+(j)+(i*80*2), ' ');
				putInMemory(Base2, Base+1+(j)+(i*80*2), 0x0);
			}
		}
	}	
}


