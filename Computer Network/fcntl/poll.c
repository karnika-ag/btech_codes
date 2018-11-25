#include<stdio.h>
#include <stropts.h>
#include <poll.h>
#include <fcntl.h>

int main() {

    struct pollfd fds[2];
    int timeout_msecs = -1;
    int ret;
    int i;

    /* Open STREAMS device. */
    fds[0].fd = open("f1.txt", O_RDONLY);
    fds[1].fd = open("f2.txt", O_RDONLY);
    fds[0].events = POLLOUT | POLLWRBAND;
    fds[1].events = POLLOUT | POLLWRBAND;

    while (1) {
        ret = poll(fds, 2, timeout_msecs);

        if (ret > 0) {
            /* An event on one of the fds has occurred. */
            for (i = 0; i < 2; i++) {
                if (fds[i].revents != 0) {
                    /* Priority data may be written on device number i. */
                    printf(
                            "Priority Data may be written on device number %d POLLWRBAND\n",
                            i);

                }
                if (fds[i].revents = !0) {
                    /* Data may be written on device number i. */
                    printf("Data may be written on device number %d POLLOUT\n",
                            i);
                }
                if (fds[i].revents = !0) {
                    /* A hangup has occurred on device number i. */
                    printf("A hangup has occurred on device number %d\n", i);

                }
            }
        }
    }
    return 0;
}
