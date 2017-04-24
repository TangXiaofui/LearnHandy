#include <vector>
#include <string.h>
#include <string>

namespace txh{
	using namespace std;

class Slice{
public:
	Slice():pb(""){ pe = pb;}
	Slice(const char *b,const char *e):pb(b),pe(e){}
	Slice(const char *b,size_t n):pb(b),pe(b+n){}
	Slice(const string &str):pb(str.data()),pe(str.data() + str.size()){}
	Slice(const char *b):pb(b),pe(b+strlen(b)){}

	const char* data() const { return pb ;}
	const char* begin() const { return pb ;}
	const char* end() const { return pe;}
	char front(){ return *pb; }
	char back() { return pe[-1]; }
	size_t size() const{ return pe - pb; }
	void resize(size_t sz){ pe = pb + sz; }
	inline bool empty() const { return pb == pe; }
	void clear(){ pb = pe = ""; }

	Slice eatWord();
	Slice eatLine();
	Slice eat(int sz) { Slice t(pb,sz); pb += sz; return t;}
	Slice sub(int boff,int sz){ Slice s(*this); s.pb += boff; s.pe = s.pb + sz ; return s;}
	Slice& trimSpace();

	inline char operator[](size_t n){ return pb[n]; }

	string toString() const { return string(pb,pe); }

	int compare(const Slice & rb )const;

	bool startWith(const Slice &x)const;
	bool endWith(const Slice &x)const;
	operator string() const {return string(pb,pe);}
	vector<Slice> split(char ch) const;
private:
	const char *pb;
	const char *pe;		
};

Slice Slice::eatWord(){
	const char *b = pb;
	while(b < pe && isspace(*b) ){
		++b;
	}
	const char *e = b;
	while(e < pe && !isspace(*e) ){
		++e;	
	}
	pb = e;
	return Slice(b,e-b);
}

Slice Slice::eatLine(){
	const char *b = pb;
	while(pb < pe && *pb != '\r'&& *pb != '\n')
		++pb;
	return Slice(b,pb-b);	
}

Slice& Slice::trimSpace(){
	while(pb < pe && isspace(*pb))
		++pb;
	while(pb < pe && isspace(pe[-1]))
		--pe;
	return *this;
}
	
int Slice::compare(const Slice& rb) const {
	size_t sz = size(),rsz = rb.size();
	const size_t min_sz = sz > rsz ? rsz : sz;
	int r = memcmp(pb,rb.pb,min_sz);
	if(r == 0){
		if(sz > rsz)
			r = 1;
		else if(sz < rsz)
			r = -1;
	}
	return r;
}

bool Slice::startWith(const Slice &x) const {
	return (size() >= x.size()) && (memcmp(pb,x.pb,x.size()) == 0);	
}

bool Slice::endWith(const Slice &x) const {
	return (size() >= x.size()) && (memcmp(pe-x.size(),x.pb,x.size()) == 0);
}

vector<Slice> Slice::split(char ch) const {
	vector<Slice> res;
	const char *p1 = pb;
	for(const char *p2 = pb ; p2 != pe ; ++p2)
	{
		if(*p2 == ch)
		{
			res.push_back(Slice(p1,p2));
			p1 = p2+1;	
		}	
	}
	if(p1 != pe)
		res.push_back(Slice(p1,pe));
	return res;
}
}
