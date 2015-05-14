void main()
{
	char str[80], buffer[512];
	syscall_moveCursor(20,2,0);
	syscall_printStringColor("Welcome to Syscall-Test ",0x4);
	syscall_moveCursor(2,10,0);
	syscall_printStringColor("Enter a your message: ",0x4);
	syscall_readStringColor(str,0x4);
	syscall_moveCursor(2,13,0);
	syscall_printStringColor("Your message was: ",0x4);
	syscall_printString(str);
	syscall_moveCursor(2,15,0);
	syscall_printString("Reading sector 30 from floppy...");
	syscall_readSector(buffer, 30);
	syscall_moveCursor(2,16,0);
	syscall_printString(buffer);

}

