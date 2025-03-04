#ifndef SOCIALNETWORK_H
#define SOCIALNETWORK_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
using namespace std;

class SocialNetwork {
    private:
        // Create an adjacency list using unordered_map
        // Key (string) --> Represents a user name (or node)
        // Value (vector<string>) --> Stores a list of connected friends (or adjacent nodes)
        unordered_map<string, vector<string>> friendList;

    public:
        void addUser(const string& user); //Pass-by-constant-reference
        //establishes a friendship (connection) between two users in a social network
        void addFriendship(const string& user1, const string& user2); //Pass-by-constant-reference
        //displays the list of friends of a given user
        void displayFriends(const string& user) const;
        void suggestFriends(const string& user) const;
        /* The const at the end of the function declaration applies to the entire function 
        and ensures that the function does not modify any member variables of the class.*/
};

#endif
