void main()
{
	int i,j;
	int PosY=0x0;
	//Clear Console
	for(i=0;i<20;i++)
	{
		for(j=0;j<160;j++)
		{
			putInMemory(0xB000, 0x8000+(j+1)+(i*80*2), 0x0);
			putInMemory(0xB000, 0x8001+(j+1)+(i*80*2), 0x1);
		}
	}
	
	//print HelloWord 
	for(i=0;i<16;i++)
	{
		PosY=((i*80)*2);
		putInMemory(0xB000, 0x8000+PosY, 'H');
		putInMemory(0xB000, 0x8001+PosY, i);	
		putInMemory(0xB000, 0x8002+PosY, 'e');
		putInMemory(0xB000, 0x8003+PosY, i);	
		putInMemory(0xB000, 0x8004+PosY, 'l');
		putInMemory(0xB000, 0x8005+PosY, i);
		putInMemory(0xB000, 0x8006+PosY, 'l');
		putInMemory(0xB000, 0x8007+PosY, i);	
		putInMemory(0xB000, 0x8008+PosY, 'o');
		putInMemory(0xB000, 0x8009+PosY, i);	
		putInMemory(0xB000, 0x800A+PosY, 'W');
		putInMemory(0xB000, 0x800B+PosY, i);	
		putInMemory(0xB000, 0x800C+PosY, 'o');
		putInMemory(0xB000, 0x800D+PosY, i);	
		putInMemory(0xB000, 0x800E, 'r');
		putInMemory(0xB000, 0x800F+PosY, i);		
		putInMemory(0xB000, 0x8010+PosY, 'd');
		putInMemory(0xB000, 0x8011+PosY, i);		
				
	}
		
}


