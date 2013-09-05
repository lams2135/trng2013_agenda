target:agenda

agenda:Date.o User.o Meeting.o UserManage.o MeetingManage.o \
       FileManage.o
#	g++ -o agenda Date.o User.o UserMange.o MeetingManage.o \
	   FileManage.o

Date.o:Date.h Date.cpp
	g++ -c Date.cpp

User.o:User.h User.cpp
	g++ -c User.cpp

Meeting.o:Meeting.h Meeting.cpp
	g++ -c Meeting.cpp

UserManage.o:UserManage.h UserManage.cpp
	g++ -c UserManage.cpp

MeetingManage.o:MeetingManage.h MeetingManage.cpp
	g++ -c MeetingManage.cpp

FileManage.o:FileManage.h FileManage.cpp
	g++ -c FileManage.cpp

clean:
	rm *.o *~
