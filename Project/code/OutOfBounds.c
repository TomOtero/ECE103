void OutOfBounds (void)
{
	int outOfBoundsFlag = 0;
	
	navX = (8 * entQuad1) + navX + (n * navX1); // not sure where the "n" is being pulled from
	navY = (8 * entQuad2) + navY + (n * navY1); // again not sure where the n is pulled
	
	entQuad1 = navX/8;
	entQuad2 = navY/8;
	entSect1 = navX - entQuad1/8;
	entSect2 = navY - entQuad2/8;
	
	if (entSect1 == 0)
	{
		entQuad1 = entQuad1 - 1;
		entSect1 = 8.0;
	}
	
	if (entSect2 == 0)
	{
		entQuad2 = entQuad2 - 1;
		entSect2 = 8.0;
	}
	
	if (entQuad1 < 1)
	{
		outOfBoundsFlag = 1;
		entQuad1 = 1;
		entSect1 = 1.0;
	}
	
	if (entQuad2 < 1)
	{
		outOfBoundsFlag = 1;
		entQuad2 = 1;
		entSect2 = 1.0;
	}
	
	if (entQuad1 > 8)
	{
		outOfBoundsFlag = 1;
		entQuad1 = 8;
		entSect1 = 8.0;
	}
	
	if (entQuad2 > 8)
	{
		outOfBoundsFlag = 1;
		entQuad2 = 8;
		entSect2 = 8.0;
	}
	
    if (outOfBoundsFlag != 0)
	{
		printf("LT. UHURA REPORTS MESSAGE FROM STARFLEET COMMAND : \n");
		printf("  'PERMISSION TO ATTEMPT CROSSING OF GALACTIC PERIMETER\n");
		printf("   IS HEREBY *DENIED*.  SHUT DOWN YOUR ENGINES.'\n");
		printf("   CHIEF ENGINEER SCOTT REPORTS  'WARP ENGINES SHUT DOWN\n");
		printf("   AT SECTOR %.1lf,%.1lf OF QUADRANT %d, %d.'", entSect1, entSect2, entQuad1, entQuad2);
	}
}