#define Base2 0xB000
#define Base 0x8000
#define COLUMN_BEGIN 0x2
#define COLUMN_END 78
#define WORD_SIZE 80


void printString(char Word[]);
void readString(char cha[]);
void readStringColor(char cha[],int color);
void pressReturn();
void PrintBorder();
void printStringColor(char Word[],int color);



enum Color {BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHT_GRAY,DARK_GRAY,LIGHT_BLUE,
LIGHT_GREEN,LIGHT_CYAN,LIGHT_RED,LIGHT_MAGENTA,YELLOW,WHITE};

void main()
{
	char buffer[512];
	char word[WORD_SIZE];
	Clr();
	changeBackgroundColor(15);
	PrintBorder();

	moveCursor(30,2,0);
	printStringColor("Welcome to my OS",DARK_GRAY);
	
	moveCursor(2,8,0);
	printStringColor("Write a message: ",DARK_GRAY);
	readStringColor(word,BROWN);
	pressReturn();

	printStringColor("Your message was: ",DARK_GRAY);
	printStringColor(word,BROWN);
	pressReturn();
	pressReturn();

	printStringColor("Reading sector 30 from floppy...",DARK_GRAY);
	pressReturn();
	readSector(buffer, 30);
	printStringColor(buffer,LIGHT_BLUE);

	moveCursor(27,20,0);
	printStringColor("Press any key to continue... ",0x88);
	readChar();

	//Interrupt 21
	Clr();
	PrintBorder();
	makeInterrupt21();
	loadProgram();
}


void printString(char Word[])
{
	int i=0;
	for(i=0;i<WORD_SIZE;i++)
	{	
		if(getCursorColumn()==78)
			moveCursorDown();
		if(Word[i]!='\0')
			printChar(Word[i]);
		else
			i=WORD_SIZE;
	}
}

void printStringColor(char Word[],int color)
{
	int i=0;
	for(i=0;i<WORD_SIZE;i++)
	{	
		if(getCursorColumn()==COLUMN_END)
			moveCursorDown();
		if(Word[i]!='\0')
			printCharC(Word[i],color);
		else
			i=WORD_SIZE;
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
		}else if(cont<=WORD_SIZE && character!=0x8 && character!=0xd)
		{
			if(getCursorColumn()==COLUMN_END)
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
			
				

		}else if(cont<=WORD_SIZE && character!=0x8 && character!=0xd)
		{
			if(getCursorColumn()==COLUMN_END)
				moveCursorDown();
			cha[cont]=character;
			printCharC(cha[cont],color);
			cont++;
		}
	}
	pressReturn();
	
	for(cont=cont+1;cont<WORD_SIZE;cont++)
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
		for(j=0;j<WORD_SIZE*2;j++)
		{
			if(!(j>3 && j<156 && i>0 && i<24))
			{
				putInMemory(Base2, Base+(j)+(i*WORD_SIZE*2), ' ');
				putInMemory(Base2, Base+1+(j)+(i*WORD_SIZE*2), 0x0);
			}
		}
	}	
}





