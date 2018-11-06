#include <stdio.h>

int calculation_Checksum(int *msg)
{
	unsigned int	sum	= 0;		//32bit sum
	unsigned short	word	= 0xffff;	//16bit word
	unsigned short	csum	= 0xffff;	//final checksum

	int lth	= sizeof(*msg)/2;		//msg length in word
	if (sizeof(*msg)%2)lth++;

	int i;
	for(i=0; i<lth; i++){			//more words?
		word = word & (*msg>>(16*i));
		sum += word;
		word = 0xffff;
	}
	
	while(sum>>16){				//Left(sum) is nonzero?
		sum = sum>>16 + sum&0xffff;
	}

	//truncate & inverse
	csum = csum&sum;
	return ~csum;
}

int check_Checksum(int *msg)
{
	unsigned int	sum	= 0;		//32bit sum
	unsigned short	word	= 0xffff;	//16bit word
	unsigned short	csum	= 0xffff;	//final checksum

	int lth = sizeof(*msg)/2;		//msg length in word
	if (sizeof(*msg)%2)lth++;

	int i;
	for(i=0; i<lth; i++){			//more words?
		word = word & (*msg>>(16*i));
		sum += word;
		word = 0xffff;
	}

	while(sum>>16){				//Left(sum) is nonzero?
		sum = sum>>16 + sum&0xffff;
	}

	//truncate & inverse
	csum = ~(csum&sum);
	if(csum)	return 0;		//false if csum!=0
	else		return 1;		//true if csum==0
}        
         
int main(void){					//!!main function!!

	int msg;
	printf("enter any integer :");
	scanf("%d",&msg);
	msg = msg<<16;		//attach 16bit checksum(ignore msg lose)
	printf("\n\n*present msg = %x*\n",msg);

	//checksum test before create checksum
	printf("checksum test for msg without calculated checksum\n");
	printf("checksum is fitted if result == 1\n>>result = %d\n\n",check_Checksum(&msg));
	
	//find checksum & attach
	unsigned short checksum = calculation_Checksum(&msg);
	printf("*calculated checksum is %x*\n\n",checksum);
	msg = msg|checksum;
	printf("*present msg = %x*\n",msg);

	//checksum test after
	printf("checksum test for msg with calculated checksum\n");
	printf("checksum is fitted if result == 1\n>>result = %d\n\n",check_Checksum(&msg));
	return 0;
}	
                                               

