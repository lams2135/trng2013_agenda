// Lams 's Agenda Unittest
// Version 0.3 (Updating)
// Author : Lams Lupin
// Email : lams2135@gmail.com
// Special thanks to Idiot Chuang

#include <gtest/gtest.h>

#include "../src/Date.h"
#include "../src/User.h"
#include "../src/Meeting.h"
#include "../src/UserManage.h"
#include "../src/MeetingManage.h"
#include "../src/FileManage.h"
#include "../src/AgendaService.h"

TEST(Date,Constructor) {
	Date a(1993,12,1,13,14);
	EXPECT_EQ(1993,a.getYear());
	EXPECT_EQ(12,a.getMonth());
	EXPECT_EQ(1,a.getDay());
	EXPECT_EQ(13,a.getHour());
	EXPECT_EQ(14,a.getMinute());
}

TEST(Date,SetGetOp) {
	Date b(1234,1,1,1,1);
	b.setYear(1994);
	b.setMonth(8);
	b.setDay(19);
	b.setHour(23);
	b.setMinute(59);
	EXPECT_EQ(1994,b.getYear());
	EXPECT_EQ(8,b.getMonth());
	EXPECT_EQ(19,b.getDay());
	EXPECT_EQ(23,b.getHour());
	EXPECT_EQ(59,b.getMinute());
}

TEST(Date,CompOp) {
	Date c,d,e;
	e.setMinute(3);
	EXPECT_TRUE(c==d);
	EXPECT_TRUE((d<=e)&&(d<e));
	EXPECT_TRUE((e>c)&&(e>=c));
}

TEST(Date,StaticFunc) {
	Date f(-1,12,1,0,0);
	EXPECT_FALSE(Date::isValid(f));
	f.setYear(1993);
	EXPECT_TRUE(Date::isValid(f));
	std::string stra = Date::dateToString(f);
	EXPECT_TRUE(f==Date::stringToDate(stra));
	EXPECT_EQ("1993-12-01/00:00",stra);
}

TEST(User,FullTest) {
	User a("KEN","123","DK@xx","188");
	a.setName("BEN");
	a.setPassword("456");
	a.setEmail("fuckyou@hehe.com");
	a.setPhone("3838438");
	EXPECT_EQ("BEN",a.getName());
	EXPECT_EQ("456",a.getPassword());
	EXPECT_EQ("fuckyou@hehe.com",a.getEmail());
	EXPECT_EQ("3838438",a.getPhone());
}

TEST(User,funcFindUserByName) {
	UserManage *ins = UserManage::getInstance();
	ins->createUser("Ken","123","213","438");
	ins->createUser("MSTC","222","fuckyou@microsoft.com","213");
	EXPECT_TRUE(ins->findUserByName("MSTC"));
	EXPECT_FALSE(ins->findUserByName("LLM"));
	EXPECT_TRUE(ins->findUserByName("Ken"));
	EXPECT_EQ(ins->findUserByName("MSTC")->getEmail(),"fuckyou@microsoft.com");
	EXPECT_EQ(ins->findUserByName("Ken")->getPhone(),"438");
	delete ins;
}

TEST(User,funcDeleteUser) {
	UserManage *ins = UserManage::getInstance();
	EXPECT_TRUE(ins);
	ins->createUser("HLD","123","fff","198");
	ins->createUser("CTEG","234","ddd","222");
	EXPECT_TRUE(ins->findUserByName("CTEG"));
	EXPECT_TRUE(ins->deleteUser(User("CTEG","234","ddd","222")));
	EXPECT_FALSE(ins->deleteUser(User("CTEG","","","")));
	EXPECT_FALSE(ins->findUserByName("CTEG"));
	delete ins;
}

TEST(Meeting,addMeeting) {
	Date dtmpa_(2013,9,30,13,0);
	Date dtmpb_(2013,12,1,0,14);
	Date dtmpc_(2012,6,6,0,0);
	Date dtmpd_(2013,10,1,0,0);
	Date dtmpe_(2013,6,8,0,0);
	MeetingManage* p = MeetingManage::getInstance();
	EXPECT_TRUE(p->addMeeting("Lams","Silly",dtmpa_,dtmpb_,"App1"));
	EXPECT_FALSE(p->addMeeting("ctsc_","Candy",dtmpb_,dtmpa_,"App2"));
	EXPECT_FALSE(p->addMeeting("Lams","cmsc_",dtmpa_,dtmpb_,"App3"));
	EXPECT_TRUE(p->addMeeting("huangl333","hLR",dtmpa_,dtmpb_,"App4"));
	EXPECT_FALSE(p->addMeeting("a","b",dtmpa_,dtmpb_,"App1"));
	EXPECT_TRUE(p->addMeeting("Lams","cmsc_",dtmpc_,dtmpe_,"App5"));
	EXPECT_FALSE(p->addMeeting("Silly","MSTC",dtmpe_,dtmpd_,"App6"));
	delete p;
}

TEST(File,User) {
	std::list<User> users_, utmp_;
	users_.push_back(User("Ken","123","X","X"));
	users_.push_back(User("Lams Lupin","Iloveyou 1314","E","D"));
	users_.push_back(User("MSTC","233","fuckyou@123.com","E"));
	FileManage *p = FileManage::getInstance();
	p->writeUsersToFile(users_);
	utmp_ = p->readUsersFromFile();
	bool futst1 = false;
	bool futst2 = false;
	for (std::list<User>::iterator i = utmp_.begin();
	     i != utmp_.end(); ++i) {
		if (i->getName() == "MSTC" && i->getEmail() == "fuckyou@123.com")
			futst1 = true;
		if (i->getName() == "Ken" && i->getPassword() == "123")
			futst2 = true;
	}
	EXPECT_TRUE(futst1);
	EXPECT_TRUE(futst2);
	delete p;
}

TEST(File,Meeting) {
	Date dtmpa_(1993,12,1,13,0);
	Date dtmpb_(2013,9,30,0,14);
	Date dtmpc_;
	std::list<Meeting> meetings_, mtmp_;
	meetings_.push_back(Meeting("Lams","Silly",dtmpa_,dtmpb_,"App"));
	meetings_.push_back(Meeting("Kevin","cmsc_",dtmpb_,dtmpa_,"Er"));
	bool fmtst1 = false;
	bool fmtst2 = false;
	FileManage *p = FileManage::getInstance();
	p->writeMeetingsToFile(meetings_);
	mtmp_ = p->readMeetingsFromFile();
	for (std::list<Meeting>::iterator i = mtmp_.begin();
	     i != mtmp_.end(); ++i) {
		if (i->getTitle() == "Er" && i->getParticipator() == "cmsc_")
			fmtst1 = true;
		if (i->getSponsor() == "Lams" && i->getParticipator() == "Silly")
			fmtst2 = true;
		if (i->getTitle() == "App")
			dtmpc_ = i->getStartDate();
	}
	EXPECT_TRUE(fmtst1);
	EXPECT_TRUE(fmtst2);
	EXPECT_EQ(dtmpa_,dtmpc_);
	delete p;
}

TEST(AgendaService,FullTest) {
	AgendaService ser;
	std::string dtmpa_ = Date::dateToString(Date(2013,9,30,13,0));
	std::string dtmpb_ = Date::dateToString(Date(2013,12,1,0,14));
	std::string dtmpc_ = Date::dateToString(Date(2012,6,6,0,0));
	std::string dtmpd_ = Date::dateToString(Date(2013,10,1,0,0));
	std::string dtmpe_ = Date::dateToString(Date(2013,6,8,0,0));
	std::string dtmpg_ = Date::dateToString(Date(999,0,0,0,0));
	std::string dtmph_ = Date::dateToString(Date(1993,9,30,4,68));
	
	EXPECT_TRUE(ser.userRegister("Lams","1","2","3"));
	EXPECT_TRUE(ser.userRegister("cmsc_","1","2","3"));
	EXPECT_TRUE(ser.userRegister("Idiot","1","2","3"));
	EXPECT_FALSE(ser.userRegister("cmsc_","1","2","333"));

	EXPECT_FALSE(ser.createMeeting("Lams","K","Idiot",dtmph_,dtmpb_));
	EXPECT_FALSE(ser.createMeeting("cmsc_","A","Lams",dtmpg_,dtmpa_));
	EXPECT_TRUE(ser.createMeeting("Lams","A","Idiot",dtmpa_,dtmpb_));
	EXPECT_FALSE(ser.createMeeting("cmsc_","B","Idiot",dtmpb_,dtmpa_));
	EXPECT_FALSE(ser.createMeeting("Lams","C","cmsc_",dtmpa_,dtmpb_));
	EXPECT_FALSE(ser.createMeeting("cmsc_","D","hLR",dtmpa_,dtmpb_));
	EXPECT_FALSE(ser.createMeeting("cmsc_","A","Idiot",dtmpc_,dtmpe_));
	EXPECT_TRUE(ser.createMeeting("cmsc_","E","Lams",dtmpc_,dtmpe_));
	
	EXPECT_TRUE(ser.meetingQuery("A"));
	EXPECT_TRUE(ser.meetingQuery("E"));
	EXPECT_FALSE(ser.meetingQuery("B"));
	EXPECT_FALSE(ser.meetingQuery("C"));
	
	EXPECT_FALSE(ser.deleteMeeting("Lams","F"));
	EXPECT_TRUE(ser.deleteMeeting("Lams","A"));
	EXPECT_TRUE(ser.deleteMeeting("cmsc_","E"));
	EXPECT_FALSE(ser.meetingQuery("A"));
	EXPECT_FALSE(ser.meetingQuery("E"));
	EXPECT_FALSE(ser.deleteMeeting("Lams","A"));
	EXPECT_FALSE(ser.deleteMeeting("Lams","E"));

}

GTEST_API_ int main(int argc, char **argv) {
	printf("Running main() from gtest_main\n");
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
