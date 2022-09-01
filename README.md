# SystemsProgramming
Project consist of 3 parts in total:

### Implementing a binary tree ### 
Insert, search, delete, delete subtree etc. 
<br/>
### Balancing the binary tree ###
Detect when a (sub-)tree goes out of balance. And second, we need a way to rearrange the nodes so that the tree is in balance again.
<br/>
### Simple file processing ###
Sample client commands are processed from a text document with commands such as: Insert, delete, delete subtree etc.
Read the client commands from the file and handle it accordingly.
<br/>
### Tackling race conditions ###
If two clients request a deletion operation, handle any race conditions that can occur. Basic idea of how to use mutex locks. 
