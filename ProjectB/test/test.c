void main()
{
	char str[80], buffer[512];
	
	
	syscall_moveCursor(27,2,0);
	syscall_printStringColor("Welcome to Syscall-Test ",0x8);
	syscall_moveCursor(2,8,0);
	syscall_printStringColor("Enter a your message: ",0x8);
	syscall_readStringColor(str,0x6);
	syscall_moveCursor(2,11,0);
	syscall_printStringColor("Your message was: ",0x8);
	syscall_printStringColor(str,0x6);
	syscall_moveCursor(2,14,0);
	syscall_printStringColor("Reading sector 30 from floppy...",0x8);
	syscall_readSector(buffer, 30);
	syscall_moveCursor(2,15,0);
	syscall_printStringColor(buffer,0x9);

	while(1==1)
	{
		
	}

}

