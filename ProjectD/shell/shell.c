
int getToken(char string[], char file[]);
void executeToken(int token,char file[]);
void PrintCommands();
void ls(char character);

void main()
{
	int token;
	char str[80];
	char file[6];
	int i;
	syscall_Clr();
	PrintCommands();
	while(1==1)
	{	
		for(i=0;i<80;i++)
			str[i]=0x0;
		for(i=0;i<6;i++)
			file[i]=0x0;
		syscall_printStringColor("shell ->$ ",0xA);
		syscall_readStringColor(str,15);
		if(str[0]!=0xd){
			token=getToken(str,&file);
			executeToken(token,file);
		}
	}
}


int getToken(char string[], char file[])
{
	int i=0;
	int j=0;
	int token=-2;
	while(string[i]==' ')
		i++;
	
	if(string[i]=='c' && string[i+1]=='l'&& string[i+2]=='e'&& string[i+3]=='a'&& string[i+4]=='r'){
		i+=5;
		token=0;	
	}else if(string[i]=='t' && string[i+1]=='y'&& string[i+2]=='p'&& string[i+3]=='e' && string[i+4]==' '){
		i+=4;
		token=1;
	}else if(string[i]=='e' && string[i+1]=='x'&& string[i+2]=='e'&& string[i+3]=='c' && string[i+4]==' '){
		i+=4;
		token=2;
	}else if(string[i]=='h' && string[i+1]=='e'&& string[i+2]=='l'&& string[i+3]=='p'){
		i+=4;
		token=3;
	}else if(string[i]=='l' && string[i+1]=='s' && (string[i+2]==' ' ||string[i+2]=='\0')){
		i+=2;
		token=4;
	}else if(string[i]!=0x0)
		token=-1;
	
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
	int i;	
	for(i=0;i<13312;i++)
	{
		buffer[i]=0x0;
	}
	
	switch(token)
	{
		case -1: syscall_printStringColor("Invalid Command.",14);
			syscall_printString("\n\r");
			break;
		case 0: syscall_Clr();
			break;
		
		case 1: if(syscall_readFile(file,buffer)==1){
				syscall_printStringColor(buffer,0x7);
			}else
				syscall_printStringColor("File not found.",14);
			syscall_printString("\n\r");
			break;
		
		case 2:	syscall_executeProgram(file,0x3000);
			break;

		case 3:	PrintCommands();
			break;
		
		case 4:	ls(file[0]);
			syscall_printString("\n\r");
			break;
				
		
	}
}
void ls(char character)
{
	char buff[512];
	char fil[96];
	int i,j,k,x;
	int cont=0;
	int column=0;
	
	for(x=0;x<512;x++)
		buff[x]=0x0;
	for(x=0;x<96;x++)
		fil[x]=0x0;
	syscall_readSector(buff, 2);
	
	for(i=0;i< 16;i++)
	{
		if(character!=0)
		{
			if(buff[(i*32)]==character)
			{
				if(column>5)
				{
					syscall_printString("\n\r");
					cont++;
					column=0;
				}else{
					syscall_printString("       ");
					column++;
				}

				for(j=0;j<6;j++)
				{
					if(buff[(i*32)+j]!='\0'){
						syscall_printCharColor(buff[(i*32)+j],0x3);
							
					}	
					
				}
				
			}	
		}else
		{
			if(buff[(i*32)]!=0)
			{
				if(column>5)
				{
					syscall_printString("\n\r");
					cont++;
					column=0;
				}else{
					syscall_printString("       ");
					column++;
				}
				for(j=0;j<6;j++)
				{	
					syscall_printCharColor(buff[(i*32)+j],0x3);
				}	
				
				
			}
		}
	}

}

void PrintCommands()
{

	syscall_printStringColor("List of Commands...\0",0xE);
	syscall_printString("\n\r");
	
     	syscall_printStringColor("Command          Description                                                  \n",0x70);
	//syscall_printString("\n\r");
	syscall_printStringColor("clear        ",0x3); 
	syscall_printStringColor("|\0",0x1);
	syscall_printStringColor("clear the shell.",0x7);	
	
	syscall_printString("\n\r");
	syscall_printStringColor("help         ",0x3); 
	syscall_printStringColor("|\0",0x1);
	syscall_printStringColor("show the existing commands.",0x7);	
	syscall_printString("\n\r");

	syscall_printStringColor("type\0",0x3);     
	syscall_printStringColor("(file)   \0",0x8);
	syscall_printStringColor("|\0",0x1);
	syscall_printStringColor("print the text of the file.",0x7);
	syscall_printString("\n\r");
	
	syscall_printStringColor("exec\0",0x3);
	syscall_printStringColor("(file)   \0",0x8);
	syscall_printStringColor("|\0",0x1);
	syscall_printStringColor("execute a program.",0x7);
	syscall_printString("\n\r");

	syscall_printStringColor("ls\0",0x3);
	syscall_printStringColor("(character)\0",0x8);
	syscall_printStringColor("|\0",0x1);
	syscall_printStringColor("show the list of files that start with (character) or all.",0x7);	

	syscall_printString("\n\r");
	syscall_printStringColor("------------------------------------------------------------------------------\n",0x1);

}

