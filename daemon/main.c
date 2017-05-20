#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <syslog.h>

struct flock lock;

int set_pid()
{
    int ret;
    int fd = -1;
    #define TEMP_BUF_LEN    16
    char temp_buf[TEMP_BUF_LEN];

    fd = open("/tmp/daemon.pid", O_WRONLY|O_CREAT, 0644);
    if (fd < 0) {
        syslog(LOG_ERR, "open /tmp/daemon.pid error: %s\n", strerror(errno));
        return -1;
    }

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    ret = fcntl(fd, F_SETLK, &lock);
    if (ret < 0) {
        syslog(LOG_ERR, "lock pid file error: %s\n", strerror(errno));
        return -1;
    }

    ret = ftruncate(fd, 0);
    if (ret < 0) {
        syslog(LOG_ERR, "truncate file error: %s\n", strerror(errno));
        return -1;
    }

    memset(temp_buf, 0, TEMP_BUF_LEN);
    snprintf(temp_buf, TEMP_BUF_LEN, "%d", getpid());
    ret = write(fd, temp_buf, strlen(temp_buf));
    if (ret != strlen(temp_buf)) {
        syslog(LOG_ERR, "write /tmp/daemon.pid error\n");
        return -1;
    }

    return 0;
}

int main()
{
    int i;
    pid_t id;

    // fork, background
    id = fork();
    if (id < 0)
        exit(-1);

    if (id > 0)
        exit(0);

    // new session, detech from terminal and create new session
    if (setsid() < 0)
        exit(-1);

    // fork again, ensure that daemon can never re-acquire a terminal again
    id = fork();
    if (id < 0)
        exit(-1);

    if (id > 0)
        exit(0);

    // deal signal
    signal(SIGHUP, SIG_IGN);
    
    // deal file descriptors
    for (i = 0; i < getdtablesize(); i++)
        close(i);

    // deal mask
    syslog(LOG_NOTICE, "old mask = %d", umask(0));

    // deal dir, avoid unmount
    chdir("/");

    openlog("firstdaemon", LOG_PID, LOG_DAEMON);

    // set pid file lock
    set_pid();

    syslog (LOG_NOTICE, "First daemon started.");

    closelog();

    return 0;
}
