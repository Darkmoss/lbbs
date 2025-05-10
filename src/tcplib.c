#include "tcplib.h"
#include "common.h"

int NonBlockConnectEx(int sockfd, const struct sockaddr *saptr, socklen_t salen,
					  const int msec, const int conn)
{
	int flags, ret, error;
	socklen_t len;
	fd_set rset, wset;
	struct timeval tval;

	/*
	 * ����Ϊ�������� socket
	 */
	flags = fcntl(sockfd, F_GETFL, 0);
	fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

	error = 0;
	if (conn == 1)
	{
		if ((ret = connect(sockfd, saptr, salen)) < 0)
		{
			if (errno != EINPROGRESS)
			{
				return ERR_TCPLIB_CONNECT; /* ����ʧ�� */
			}
		}

		/*
		 * Do whatever we want while the connect is taking place.
		 */
		if (ret == 0)
		{
			goto done; /* connect completed immediately */
		}
	}

	tval.tv_sec = msec / 1000;
	tval.tv_usec = msec % 1000 * 1000;

	while (!SYS_server_exit)
	{
		FD_ZERO(&rset);
		FD_SET(sockfd, &rset);

		FD_ZERO(&wset);
		FD_SET(sockfd, &wset);

		ret = select(sockfd + 1, &rset, &wset, NULL, &tval);

		if (ret == 0)
		{
			return ERR_TCPLIB_TIMEOUT; /* ���ӷ�������ʱ */
		}
		else if (ret < 0)
		{
			if (errno != EINTR)
			{
				return ERR_TCPLIB_OTHERS; /* select()���� */
			}
			continue;
		}

		if (FD_ISSET(sockfd, &rset) || FD_ISSET(sockfd, &wset))
		{
			len = sizeof(error);
			if (getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error, &len) < 0)
			{
				return ERR_TCPLIB_OTHERS; /* Solaris pending error */
			}
		}

		break;
	}

done:
	fcntl(sockfd, F_SETFL, flags); /* restore file status flags */

	if (error)
	{
		errno = error;
		return ERR_TCPLIB_CONNECT; /* ���ӷ�����ʧ�� */
	}

	return 0; /* ���ӷ������ɹ� */
}
