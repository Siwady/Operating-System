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


void readFile(char* name, char* buffer)
{
	char buff[512];
	char temp[512];
	char temp1[2];
	int i,j,k,c;
	int exist=0;
	int cont=0;
	
	
	readSector(buff, 2);
	
	
	for(i=0;i< 16;i++)
	{
		printString(temp1);
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
				printString(name);
				//fillBuffer(&buffer,(cont*512),temp);
				for(c=0;c<512;c++)
				{
					buffer[(cont*512)+c]=temp[c];	
				}				
				//buffer[cont*512]=temp;
				cont++;
			}
		}
	}
	
}

void executeProgram(char fileName[], int segment)
{
	char buffer [13312];

	if(segment!=0x1000 && segment!=0x0000) //o  segment<0xA000 && 
	{
		readFile(fileName,buffer);
	
		putInSegment(buffer,segment,13312);
	
		launchProgram(segment);
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




