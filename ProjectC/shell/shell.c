
int getToken(char string[], char file[]);
void executeToken(int token,char file[]);
void PrintCommands();
void ls(char character);

void main()
{
	int token;
	char str[80];
	char file[6];
	syscall_Clr();
	PrintCommands();
	while(1==1)
	{
		syscall_printStringColor("shell ->$ ",0xA);
		syscall_readStringColor(str,15);
		token=getToken(str,&file);
		executeToken(token,file);
	}
	
}


int getToken(char string[], char file[])
{
	int i=0;
	int j=0;
	int token=-1;
	while(string[i]==' ')
		i++;
	
	if(string[i]=='c' && string[i+1]=='l'&& string[i+2]=='e'&& string[i+3]=='a'&& string[i+4]=='r'){
		i+=5;
		token=0;	
	}else if(string[i]=='t' && string[i+1]=='y'&& string[i+2]=='p'&& string[i+3]=='e'){
		i+=4;
		token=1;
	}else if(string[i]=='e' && string[i+1]=='x'&& string[i+2]=='e'&& string[i+3]=='c'&& string[i+4]=='u' &&
		 string[i+5]=='t'&& string[i+6]=='e'){
		i+=7;
		token=2;
	}else if(string[i]=='h' && string[i+1]=='e'&& string[i+2]=='l'&& string[i+3]=='p'){
		i+=4;
		token=3;
	}else if(string[i]=='l' && string[i+1]=='s'){
		i+=2;
		token=4;
	}
	
	while(string[i]==' ')
		i++;
	
	for(j=0;j<6;j++)
	{
		file[j]=string[i];
		i++;
	}		
		
	
	return token;	
}


void executeToken(int token,char file[])
{	
	char buffer[13312];
	switch(token)
	{
		case -1: syscall_printStringColor("Invalid Command.",14);
			break;
		case 0: syscall_Clr();
			break;
		
		case 1: syscall_readFile(file,buffer);
			syscall_printString(buffer);
			break;
		
		case 2:	syscall_executeProgram(file,0x3000);
			break;

		case 3:	PrintCommands();
			break;
		
		case 4:	ls(file[0]);
			break;
	}
}
void ls(char character)
{
	char buff[512];
	char fil[112];
	int i,j,k;
	int cont=0;
	
	for(k=0;k<112;k++)
		fil[i]='\0';
	
	syscall_readSector(buff, 2);
	
	for(i=0;i< 16;i++)
	{
		if(character!=0)
		{
			if(buff[(i*32)]==character)
			{
				for(j=0;j<6;j++)
				{
					if(buff[(i*32)+j]!='\0')
						syscall_printCharColor(buff[(i*32)+j],0xE);		
					
				}
				syscall_printString("\n\r");
				cont++;
			}
		}else
		{
			if(buff[(i*32)]!=0)
			{
				for(j=0;j<6;j++)
				{	
					syscall_printCharColor(buff[(i*32)+j],0x3);	
				}	
				syscall_printString("\n\r");
				cont++;
			}
		}
	}
}

void PrintCommands()
{
	syscall_printStringColor("List of Commands...",0xE);
	syscall_nextLine();
	syscall_printStringColor("--------------------------------------------------------------------------------",0x1);
	syscall_nextLine();

	syscall_printStringColor("clear          ",0x3);	
	syscall_printStringColor("| ",0x1);
	syscall_printStringColor("clear the shell            ",0x7);	
	syscall_nextLine();

	syscall_printStringColor("type ",0x3);
	syscall_printStringColor("(file)    ",0x8);
	syscall_printStringColor("| ",0x1);
	syscall_printStringColor("print the text of the file ",0x7);
	syscall_nextLine();	

	syscall_printStringColor("execute ",0x3);
	syscall_printStringColor("(file) ",0x8);
	syscall_printStringColor("| ",0x1);
	syscall_printStringColor("execute a program          ",0x7);
	syscall_nextLine();	

	syscall_printStringColor("ls ",0x3);
	syscall_printStringColor("(character) ",0x8);
	syscall_printStringColor("| ",0x1);
	syscall_printStringColor("show the list of files that start with (character) or all.",0x7);
	syscall_nextLine();
	syscall_printStringColor("--------------------------------------------------------------------------------",0x1);
	syscall_nextLine();	
}

