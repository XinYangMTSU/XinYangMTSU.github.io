#include "SocialNetwork.h"
#include <algorithm> // Required for find

// Add a new user to the network
void SocialNetwork::addUser(const string& user) {
    //Searches for user in friendList. Returns an iterator pointing to the key-value pair if found, or end() if not found.
    if (friendList.find(user) == friendList.end()) {
        friendList[user] = {}; // Initialize empty friend list (an empty vector)
    }
    //Do nothing if the user already exists
}

// Create a friendship (bi-directional edge)
void SocialNetwork::addFriendship(const string& user1, const string& user2) {
    
    // The function only adds friendships if both users exist:
    // Checks if user1 exists in friendList and Checks if user2 exists in friendList
    if (friendList.find(user1) != friendList.end() && friendList.find(user2) != friendList.end()) {
        //Adds user2 to user1's friend list (creates an edge from user1 --> user2).
        friendList[user1].push_back(user2); 
        //Adds user1 to user2's friend list (creates an edge from user2 --> user1).
        friendList[user2].push_back(user1);
    }
    else{
        
        // Print an error message if user1 does exist in friendList
        if(friendList.find(user1) == friendList.end())
            cout << "User " << user1 << " does not exist.\n";
        
        // Print an error message if user2 does exist in friendList
        if(friendList.find(user2) == friendList.end())
            cout << "User " << user2 << " does not exist.\n";
        
        return;
    }
}

//This function displays the list of friends for a given user in the Social Network.
void SocialNetwork::displayFriends(const string& user) const {
    
    // Print an error message if user does exist in friendList
    if (friendList.find(user) == friendList.end()) {
        cout << "User " << user << " does not exist.\n";
        return;
    }
    // Display User’s Friends if user exists in friendList
    cout << user << "'s friends: ";
    //This range-based for loop iterates through the list of friends of a given user and prints their names.
    for (const string& friendName : friendList.at(user)) {
        cout << friendName << " ";
    }
    cout << endl;
}

// This function suggests new friends for a given user based on mutual friends (friends-of-friends).
void SocialNetwork::suggestFriends(const string& user) const{
    
    // Print an error message if user does exist in friendList
    if (friendList.find(user) == friendList.end()) {
        cout << "User " << user << " does not exist.\n";
        return;
    }

    set<string> suggestions;
    //Loops through all direct friends of the user.
    for (const string& friendName : friendList.at(user)) {
        //Loops through each friend's friends (friends-of-friends).
        for (const string& friendOfFriend : friendList.at(friendName)) {
            //Filter Out Invalid Suggestions
            //Checks if friendOfFriend is already a direct friend. If it's not found, then it's a valid suggestion.
            if (friendOfFriend != user && find(friendList.at(user).begin(), friendList.at(user).end(), friendOfFriend) == friendList.at(user).end()) {
                suggestions.insert(friendOfFriend); //add friendOfFriend to friend suggestions if it is a valid suggestion
            }
        }
    }

    //Display Suggested Friends
    if (suggestions.empty()) {
        cout << "No friend suggestions for " << user << ".\n";
    } else {
        cout << "Friend suggestions for " << user << ": ";
        for (const string& suggestion : suggestions) {
            cout << suggestion << " ";
        }
        cout << endl;
    }
}
