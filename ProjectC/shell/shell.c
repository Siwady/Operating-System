
int getToken(char string[], char file[]);
void executeToken(int token,char file[]);


void main()
{
	int token;
	char string[80];
	char file[6];
	syscall_Clr();
	while(1==1)
	{
		syscall_printStringColor("shell ->$ ",0x4);
		syscall_readStringColor(string,0x2);
		token=getToken(string,&file);
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
	}
	
	while(string[i]==' ')
		i++;
	
	for(j=0;j<6;j++)
		file[j]=string[i];
		
		
	
	return token;	
}


void executeToken(int token,char file[])
{
	switch(token)
	{
		case 0: syscall_Clr();
			break;
		
		case 1: syscall_printString(file);
			break;
	}
}

