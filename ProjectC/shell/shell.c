static int token;
static char string[80];

void getToken(char string[],char file[]);
void executeToken(char* file);


void main()
{
	
	char file[6];
	while(1==1)
	{
		syscall_printStringColor("shell ->$ ",0x4);
		syscall_readStringColor(string,0x2);
		getToken(string,&file);
		executeToken(&token,&file);
	}
	
}


void getToken(char string[],char file[])
{
	if(string[0]=='c' && string[0]=='l' && string[0]=='e' && string[0]=='a' && string[0]=='r')
		token=0;
}


void executeToken(char* file)
{
	switch(token)
	{
		case 0: syscall_Clr();
			break;
		
		case 1: syscall_printStringColor(file,0x2);
			break;
	}
}
