void LongRangeScan (void)
{
if (damage[3] < 0)
	{
	printf("Long Range Sensors are inopperable");
	break;
	}
	
printf("Long Range Scan for Quadrant %d, %d", entQuad1, entQuad2);

printf("    -------------------");

for (int i = entQuad1 -1, i <= entQuad1 + 1, i++)
	{
	for (int j = entQuad2 - 1, j <= entQuad2 + 1, j++)
		{
		if (((i > 0) && (i < 9)) && ((j > 0) && (j < 9))
			{
			galaxyRecord [i][j] = galaxy [i][j];
			printf("%d :",galaxyRecordecord [i][j]);
			}
		
		else 
			{
			printf(" *** :);
			}
		}
		printf("\n");
	}
printf("    -------------------");	

}


