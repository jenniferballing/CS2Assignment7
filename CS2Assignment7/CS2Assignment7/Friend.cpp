#include "Friend.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

Friend::Friend(void)
{
	
}
void Friend::addAFriend()
{
	
	//GET INFO FROM USER
	char name[30];
	char interests[100];
	int age;
	char input;
    int index=0;
    cin.clear();
    cin.sync();
	cout<<"What is the name of the friend you would like to add?"<<endl;
    //getline(cin, name);
	cin.getline(name, 30, '\n');
	cout<<"What are the interests of your friend?"<<endl;
    //getline(cin, interests);
	cin.getline(interests, 100, '/n');
	cout<<"What is the age of your friend?"<<endl;
    cin.getline((char*)age, 3, '\n');

	//PLACE INFO IN FILE
	fstream fout;
	fout.open("myNetwork.dat", ios::out | ios::binary);
	//if(!fout.fail()
	  //  cout<<"myNetwork.dat already exists. Would you like to override it?"<<endl;

		//if(input=='y'||input=='Y')//needs to overwrite
		//{
			fout.write((char*)&name, sizeof(name));
			fout.write((char*)&interests, sizeof(interests));
			fout.write((char*)&age, sizeof(age));
		/*}
		else//Append to existing file
		{
			fout.write(name, sizeof(name));
			fout.write(interests, sizeof(interests));
			fout.write(age, sizeof(age));
		}
	}*/
	index++;
	/*int sizeofObj= sizeof(Friend);
	int sizeofFile= sizeof("myNetwork.dat");
	int index=sizeofFile/sizeofObj;*/

	cout<<"The index of your friend is: "<<index<<endl;
}
void removeFriend()
{
    int input;
    cout<<"What is the index of the friend you would like to remove?"<<endl;
    cin>>input;

}
/*//Set all of the values back to default of "EMPTY", "EMPTY" and 0.
void Friend::resetToDefault(FRIEND_STRUCT friendArr[], int size)
{
	int i=0;
	for(i=0; i<size; i++)
	{
		friendArr[i].Name='EMPTY';
		friendArr[i].Interests="EMPTY";
		friendArr[i].Age=0;
	}
}

void Friend::AddFriend (FRIEND_STRUCT friendArr[], int size)
{
	string screenName="", interests="";
	int i=0, age=0;
	bool found=false;
	
	while (found==false)
	{
		for(i=0; i<size; i++)
		{
			if (friendArr[i].Name=="EMPTY" && friendArr[i].Age==0 && friendArr[i].Interests=="EMPTY")
			{
				//clear and sync allow me to use multiple getline functions
				cin.clear();
				cin.sync();
	
				//Get new friend input
				cout<<"*** Add a new friend profile \n";
				cout<<"ScreenName: \n";
				getline(cin, Name);
				cout<<"Interests: \n";
				getline(cin, Interests);
				cout<<"Age: \n";
				cin>> age;

				//Fill new friend info into available space
				friendArr[i].Name=screenName;
				if(age>=0)
				{
					friendArr[i].Age=age;
				}
				else
				{
					friendArr[i].Age=0;
					cout<<"All friends must have positive age numbers. This friend's age has been set to 0.\n";
				}
				friendArr[i].Interests=interests;
				found=true;
				return;
			}
		}
			
			//If no available index is found, inform user
			if(found==false)
			{
				cout<<"\nSorry, there is no available space.\n\n";
				return;
			}
		
	}
}	

void Friend::RemoveFriend(FRIEND_STRUCT friendArr[], int size)
{
	int i=0, j=0, emptySum=0;
	int indexChoice;
	for(j=0; j<size; j++)
	{
		if(friendArr[j].Name=="EMPTY")
		{
			emptySum+=1;
		}
	}
	if(emptySum==5)
	{
		cout<<"There are no friends to remove.\n";
		return;
	}
	else
	{
		cout<< "*** Remove a friend ***\n";
		for (int i=0; i<size; i++)
		{
			if(friendArr[i].Name!="EMPTY")
			{
				cout<< i <<". "<< friendArr[i].Name<< endl;
			}
		}
		cout<<"\nWhich to remove: ";
		cin>>indexChoice;
		if(indexChoice<5 && indexChoice>-1)
		{
			//Set the values back to the default
			friendArr[indexChoice].Name="EMPTY";
			friendArr[indexChoice].Interests="EMPTY";
			friendArr[indexChoice].Age=0;
		}
		else
		{
			cout<<"\nInvalid input.\n\n";
			return;
		}
	}
}

void Friend::SearchInterest(FRIEND_STRUCT friendArr[], int size, string keywords)
{
	int i=0, k=0, l=0;
	string tempInterests, screenName;
	string tempInterestsArr[5];
	
	//Check only occupied indexes- no need to check empty indexes for keywords
		
	//Put array values into temp arrays and change to lowercase
	for(i=0; i<size; i++)
	{
		if (friendArr[i].Name!="EMPTY" && friendArr[i].Age!=0 && friendArr[i].Interests!="EMPTY")
		{
			tempInterests=friendArr[i].Interests;
			transform(tempInterests.begin(), tempInterests.end(), tempInterests.begin(), ::tolower);
			tempInterestsArr[i]=tempInterests;

			//Make the keywords string lowercase
			transform(keywords.begin(), keywords.end(), keywords.begin(), :: tolower);

			//Compare lowercase interests to lowercase keywords
			if(tempInterestsArr[i]!="EMPTY")
			{
				for(l=0, k=0; k<tempInterests.length(); k++)
				{
					if(keywords[l]==tempInterests[k])
					{
						l++;
						if(l==keywords.length())
						{
							cout<< friendArr[i].Name<<endl;
							break;
						}
					}
					else
					{
						l=0;
					}
				}
			}
		}
	}
}

//Print the current values in the struct array.
void Friend::DisplayFriend (FRIEND_STRUCT friendArr[], int size)
{
	for (int i=0; i<size; i++)
	{
		if(friendArr[i].Name!="EMPTY")
		{
			cout<< "Index: "<<i<< endl;
			cout<< "ScreenName: "<<friendArr[i].Name<< endl;
			cout<< "Interests: " << friendArr[i].Interests<<endl;
			cout<< "Age: " << friendArr[i].Age<< endl<<endl;
		}
	}
}

void Friend::ListFriend (FRIEND_STRUCT friendArr[], int size)
{
	FRIEND_STRUCT tempArr[5];
	string testFr1, testFr2;
	int i=0, j=0;
	for(i=0; i<size; i++)
	{
		tempArr[i]=friendArr[i];
	}
	//int tempArrSize=tempArr.size();
	BubbleSort(tempArr, 5);//***figure out size
	for(j=0; j<5; j++)
	{
		if(tempArr[j].Name!="EMPTY")
		{
			cout<<tempArr[j].Name<<endl;
		}
	}	
	cout<<endl;
}

bool Friend::IsBefore(FRIEND_STRUCT friend1, FRIEND_STRUCT friend2)
{
	bool before=true;
	int length=3, i=0;
	//Create and initiallize temp variables
	string tempF1N=	friend1.Name;
	string tempF2N=	friend2.Name;
	int tempF1A=friend1.Age;
	int tempF2A=friend2.Age;

	//friendOne.ScreenName=friend1.ScreenName;
	//friendTwo.ScreenName=friend2.ScreenName;

	//Set all chars in temp variables to lowercase 
	transform(tempF1N.begin(), tempF1N.end(), tempF1N.begin(), ::tolower);
	transform(tempF2N.begin(), tempF2N.end(), tempF2N.begin(), ::tolower);
	
	//Find the shortest string
	if(tempF1N.length() > tempF2N.length())
	{
		length=tempF2N.length();
	}
	else if(tempF1N.length() < tempF2N.length())
	{
		length=tempF1N.length();
	}

	//Compare to find if it is before
	for(i=0; i<length-1; i++)
	{
		if(tempF1N[i]>tempF2N[i])
		{
			return false;
		}
		else if (tempF1N[i]!=tempF2N[i])
		{
			return true;
		}
	}
	//If the strings are equal, organize by age
	if(tempF1N==tempF2N)
	{
		if(tempF1A>tempF2A)
		{
			return false;
		}
		else if (tempF1A<tempF2A)
		{
			return true;
		}
		else
		{
			return true;
		}
	}
return before;
}

void Friend::BubbleSort (FRIEND_STRUCT friendArr[ ], int size)
	{
		bool done=false;
		int i=0, j=0, l=0;
		FRIEND_STRUCT a, b;
		while(!done)
		{
			done=true;
			for(i=0; i<size-1; i++)
			{
				if(! IsBefore(friendArr[i], friendArr[i+1]))
				{
					a=friendArr[i];
					b=friendArr[i+1];
					friendArr[i+1]=a;
					friendArr[i]=b;

					done=false;
				}
			}
			size--;
		}
	}

float Friend::ReportAge (FRIEND_STRUCT friendArr[], int size)
{
	int i=0, j=0;
	float numFriends=0, sum=0, average=0;
	
	//Count the number of friends in the array
	for(j=0; j<size; j++)
	{
		if(friendArr[j].ScreenName != "EMPTY")
		{
			numFriends++;
		}
	}
	//Find the sum of the ages
	for(i=0; i<size; i++)
	{
		if(friendArr[i].Age!=0 && friendArr[i].Interests!="EMPTY" && friendArr[i].ScreenName!="EMPTY")
		{
			sum+=friendArr[i].Age;
		}
		
	}
	//Find and return the average of the ages
	average=sum/numFriends;
	return average;
}*/
		
