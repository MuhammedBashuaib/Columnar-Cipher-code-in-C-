// C++ program for illustrating
// Columnar Transposition Cipher
#include <iostream>
#include <String>
#include <map>

using namespace std;

// Key for Columnar Transposition
map<int,int> keyMap; //map cntainer

void setPermutationOrder(string key)
{
	// Add the permutation order into map
	for(int i=0; i < key.length(); i++)
	{
		keyMap[key[i]] = i;
	}
}

// Encryption
string encryption(string plain_text , string key)
{
	int row,col,j;
	string cipher_text = "";

	/* calculate column of the matrix*/
	col = key.length();

	/* calculate Maximum row of the matrix*/
	row = plain_text.length()/col;

	if (plain_text.length() % col)
		row += 1;

	char matrix[row][col];

	for (int i=0,k=0; i < row; i++)
	{
		for (int j=0; j<col; )
		{
			if(plain_text[k] == '\0')
			{
				/* Adding the padding character '_' */
				matrix[i][j] = '_';
				j++;
			}

			if( isalpha(plain_text[k]) || plain_text[k]==' ')
			{
				/* Adding only space and alphabet into matrix*/
				matrix[i][j] = plain_text[k];
				j++;
			}
			k++;
		}
	}

	for (map<int,int>::iterator ii = keyMap.begin(); ii!=keyMap.end(); ++ii)
	{
		j=ii->second;

		// getting cipher text from matrix column wise using permuted key
		for (int i=0; i<row; i++)
		{
			if( isalpha(matrix[i][j]) || matrix[i][j]==' ' || matrix[i][j]=='_')
				cipher_text += matrix[i][j];
		}
	}

	return cipher_text;
}

// Decryption
string decryption(string cipher_text , string key)
{
	/* calculate row and column for cipher Matrix */
	int col = key.length();

	int row = cipher_text.length()/col;
	char cipherMat[row][col];

	/* add character into matrix column wise */
	for (int j=0,k=0; j<col; j++)
		for (int i=0; i<row; i++)
			cipherMat[i][j] = cipher_text[k++];

	/* update the order of key for decryption */
	int index = 0;
	for( map<int,int>::iterator ii=keyMap.begin(); ii!=keyMap.end(); ++ii)
		ii->second = index++;

	/* Arrange the matrix column wise according
	to permutation order by adding into new matrix */
	char decCipher[row][col];
	map<int,int>::iterator ii=keyMap.begin();
	int k = 0;
	for (int l=0,j; key[l]!='\0'; k++)
	{
		j = keyMap[key[l++]];
		for (int i=0; i<row; i++)
		{
			decCipher[i][k]=cipherMat[i][j];
		}
	}

	/* getting Message using matrix */
	string plain_text = "";
	for (int i=0; i<row; i++)
	{
		for(int j=0; j<col; j++)
		{
			if(decCipher[i][j] != '_')
				plain_text += decCipher[i][j];
		}
	}
	return plain_text;
}

// Driver Program
int main(void)
{
    string key = "code";
    string text = "Geeks for Geeks";
    setPermutationOrder(key);
    cout<<"the plain text is: "<<text<<endl;
    cout<<"the key is: "<<key<<endl;
    string cipher_text = encryption(text , key);
    cout<<"the Cipher text is: "<<cipher_text<<endl;
    //cout<<"the plain text is: "<<decryption(cipher_text , key);

	return 0;
}

