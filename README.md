##FriendZoneChat 

- FriendZoneChat is a simple C++ console-based application that allows users to:
- Register and log in.
- Manage friends by adding or removing them.
- Chat with friends in real-time, with messages saved to a text file.
- View previous chat conversations in an inbox.
- Log out securely.
**Features**
- User Registration & Login: Create accounts and log in to access friends and chats.
- Friend Management: Add friends, with automatic updates to both users' friend lists.
- Real-time Chat: Chat in a console-based environment, with timestamped messages saved.
- Inbox: View past conversations.
- Data Persistence: Data is stored in text files, including credentials, friend lists, and chats.
**Files**
- Database.txt: Stores usernames and passwords.
- username_friendList.txt: Stores the friend list for each user.
- user1_user2_chat.txt: Stores chat history between two users.
**How to Use**
- Sign Up: Create an account with a username and password.
- Login: Access your account with the credentials.
- Add Friends: Provide usernames to add friends. This updates both users' lists.
- chat: Select a friend to start chatting. All chats are saved.
- Inbox: View previous chat conversations with friends.
- Logout: Securely log out
**Future Improvements**
- Add a feature to remove friends.
- Encrypt passwords for security.
- Implement a graphical user interface (GUI)
**How to Run**
- cd FriendZoneChat
- g++ -o FriendZonechat FriendZonechat.cpp
- ./FriendZonechat
