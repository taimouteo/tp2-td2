<title>School Project N°2: C Language</title>
<body>
The objective of this project is to implement a data structure that allows us to go through a dictionary of words efficiently and with this implement functions to predict a possible set of words based on a prefix.

From the following structures, a keysPredict is defined:
</body>
<img width="521" height="123" alt="image" src="https://github.com/user-attachments/assets/a2226630-31c2-4fed-95fd-ab05f74237cb" />
<body>
The keysPredict structure contains a pointer to a list of node lists. Each node represents a letter indicated by the character field. The next field points to the next letter within the same level, while the down field allows you to reach the next list of letters at a lower level. The end and word fields are related, as they indicate the complete word formed by the nodes from the first to the last. The end field indicates that that node is the end node of a word, while word is a pointer to the word stored for that node.
Within the main structure, in addition to the first pointer, there are two more fields. The totalKeys field indicates the total number of letters within the structure, while totalWords corresponds to the total number of words stored.
An example of the structure is illustrated below:
</body>
<img width="643" height="305" alt="image" src="https://github.com/user-attachments/assets/00341f9a-bf6d-49b0-a751-30281a7a2caf" />
<body>
In the example you can see how the first level of the structure is composed of the letters 'a', 'b', 'c', 'l' and 'p'. These are always stored in alphabetical order within the list. Then the down pointers point to the following lists, some may have a single element like the one that starts from the first node with an 'a', or they can have more elements, such as the next pointer. This first part of the structure manages to store the words 'ala' and 'ale'. The last letter being the only different one.
It is even possible to have words stored in an intermediate node, as is the case of the word 'lo', which a node further down constructs the word 'los'.
</body>
