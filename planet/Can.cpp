//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
//#include <net/if.h>
//#include <sys/ioctl.h>
//#include <sys/socket.h>
//#include <linux/can.h>
//#include <linux/can/raw.h>
//#include <iostream>
//#include "can.h"
//using namespace std;
//
//
////typedef struct vison_info_t
////{
////    u_int8_t sof;
////    int16_t yaw;
////    int16_t pitch;
////    int16_t dis;
////    u_int8_t others;
////}vision;
////vision vision_t;
//
//
////huxiao test
//int16_t adata[8] = { 0 };
//u_int8_t bdata[2] = { 0,0 };
//
//static int16_t Int16ToUint8_p(int16_t adata, u_int8_t bdata[])
//{
//	bdata[0] = (adata >> 8 & 0x00FF);
//	bdata[1] = (adata & 0x00FF);
//
//	return bdata[0];
//}
//
//int Can(int order) {
//
//	/*if (find == 1) {
//		fire = 1;
//	}
//	else {
//		fire = 0;
//	}*/
//
//	int s, nbytes;
//	struct sockaddr_can addr;
//	struct ifreq ifr;
//	struct can_frame vision_t = { 0 };
//
//
//	s = socket(PF_CAN, SOCK_RAW, CAN_RAW);//�����׽���
//	strcpy(ifr.ifr_name, "can0");//
//
//	ioctl(s, SIOCGIFINDEX, &ifr); //ָ�� can0 �豸
//	addr.can_family = AF_CAN;
//	addr.can_ifindex = ifr.ifr_ifindex;
//
//	bind(s, (struct sockaddr *)&addr, sizeof(addr));//���׽����� can0 ��
//	//���ù��˹��򣬱����̲����ձ��ģ�ֻ������
//
//	//setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, NULL, 0);
//
//	//int loop = 0;
//	//setsockopt(s, SOL_CAN_RAW, CAN_RAW_LOOPBACK, &loop, sizeof(loop));
//	//setsockopt(s, SOL_CAN_RAW, CAN_RAW_RECV_OWN_MSGS, &loop, sizeof(loop));
//
//
//	//���ɱ���
//	vision_t.can_id = 0xAA;
//	vision_t.can_dlc = 8;
//
//	//Int16ToUint8_p((int16_t)yaw, bdata);
//	//vision_t.data[0] = 666;//bdata[0];//yaw1
//	//vision_t.data[1] = bdata[1];//yaw2
//
//	//Int16ToUint8_p((int16_t)pitch, bdata);
//	//vision_t.data[2] = bdata[0];//pitch1
//	//vision_t.data[3] = bdata[1];//pitch1
//
//	//Int16ToUint8_p((int16_t)distance, bdata);
//	//vision_t.data[4] = bdata[0];//distance1
//	//vision_t.data[5] = bdata[1];//distance2
//
//	/*vision_t.data[6] = (uint8_t)fire;*/
//	    /*vision_t.data[7] = (uint8_t)find;*/
//	    vision_t.data[0] = 0;//
//	    vision_t.data[1] = 0;//
//
//	    vision_t.data[2] = order;
//	   /* vision_t.data[3] = pitch;
//
//	    vision_t.data[4] = distance;
//	    vision_t.data[5] = distance;*/
//
//
//
//	printf("%d\n", order);
//	 
//
//	nbytes = write(s, &vision_t, sizeof(vision_t)); //���� frame1[0]
//	cout << " 0 nbytes :" << nbytes << endl;
//
//	if (nbytes != sizeof(vision_t))
//	{
//		printf("Send Error vision_t!\n");
//		//break; //���ʹ����˳�
//	}
//
//
//	close(s);
//	printf("this\n");
//
//}
