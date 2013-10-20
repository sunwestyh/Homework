// GrayCode.cpp : Defines the entry point for the console application.
//


#include <conio.h>
#include <ctype.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>

#define MAX_NUMBER_OF_BIT 16

unsigned short BinaryToGray( unsigned short binaryCode );
unsigned short GrayToBinary( unsigned short grayCode );
void ConvertIntToBinaryString( unsigned short inputValue, int inputLength, char * outputBuffer );

void main( void )
{
	int ch = '?';

	while ( ( ch != '1' ) && ( ch != '2' ) && ( ch != 'B' ) && ( ch != 'b' ) )
	{
	   _cputs( "\nType '1' for binary code to Gray code conversion\nType '2' for Gray code to binary code conversion\nType 'B' to say good-bye\n" );
	   ch = _getche();
	}

	bool bBinaryToGray = true;
	switch ( ch )
	{
		case 'B':
		case 'b':
			return;
			break;
		case '1':
			bBinaryToGray = true;
			break;
		case '2':
			bBinaryToGray = false;
			break;
	}

	char inputBuffer[ MAX_NUMBER_OF_BIT + 10];
	for ( ; ; )
	{
		if ( bBinaryToGray )
			printf( "\nEnter binary code up to %d bits(or type 'B' + [Enter] to say good-bye):\n\n", MAX_NUMBER_OF_BIT );
		else
			printf( "\nEnter Gray code up to %d bits(or type 'B' + [Enter] to say good-bye):\n\n", MAX_NUMBER_OF_BIT );
		memset( inputBuffer, 0, sizeof( inputBuffer ) );
		fgets( inputBuffer, sizeof( inputBuffer ), stdin );

		if ( ( inputBuffer[0] == 'B' ) || ( inputBuffer[0] == 'b' ) )
			break;

		unsigned short nInputValue = 0;
		int nInputLength = 0;
		bool bInputValid = true;
		int i = 0;
		while ( ( bInputValid == true ) && ( i < MAX_NUMBER_OF_BIT ) && ( inputBuffer[i] != 0x0A ) && ( inputBuffer[i] != 0x0D ) )
		{
			nInputValue = nInputValue << 1;
			nInputLength = nInputLength + 1;
			switch ( inputBuffer[i] )
			{
				case '0':
					break;
				case '1':
					nInputValue = nInputValue | 1;
					break;
				default:
					bInputValid = false;
					break;
			}
			i = i + 1;
		}

		if ( nInputLength < 1 )
			continue;

		if ( bInputValid == false )
		{
			printf( "\nInvalid input.\n" );
			continue;
		}

		char outputBuffer[ MAX_NUMBER_OF_BIT + 1];
		if ( bBinaryToGray )
		{
			unsigned short nConvertedValue = BinaryToGray( nInputValue );
			ConvertIntToBinaryString( nConvertedValue, nInputLength, outputBuffer );
			printf( "\nGray code: %s\n", outputBuffer );
		}
		else
		{
			unsigned short nConvertedValue = GrayToBinary( nInputValue );
			ConvertIntToBinaryString( nConvertedValue, nInputLength, outputBuffer );
			printf( "\nBinary code: %s\n", outputBuffer );
		}
	}
}

unsigned short BinaryToGray( unsigned short binaryCode )
{
	return ( binaryCode >> 1 ) ^ binaryCode;
}

unsigned short GrayToBinary( unsigned short grayCode )
{
	unsigned short nBinary = grayCode;
	unsigned short nMask = grayCode >> 1;
	while ( nMask > 0 )
	{
		nBinary = nBinary ^ nMask;
		nMask = nMask >> 1;
	}
	return nBinary;
}

void ConvertIntToBinaryString( unsigned short inputValue, int inputLength, char * outputBuffer )
{
	memset( outputBuffer, 0, sizeof( outputBuffer ) );
	if ( inputLength < 1 )
		return;
	unsigned short nMask = 1 << ( inputLength - 1 );
	while ( nMask > 0 )
	{
       strcat( outputBuffer, ( ( inputValue & nMask ) == nMask ) ? "1" : "0" );
	   nMask = nMask >> 1;
	}
}