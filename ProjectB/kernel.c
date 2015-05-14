#define Base2 0xB000
#define Base 0x8000
#define COLUMN 0x2

void printString(char Word[]);
void readString(char cha[]);
void readStringColor(char cha[],int color);
void pressReturn();
void PrintBorder();
void printStringColor(char Word[],int color);


void main()
{
	char buffer[512];
	char word[80];
	
	Clr();	
	changeBackgroundColor(15);
	PrintBorder();	
	
	moveCursor(15,2,0);
	readSector(buffer, 30);
	printString(buffer);

	moveCursor(2,10,0);
	printStringColor("Write a message: ",0x8);
	readStringColor(word,0x6);
	
	pressReturn();
	printStringColor("Your message was: ",0x8);
	printStringColor(word,0x6);
	
	moveCursor(27,20,0);
	printStringColor("Press any key to continue... ",0x88);
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
		if(getCursorColumn()==78)
			moveCursorDown();
		if(Word[i]!='\0')
			printChar(Word[i]);
		else
			i=80;
	}
}

void printStringColor(char Word[],int color)
{
	int i=0;
	for(i=0;i<80;i++)
	{	
		if(getCursorColumn()==78)
			moveCursorDown();
		if(Word[i]!='\0')
			printCharC(Word[i],color);
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
			if(getCursorColumn()==2)
				moveCursorUp();
			printChar(character);
			printChar(0x0);				
			printChar(character);
			cont=cont-1;
			cha[cont]=0x0;
		}else if(cont<=80 && character!=0x8 && character!=0xd)
		{
			if(getCursorColumn()==78)
				moveCursorDown();
			cha[cont]=character;
			printChar(cha[cont]);
			cont++;
		}
	}
	pressReturn();
	
	for(cont=cont+1;cont<80;cont++)
		cha[cont]=0x0;
				
}

void readStringColor(char cha[],int color)
{
	int cont=0;
	char character;		
	
	while(character!=0xd)
	{
		character=readChar();
		
		if(character==0x8 && cont>0)
		{
			if(getCursorColumn()==2)
				moveCursorUp();
			printChar(character);
			printChar(0x0);				
			printChar(character);
			cont=cont-1;
			cha[cont]=0x0;
			
				

		}else if(cont<=80 && character!=0x8 && character!=0xd)
		{
			if(getCursorColumn()==78)
				moveCursorDown();
			cha[cont]=character;
			printCharC(cha[cont],color);
			cont++;
		}
	}
	pressReturn();
	
	for(cont=cont+1;cont<80;cont++)
		cha[cont]=0x0;
				
}


void pressReturn()
{
	moveCursorDown();	
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


