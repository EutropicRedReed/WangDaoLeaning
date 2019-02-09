#include "func.h"

int main()
{
	//openlog("log",LOG_PID|LOG_CONS|LOG_NOWAIT,LOG_USER);
	syslog(LOG_ALERT,"this is alert\n");
	syslog(LOG_INFO,"this is info\n");
	syslog(LOG_DEBUG,"this is debug%d\t %s",10,"aaaa");
	syslog(LOG_ERR,"err");
	syslog(LOG_CRIT,"crit");
	//closelog();
}
