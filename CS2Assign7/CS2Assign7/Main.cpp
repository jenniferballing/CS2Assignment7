#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <string.h>

using namespace std;

typedef struct Friend
{
	char name [30];
	char interests [100];
	short age;

}FRIEND;

void AddFriend(char i);
void RemoveFriend( char i);
int fileSize(const char* fileName);
char fileType();



int main()
{
    char input;
    input=fileType();
	AddFriend(input);
    RemoveFriend(input);

	return 0;
}


void AddFriend(char i)
{
	string newName;
	string newInterests;
	short newAge=0;
	
	//GET INFO FROM USER
    cin.clear();
	cin.sync();
    //check for valid info from user
	cout<<"What is the name of the friend you would like to add?"<<endl;
	getline(cin, newName);
	cout<<"What are the interests of your friend?"<<endl;
	getline(cin, newInterests);
	if(sizeof (newInterests)>99)
    {
		cout<<"Your friend has too many interests. Please try again with fewer characters."<<endl;
		getline(cin, newInterests);
	}
	cout<<"What is the age of your friend?"<<endl;
	cin>>newAge;

    //PUT INTO A CHAR ARR
	char nName [30];
	char nInterests [100];

	for(int j=0; j<30; j++)
    {
		if(j<(int)newName.size())
		{
			nName[j]=newName[j];
		}
		else
		{
			nName[j]='-';
		}
	}
	for(int k=0; k<100; k++)
    {
		if(k<(int)newInterests.size())
		{
			nInterests[k]=newInterests[k];
		}
		else
		{
			nInterests[k]='-';
		}
	}
    
	//PUT INTO STRUCT
	FRIEND newFriend;
	memcpy(newFriend.name, nName, sizeof(nName));
	memcpy(newFriend.interests, nInterests, sizeof(nInterests));
	newFriend.age=newAge;

    fstream fout;
    if(i=='y' || i=='Y')
    {
        fout.close();
        fout.open("myNetwork.dat", ios:: in | ios:: out | ios::binary | ios::trunc);
    }
    else
    {
        fout.open("myNetwork.dat", ios:: in | ios:: out | ios::binary | ios::ate);
    }

	//PUT STRUCT INTO FILE 
	fout.write((char*)&newFriend, sizeof(newFriend));

	//TELL USER THE ID
    fout.close();
	long sizeFile= fileSize("myNetwork.dat");
	int sizeObj= sizeof(newFriend);
	int id=sizeFile/sizeObj;
	cout<<"The record number of this friend is: "<<id<<endl;
	
}
int fileSize(const char* fileName)
{
	fstream fin(fileName, ios::in | ios::binary);
	fin.seekg(0L, ios::end);
	return (int)fin.tellg();
}
char fileType()
{
    fstream fout("myNetwork.dat");
    char input;

	//FILE ALREADY EXISTS
	if(fout.fail())
	{
        return 'y';
	}
	//FILE DOES NOT EXIST
	else
	{
		cout<<"myNetwork.dat already exists. Would you like to override it? (y/n)"<<endl;
		cin>>input;
        if(input=='y' ||input=='Y')
        {
            return 'y';
		}
		else if (input=='n' || input == 'N')
		{
            return 'n';
		} 
        else
        {
            while(input!='y' || input!='Y' || input!='n' || input!='N')
		    {
			    cout<<"Please choose whether or not to override the file. (y/n)"<<endl;
			    cin>>input;
		    }
        }
    }return input;
}
void RemoveFriend(char i)
{
    int id;
    fstream fout("myNetwork.dat");
    if(i=='y' || i=='Y')
    {
        fout.close();
        fout.open("myNetwork.dat", ios:: in | ios:: out | ios::binary | ios::trunc);
    }
    else
    {
        fout.open("myNetwork.dat", ios:: in | ios:: out | ios::binary | ios::ate);
    }
    cout<<"What is the ID number of the friend you would like to delete?"<<endl;
    cin>>id;
    long sizeFile= fileSize("myNetwork.dat");
	int sizeObj= sizeof(FRIEND);
	int index =sizeFile/sizeObj;
    long starting = sizeObj*id;
    while(id>index || id<0)
    {
        cout<<"This selection is out of range. Please enter the ID of the friend you would like to delete."<<endl;
        cin>>id;
    }
    //the one after the deleted
    
    
    FRIEND newFriend, emptyFriend;
    memcpy(emptyFriend.name, "Empty", 5);
    memcpy(emptyFriend.interests, "Empty", 5);
    emptyFriend.age= 0;
    long num=sizeof(FRIEND);
    cout<<"size:"<<sizeFile<<endl;
    for(long l =starting; l<sizeFile; l+=132)
    {
        fout.seekg(l, ios::beg);
        fout.read((char*) &newFriend, sizeof(newFriend));
        fout.seekp(-l, ios::cur);
        fout.write((char*)&newFriend, sizeof(newFriend));
    }
    cout<<"size:"<<sizeFile<<endl;
    fout.seekp(-132L, ios::cur);
    fout.write((char*)&emptyFriend, sizeof(emptyFriend));
    fout.close();
}
