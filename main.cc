#include "UnitTest.h"
#include "Slice.h"
using namespace txh;
using namespace std;

TEST(TestSlice)
{
	char *str = " abc def hij k ";
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

int main(int argc,char *argv[])
{
	if(argc > 1)
	{
		for(int i = 1 ; i < argc ;++i)
		{
			test::RunAllTests(argv[i]);	
		}
	}
	else
	{
	    test::RunAllTests(NULL);
	}
	return 0;
}
