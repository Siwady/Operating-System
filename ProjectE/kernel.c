#define Base2 0xB000
#define Base 0x8000
#define SECTOR_SIZE 512
#define WORD_SIZE 80
#define STORAGE_CAPACITY 16
#define FILENAME_SIZE 6
#define COLUMN_END 80
#define ROW_END 24

void printString(char Word[]);
int readString(char cha[]);
int readStringColor(char cha[],int color);
void pressReturn();
void PrintBorder();
int printStringColor(char Word[],int color);
int readFile(char name[], char buffer[]);
void executeProgram(char fileName[], int segment);
void terminate();
int deleteFile(char name[]);
int writeFile(char name[], char buffer[], int size);
int getSectorsCount(int size);
int getBufferSize(char buffer[]);
void printInt(int integer,int color);
int isTextFile(char buffer[],int size);
void handleTimerInterrupt(int segment, int stack);

void main()
{
	Clr();
		
	//moveCursor(2,2,0);
	//PrintBorder();
	
	makeInterrupt21();
	makeTimerInterrupt();
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

int printStringColor(char Word[],int color)
{
	int i=0;
	int cont=0;
	while(Word[i]!='\0')
	{	
		
		if(getCursorColumn()>79 && getCursorRow()>23)
		{
			nextLine(0);
			cont=0;
		}
		if(Word[i]=='\n')
			nextLine(0);
		else
			printCharC(Word[i],color);

		i++;
		cont++;
		
	}
	
	return cont;
}


int readString(char cha[])
{
	int cont=0;
	char character;		
	
	while(character!=0xd)
	{
		character=readChar();
		if(getCursorColumn()>78 && getCursorRow()>23)
		{
			nextLine(0);
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
	
	return cont;
				
}

int readStringColor(char cha[],int color)
{
	int cont=0;
	char character='\0';		
	char re[2];
	re[0]='\n';
	re[1]='\r';
	while(character!=0xd)
	{
		character=readChar();

		if((getCursorColumn()>78 && getCursorRow()>23) || (getCursorRow()>23 && character==0xd))
		{
			nextLine(0);
		}

		if(character==0x8 && cont>0)
		{
			if(getCursorColumn()==0)
				moveCursorUp();
			printChar(character);
			printChar(0x0);				
			printChar(character);
			cont=cont-1;
			cha[cont]=0x0;
			
				

		}else if(character!=0x8 && character!=0xd)
		{
			if(getCursorColumn()==79)
				nextLine(0);
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

int deleteFile(char name[])
{
	char buff[512];
	int i,j;
	int exist=0;
	char map[512];
	int sector;
	for(i=0;i<512;i++){
		buff[i]=0x0;
		map[i]=0x0;	
	}

	readSector(buff, 2);
	readSector(map,1);
	
	for(i=0;i< 16;i++)
	{
		for(j=0;j<6;j++)
		{
			if(name[j]==buff[(i*32)+j]){		
				exist=1;
			}
			else{
				exist=0;
				break;
			}			
		}
		if(exist==1){
			break;
		}
	}
	
	if(exist==1)
	{	
		if(buff[(i*32)]!='\0')
		{
			buff[(i*32)]='\0';
			
			for(j=6;j<32;j++)
			{
				if(buff[(i*32)+j]!='\0')
				{
					sector=buff[(i*32)+j];
					map[sector]=0x0;
					buff[(i*32)+j]='\0';
				}
			}	
		}
		writeSector(map,1);
		writeSector(buff,2);
		return 1;
	}
	return 0;
}
int writeFile(char name[], char buffer[], int size)
{
	char map[512];
	char dir[512];
	char temp[512];
	int dirIndex,j,sector,k;
	int mapfree=0;
	int dirfree=0;
	
	readSector(map,1);
	readSector(dir,2);

	for(dirIndex=0;dirIndex<16;dirIndex++)
	{
		if(dir[(dirIndex*32)]=='\0')
		{
			dirfree=1;
			break;
		}	
	}
	if(dirfree==1)
	{
		for(j=0;j<6;j++)
		{
			dir[(dirIndex*32)+j]=name[j];
		}
		
		for(j=0;j<getSectorsCount(size);j++)
		{
			for(sector=0;sector<26;sector++)
			{
				if(map[sector]=='\0')
				{
					mapfree=1;
					break;
				}		
			}
			if(mapfree==1 && sector<26)
			{
				map[sector]=0xFF;
				dir[(dirIndex*32)+6+j]=sector;
				for(k=0;k<512;k++)
				{
					temp[k]=buffer[(j*512)+k];          
				}
				writeSector(temp,sector);
			}
			else 
				return -1; //not enough space.
		}
		writeSector(map,1);
		writeSector(dir,2);	
		return 1; //WriteFile Successful
	
	}else
		return 0;  //Dir is full.
}

int getSectorsCount(int size)
{
	int cont=0;
	int Size=size;
	while(Size>0)
	{
		Size=Size-512;
		cont++;
	}
	return cont;
}

int getBufferSize(char buffer[])
{
	int size=0;
	int i=0;
	while(buffer[i]!=0x0)
	{
		i++;
		size++;
	}
	
	return size;
}

void printInt(int integer,int color)
{
	int digits=1;
	while(integer>=digits)
		digits=digits*10;
		
	digits=digits/10;
	while(digits!=1)
	{
		printCharC((integer/digits)+48,color);
		integer=integer-(integer/digits)*digits;
		digits=digits/10;
	}
	printCharC((integer/digits)+48,color);
}

int isTextFile(char buffer[],int size)
{
	int i,j;
	for(i=0;i<size;i++)
	{
		if(buffer[i]==0x0)
		{
			for(j=i+1;j<size;j++)
			{
				if(buffer[j]!=0x0)
					return 0;      // its a program
			}
			break;
		}
	}
	
	return 1;    //its a textfile
}

void handleTimerInterrupt(int segment, int stack)
{
	printString("Tic");
	returnFromTimer(segment,stack);
	restoreDataSegment();
}

void terminate()
{
	char s[6]; s[0]='s'; s[1]='h'; s[2]='e'; s[3]='l'; s[4]='l'; s[5]='\0';
	readChar();
	executeProgram(s,0x2000);
}




