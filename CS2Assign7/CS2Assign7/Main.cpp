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
void menu();



int main()
{
    char input;
    input=fileType();
	AddFriend(input);
    AddFriend('n');
    AddFriend('n');
    RemoveFriend(input);

	return 0;
}

void menu(char i)
{
    char input;
    cout<<"***Network of My Friends***"<<endl;
    cout<<"A: Add a Friend"<<endl;
    cout<<"R: Remove a Friend by ID Number"<<endl;
    cout<<"M: Modify a Friend's Information by ID Number"<<endl;
    cout<<"S:Search Interests"<<endl;
    cout<<"D:Display \"myNetwork.dat\" Database Information"<<endl;
    cout<<"L: List the Oldest and the Youngest Friends' Information"<<endl;
    cout<<"E: Exit"<<endl;

    cin>>input;
    if(input=='a' || input == 'A')AddFriend(i);
    else if(input=='r' || input == 'R') RemoveFriend(i);
    //else if(input=='m' || input == 'M') ModifyFriend(i);
    //else if(input=='s' || input == 'S') SearchFriend(i);
    //else if(input=='d' || input == 'D') DisplayFriend(i);
    //else if(input=='l' || input == 'L') ListFriend(i);
    else if(input=='e' || input == 'E')
    {
        exit(0);
    }
    else
    {
        cout<<input<<" isn't one of the menu options, \nPlease choose from the menu: \n"<<endl;
        cout<<"***Network of My Friends***"<<endl;
    cout<<"A: Add a Friend"<<endl;
    cout<<"R: Remove a Friend by ID Number"<<endl;
    cout<<"M: Modify a Friend's Information by ID Number"<<endl;
    cout<<"S:Search Interests"<<endl;
    cout<<"D:Display \"myNetwork.dat\" Database Information"<<endl;
    cout<<"L: List the Oldest and the Youngest Friends\'"<<endl;
    }
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
        //fout.close();
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
    long chosen;
    long offset= sizeof(FRIEND)*2;
    FRIEND storage;
    FRIEND nf;
    FRIEND empty;
    memcpy(empty.name, "Empty", 5);
    memcpy(empty.interests, "Empty", 5);
    empty.age= 0;

    fstream fout;
    
    fout.open("myNetwork.dat", ios::in | ios::out | ios::binary | ios::ate);
    cout<<"Which is chosen: "<<endl;
    cin>>chosen;
    int numIndex = fileSize("myNetwork.dat")/132;
    for(int i=chosen; i<numIndex; i++)
    {
        fout.seekg(i*sizeof(nf), ios::beg);
        fout.read((char *)&storage, sizeof(storage));
        fout.seekp(-offset, ios::cur);
        fout.write((char*)&storage, sizeof(storage));
    }

    fout.seekp(-132, ios::end);
    fout.write((char*)&empty, sizeof(empty));
    

    fout.close();


    /*int id;
    fstream fout("myNetwork.dat");
    if(i=='y' || i=='Y')
    {
        //fout.close();
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
        streampos a = fout.tellg();
        //cout<<(int)fout.tellg()<<end;
        fout.read((char*) &newFriend, sizeof(newFriend));
        streampos b = fout.tellg();
        //cout<<fout.tellg()<<end;
        fout.seekp(l-132, ios::beg);
        int pos2=fout.tellp();
        cout<<pos2<<endl;
        fout.write((char*)&newFriend, sizeof(newFriend));
    }
    cout<<"size:"<<sizeFile<<endl;
    fout.seekp(-132L, ios::cur);
    fout.write((char*)&emptyFriend, sizeof(emptyFriend));
    fout.close();*/
}
