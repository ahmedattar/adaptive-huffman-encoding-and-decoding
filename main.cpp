#include <iostream>
#include <string>
#include <string.h>
#include<conio.h>
#include <stdlib.h>
#include <cmath>
using namespace std;
struct node
{
    int weight;
    char value;
    node* right;
    node* left;
    node* child;
    node* father;

};
int convertBinaryToDecimal(string binaryString)
{
    int value = 0;
    int indexCounter = 0;
    for(int i=binaryString.length()-1; i>=0; i--)
    {

        if(binaryString[i]=='1')
        {
            value += pow(2, indexCounter);
        }
        indexCounter++;
    }
    return indexCounter;
}

void CreateTreeOfEncoding(string stream,char data[],int e, int r, int length, string binary[] )
{

    int nyt=1;
    char store[length];
    string buffer;
    string output;
    node* root = new node;
    root->left->value='#';
    root->left->weight=0;
    root->right->weight=1;
    root->right->value=stream[0];
    buffer=binary[0];
    output+=buffer;
    store[0]=stream[0];
    node* currentnode = new node;
    currentnode = root;
    for(int i=1; i<length; i++)
    {
        node* newnode= new node;
        for (int j=0; j<=length; j++)
        {
            if (stream[i]==store[j])
            {
                for (int z=0; z<nyt; i++)
                {
                    if (currentnode->left->value == stream[i])
                    {
                        currentnode->left->weight=+1;
                        currentnode->weight+=1;
                    }
                    else if (currentnode->right->value == stream[i])
                    {
                        currentnode->right->weight +=1;
                        currentnode->weight+=1;
                    }
                    else
                    {
                        if ( currentnode->left->weight >= currentnode->right->weight )
                        {
                            currentnode= currentnode->left;
                        }
                        else
                        {
                            currentnode= currentnode->right;
                        }


                    }



                }
            }
            else
            {

                newnode->left=currentnode;
                currentnode->father=newnode;
                newnode->right->weight=1;
                newnode->weight= newnode->left->weight+newnode->right->weight;
                newnode->value=stream[i];

                buffer=binary[j];
                nyt+=1;

            }
        }


        currentnode = newnode;
        for (int i=0; i<nyt; i++) // modifying of the tree weights
        {
            if (currentnode->left->weight > currentnode->right->weight )
            {
                node* temporaraynode= currentnode->left;
                currentnode->left= currentnode->right;
                currentnode->right= temporaraynode;
                currentnode= currentnode->right;

            }
        }
        for (int t=0; t<nyt; t++)
        {
            output+='0';
        }
        output+=buffer;
    }
    for (int i=0; i<26; i++)
    {
        cout<<output[i];

    }
}

void encoding()
{
    int decision, r, e, length;
    string stream ;
//int* input = new int [length] ;


    cout << " for alphabet enter 1, for numbers enter 2 "<<endl;
    cin>>decision;

    cout << " enter the stream "<<endl;
    cin>>stream;
    length = stream.length();
    char chars[26]= {'A','B','C','D', 'E', 'F', 'G', 'H', 'I', 'J',
                     'K', 'L', 'M', 'N', 'O', 'P','Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
                    };
    string chars_binary[26]= {"00000","00001","00010","00011","00100","00101","00110","00111",
                              "01000","01001","01010","01011",
                              "01100","01101","01110","01111","10000","10001","10010","10011","1010",
                              "1011","1100","1101","1110","1111"
                             };
    string numbers_binary[10]= {"0000","0001","0010","0011","010","011","100","101","110","111"};
    char numbers[10]= {'0','1','2','3','4','5','6','7','8','9'};
    if (decision==1)
    {
        r=10;
        e=4;
        CreateTreeOfEncoding(stream,chars,e,r,length,chars_binary);
    }

    else if ( decision ==2)
    {
        r=2;
        e=3;
        CreateTreeOfEncoding(stream,numbers,e,r,length,numbers_binary);

    }

}
string treeofdecoding(string stream,char data[],int e, int r, int length, string binary[])
{
    int nyt=1;
    int i=0;
    char character;
    char store[length];
    string buffer;
    string output;
    node* root = new node;
    root->left->value='#';
    root->left->weight=0;

    buffer=binary[0];
    output+=buffer;

    node* currentnode = new node;
    currentnode = root;
    for (int j=0; j<4; j++)
    {
        buffer+=stream[j];
    }
    int i_bin = convertBinaryToDecimal(buffer);
    if (i_bin>r)
    {
        i_bin+=r;
        i_bin+=1;
        for (int k=0; k<26; k++)
        {
            if (i_bin==k+1)
            {
                character=data[k+1];
            }
            i=4;
            buffer.clear();
        }
    }
    else
    {
        buffer+=stream[5];
        int i_bin = convertBinaryToDecimal(buffer);
        for (int k=0; k<26; k++)
        {
            if (i_bin==k+1)
            {
                character=data[k+1];
                i=5;
                buffer.clear();
            }
        }
    }
    root->left->value=character;
    for(; i<length; i++)
    {
        node* newnode= new node;
        for (int z=0; z<nyt; i++)
        {
            buffer+=stream[i];
        }
        buffer=stream[i];
        int i_bin = convertBinaryToDecimal(buffer);

        for (int i=0; i<length; i++)
        {
            for (int j=0; j<4; j++)
            {
                buffer+=stream[j];
            }
            int i_bin = convertBinaryToDecimal(buffer);
            if (i_bin>r)
            {
                i_bin+=r;
                i_bin+=1;
                for (int k=0; k<26; k++)
                {
                    if (i_bin==k+1)
                    {
                        character=data[k+1];
                    }
                }
            }
            else
            {
                buffer+=stream[5];
                int i_bin = convertBinaryToDecimal(buffer);
                for (int k=0; k<26; k++)
                {
                    if (i_bin==k+1)
                    {
                        character=data[k+1];
                    }
                }
            }
        }
        for (int j=0; j<=length; j++)
        {
            if (stream[i]==store[j])
            {
                for (int z=0; z<nyt; i++)
                {
                    if (currentnode->left->value == stream[i])
                    {
                        currentnode->left->weight=+1;
                        currentnode->weight+=1;
                    }
                    else if (currentnode->right->value == stream[i])
                    {
                        currentnode->right->weight +=1;
                        currentnode->weight+=1;
                    }
                    else
                    {
                        if ( currentnode->left->weight >= currentnode->right->weight )
                        {
                            currentnode= currentnode->left;
                        }
                        else
                        {
                            currentnode= currentnode->right;
                        }


                    }



                }
            }
            else
            {

                newnode->left=currentnode;
                currentnode->father=newnode;
                newnode->right->weight=1;
                newnode->weight= newnode->left->weight+newnode->right->weight;
                newnode->value=stream[i];

                buffer=binary[j];
                nyt+=1;

            }
        }


        currentnode = newnode;
        for (int i=0; i<nyt; i++) // modifying of the tree weights
        {
            if (currentnode->left->weight > currentnode->right->weight )
            {
                node* temporaraynode= currentnode->left;
                currentnode->left= currentnode->right;
                currentnode->right= temporaraynode;
                currentnode= currentnode->right;

            }
        }
        for (int t=0; t<nyt; t++)
        {
            output+='0';
        }
        output+=buffer;
    }
}

void decoding ()
{
    int decision, r, e, length;
    string buffer;
    string stream ;
    char character, chars[26]= {'A','B','C','D', 'E', 'F', 'G', 'H', 'I', 'J',
                                'K', 'L', 'M', 'N', 'O', 'P','Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
                               }, numbers[10]= {'0','1','2','3','4','5','6','7','8','9'};


    cout << " for alphabet enter 1, for numbers enter 2 "<<endl;
    cin>>decision;

    cout << " enter the stream "<<endl;
    cin>>stream;
    length = stream.length();


}





void making_decision()
{
    int number;
    cout << " for encoding enter 1 , for decoding enter 2" << endl;
    cin>> number;
    if ( number ==1 )
    {
        encoding();
    }
    else if ( number==2)
    {
        decoding();
    }
    else
    {
        cout<<" error choice "<<endl;
    }
}


int main()
{

    making_decision();
    return 0;
}
