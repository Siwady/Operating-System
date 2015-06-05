#define Base2 0xB000
#define Base 0x8000
#define SECTOR_SIZE 512
#define WORD_SIZE 80
#define STORAGE_CAPACITY 16
#define FILENAME_SIZE 6
#define COLUMN_END 80
#define ROW_END 24

void printString(char Word[]);
void readString(char cha[]);
void readStringColor(char cha[],int color);
void pressReturn();
void PrintBorder();
void printStringColor(char Word[],int color);
int readFile(char name[], char buffer[]);
void executeProgram(char fileName[], int segment);
void terminate();

enum Color {BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHT_GRAY,DARK_GRAY,LIGHT_BLUE,
LIGHT_GREEN,LIGHT_CYAN,LIGHT_RED,LIGHT_MAGENTA,YELLOW,WHITE};

void main()
{
	Clr();
	moveCursor(2,2,0);
	PrintBorder();
	makeInterrupt21();
	//loadProgram();
	
	executeProgram("shell",0x2000);
}


void printString(char Word[])
{
	int i=0;
	while(Word[i]!='\0')
	{	
		if(getCursorColumn()>79 && getCursorRow()>23)
		{
			printString("\n\r");
		}
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
	while(Word[i]!='\0')
	{	
		if(getCursorColumn()>79 && getCursorRow()>23)
		{
			nextLine(0);
		}
		if(Word[i]=='\n')
			nextLine(0);
		else
			printCharC(Word[i],color);

		i++;
		
	}
	/*int i=0;
	while(Word[i]!='\0')
	{	
		if(getCursorColumn()>79 && getCursorRow()>23)
		{
			nextLine(0);
		}
		
		if(Word[i]=='\n'){
			nextLine(0);		
		}else
			printCharC(Word[i],color);
	}*/
}


void readString(char cha[])
{
	int cont=0;
	char character;		
	
	while(character!=0xd)
	{
		character=readChar();
		if(getCursorColumn()>79 && getCursorRow()>23)
		{
			printString("\n\r");
		}
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
				printString("\n\r");
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
	char re[2];
	re[0]='\n';
	re[1]='\r';
	while(character!=0xd)
	{
		character=readChar();

		/*if((getCursorColumn()>79 && getCursorRow()>23) || (getCursorRow()>23 && character==0xd) )
		{
			printString(re);
			
		}*/

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
				printString("\n\r");
			cha[cont]=character;
			printCharC(cha[cont],color);
			cont++;
		}
	}
	//printString(re);
	nextLine();
	moveCursor(0,getCursorRow(),0);
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


int readFile(char* name, char* buffer)
{
	char buff[512];
	char temp[512];
	int i,j,k,c,l,x;
	int exist=0;
	int cont=0;

	readSector(buff, 2);
	
	
	for(i=0;i< 16;i++)
	{
		for(j=0;j<6;j++)
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
				
				for(c=0;c<512;c++)
				{
					buffer[(cont*512)+c]=temp[c];	
				}				
				cont++;
			}
		}
		return 1;
	}else
	{
		for(l=0;l<13312;l++)
			buffer[l]=0x0;
		return 0;
	}
	
	
}

void executeProgram(char fileName[], int segment)
{
	char buffer [13312];

	if(segment!=0x1000 && segment!=0x0000 && segment<0xA000) //o  segment<0xA000 && 
	{
		if(readFile(fileName,buffer)==1)
		{
			putInSegment(buffer,segment,13312);
	
			launchProgram(segment);
		}
	}
}

void terminate()
{
	char s[6];
	s[0]='s';
	s[1]='h';
	s[2]='e';
	s[3]='l';
	s[4]='l';
	s[5]='\0';
	readChar();
	
	executeProgram(s,0x2000);
}




