#define Base2 0xB000
void main()
{
	
	int i,j,w;
	int PosY=0x0;
	char* Word="Hello World";
	int Size=11;
	int Base=0x8000;

	
	//Clear Console
	for(i=0;i<30;i++)
	{
		for(j=0;j<160;j++)
		{
			
			putInMemory(Base2, Base+(j)+(i*80*2), 0x0);
			putInMemory(Base2, Base+1+(j)+(i*80*2), 0x1);
			
		}
	}

	//border
	for(i=0;i<30;i++)
	{
		for(j=0;j<160;j++)
		{
			if(!(j>3 && j<156 && i>0 &&i<24))
			{
				putInMemory(Base2, Base+(j)+(i*80*2), '*');
				putInMemory(Base2, Base+1+(j)+(i*80*2), 0x5);
			}
			
		}
	}	
	
	//print Hello World 
	
	for(i=0;i<16;i++)
	{
		PosY=(((i+2)*80)*2);
		for(w=0;w<Size;w++)
		{
			putInMemory(Base2, Base+PosY+10, Word[w]);
			putInMemory(Base2, Base+1+PosY+10, i);
			
			Base+=2;
		}
		Base-=Size*2;
	}
		
}



