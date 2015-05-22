#define Base2 0xB000
#define Base 0x8000
#define SECTOR_SIZE 512
#define WORD_SIZE 80
#define STORAGE_CAPACITY 16
#define FILENAME_SIZE 6
#define COLUMN_END 78


void printString(char Word[]);
void readString(char cha[]);
void readStringColor(char cha[],int color);
void pressReturn();
void PrintBorder();
void printStringColor(char Word[],int color);
void readFile(char name[], char buffer[]);
void fillBuffer(char buf[],int begin);


enum Color {BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHT_GRAY,DARK_GRAY,LIGHT_BLUE,
LIGHT_GREEN,LIGHT_CYAN,LIGHT_RED,LIGHT_MAGENTA,YELLOW,WHITE};

void main()
{
	//char buffer[512];
	char word[WORD_SIZE];
	char buffer [13312];
	//char Screen[2124];
			
	Clr();
	moveCursor(2,2,0);
	readFile("ccc.c",buffer);
	printString(buffer);
	ScrollDown();
	/*changeBackgroundColor(15);
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
	Clr();*/
	PrintBorder();
	//makeInterrupt21();
	//loadProgram();
}


void printString(char Word[])
{
	int i=0;
	while(Word[i]!='\0')
	{	
		if(Word[i]=='\n')
			pressReturn();
		else
			printChar(Word[i]);

		i++;
		
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


void readFile(char name[], char buffer[])
{
	char buff[512];
	char temp[512];
	int i,j,k;
	int exist=0;
	int cont=0;
	
	readSector(buff, 2);
	//printString(name);
	
	for(i=0;i< STORAGE_CAPACITY;i++)
	{
		for(j=0;j<FILENAME_SIZE;j++)
		{
			if(name[j]==buff[(i*32)+j])
				exist=1;
			else{
				exist=0;
				break;
			}			
		}
		if(exist==1)
			break;
	}
	
	if(exist==1)
	{
		for(j=6;j<32;j++)
		{
			if(buff[(i*32)+j]!='\0')
			{
				readSector(temp,buff[(i*32)+j]);
				//printString(temp);
				fillBuffer(&buffer,(cont*512),temp);				
				//buffer[cont*512]=temp;
				cont++;
			}
		}
	}
	
}

void fillBuffer(char buf_des[],int begin,char buf_ori[])
{
	int i;
	for(i=0;i<SECTOR_SIZE;i++)
	{
		buf_des[begin+i]=buf_ori[i];	
	}
}




