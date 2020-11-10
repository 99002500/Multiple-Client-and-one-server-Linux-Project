compile:
	gcc -Wall -g3 -fsanitize=address -pthread chatroom.c -o chatroom
	gcc -Wall -g3 -fsanitize=address -pthread chatroomclient.c -o chatroomclient
