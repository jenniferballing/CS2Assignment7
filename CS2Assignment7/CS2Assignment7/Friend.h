#ifndef FRIEND_H
#define FRIEND_H
#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

typedef	struct friendStruct
	{
		char Name [30];
		char Interests[100];
		int Age;
		
	}FRIEND_STRUCT;
class Friend
{	
public:
	Friend(void);
    void addAFriend();
    void removeFriend();
	/*void resetToDefault(FRIEND_STRUCT friendArr[], int size);
	void AddFriend (FRIEND_STRUCT friendArr[], int size);
	void RemoveFriend(FRIEND_STRUCT friendArr[], int size);
	void SearchInterest(FRIEND_STRUCT friendArr[], int size, string keywords);
	void DisplayFriend (FRIEND_STRUCT friendArr[], int size);
	void ListFriend (FRIEND_STRUCT friendArr[], int size);
	bool IsBefore(FRIEND_STRUCT friend1, FRIEND_STRUCT friend2);
	float ReportAge (FRIEND_STRUCT friendArr[], int size);
	void BubbleSort (FRIEND_STRUCT friendArr[ ], int size);*/
	~Friend(void);
};

#endif