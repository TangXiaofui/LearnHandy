#include "UnitTest.h"
#include "file.h"
#include "conf.h"
#include "util.h"
#include "Slice.h"
#include "status.h"
#include "daemon.h"
#include "logging.h"
using namespace txh;
using namespace std;

TEST(TestLog)
{
	Logger::getLogger().setFileName("test.log");
	Logger::getLogger().setLogLevel("trace");
	Logger::getLogger().setRotateInterval(5);
	int i = 0;
	while(1)	
	{
		//debug("This is %s\n","debug");
		Logger::getLogger().logv(3,__FILE__,__LINE__,__func__,"this is a %d\n",i); 
		sleep(1);
		i++;
		exitif(i == 10,"timeout");
	}
}

TEST(TestFile)
{
	ASSERT_EQ(File::fileExist("test"),true);
	ASSERT_EQ(File::fileExist("t"),false); 
	uint64_t size;
	File::getFileSize("test",&size);
	cout << size << endl;
	File::createDir("abc");
	File::deleteDir("def");
	string cont;
	File::getContent("tags",cont);
	File::renameSave("tags_bak","tmp",cont);
	vector<string> res;
	File::getChildren("./",&res);
	for(auto r : res)
	{
		cout << r << endl;	
	}
}

TEST(TestStatus)
{
	Status t(Status::ioError("+","t"));
	Status t2(move(Status::fromSystem()));
	Status t3;
	t3 = t2;
	Status t4;
	t4 = move(t3);
	cout << t4.code() << " " << t4.msg() << endl;
	cout << t4.toString().c_str() << endl;

	
}

TEST(TestConf)
{
	LineScanner ls((char*)" [section] ");
	string section = ls.skipSpace().skip(1).consumeTill(']');
	Conf f;
	f.parse("./test.ini");
	cout << f.getInteger("section3","key1",0) << endl;
	cout << f.getBoolean("section3","key4",false) << endl;
	cout << f.getReal("section3","key3",0.0) << endl;
}

TEST(TestSlice)
{
	char *str = (char *)" abc def hij k ";
	Slice ss(str);
	cout << ss.begin() << endl;
	ss.trimSpace();
	ss.eatWord();
	cout << ss.begin() << endl;
	ss.eat(1);
	cout << ss.begin() << endl;
	vector<Slice> res = ss.split(' ');
	for(auto r : res)
	{
		cout << string(r).data() << endl;	
		cout << r.toString().data() << endl;
	}
}

TEST(TestUtil)
{
	time_t t;
	time(&t);
	cout << util::format("%s\n","test");
	cout <<	util::readableTime(t).data() << endl;	
	cout << atoi("123abc") << endl;
	cout << util::timeMilli() << endl;
	ExitCaller test([](){ cout << "destory" << endl;});
	cout << "Test Return" << endl;
}

void quitfunc()
{
	exit(0);
}

int main(int argc,char *argv[])
{
	if(argc > 1)
	{
		for(int i = 1 ; i < argc ;++i)
		{
			test::RunAllTests(argv[i]);	
		}
/*		char buf[64] = {0};
		snprintf(buf,64,"%s.pid",argv[0]);
		Daemon::daemonProcess(argv[1],buf);
		Signal::signal(SIGQUIT,quitfunc);
		sleep(300);
*/
	}
	else
	{
	    test::RunAllTests(NULL);
	}

	
	return 0;
}
