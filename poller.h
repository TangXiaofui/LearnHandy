#ifndef POLLER_H
#define POLLER_H
#include "channel.h"
#include <unistd.h>
#include "logging.h"
#include <string.h>
#include <errno.h>
#include <map>
#include <sys/epoll.h>
#include "util.h"
#include <atomic>
#include <set>

namespace txh{

using namespace std;
const int MaxEvent = 2000;
const int ReadEvent = POLLIN;
const int WriteEvent = POLLOUT;

struct PollerBase:private noncopyable{
	int64_t m_id;
	int m_lastActive;
	PollerBase():lastActive(-1){
		static atomic<int64_t> id(0);
		m_id = ++id; 
	}
	virtual ~PollerBase(){}
	virtual void addChannel(Channel *ch) = 0;
	virtual void removeChannel(Channel *ch) = 0;
	virtual void updateChannel(Channel *ch) = 0;
	virtual void loop_once(int waitMs) = 0;
};	

struct PollerEpoll:public PollerBase{
	int m_fd;
	set<Channel*> m_liveChannels;
	struct epoll_event m_activeEvents[MaxEvent];
	PollerEpoll();
	~PollerEpoll();
	virtual void addChannel(Channel *ch);
	virtual void removeChannel(Channel *ch);
	virtual void updateChannel(Channel *ch);
	virtual void loop_once(int waitMs);
};

PollerBase* createPoller();

}


#endif
