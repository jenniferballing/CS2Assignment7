#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <string.h>
#include <sstream>

using namespace std;

typedef struct Friend
{
	char name [30];
	char interests [100];
	short age;

}FRIEND;

void AddFriend();
void RemoveFriend();
void ModifyFriend ();
void SearchFriend ();
void ListFriend();
void DisplayFriend();

int fileSize(const char* fileName);
void fileType();
void menu();

int main()
{

    fileType();
    menu();   
	
	return 0;
}

void menu()
{
    char input=' ';
    while(input!='e' && input!='E')
    {
        cout<<endl<<"**********************************************************"<<endl;
        cout<<"***Network of My Friends***"<<endl;
        cout<<"A: Add a Friend"<<endl;
        cout<<"R: Remove a Friend by ID Number"<<endl;
        cout<<"M: Modify a Friend's Information by ID Number"<<endl;
        cout<<"S: Search Interests"<<endl;
        cout<<"D: Display \"myNetwork.dat\" Database Information"<<endl;
        cout<<"L: List the Oldest and the Youngest Friends' Information"<<endl;
        cout<<"E: Exit"<<endl;
        cout<<endl<<"**********************************************************"<<endl;

        cin>>input;
        if(input=='a' || input == 'A')AddFriend();
        else if(input=='r' || input == 'R') RemoveFriend();
        else if(input=='m' || input == 'M') ModifyFriend();
        else if(input=='s' || input == 'S') SearchFriend();
        else if(input=='d' || input == 'D') DisplayFriend();
        else if(input=='l' || input == 'L') ListFriend();
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
}
int fileSize(const char* fileName)
{
	fstream fin(fileName, ios::in | ios::binary);
	fin.seekg(0L, ios::end);
	return (int)fin.tellg();
}
void fileType()
{
    fstream fout("myNetwork.dat");
    char input;

	//FILE ALREADY EXISTS
	if(fout.fail())
	{
        fout.open("myNetwork.dat", ios::in | ios::out | ios::binary | ios::ate);
	}
	//FILE DOES NOT EXIST
	else
	{
		cout<<"myNetwork.dat already exists. Would you like to override it? (y/n)"<<endl;
		cin>>input;
        if(input=='y' ||input=='Y')
        {
            fout.close();
            fout.open("myNetwork.dat", ios::in | ios::out | ios::binary | ios::trunc);
		}
		else if (input=='n' || input == 'N')
		{
            fout.open("myNetwork.dat", ios::in | ios::out | ios::binary | ios::ate);
		} 
        else
        {
            while(input!='y' && input!='Y' && input!='n' && input!='N')
		    {
			    cout<<"Please choose whether or not to override the file. (y/n)"<<endl;
			    cin>>input;
		    }
        }
    }
}
void AddFriend()
{
	string newName;
	string newInterests;
	string newAge;
	
	//GET INFO FROM USER
    cin.clear();
	cin.sync();

	cout<<"What is the name of the friend you would like to add?"<<endl;
	getline(cin, newName);
    if(newName.size()>29)
    {
		cout<<"Your friend's name is too long. Please try again with fewer characters."<<endl;
		getline(cin, newInterests);
	}
	cout<<"What are the interests of your friend?"<<endl;
	getline(cin, newInterests);
    if(newInterests.size()>99)
    {
		cout<<"Your friend has too many interests. Please try again with fewer characters."<<endl;
		getline(cin, newInterests);
	}
	cout<<"What is the age of your friend?"<<endl;
	getline(cin, newAge);

    int num=0;
    while(num<newAge.size())
    {
        if(!isdigit(newAge[num]))
        {
            cout<<"Please indicate the age of your friend using only digits..."<<endl;
            cin>>newAge;
        }num++;
    }
    int age;
    stringstream ss(newAge);
    ss>>age; 

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
	newFriend.age=age;

    fstream fout;
    fout.open("myNetwork.dat", ios:: in | ios:: out | ios::binary | ios::ate);

	//PUT STRUCT INTO FILE 
	fout.write((char*)&newFriend, sizeof(newFriend));

	//TELL USER THE ID
    fout.close();
	long sizeFile= fileSize("myNetwork.dat");
	int sizeObj= sizeof(newFriend);
	int id=sizeFile/sizeObj;
	cout<<"The record number of this friend is: "<<id<<endl;
	
}
void RemoveFriend()
{
    char RUSure;
    long chosen;
    long offset= sizeof(FRIEND)*2;
    FRIEND storage;

    FRIEND empty;
    memcpy(empty.name, "Empty", 5);
    memcpy(empty.interests, "Empty", 5);
    empty.age= 0;

    //TRUNC or ATE
    fstream fout;
    fout.open("myNetwork.dat", ios:: in | ios:: out | ios::binary | ios::ate);
    
    cout<<"What is the ID number of the friend you would like to delete?"<<endl;
    cin>>chosen;

    int numIndex = fileSize("myNetwork.dat")/132;
    while(chosen>numIndex || chosen<0)
    {
        cout<<"This selection is out of range. Please enter the ID of the friend you would like to delete."<<endl;
        cin>>chosen;
    } 
    
    int sizeObj= sizeof(FRIEND);
	long starting = sizeObj*chosen;
        
    fout.seekg((chosen-1)*sizeof(storage), ios::beg);
    fout.read((char *)&storage, sizeof(storage));
    
    //VALIDATE
    cout<<"The indicated friend object information is: "<<endl;
    for( int i=0; i<30; i++)
    {
        if(storage.name[i]!='-')cout<<storage.name[i];
    }cout<<endl;
    for( int i=0; i<100; i++)
    {
        if(storage.interests[i]!='-')cout<<storage.interests[i];
    }cout<<endl;
    cout<< storage.age<<endl;
    
    cout<<"Do you intend to delete the indicated Friend object from the disk file? \nPress Y to delete this Friend object. Press N to cancel this deletion."<<endl;
    
    cin>>RUSure;
    if(RUSure!='y' && RUSure!='Y' && RUSure!='N' && RUSure!='n')
    {
        cout<<RUSure<<" is not valid.\nWould you like to delete this friend?"<<endl;
        cin>>RUSure;
    }
    if(RUSure=='n' || RUSure=='N')return;
    if (RUSure=='Y' || RUSure=='y')
    {
        for(int i=chosen; i<numIndex; i++)
        {
            fout.seekg(i*sizeof(storage), ios::beg);
            fout.read((char *)&storage, sizeof(storage));
            fout.seekp(-offset, ios::cur);
            fout.write((char*)&storage, sizeof(storage));
        }
        fout.seekp(-132, ios::end);
        fout.write((char*)&empty, sizeof(empty));
    }    
    fout.close();
}
void ModifyFriend()
{
    FRIEND storage;
    char sure;
    long chosen;
    cout<<"What is the ID number of the friend you would like to modify?"<<endl;
    cin>>chosen;

    fstream fout;
    fout.open("myNetwork.dat", ios:: in | ios:: out | ios::binary | ios::ate);

    int numIndex = fileSize("myNetwork.dat")/132;
    while(chosen>numIndex || chosen<0)
    {
        cout<<"This selection is out of range. Please enter the ID of the friend you would like to delete."<<endl;
        cin>>chosen;
    }

    string newName;
	string newInterests;
	string newAge;
	
	//GET INFO FROM USER
    cin.clear();
	cin.sync();
    
	cout<<"What is the name of the friend you would like to add?"<<endl;
	getline(cin, newName);
    if(newName.size()>29)
    {
		cout<<"Your friend's name is too long. Please try again with fewer characters."<<endl;
		getline(cin, newInterests);
	}
	cout<<"What are the interests of your friend?"<<endl;
	getline(cin, newInterests);
    if(newInterests.size()>99)
    {
		cout<<"Your friend has too many interests. Please try again with fewer characters."<<endl;
		getline(cin, newInterests);
	}
	cout<<"What is the age of your friend?"<<endl;
	getline(cin, newAge);

    int num=0;
    while(num<newAge.size())
    {
        if(!isdigit(newAge[num]))
        {
            cout<<"Please indicate the age of your friend using only digits..."<<endl;
            cin>>newAge;
        }num++;
    }
    int age;
    stringstream ss(newAge);
    ss>>age;

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

    int sizeObj= sizeof(FRIEND);
	long starting = sizeObj*chosen;

    FRIEND newFriend;
	memcpy(newFriend.name, nName, sizeof(nName));
	memcpy(newFriend.interests, nInterests, sizeof(nInterests));
	newFriend.age=age;
        
    fout.seekg((chosen-1)*sizeof(storage), ios::beg);
    fout.read((char *)&storage, sizeof(storage));
    
    //VALIDATE
    cout<<endl<<endl<<"The indicated friend object information is: "<<endl;
    for( int i=0; i<30; i++)
    {
        if(storage.name[i]!='-')cout<<storage.name[i];
    }cout<<endl;
    for( int i=0; i<100; i++)
    {
        if(storage.interests[i]!='-')cout<<storage.interests[i];
    }cout<<endl;
    cout<< storage.age<<endl;
    
    cout<<endl<<endl<<"The new updated friend object information is: "<<endl;
    for( int i=0; i<30; i++)
    {
        if(newFriend.name[i]!='-')cout<<newFriend.name[i];
    }cout<<endl;
    for( int i=0; i<100; i++)
    {
        if(newFriend.interests[i]!='-')cout<<newFriend.interests[i];
    }cout<<endl;
    cout<< newFriend.age<<endl;

    cout<<"Do you intend to replace the indicated friend object with this new information? \nPress Y to preplace this information int he database.\nPress N to cancel this update."<<endl;
    cin>>sure;

    if(sure!='y' && sure!='Y' && sure!='N' && sure!='n')
    {
        cout<<sure<<" is not valid.\nWould you like to delete this friend?"<<endl;
        cin>>sure;
    }
    if(sure=='n' || sure=='N')return;
    if(sure=='Y' || sure=='y')
    {
        fout.seekp((chosen-1)*132, ios::beg);
        fout.write((char*)&newFriend, sizeof(newFriend));
    }fout.close();
}
void SearchFriend()
{
    FRIEND holder;
    string keyword;
    int fSize= fileSize("myNetwork.dat");

    cin.clear();
    cin.sync();
    cout<<"What is the keyword you would like to search for? "<<endl;
    getline(cin, keyword);

    fstream fout;
    fout.open("myNetwork.dat", ios::in | ios::out | ios::binary | ios::ate);

    int found=0;
    for( int i=0; i<fSize; i+=132)
    {
        fout.seekg(i, ios::beg);
        fout.read((char*)&holder, sizeof(holder));
        string str = holder.interests;
        int pos=str.find(keyword);
        if (pos!=std::string::npos)
        {
            cout<<"Name: ";
            for( int h=0; h<30; h++)
            {
                if(holder.name[h]!='-')cout<<holder.name[h];
            }
            cout<<endl;
            int ID = (i+132)/132;
            cout<<"ID: "<<ID<<endl;            
            found=1;
        }
    }
    if(found==0) cout<<"No matches were found for your keyword."<<endl;
}
void ListFriend()
{
    int oldest=0, i, j, youngest=100;
    FRIEND structCheck;
    
    fstream fout;
    fout.open("myNetwork.dat", ios::in | ios::out | ios::binary | ios::ate);
    cout<<"Here are your oldest and youngest friends (oldest first): "<<endl;
    
    //FIND THE OLDEST AND YOUNGEST AGE
    for(i=0; i<fileSize("myNetwork.dat"); i+=132)
    {
        fout.seekg(i, ios::beg);
        fout.read((char*)&structCheck, sizeof(structCheck));
        
        if(structCheck.age > oldest) oldest=structCheck.age; 
    }
    for(i=0; i<fileSize("myNetwork.dat"); i+=132)
    {
        fout.seekg(i, ios::beg);
        fout.read((char*)&structCheck, sizeof(structCheck));
        
        if(structCheck.age < youngest) youngest=structCheck.age; 
    }

    //PRINT THE OLDEST ONES
    for(j=0; j<fileSize("myNetwork.dat"); j+=132)
    {
        fout.seekg(j, ios::beg);
        fout.read((char*)&structCheck, sizeof(structCheck));

        if(structCheck.age==oldest) 
        {
            char tempN[30];
            char tempI[100];
            memcpy(tempN, structCheck.name, sizeof(structCheck.name));
            memcpy(tempI, structCheck.name, sizeof(structCheck.interests));
            
            cout<<"Name: ";
            for( int k=0; k<30; k++)
            {
                if(tempN[k]!='-') cout<<tempN[k];
            }cout<<endl;
            
            cout<<"Interests: ";
            for( int k=0; k<100; k++)
            {
                if(tempI[k]!='-') cout<<tempI[k];
            }cout<<endl;

            cout<<"Age: "<<structCheck.age<<endl<<endl;
        }
    }
    for(int l=0; l<fileSize("myNetwork.dat"); l+=132)
    {
        fout.seekg(l, ios::beg);
        fout.read((char*)&structCheck, sizeof(structCheck));
        
        //PRINT THE YOUNGEST
        if(structCheck.age==youngest) 
        {
            char tempN[30];
            char tempI[100];
            memcpy(tempN, structCheck.name, sizeof(structCheck.name));
            memcpy(tempI, structCheck.interests, sizeof(structCheck.interests));
            
            cout<<"Name: ";
            for( int k=0; k<30; k++)
            {
                if(tempN[k]!='-') cout<<tempN[k];
            }cout<<endl;
            
            cout<<"Interests: ";
            for( int k=0; k<100; k++)
            {
                if(tempI[k]!='-') cout<<tempI[k];
            }cout<<endl;

            cout<<"Age: "<<structCheck.age<<endl<<endl;
        }
    }    
    fout.close();
}
void DisplayFriend()
{
    int i=0, ID=1;

    fstream fout;
    fout.open("myNetwork.dat", ios::in | ios::out | ios:: ate | ios::binary);

    FRIEND structCheck;
    for(i=0; i<fileSize("myNetwork.dat"); i+=132)
    {
        fout.seekg(i, ios::beg);
        fout.read((char*)&structCheck, sizeof(structCheck));

        char tempN[30];
        char tempI[100];
        memcpy(tempN, structCheck.name, sizeof(structCheck.name));
        memcpy(tempI, structCheck.interests, sizeof(structCheck.interests));
            
        cout<<"ID: "<<ID<<endl;

        cout<<"Name: ";
        for( int k=0; k<30; k++)
        {
            if(tempN[k]!='-') cout<<tempN[k];
        }cout<<endl;
            
        cout<<"Interests: ";
        for( int k=0; k<100; k++)
        {
            if(tempI[k]!='-') cout<<tempI[k];
        }cout<<endl;

        cout<<"Age: "<<structCheck.age<<endl<<endl;
        ID++;
    }fout.close();
}
