#ifndef _TCPLIB_H
#define _TCPLIB_H

#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <unistd.h>
#include <fcntl.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>

/**
 * tcplib �õ��Ĵ����.
 */
enum TCPLIB_ERRNO
{
	ERR_TCPLIB_CONNECT = -2,	/** ����ʧ�� */
	ERR_TCPLIB_TIMEOUT = -3,	/** ��ʱ */
	ERR_TCPLIB_RECVFAILED = -4, /** ���ձ���ʧ�� */
	ERR_TCPLIB_SENTFAILED = -5, /** ���ͱ���ʧ�� */
	ERR_TCPLIB_VERSION = -10,	/** �汾���� */
	ERR_TCPLIB_HEADER = -11,	/** ����ͷ��ʽ���� */
	ERR_TCPLIB_TOOLONG = -12,	/** �������ݹ��� */
	ERR_TCPLIB_OPENFILE = -20,	/** ���ļ����� */
	ERR_TCPLIB_RESUMEPOS = -21, /** ����λ�ô��� */
	ERR_TCPLIB_OTHERS = -100	/** �������󣬿ɴ� errno ��ô�����Ϣ */
};

/**
 * �������͵� TCP ���Ӻ���.
 * ��������÷����׼�� connect() �����ǳ����ƣ�Ψһ�����������û�
 * �����Լ�ָ�� TCP ���ӹ��̵ĳ�ʱʱ�䡣��������ʱ����û�ܳɹ���
 * ������Ŀ�꣬�����س�ʱ����ǰ������������������ connect() ��ȫ
 * ��ͬ�����һ�������ǳ�ʱʱ�䡣�������������ʵ����ο� UNPv1e2
 * �� 411 ҳ��
 *
 * @param sockfd socket ������
 * @param saptr ָ����Ŀ��������ַ�ṹ��ָ��
 * @param salen ��ַ�ṹ�ĳ���
 * @param msec ���ӹ��̵ĳ�ʱʱ�䣬��λ����
 * @return ==0 ���ӳɹ�
 *         <0  ����ʧ��
 * @see connect()
 */
int NonBlockConnectEx(int sockfd, const struct sockaddr *saptr,
					  socklen_t salen, const int msec, const int conn);

#endif /* _TCPLIB_H */
