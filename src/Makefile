all : agenda install

install : user.dat meeting.dat

agenda : Date.o User.o Meeting.o UserManage.o MeetingManage.o \
         FileManage.o AgendaService.o AgendaController.o \
	     Agenda.o
	g++ -o agenda Date.o User.o Meeting.o \
	       UserManage.o MeetingManage.o \
	       FileManage.o AgendaService.o AgendaController.o \
	       Agenda.o

Date.o : Date.h Date.cpp
	g++ -c Date.cpp

User.o : User.h User.cpp
	g++ -c User.cpp

Meeting.o : Meeting.h Meeting.cpp
	g++ -c Meeting.cpp

UserManage.o : UserManage.h UserManage.cpp
	g++ -c UserManage.cpp

MeetingManage.o : MeetingManage.h MeetingManage.cpp
	g++ -c MeetingManage.cpp

FileManage.o : FileManage.h FileManage.cpp
	g++ -c FileManage.cpp

AgendaService.o : AgendaService.h AgendaService.cpp
	g++ -c AgendaService.cpp

AgendaController.o : AgendaController.h AgendaController.cpp
	g++ -c AgendaController.cpp

Agenda.o : Agenda.cpp AgendaController.h
	g++ -c Agenda.cpp

user.dat :
	touch user.dat

meeting.dat :
	touch meeting.dat

clean :
	rm *.o *~ agenda
