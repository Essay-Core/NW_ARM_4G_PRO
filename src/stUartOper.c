#include"stUartOper.h"

char* findstr(char *str,char c);
int splitString(char* p1, char c, char buffer[30][64], int *count);

int UART0_Open(int fd, char* port)  
{  
	//fd = open( port, O_RDWR|O_NOCTTY|O_NDELAY);  
	fd = open(port, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (-1 == fd)  
	{  
		perror("Can't Open Serial Port");  
		return(-1);  
	}  
	//恢复串口为阻塞状态                                 
	if(fcntl(fd, F_SETFL, 0) < 0)  
	{  
		printf("fcntl failed!\n");  
		return(-1);  
	}       
	else  
	{  
		printf("fcntl=%d\n",fcntl(fd, F_SETFL,0));  
	}  
	//测试是否为终端设备      
	if(0 == isatty(STDIN_FILENO))  
	{    
		printf("standard input is not a terminal device\n");  
		return(-1);  
	}  
	else  
	{  
		printf("isatty success!\n");  
	}                
	printf("fd->open=%d\n",fd);  
	return fd;  
}  

int UART0_Set(int fd,int speed,int flow_ctrl,int databits,int stopbits,char parity)  
{  
     
	int   i;  
	int   status;  
	int   speed_arr[] = { B115200, B19200, B9600, B4800, B2400, B1200, B300};  
	int   name_arr[] = {115200,  19200,  9600,  4800,  2400,  1200,  300};  
           
	struct termios options;  
     
	/*tcgetattr(fd,&options)得到与fd指向对象的相关参数，并将它们保存于options,该函数还可以测试配置是否正确，该串口是否可用等。若调用成功，函数返回值为0，若调用失败，函数返回值为1. 
    */  
	if( tcgetattr( fd,&options)  !=  0)  
	{  
		perror("SetupSerial 1");      
		return -1;   
	}  
    
    //设置串口输入波特率和输出波特率  
	for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)  
	{  
		if  (speed == name_arr[i])  
		{               
			cfsetispeed(&options, speed_arr[i]);   
			cfsetospeed(&options, speed_arr[i]);    
		}  
	}       
     
    //修改控制模式，保证程序不会占用串口  
    options.c_cflag |= CLOCAL;  
    //修改控制模式，使得能够从串口中读取输入数据  
    options.c_cflag |= CREAD;  
    
    //设置数据流控制  
    switch(flow_ctrl)     
    {  
        
		case 0 ://不使用流控制  
              options.c_cflag &= ~CRTSCTS;  
              break;     
        
		case 1 ://使用硬件流控制  
              options.c_cflag |= CRTSCTS;  
              break;  
		case 2 ://使用软件流控制  
              options.c_cflag |= IXON | IXOFF | IXANY;  
              break;  
    }  
    //设置数据位  
    //屏蔽其他标志位  
    options.c_cflag &= ~CSIZE;  
    switch (databits)  
    {    
		case 5    :  
                     options.c_cflag |= CS5;  
                     break;  
		case 6    :  
                     options.c_cflag |= CS6;  
                     break;  
		case 7    :      
                 options.c_cflag |= CS7;  
                 break;  
		case 8:      
                 options.c_cflag |= CS8;  
                 break;    
		default:     
                 fprintf(stderr,"Unsupported data size\n");  
                 return -1;   
    }  
    //设置校验位  
    switch (parity)  
    {    
		case 'n':  
		case 'N': //无奇偶校验位。  
                 options.c_cflag &= ~PARENB;   
                 options.c_iflag &= ~INPCK;      
                 break;   
		case 'o':    
		case 'O'://设置为奇校验      
                 options.c_cflag |= (PARODD | PARENB);   
                 options.c_iflag |= INPCK;               
                 break;   
		case 'e':   
		case 'E'://设置为偶校验    
                 options.c_cflag |= PARENB;         
                 options.c_cflag &= ~PARODD;         
                 options.c_iflag |= INPCK;        
                 break;  
		case 's':  
		case 'S': //设置为空格   
                 options.c_cflag &= ~PARENB;  
                 options.c_cflag &= ~CSTOPB;  
                 break;   
        default:    
                 fprintf(stderr,"Unsupported parity\n");      
                 return -1;   
    }   
    // 设置停止位   
    switch (stopbits)  
    {    
		case 1:     
                options.c_cflag &= ~CSTOPB; break;   
		case 2:     
                options.c_cflag |= CSTOPB; break;  
		default:     
               fprintf(stderr,"Unsupported stop bits\n");   
              return -1; 
    }  
     
	//修改输出模式，原始数据输出  
	options.c_oflag &= ~OPOST;  
    
	options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);  
	//options.c_lflag &= ~(ISIG | ICANON);  
     
    //设置等待时间和最小接收字符  
    options.c_cc[VTIME] = 1; /* 读取一个字符等待1*(1/10)s */    
    options.c_cc[VMIN] = 1; /* 读取字符的最少个数为1 */  
    //options.c_cc[VMIN] = 0; /* 读取字符的最少个数为1 */  
     
    //如果发生数据溢出，接收数据，但是不再读取 刷新收到的数据但是不读  
    tcflush(fd,TCIFLUSH);  
     
    //激活配置 (将修改后的termios数据设置到串口中）  
    if (tcsetattr(fd,TCSANOW,&options) != 0)    
	{  
		perror("com set error!\n");    
		return -1;   
	}  

    return -1;   
} 

/******************************************************************* 
* 名称：                  sniffer_Open 
* 功能：            打开串口，并初始化相关设置 
* 入口参数：          port       串口号                  
* 出口参数：        正确返回大于0的整数，错误返回为-1 
*******************************************************************/
int sniffer_Open(char* port)
{
	int fd = 0;
	int speed = 9600;
	int flow_ctrl = 0; //不使用数据流控制
	int databits = 8;
	int stopbits = 1;
	char parity = 'N';

	fd = UART0_Open(fd, port);
	if (-1 == fd)  
	{  
		perror("Can't Open Serial Port");  

		sleep(3);
		
		fd = UART0_Open(fd, port);
		if (-1 == fd) 
		{
			perror("Can't Open Serial Port");  
			return -1; 
		}

		 
	} 
	//设置串口属性
	if(!UART0_Set(fd, speed, flow_ctrl, databits, stopbits, parity))
	{
		perror("UART0_Set failed!");  
		return -1; 
	}

	return fd;

}


/******************************************************************* 
* 名称：                sniffer_Close 
* 功能：                关闭串口并返回串口设备文件描述 
* 入口参数：        fd    :文件描述符     
*				  port   :串口号
* 出口参数：       int 		
*******************************************************************/     
int sniffer_Close(int fd)
{
	return close(fd);  
}



 
/******************************************************************** 
* 名称：                  UART0_Send 
* 功能：                发送数据 
* 入口参数：        fd     :文件描述符     
*             send_buf    :存放串口发送数据 
*             data_len    :一帧数据的个数 
* 出口参数：   正确返回为0，错误返回为-1 
*******************************************************************/  
int UART0_Send(int fd, char *send_buf,int data_len)  
{  
    int len = 0;  
     
    len = write(fd,send_buf,data_len);  
    if (len == data_len )  
	{  
		printf("send data is %s\n",send_buf);
		return len;  
	}       
    else     
	{  
                 
		tcflush(fd,TCOFLUSH);  
		return -1;  
	}  
     
    return 0;
}  

