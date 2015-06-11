
int getToken(char string[], char file[],char file2[]);
void executeToken(int token,char file[],char file2[]);
void PrintCommands();
void ls(char character);
int copyFile(char filename1[],char filename2[]);
int createFile(char filename[]);
int getSectorsNumber(char name[]);

void main()
{
	int token;
	char str[80];
	char file[6];
	char file2[6];
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
			token=getToken(str,file,file2);
			executeToken(token,file,file2);
		}
	}
}


int getToken(char string[], char file[], char file2[])
{
	int i=0;
	int j=0;
	int k;
	int token=-2;
	for(k=0;k<6;k++)
	{
		file[k]=0x0;
		file2[k]=0x0;
	}
	
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
	}else if(string[i]=='d' && string[i+1]=='e' && string[i+2]=='l' && string[i+3]=='e' && string[i+4]=='t' 
		&& string[i+5]=='e' && string[i+6]==' '){
		i+=6;
		token=5;
	}else if(string[i]=='c' && string[i+1]=='o' && string[i+2]=='p' && string[i+3]=='y' && string[i+4]==' '){
		i+=4;
		token=6;
	}else if(string[i]=='c' && string[i+1]=='r' && string[i+2]=='e' && string[i+3]=='a' && string[i+4]=='t' 
		&& string[i+5]=='e' && string[i+6]==' '){
		i+=6;
		token=7;
	}else if(string[i]!=0x0)
		token=-1;
	
	while(string[i]==' ')
		i++;
	
	for(j=0;j<6;j++)
	{
		if(string[i]!=' ' && string[i]!='\n' && string[i]!='\0')
		{
			file[j]=string[i];
			i++;
		}else{
			j=6;
		}
	}	
	
	while(string[i]==' ')
		i++;	
	
	if(string[i]!=0x0 || string[i]!='\0')
	{
		for(j=0;j<6;j++)
		{
			file2[j]=string[i];
			i++;
		}	
	}
	
	return token;	
}


void executeToken(int token,char file[],char file2[])
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
		
		case 5:	
			if(syscall_deleteFile(file)==1)
				syscall_printStringColor("File deleted.",14);
			else
				syscall_printStringColor("File not found.",14);
				
			syscall_printString("\n\r");
			break;
			
		case 6:	
			if(copyFile(file,file2)==1)
				syscall_printStringColor("File copied.",14);
			syscall_printString("\n\r");
			break;
			
		case 7:	createFile(file);
			
			break;
				
		
	}
}
void ls(char character)
{
	char buff[512];
	char temp[13312];
	char name[6];
	char fil[96];
	int i,j,k,x;
	int cont=0;
	int column=0;
	for(x=0;x<13312;x++)
		temp[x]=0x0;
	for(x=0;x<512;x++)
		buff[x]=0x0;
	for(x=0;x<96;x++)
		fil[x]=0x0;
	syscall_readSector(buff, 2);
	syscall_printStringColor("   File   ",0x70);
	syscall_printStringColor("   Size   ",0x40);
	syscall_printStringColor(" #Sectors ",0x20);
	for(i=0;i< 16;i++)
	{
		if(character!=0)
		{
			if(buff[(i*32)]==character)
			{
				
				syscall_printString("\n\r");
				cont++;
				column=0;

				for(j=0;j<6;j++)
				{
					if(buff[(i*32)+j]!='\0'){
						syscall_printCharColor(buff[(i*32)+j],15);
						
					}	
					name[j]=buff[(i*32)+j];	
				}
				syscall_printStringColor("      ",0x3);
				syscall_readFile(name,temp);
				syscall_printInt(getSectorsNumber(name)*512,7);
				if(getSectorsNumber(name)>1)
					syscall_printStringColor("       ",0x3);
				else
					syscall_printStringColor("        ",0x3);
				syscall_printInt(getSectorsNumber(name),7);
			}	
		}else
		{
			if(buff[(i*32)]!=0)
			{
				syscall_printString("\n\r");
				cont++;
				column=0;
				
				for(j=0;j<6;j++)
				{	
					syscall_printCharColor(buff[(i*32)+j],15);
					name[j]=buff[(i*32)+j];	
				}	
				syscall_printStringColor("      ",0x3);
				syscall_readFile(name,temp);
				syscall_printInt(getSectorsNumber(name)*512,7);
				if(getSectorsNumber(name)>1)
					syscall_printStringColor("       ",0x3);
				else
					syscall_printStringColor("        ",0x3);
				syscall_printInt(getSectorsNumber(name),7);
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
	syscall_printStringColor("clear         ",0x3); 
	syscall_printStringColor("|\0",0x1);
	syscall_printStringColor("clear the shell.",0x7);	
	
	syscall_printString("\n\r");
	syscall_printStringColor("help          ",0x3); 
	syscall_printStringColor("|\0",0x1);
	syscall_printStringColor("show the existing commands.",0x7);	
	syscall_printString("\n\r");

	syscall_printStringColor("type\0",0x3);     
	syscall_printStringColor(" (file)   \0",0x8);
	syscall_printStringColor("|\0",0x1);
	syscall_printStringColor("print the text of the file.",0x7);
	syscall_printString("\n\r");
	
	syscall_printStringColor("exec\0",0x3);
	syscall_printStringColor(" (file)   \0",0x8);
	syscall_printStringColor("|\0",0x1);
	syscall_printStringColor("execute a program.",0x7);
	syscall_printString("\n\r");

	syscall_printStringColor("ls\0",0x3);
	syscall_printStringColor(" (character)\0",0x8);
	syscall_printStringColor("|\0",0x1);
	syscall_printStringColor("show the list of files that start with (character) or all.",0x7);
	syscall_printString("\n\r");
	
	syscall_printStringColor("delete\0",0x3);
	syscall_printStringColor(" (file) \0",0x8);
	syscall_printStringColor("|\0",0x1);
	syscall_printStringColor("Delete a file.",0x7);	
	syscall_printString("\n\r");
	
	syscall_printStringColor("copy\0",0x3);
	syscall_printStringColor(" (f1) (f2)\0",0x8);
	syscall_printStringColor("|\0",0x1);
	syscall_printStringColor("Copy the first file into another file",0x7);	
	syscall_printString("\n\r");
	
	syscall_printStringColor("create\0",0x3);
	syscall_printStringColor(" (file) \0",0x8);
	syscall_printStringColor("|\0",0x1);
	syscall_printStringColor("Creates a file and its content.",0x7);		

	syscall_printString("\n\r");
	syscall_printStringColor("------------------------------------------------------------------------------\n",0x1);

}

int copyFile(char filename1[],char filename2[])
{
	char buffer[13312];
	
	if(syscall_readFile(filename1,buffer)==1)
	{
		if(syscall_writeFile(filename2,buffer,getSectorsNumber(filename1)*512)==1)
			return 1;
		else if(syscall_writeFile(filename2,buffer,syscall_getBufferSize(buffer))==-1)
			syscall_printStringColor("Not enough space.",14);
		else if(syscall_writeFile(filename2,buffer,syscall_getBufferSize(buffer))==0)
			syscall_printStringColor("Directory is full.",14);
			
	}else
		syscall_printStringColor("File not found.",14);
	return 0;
}

int getSectorsNumber(char name[])
{
	char buff[512];
	int i,j;
	int exist=0;
	int sectors=0;

	syscall_readSector(buff, 2);
	
	
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
		{
			for(j=6;j<32;j++)
			{
				if(buff[(i*32)+j]!='\0')
					sectors++;	
			}
			return sectors;
		}
	}
	return 0;
}

int createFile(char filename[])
{	
	char buffer[13312];
	int Size=0;
	int write=1;
	char temp[512];
	int i,j;
	int tempSize=0;
	
	
	for(i=0;i<13312;i++)
		buffer[i]=0x0;
	syscall_printStringColor("Start writing your textfile: \n",11);
	
	while(write==1)
	{
		syscall_readStringColor(temp,15);
		
		if(syscall_getBufferSize(temp)==0)
			write=0;
		
		else
		{
			temp[syscall_getBufferSize(temp)]='\n';
			
			
			for(i=0;i<syscall_getBufferSize(temp);i++)
			{
				buffer[Size+i]=temp[i];
			}
			Size+=syscall_getBufferSize(temp);
			
		}
		
		for(j=0;j<512;j++)
			temp[j]=0x0;
	}
	

	if(Size>0)
	{
		if(syscall_writeFile(filename,buffer,Size)==1)
			return 1;
		else if(syscall_writeFile(filename,buffer,syscall_getBufferSize(buffer))==-1)
			syscall_printStringColor("Not enough space.",14);
		else if(syscall_writeFile(filename,buffer,syscall_getBufferSize(buffer))==0)
			syscall_printStringColor("Directory is full.",14);
	}else
		syscall_printStringColor("Cannot create an empty file.",14);
}


