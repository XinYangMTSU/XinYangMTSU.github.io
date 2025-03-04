#include "SocialNetwork.h"

int main() {
    //creates an object sn of the SocialNetwork class.
    SocialNetwork sn;

    // Adding users
    sn.addUser("Alice");
    sn.addUser("Bob");
    sn.addUser("Charlie");
    sn.addUser("David");
    sn.addUser("Eve");

    // Establishing friendships
    sn.addFriendship("Alice", "Bob");
    sn.addFriendship("Alice", "Charlie");
    sn.addFriendship("Bob", "David");
    sn.addFriendship("Charlie", "Eve");
    
    // Display user friends
    sn.displayFriends("Alice");
    sn.displayFriends("Bob");

    // Suggest new friends
    sn.suggestFriends("Alice");
    sn.suggestFriends("David");

    return 0;
}
