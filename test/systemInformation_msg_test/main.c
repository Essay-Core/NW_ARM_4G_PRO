#include <stdio.h>
#include <stdbool.h>
  
/*****************************************************************
	g++ main.cc liblte/src/liblte_rrc.o -o main -I liblte/hdr/
  
*****************************************************************/
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

//sib1
//7851800125732FD820381B594442041130913E8C050A
//uint8 data_p[] = {0x50,0x40,0x04,0x03,0x00,0x01,0x00,0x00,0x00,0x1C,0x16,0x50,0x90,0x20,0x80,0x85,0x00,0x00};
//uint8 data_p[] = {0x78,0x51,0x80,0x01,0x25,0x73,0x2F,0xD8,0x20,0x38,0x1B,0x59,0x44,0x42,0x04,0x11,0x30,0x91,0x3E,0x8C,0x05,0x0A,0x00};
//uint8 data_p[] = {0x70,0x51,0x80,0x01,0x24,0x4E,0xC7,0xA7,0x00,0x18,0x1B,0x5A,0x04,0x42,0x04,0x11,0x30,0x91,0x3E,0x80,0x00,0x00};

//01100000110100011000000000000011101000110000000001000110101111001110001000000000000000000001101111010010101000001101010000100000100000000001000010000001000000000000000000000000
//01100000110100011000000000000011101000110000000001000110101111001110001000000000000000000001101111010010101000001101010000100000100000000001000010000001000000000000000000000000
//const unsigned char* pstr = "01100000110100011000000000000011101000110000000001000110101111001110001000000000000000000001101111010010101000001101010000100000100000000001000010000001000000000000000000000000";
//uint8 data_p[] = {0110b,0000b,1101b,0001b,1000b,0000b,0000b,0011b,1010b,0011b,0000b,0000b,0100b,0110b,1011b,1100b,1110b,0010b,0000b,0000b,0000b,0000b,0001b,1011b,1101b,0010b,1010b,0000b,1101b,0100b,0010b,0000b,1000b,0000b,0001b,0000b,1000b,0001b,0000b,0000b,0000b,0000b,0000b,0000b};

//60d18003a30046bce200001bd2a0d420801081000000   D??
uint8 data_p[] = {0x60,0xd1,0x80,0x03,0xa3,0x00,0x46,0xbc,0xe2,0x00,0x00,0x1b,0xd2,0xa0,0xd4,0x20,0x80,0x10,0x81,0x00,0x00,0x00};
//sib2 00800f5995648000020a580020000804012f395796dec00a111fe807c1
//uint8 data_p[] = {0x00,0x80,0x0f,0x59,0x95,0x64,0x80,0x00,0x02,0x0a,0x58,0x00,0x20,0x00,0x08,0x04,0x01,0x2f,0x39,0x57,0x96,0xde,0xc0,0x0a,0x11,0x1f,0xe8,0x07,0xc1};

//0000060FD6C8160C002A00200141000029AA55696D0C72944C1C0000

//uint8 data_p[] = {0x00,0x00,0x06,0x0F,0xD6,0xC8,0x16,0x0C,0x00,0x2A,0x00,0x20,0x01,0x41,0x00,0x00,0x29,0xAA,0x55,0x69,0x6D,0x0C,0x72,0x94,0x4C,0x1C,0x00};
  
//00821C31186FE0A834328B96E34000040246024F62B532CBC0018340030280000E641BFDC0DE36B504F01413AA572A0000
//uint8 data_p[] = {0x00,0x82,0x1C,0x31,0x18,0x6F,0xE0,0xA8,0x34,0x32,0x8B,0x96,0xE3,0x40,0x00,0x04,0x02,0x46,0x02,0x4F,0x62,0xB5,0x32,0xCB,0xC0,0x01,0x83,0x40,0x03,0x02,0x80,0x00,0x0E,0x64,0x1B,0xFD,0xC0,0xDE,0x36,0xB5,0x04,0xF0,0x14,0x13,0xAA,0x57,0x2A,0x00,0x00};

//10	00	1E	4A	5F	7F	58	70	58	10	91	A1	81	00	00	02	00	40	E2	7D	AA	A5	B7	00	03	80																																															(sib2)
//sib3 00043020384000
//uint8 data_p[] = {0x00,0x04,0x30,0x20, 0x38,0x40, 0x00};


//sib4 10086012000000
//uint8 data_p[] = {0x10,0x08,0x60,0x12,0x00,0x00,0x00};
 
 
//sib5 000F544CB591A952D3A2250308272D6444A69104E5AC889826209CB591131D841396B22258008272D440A3AB00100384315AE9001003E8315AD900100BB8315AC900100CE4315AE9000000
//uint8 data_p[] = {0x00,0x0F,0x54,0x4C,0xB5,0x91,0xA9,0x52,0xD3,0xA2,0x25,0x03,0x08,0x27,0x2D,0x64,0x44,0xA6,0x91,0x04,0xE5,0xAC,0x88,0x98,0x26,0x20,0x9C,0xB5,0x91,0x13,0x1D,0x84,0x13,0x96,0xB2,0x22,0x58,0x00,0x82,0x72,0xD4,0x40,0xA3,0xAB,0x00,0x10,0x03,0x84,0x31,0x5A,0xE9,0x00,0x10,0x03,0xE8,0x31,0x5A,0xD9,0x00,0x10,0x0B,0xB8,0x31,0x5A,0xC9,0x00,0x10,0x0C,0xE4,0x31,0x5A,0xE9,0x00,0x00,0x00};

int pos = 0;      //当前数据位置
int typeBitCounter = 5;// 4 or 5

int info_sib[32][2];//0存储重复周期，1存储sib类型
    

unsigned char mask[8] ={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};
int Bandwidth[6] ={6,15,25,50,75,100};
int si_ms_time[7]={1,2,5,10,15,20,40};//40代表40毫秒

typedef struct Mac_msg
{
	unsigned short earfn;//频点号
	unsigned short pci;//小区物理ID
	unsigned short rnti;  //rnti表示空口无线网络标识,范围1-65535
	unsigned short tti;	//tti = sfn|subframe 范围 0-10239，sfn = //tti/10,subfn=tti%10
	short rssi; //参考信号场强
	short rsrp;	//参考信号功率
	short rsrq;//参考信号质量
	unsigned short msgbliten;//有效数据bit长度
	unsigned short crcstat;//PDU解码可信度
	unsigned char *msgaddr;//PDU存放地址
}stMac_msg;

typedef struct CellScan 
{
	unsigned short earfn;//频点号
	unsigned short pci;  //小区物理ID
	uint32 cid;			 //基站识别码
	unsigned short tac;  //基站跟踪区
	short rsrp;			 //参考信号功率
	short rsrq;			 //参考信号质量
	
}stCellScan;

int DecodeSIBMeg();
int ExtraData(int bit_pos, int bitsize);
int main_test_sib5();
int main_test_sib4();
int main_test_sib3();
int main_test_sib2();
int main_test_sib1();

int main()
{
//	DecodeSIBMeg();
	main_test_sib1();
	return 0;
}

int DecodeSIBMeg()
{
	pos = 0;
	//bcch dl sch choice 
	int option_level1 =  ExtraData(pos,1);
	pos +=1;
	
	if(option_level1 == 0)
	{
		//c1
		int option_level2 =  ExtraData(pos,1);  
		printf("c1 OPTIONAL:%d\n", option_level2);
		pos +=1;
		
		if(option_level2 == 0)
		{
			//systemInformation
			int option_level3 =  ExtraData(pos,1);  
			pos +=1;
			
			if(option_level3 == 0)
			{
				//systemInformation-r8
				int systemInformationR8Op =  ExtraData(pos,1);  
				pos +=1;
				
				//sib-TypeAndInfo	SEQUENCE (SIZE (1..maxSIB)) OF CHOICE
				int maxSIB =  ExtraData(pos,5)+1;
				printf("maxSIBnu:%d\n", maxSIB);
				pos +=5;
				
				int i = 0;
				for(i;i<maxSIB;i++)
				{					
					//sib-TypeAndInfo choice
					int sibTypeAndInfo =  ExtraData(pos,5)+2;
					printf("get SIB type: SIB%d\n", sibTypeAndInfo);
					pos +=5;
					
					switch(sibTypeAndInfo)
					{
						//sib2
						case(2):
						pos = main_test_sib2();
						break;
						
						//sib3
						case(3):
						pos = main_test_sib3();
						break;
						
						//sib4
						case(4):
						pos = main_test_sib4();
						break;
						
						//sib5
						case(5):
						pos = main_test_sib5();
						break;
						
						default:
						
						break;
					}

				}
				
				
			}
			else if((option_level3&0x01) == 0x01)
			{
				//criticalExtensionsFuture-r15
			}
			
		}
		else if(option_level2 == 1)
		{
			main_test_sib1();
			
		}
		
	}

	return 0;
}


int main_test_sib5()
{	

#ifdef HEAD	
	pos = 0;
	//bcch dl sch choice 
	int option_level1 =  ExtraData(pos,1);
	pos +=1;
	
	//c1 choice
	int option_level2 =  ExtraData(pos,1);
	pos +=1;
	
	//systemInformation criticalExtensions choice
	int option_level3 =  ExtraData(pos,1);
	pos +=1;
	  
	//SystemInformation-r8 OP 
	int option_level4 =  ExtraData(pos,1);
	pos +=1;
	
	//sib-TypeAndInfo	SEQUENCE (SIZE (1..maxSIB)) OF CHOICE
	int maxSIB =  ExtraData(pos,5)+1;
	printf("maxSIBnu:%d\n", maxSIB);
	pos +=5;
	
	//sib-TypeAndInfo choice
	int sibTypeAndInfo =  ExtraData(pos,5);
	printf("sibTypeAndInfo:%d\n", sibTypeAndInfo);
	pos +=5;//14

	
	if(sibTypeAndInfo != 3)
		return -1;

#endif

	int sib5OP =  ExtraData(pos,1);
	pos += 1;//15
	
	int maxFreq = ExtraData(pos,3)+1;//取值范围	INTEGER ::= 8
	printf("maxFreq:%d", maxFreq);
	pos += 3;//18
	
	int dl_CarrierFreq[8]={0};
	int i;
	for(i = 0;  i< maxFreq;  i++)
	{
		//InterFreqCarrierFreqInfo op 
		int option_level = ExtraData(pos,5);
		pos += 5;
		
		//ARFCN-ValueEUTRA ::=				INTEGER (0..maxEARFCN)
		
		dl_CarrierFreq[i]	= ExtraData(pos,18); // 取值范围INTEGER (0..maxEARFCN)65535	
		printf("\ndl_CarrierFreq[%d]:%d\n",i, dl_CarrierFreq[i]);
		pos += 18;
		
		int qRxLevMin = ExtraData(pos,6)-70;
		printf("qRxLevMin:%d\n", qRxLevMin);
		pos += 6;    //q-RxLevMin	

		if((option_level&0x08)>0)
		{
			int pMax = ExtraData(pos,6)-30;
			printf("pMax:%d\n", pMax);
			pos+=6;   // 跳过6bit	p-Max
		}

		int ReselectionEUTRA = ExtraData(pos,3);
		printf("ReselectionEUTRA:%d\n", ReselectionEUTRA);
		pos+=3; //跳过3bit t-ReselectionEUTRA	取值范围INTEGER (0..7)

		if((option_level&0x04)>0)
		{
			int t_ReselectionEUTRA_SF = ExtraData(pos,4);
			printf("t_ReselectionEUTRA_SF:%d\n", t_ReselectionEUTRA_SF);
			pos += 4;   //  //	t-ReselectionEUTRA-SF 选择中速高速移动模式及因子
		}
		
		int threshX_High = ExtraData(pos,5);
		printf("threshX_High:%d\n", threshX_High);
		pos += 5;// threshX-High 取值范围INTEGER (0..31)	
	   
		int threshX_Low = ExtraData(pos,5);
		printf("threshX_Low:%d\n", threshX_Low);
		 pos += 5;// threshX_Low取值范围INTEGER (0..31)
		 
		int allowedMeasBandwidth =Bandwidth[ExtraData(pos,3)]; //取值范围：ENUMERATED {mbw6, mbw15, mbw25, mbw50, mbw75, mbw100}, mbw6表示带宽为6个RB。
		printf("allowedMeasBandwidth:%d\n", allowedMeasBandwidth);
		pos += 3;
	
		int presenceAntennaPort1 = ExtraData(pos,1);
		printf("presenceAntennaPort1:%d\n", presenceAntennaPort1);
	    pos+=1;//跳过1bit presenceAntennaPort1 BOOL变量
		
		if((option_level&0x02)>0)
		{ 
			int cellReselectionPriority = ExtraData(pos,3);
			printf("cellReselectionPriority:%d\n", cellReselectionPriority);
			pos+=3;//跳过3bit；cellReselectionPriority赋值范围INTEGER (0..7)；
		}
		
		int neighCellConfig = ExtraData(pos,2);
		printf("neighCellConfig:%d\n\n", neighCellConfig);
		pos += 2;//跳过2bit； neighCellConfig	
		
		
    }
	
	printf("End pos:%d sib5OP:%d \n", pos,sib5OP);

	if(sib5OP>0)
	{
		pos += 23;
		int i;
		for( i = 0;  i< 4;  i++)
		{
			pos += 18;
			
			int dl_CarrierFreqr12 = ExtraData(pos,12); // 取值范围INTEGER (0..maxEARFCN)65535	
			printf("\ndl_CarrierFreqr12:%d\n", dl_CarrierFreqr12);
			pos += 12;
			
			int qRxLevMinR12 = ExtraData(pos,6)-70;
			printf("qRxLevMinR12:%d\n", qRxLevMinR12);
			pos += 6;    //q-RxLevMin	
			
			int ReselectionEUTRAR12 = ExtraData(pos,3);
			printf("ReselectionEUTRAR12:%d\n", ReselectionEUTRAR12);
			pos+=3; //跳过3bit t-ReselectionEUTRA	取值范围INTEGER (0..7)
			
			int threshX_HighR12 = ExtraData(pos,5);
			printf("threshX_HighR12:%d\n", threshX_HighR12);
			pos += 5;// threshX-High 取值范围INTEGER (0..31)	
		   
			int threshX_LowR12 = ExtraData(pos,5);
			printf("threshX_LowR12:%d\n", threshX_LowR12);
			pos += 5;// threshX_Low取值范围INTEGER (0..31)	
			
			int allowedMeasBandwidthR12 =Bandwidth[ExtraData(pos,3)]; //取值范围：ENUMERATED {mbw6, mbw15, mbw25, mbw50, mbw75, mbw100}, mbw6表示带宽为6个RB。
			printf("allowedMeasBandwidthR12:%d\n", allowedMeasBandwidthR12);
			pos += 3;
		
			int presenceAntennaPort1R12 = ExtraData(pos,1);
			printf("presenceAntennaPort1R12:%d\n", presenceAntennaPort1R12);
			pos+=1;//跳过1bit presenceAntennaPort1 BOOL变量
			
			int neighCellConfigR12 = ExtraData(pos,2);
			printf("neighCellConfigR12:%d\n\n", neighCellConfigR12);
			pos += 2;//跳过2bit； neighCellConfig	
			pos += 1;
		}
		
	}
	
	return pos;
}

int main_test_sib4()
{
/*
#ifdef HEAD	
	pos = 0;
	//bcch dl sch choice 
	int option_level1 =  ExtraData(pos,1);
	pos +=1;
	
	//c1 choice
	int option_level2 =  ExtraData(pos,1);
	pos +=1;
	
	//systemInformation criticalExtensions choice
	int option_level3 =  ExtraData(pos,1);
	pos +=1;
	  
	//SystemInformation-r8 OP 
	int option_level4 =  ExtraData(pos,1);
	pos +=1;
	
	//sib-TypeAndInfo	SEQUENCE (SIZE (1..maxSIB)) OF CHOICE
	int maxSIB =  ExtraData(pos,5)+1;
	printf("maxSIBnu:%d\n", maxSIB);
	pos +=5;
	
	//sib-TypeAndInfo choice
	int sibTypeAndInfo =  ExtraData(pos,5);
	printf("sibTypeAndInfo:%d\n", sibTypeAndInfo);
	pos +=5;
#endif
*/
	////处理IntraFreqNeighCellList， 可以接入的同频邻区
	int PhysCellId [16] ={-1};
	int range[16][2] ={-1};//下标0存储cellID，1存储范围；
	int intra_cellID_csg[16][2] ={-1};//下标0存储cellID，1存储范围；
	
	//SystemInformationBlockType4  op 
	int option_flag = ExtraData(pos,3);
	printf("option_flag:%d\n", option_flag);
	pos +=3;
	
	if((option_flag&0x4) == 0x4)
	{
		//intraFreqNeighCellList   qOffsetCell
		int maxCellIntra=ExtraData(pos,4);
		printf("maxCellIntra:%d\n", maxCellIntra);
		pos += 4;
		int i;
	    for( i=0; i< maxCellIntra;  i++)
		{  
			PhysCellId [i] =ExtraData(pos,9);//取值范围INTEGER (0..503)
			printf("PhysCellId [%d]:%d\n",i, PhysCellId [i]);
			pos += 9;
			
			//enum 31 item
			int qOffsetCell =ExtraData(pos,5);
			printf("qOffsetCell:%d\n", qOffsetCell);
			pos += 5;//跳过5bit；q-OffsetCell
		}			 
	}

	//读取black邻区ID
	if((option_flag&0x02)==0x02)
	{
		//maxCellBlack  PhysCellIdRange
		int maxCellIntra=ExtraData(pos,4);
		printf("maxCellIntra:%d\n", maxCellIntra);
		pos += 4;
		int i;
		for( i= 0; i<maxCellIntra; i++)
		{
			int cell_potion =ExtraData(pos,1);
			pos += 1;
			range[i][0] = ExtraData(pos,9);//取值范围INTEGER (0..503)
			printf("range[%d][0]:%d\n",i, range[i][0]);
			pos += 9;
			if(cell_potion==1)
			{
				range[i][1] = ExtraData(pos,4);
				printf("range[%d][0]:%d\n",i, range[i][0]);
				//取值ENUMERATED {n4, n8, n12, n16, n24, n32, n48, n64, n84, n96,
				//n128, n168, n252, n504, spare2, spare1} ，n4赋值4；  
				pos += 4;
			}
		}
	}
	//在option_flag未选择的情况下，仍然出现？？  
	//其中一位时op位，多出一位不知道是啥
	pos += 2;
	int PhysCellId_start =  ExtraData(pos,9);
	printf("PhysCellId_start:%d\n", PhysCellId_start);
	pos += 9;
	
	int PhysCellIdRange =  ExtraData(pos,4);
	printf("PhysCellIdRange:%d\n", PhysCellIdRange);
	pos += 4;
	
	return pos;
}


int main_test_sib3()
{
	
/*	
	pos = 0;
	//bcch dl sch choice 
	int option_level1 =  ExtraData(pos,1);
	pos +=1;
	
	//c1 choice
	int option_level2 =  ExtraData(pos,1);
	pos +=1;
	
	//systemInformation criticalExtensions choice
	int option_level3 =  ExtraData(pos,1);
	pos +=1;
	
	//SystemInformation-r8-IEs nonCriticalExtension OP 
	int option_level4 =  ExtraData(pos,1);
	pos +=1;
	
	//sib-TypeAndInfo	SEQUENCE (SIZE (1..maxSIB)) OF CHOICE
	int maxSIB =  ExtraData(pos,5)+1;
	printf("maxSIBnu:%d\n", maxSIB);
	pos +=5;
	
	//sib-TypeAndInfo choice
	int sibTypeAndInfo =  ExtraData(pos,6);
	printf("sibTypeAndInfo:%d\n", sibTypeAndInfo);
	pos +=6;
	//pos =15;
*/
	//补充位置
	pos+=1;
	
	//pos=15;
	//cellReselectionInfoCommon
	int option = ExtraData(pos,1); 
	pos+=1;
	
	int q_Hyst = ExtraData(pos,4); 
	printf("q_Hyst:%d\n", q_Hyst);
	pos+=4;


	//speedStateReselectionPars  18b
	if(option ==1)
	{
		//mobilityStateParameters				MobilityStateParameters
		int t_Evaluation = ExtraData(pos,3);//{s30, s60, s120, s180, s240, spare3, spare2, spare1}, 
		printf("t_Evaluation:%d\n", t_Evaluation);
		pos+=3;
	    int t_HystNormal= ExtraData(pos,3); 
		printf("t_HystNormal:%d\n", t_HystNormal);
		pos+=3;
		int n_CellChangeMedium= ExtraData(pos,4); //INTEGER (1..16),
		printf("n_CellChangeMedium:%d\n", n_CellChangeMedium);
		pos+=4;					
		int n_CellChangeHigh= ExtraData(pos,4); //INTEGER (1..16)
		printf("n_CellChangeHigh:%d\n", n_CellChangeHigh);
		pos+=4;	
		//q-HystSF
		int sf_Medium = ExtraData(pos,2); //{dB-6, dB-4, dB-2, dB0},
		printf("sf_Medium:%d\n", sf_Medium);
		pos+=2;
	    int sf_High= ExtraData(pos,2); 
		printf("sf_High:%d\n",sf_High);
		pos+=2;
	}
	//cellReselectionServingFreqInfo
	option = ExtraData(pos,1); 
	pos+=1;
	if(option ==1)
	{
		int s_NonIntraSearch = ExtraData(pos,5)*2; //INTEGER (0..31) unit:db
		printf("s_NonIntraSearch:%d\n", s_NonIntraSearch);
		pos+=5;		
	}
	
	int threshServingLow= ExtraData(pos,5)*2; //INTEGER (0..31) unit:db
	printf("threshServingLow:%d\n", threshServingLow);
	pos+=5;				
	
	int cellReselectionPriority	= ExtraData(pos,3); //INTEGER (0..7)
	printf("cellReselectionPriority:%d\n", cellReselectionPriority);
	pos+=3;

	//intraFreqCellReselectionInfo
	option = ExtraData(pos,4); 
	pos+=4;
	
	//Q-RxLevMin ::=	INTEGER (-70..-22)
	int q_RxLevMin = ExtraData(pos,6)-70;
	printf("q_RxLevMin:%d\n", q_RxLevMin);
	pos+=6;
	if((option&0x08)>0)
	{
		int p_max =ExtraData(pos,6)-30; //INTEGER (-30..33)
		printf("p_max:%d\n", p_max);
		pos+=6;
	}
	if((option&0x04)>0)
	{
		int s_IntraSearch = ExtraData(pos,5)*2; //INTEGER (0..31) unit:db
		printf("s_IntraSearch:%d\n", s_IntraSearch);
		pos+=5;				
	}
	if((option&0x02)>0)
	{
		int allowedMeasBandwidth = Bandwidth[ExtraData(pos,3)]; //
		printf("allowedMeasBandwidth:%d\n", allowedMeasBandwidth);
		pos+=3;		
	}
	
	int presenceAntennaPort1 = ExtraData(pos,1); //1 or 0
	printf("presenceAntennaPort1:%d\n", presenceAntennaPort1);
	pos+=1;		
	
	int neighCellConfig = ExtraData(pos,2); //BIT STRING (SIZE (2))
	printf("neighCellConfig:%d\n", neighCellConfig);
	pos+=2;		
	
	int t_ReselectionEUTRA=ExtraData(pos,3);//0-7
	printf("t_ReselectionEUTRA:%d\n", t_ReselectionEUTRA);
	pos+=3;	
	if((option&0x01)>0)
	{
	//t-ReselectionEUTRA-SF
		int sf_Medium = ExtraData(pos,2);//ENUMERATED {oDot25, oDot5, oDot75, lDot0}
		printf("sf_Medium:%d\n", sf_Medium);
		pos+=2;								
		int sf_High	  = ExtraData(pos,2);//ENUMERATED {oDot25, oDot5, oDot75, lDot0}
		printf("sf_High:%d\n", sf_High);
		pos+=2;			
	}
	
	printf("pos:%d\n", pos);	
	
	return pos;
	
}

//ok
int main_test_sib2()
{
	pos = 0;
	//bcch dl sch choice 
	int option_level1 =  ExtraData(pos,1);
	pos +=1;
	
	//c1 choice
	int option_level2 =  ExtraData(pos,1);
	pos +=1;
	
	//systemInformation criticalExtensions choice
	int option_level3 =  ExtraData(pos,1);
	pos +=1;
	
	//systemInformation-r8
	if(option_level3 == 0)
	{
		//SystemInformation-r8-IEs nonCriticalExtension OP 
		int option_level4 =  ExtraData(pos,1);
		pos +=1;
		
		//sib-TypeAndInfo	SEQUENCE (SIZE (1..maxSIB)) OF CHOICE
		int maxSIB =  ExtraData(pos,5)+1;
		printf("maxSIBnu:%d\n", maxSIB);
		pos +=5;
		
		//sib-TypeAndInfo choice
		//int sibTypeAndInfo =  ExtraData(pos,4);
		//pos +=4; //???? 4 or 6
	
		int sibTypeAndInfo =  ExtraData(pos,typeBitCounter);
		pos +=typeBitCounter; //???? 4 or 6
		
		if( sibTypeAndInfo == 0)
		{
			//sib2
			//SystemInformationBlockType2 op
			int option_level6 = ExtraData(pos,2);//可选项标识
			pos+=2; 
			
			//ac-BarringInfo
			if((option_level6&0x02) == 2)
			{
				int option_level7 = ExtraData(pos,2);//AC-Barringinfo可选项标识
				pos+=2;  
				pos+=1;//ac-BarringForEmergency
				
				if((option_level7&0x02)==0x02)
					pos+=12;//跳过4+3+5跳过AC-BarringConfig
				if((option_level7&0x01)==0x01)
					pos+=12;//跳过4+3+5跳过AC-BarringConfig
			}
			
			//处理RadioResourceConfigCommonSIB
			//rach-ConfigCommon  					RACH-ConfigCommon
			//preambleInfo
			int option_level8 =  ExtraData(pos,1);//可选项标识
			pos+=1;
			pos+=3;//add
			
			int numberOfRA_Preambles =  ExtraData(pos,4);
			printf("numberOfRA_Preambles:%d\n", numberOfRA_Preambles);
			pos+=4;
			printf("pos:%d\n", pos);
			
			//pos+=1; //补位
			
			//preamblesGroupAConfig 
			if(option_level8==1)
			{
				//sizeOfRA-PreamblesGroupA ENUMERATED 
				int sizeOfRA_PreamblesGroupA = ExtraData(pos,4);
				printf("sizeOfRA_PreamblesGroupA:%d\n", sizeOfRA_PreamblesGroupA);
				pos+=4;
				
				//messageSizeGroupA ENUMERATED
				int messageSizeGroupA = ExtraData(pos,2);
				printf("messageSizeGroupA:%d\n", messageSizeGroupA);
				pos+=2;
				
				//
				int messagePowerOffsetGroupB = ExtraData(pos,3);
				printf("messagePowerOffsetGroupB:%d\n", messagePowerOffsetGroupB);
				pos+=3;
			}
			
			//powerRampingParameters
			//powerRampingStep ENUMERATED
			int powerRampingStep = ExtraData(pos,2);
			printf("powerRampingStep:%d\n" , powerRampingStep);
			pos+=2; // PowerRampingParameters 2+4

			
			int preambleInitialReceivedTargetPower = ExtraData(pos,4);
			printf("preambleInitialReceivedTargetPower:%d\n" , preambleInitialReceivedTargetPower);
			pos+=4;
			
			// ra-SupervisionInfo  PreambleTransMax	  11
			int preambleTransMax =ExtraData(pos,4);
			printf("preambleTransMax:%d\n", preambleTransMax);
			pos+=4;   
			
			int  ra_ResponseWindowSize = ExtraData(pos,3);
			printf("ra_ResponseWindowSize:%d\n", ra_ResponseWindowSize);
			pos+=3;   
			int  mac_ContentionResolutionTimer = ExtraData(pos,3);
			printf("mac_ContentionResolutionTimer:%d\n", mac_ContentionResolutionTimer);
			pos+=3;//mac-ContentionResolutionTimer;

			int maxHARQ_Msg3Tx =ExtraData(pos,3)+1; //msg3发送的最大个数
			printf("maxHARQ_Msg3Tx:%d\n", maxHARQ_Msg3Tx);
			pos+=3; 
			

			// BCCH-Config配置处理
			//modificationPeriodCoeff				ENUMERATED {n2, n4, n8, n16}
			int modificationPeriodCoeff=ExtraData(pos,2);
			printf("modificationPeriodCoeff:%d\n", modificationPeriodCoeff);
			pos+=2;
			
			// PCCH-Config配置处理
			int defaultPagingCycle = ExtraData(pos,2);
			printf("defaultPagingCycle:%d\n", defaultPagingCycle);
			pos+=2;
			
			int nb =ExtraData(pos,3);
			printf("nb:%d\n", nb);  
			pos+=3;
						
			//PRACH-ConfigSIB配置处理
			int  rootSequenceIndex = ExtraData(pos,10); //根索引，取值范围 INTEGER (0..837)
			printf("rootSequenceIndex:%d INTEGER (0..837)\n", rootSequenceIndex);
			pos+=10;
			
			int   prach_ConfigIndex = ExtraData(pos,6);//取值范围INTEGER (0..63),
			printf("prach_ConfigIndex:%d INTEGER (0..63)\n", prach_ConfigIndex );
			pos+=6;
			
			int   highSpeedFlag =  ExtraData(pos,1);	//取值范围		BOOLEAN（0，1）, 
			printf("highSpeedFlag:%d BOOLEAN（0，1）\n", highSpeedFlag );
			pos+=1;
			
			int 	zeroCorrelationZoneConfig= ExtraData(pos,4);//取值范围			INTEGER (0..15),
			printf("zeroCorrelationZoneConfig:%d INTEGER (0..15)\n", zeroCorrelationZoneConfig );
			pos+=4;
			
			int	prach_FreqOffset =  ExtraData(pos,7); 		//取值范围			INTEGER (0..94)
			printf("prach_FreqOffset :%d INTEGER (0..94)\n", prach_FreqOffset );
			pos+=7;

			// PDSCH-ConfigCommon配置处理
			int referenceSignalPower =ExtraData(pos,7)-60;  //取值范围INTEGER (-60..50)
			printf("referenceSignalPower:%d (-60..50)\n", referenceSignalPower );
			pos+=7;
			
			int p_b =ExtraData(pos,2); 
			printf("p_b:%d\n", p_b );
			pos+=2;
			
			// PUSCH-ConfigCommon配置项处理
			int  n_SB = ExtraData(pos,2)+1  ; // pusch物理资源映射中用于计算子带（sub-band）长度，即子带数目
			printf("n_SB:%d\n", n_SB );
			pos+=2;
			
			int  hoppingMode = ExtraData(pos,1);// 跳频模式。不同跳频模式下pusch发送信号使用的资源块获得方式不一样。ENUMERATED {interSubFrame, intraAndInterSubFrame}
			printf("hoppingMode:%d ENUMERATED {interSubFrame, intraAndInterSubFrame}\n", hoppingMode );
			pos+=1;
			
			int  pusch_HoppingOffset =ExtraData(pos,7); // 跳频偏移
			printf("pusch_HoppingOffset:%d\n", pusch_HoppingOffset );
			pos+=7;
			
			int  enable64QAM = ExtraData(pos,1) ; //是否支持64QAM调制
			printf("enable64QAM:%d\n", enable64QAM );
			pos+=1;
			
			//ul-ReferenceSignalsPUSCH			UL-ReferenceSignalsPUSCH
			int  groupHoppingEnabled = ExtraData(pos,1)  ; //是否允许组跳频。
			printf("groupHoppingEnabled:%d\n", groupHoppingEnabled );
			pos+=1;
			
			int   groupAssignmentPUSCH =ExtraData(pos,5) ; // 组分配PUSCH ，用于定义pusch不用的位移序列样式。取值范围（0。。29）
			printf("groupAssignmentPUSCH:%d\n", groupAssignmentPUSCH );
			pos+=5;
			
			int   sequenceHoppingEnabled =ExtraData(pos,1)  ; //是否允许序列跳频
			printf("sequenceHoppingEnabled:%d\n",  sequenceHoppingEnabled);
			pos+=1;
			
			int  cyclicShift =ExtraData(pos,3); // 循环移位
			printf("cyclicShift:%d\n", cyclicShift );
			pos+=3;
  

			// PUCCH-ConfigCommon配置项处理，
			int  deltaPUCCH_Shift = ExtraData(pos,2);// 协助计算pucch格式1、1a、1b时的循环移位及正交序列索引的确定。ENUMERATED {ds1, ds2, ds3}
			printf("deltaPUCCH_Shift:%d ENUMERATED {ds1, ds2, ds3}\n", deltaPUCCH_Shift );
			pos+=2;
			
			int  nRB_CQI =ExtraData(pos,7); // 即 ，表示每个时隙中可用于PUCCH格式2/2a/2b 传输的物理资源块数. INTEGER (0..98)
			printf("nRB_CQI:%d INTEGER (0..98)\n", nRB_CQI );
			pos+=7;
			
			int  nCS_AN =ExtraData(pos,3); // 即 ，表示的是PUCCH格式1/1a/1b和格式2/2a/2b在一个物理资源块中混合传输时格式1/1a/1b可用的循环移位数
			printf("nCS_AN:%d\n", nCS_AN );
			pos+=3;
			
			int  n1PUCCH_AN  =ExtraData(pos,11); // 即 ，用于传输PUCCH格式1/1a/1b的资源的非负索引值，INTEGER (0..2047)
			printf("n1PUCCH_AN:%d INTEGER (0..2047)\n", n1PUCCH_AN );
			pos+=11;

			//SoundingRS-UL-ConfigCommon配置处理，// SRS配置信息，包括SRS带宽配置、子帧配置以及可否在UpPTS发送等
			int option_choice =ExtraData(pos,1);
			printf("option_choice:%d\n", option_choice );
			pos += 1;
			
			if(option_choice==1)
			{
				int option_setup_flag = ExtraData(pos,1);
				printf("option_setup_flag:%d\n", option_setup_flag );
				pos += 1;
				
				int srs_BandwidthConfig= ExtraData(pos,3); // ENUMERATED { bw0, bw1, bw2, bw3, bw4, bw5, bw6, bw7 }探测参考信号带宽
				printf("srs_BandwidthConfig:%d\n", srs_BandwidthConfig );
				pos += 3;
				
				int srs_SubframeConfig=ExtraData(pos,4); // ENUMERATED { sc0, sc1, sc2, sc3, sc4, sc5, sc6, sc7, sc8, sc9, sc10, sc11, sc12, sc13, sc14, sc15}探测参考信号子帧配置
				printf("srs_SubframeConfig:%d \n", srs_SubframeConfig );
				pos += 4;
				
				int ackNackSRS_SimultaneousTransmission=ExtraData(pos,1); //决定了UE是否配置支持在同一个子帧中进行PUCCH ACK/NACK和SRS的传输
				printf("ackNackSRS_SimultaneousTransmission:%d\n", ackNackSRS_SimultaneousTransmission );
				pos += 1;
				
				if (option_setup_flag ==1)
				{
					int srs_MaxUpPts = 1; // ENUMERATED { true}
					printf("srs_MaxUpPts:%d\n", srs_MaxUpPts );
					//pos += 1;						
				}
			}
			
			////UplinkPowerControlCommon配置项处理
			int  p0_NominalPUSCH=ExtraData(pos,8)-126 ; // 该参数只用于非持续调度，用于pusch功率计算
			printf("p0_NominalPUSCH:%d\n", p0_NominalPUSCH );
			pos += 8;
			
			int  Alpha_r12=ExtraData(pos,3) ; // 即α，是一个 3bit 的小区专用参数，用于pusch功率计算，ENUMERATED {al0, al04,al05,al06,al07,al08,al09,al1}07代表0.7
			printf("Alpha_r12:%d\n", Alpha_r12 );
			pos += 3;
			
			int  p0_NominalPUCCH=ExtraData(pos,5)-127 ; // 用于pucch功率计算
			printf("p0_NominalPUCCH:%d\n", p0_NominalPUCCH );
			pos += 5;
			
			int  deltaF_PUCCH_Format    = ExtraData(pos,2) ; // {deltaF-2, deltaF0, deltaF2}，1表示deltaF0
			printf("deltaF_PUCCH_Format:%d\n", deltaF_PUCCH_Format );
			pos += 2;
			
			int  deltaF_PUCCH_Format1b  = ExtraData(pos,2) ; // {deltaF1, deltaF3, deltaF5}，1表示deltaF3
			printf("deltaF_PUCCH_Format1b:%d\n", deltaF_PUCCH_Format1b );
			pos += 2;
			int  deltaF_PUCCH_Format2   = ExtraData(pos,2); // {deltaF-2, deltaF0, deltaF1, deltaF2}，2表示deltaF1
			printf("deltaF_PUCCH_Format2:%d\n", deltaF_PUCCH_Format2 );
			pos += 2;
			int  deltaF_PUCCH_Format2a  = ExtraData(pos,2) ; // {deltaF-2, deltaF0, deltaF2}，2表示deltaF2
			printf("deltaF_PUCCH_Format2a:%d\n", deltaF_PUCCH_Format2a );
			pos += 2;
			int  deltaF_PUCCH_Format2b  = ExtraData(pos,2); // {deltaF-2, deltaF0, deltaF2}，2表示deltaF2
			printf("deltaF_PUCCH_Format2b:%d\n", deltaF_PUCCH_Format2b );
			pos += 2;
			
			int  deltaPreambleMsg3 =(ExtraData(pos,3)-1)*2; // 用于随机接入响应许可的PUSCH的功率计算。实际值= IE value * 2 [dB],4*2=8
			printf("deltaPreambleMsg3:%d\n", deltaPreambleMsg3 );
			pos += 3;
			/////////////////UL-CyclicPrefixLength
				
			int UL_CyclicPrefixLength= ExtraData(pos,2);   //ENUMERATED {len1, len2}循环前缀长度 。len1表示常规循环前缀，len2表示扩展循环前缀
			printf("UL_CyclicPrefixLength:%d\n", UL_CyclicPrefixLength );
			pos+=2;
			///end of RadioResourceConfigCommonSIB,

			//////// UE-TimersAndConstants配置项处理，连接态和空闲态相关计时器设置，目前不用。
			//跳过3+3+3+3+3+3=18比特
			int TimersAndConstants1= ExtraData(pos,3);   //ENUMERATED {len1, len2}循环前缀长度 。len1表示常规循环前缀，len2表示扩展循环前缀
			printf("TimersAndConstants1:%d\n", TimersAndConstants1 );
			pos+=3;
			int TimersAndConstants2= ExtraData(pos,3);   //ENUMERATED {len1, len2}循环前缀长度 。len1表示常规循环前缀，len2表示扩展循环前缀
			printf("TimersAndConstants2:%d\n", TimersAndConstants2 );
			pos+=3;
			int TimersAndConstants3= ExtraData(pos,3);   //ENUMERATED {len1, len2}循环前缀长度 。len1表示常规循环前缀，len2表示扩展循环前缀
			printf("TimersAndConstants3:%d\n", TimersAndConstants3 );
			pos+=3;
			int TimersAndConstants4= ExtraData(pos,3);   //ENUMERATED {len1, len2}循环前缀长度 。len1表示常规循环前缀，len2表示扩展循环前缀
			printf("TimersAndConstants4:%d\n", TimersAndConstants4 );
			pos+=3;
			int TimersAndConstants5= ExtraData(pos,3);   //ENUMERATED {len1, len2}循环前缀长度 。len1表示常规循环前缀，len2表示扩展循环前缀
			printf("TimersAndConstants5:%d\n", TimersAndConstants5 );
			pos+=3;
			int TimersAndConstants6= ExtraData(pos,3);   //ENUMERATED {len1, len2}循环前缀长度 。len1表示常规循环前缀，len2表示扩展循环前缀
			printf("TimersAndConstants6:%d\n", TimersAndConstants6 );
			pos+=3;
			//pos+=18;
					
			////////freqInfo配置项处理
			option_level2 =ExtraData(pos,2);
			printf("option_level2:%d\n",  option_level2);
			pos+=2;
			
			if(option_level2>1)
			{
				int  ul_CarrierFreq = ExtraData(pos,16);//0-65535
				printf("ul_CarrierFreq:%d\n", ul_CarrierFreq );
				pos+=16;
			}
			
			printf("option_level2:%d\n", option_level2 );
			if((option_level2%2)==1)
			{
				int  ul_Bandwidth =Bandwidth[ExtraData(pos,3)];
				printf("ul_Bandwidth:%d\n", ul_Bandwidth );
				pos+=3;
		
			}
			
			int  AdditionalSpectrumEmission = ExtraData(pos,5)+1;
			printf("AdditionalSpectrumEmission:%d\n", AdditionalSpectrumEmission );
			pos+=5;

			//MBSFN-SubframeConfigList配置参数处理
			if((option_level1&0x01) == 1)	
			{
				int maxMBSFN_Allocations= ExtraData(pos,3)+1;//取值范围1-8
				printf("maxMBSFN_Allocations:%d\n", maxMBSFN_Allocations );
				pos+=3;
				
				int k;
				for( k = 0; k< maxMBSFN_Allocations;k++)
				{
					int  radioframeAllocationPeriod = ExtraData(pos,3);//ENUMERATED {n1, n2, n4, n8, n16, n32},
					printf("radioframeAllocationPeriod:%d\n",  radioframeAllocationPeriod);
					pos+=3;
					int  radioframeAllocationOffset =  ExtraData(pos,3);//	INTEGER (0..7),
					printf("radioframeAllocationOffset:%d\n", radioframeAllocationOffset );
					pos+=3;
					int  choice_flag = ExtraData(pos,1);	
					printf("choice_flag:%d\n", choice_flag );
					pos+=1;
					if(choice_flag ==0)
					{
						int  oneFrame=ExtraData(pos,6);// 取值范围BIT STRING (SIZE(6)),
						printf("oneFrame:%d\n", oneFrame );
						pos+=6;
					}
					else //if（choice_flag ==1）
					{
						int  fourFrames= ExtraData(pos,24);//取值范围BIT STRING (SIZE(24))
						printf("fourFrames:%d\n", fourFrames );
						pos+=24;
					}
				}
			}//参数可以不取，但需要按照规则跳过一定bit数

			int TimeAlignmentTimer = ExtraData(pos,3); //{sf500, sf750, sf1280, sf1920, sf2560, sf5120,	sf10240, infinity}
			printf("TimeAlignmentTimer:%d\n", TimeAlignmentTimer );
	
			pos+=3;
		
		}//end sib2
		
	printf("---pos:%d---\n",pos);

	}
	
	return pos;
}

int main_test_sib1()
{
/*	
	pos = 0;
	//bcch dl sch choice 
	int option_level1 =  ExtraData(pos,1);
	//printf("option_level1:%d, pos:%d, bitSize:%d\n", option_level1, pos, 2);
	pos +=1;

	//system message --type 0:sy  1:type  
	int option_level2 =  ExtraData(pos,1);  
	//printf("option_level2:%d, pos:%d, bitSize:%d\n", option_level2, pos, 1);
	pos +=1;
*/	
	//SystemInformationBlockType1 op 
	int option_level3 =   ExtraData(pos,3);  
	//printf("option_level3:%d, pos:%d, bitSize:%d\n", option_level3, pos, 3);
	pos +=3;

	//cellAccessRelatedInfo op 
	int option_level4 =   ExtraData(pos,1);  
	//printf("option_level4:%d, pos:%d, bitSize:%d\n", option_level4, pos, 1);
	pos +=1;
	
	//plmn list op 
	int option_level5 =   ExtraData(pos,3);  
	//printf("option_level5:%d, pos:%d, bitSize:%d\n", option_level5, pos, 3);
	pos +=3;
	
	//PLMN-Identity mcc op 
	int option_level6 =   ExtraData(pos,1);  
	//printf("option_level6:%d, pos:%d, bitSize:%d\n", option_level6, pos, 1);
	pos +=1;
	
	if(option_level6 == 1)
	{
		//dec mcc 
		int mcc1 =   ExtraData(pos,4);  
		printf("mcc1:%d\n", mcc1);
		pos +=4;
		
		int mcc2 =   ExtraData(pos,4);  
		printf("mcc2:%d\n", mcc2);
		pos +=4;
		
		int mcc3 =   ExtraData(pos,4);  
		printf("mcc3:%d\n", mcc3);
		pos +=4;
	}
	
	int mmc_size_op =   ExtraData(pos,1);  
	printf("mmc_size_op:%d\n", mmc_size_op);
	pos +=1;
	
	int mnc1,mnc2,mnc3;
	switch(mmc_size_op)
	{
		case(0):
			//dec mnc 
			mnc1 =   ExtraData(pos,4);  
			printf("mnc1:%d\n", mnc1);
			pos +=4;
			mnc2 =   ExtraData(pos,4);  
			printf("mnc2:%d\n", mnc2);
			pos +=4;
		break;
		
		case(1):
			mnc1 =   ExtraData(pos,4);  
			printf("mnc1:%d\n", mnc1);
			pos +=4;
			mnc2 =   ExtraData(pos,4);  
			printf("mnc2:%d\n", mnc2);
			pos +=4;
			mnc3 =   ExtraData(pos,4);  
			printf("mnc3:%d\n", mnc3);
			pos +=4;
		break;
		
		default:
		break;
	}
	
	//cellReservedForOperatorUse  enum 0 1
	int cellReservedForOperatorUse =   ExtraData(pos,1);  
	printf("cellReservedForOperatorUse:%d\n", cellReservedForOperatorUse);
	pos +=1;
	
	//TrackingAreaCode  BIT STRING (SIZE (16))
	int  TrackingAreaCode = ExtraData(pos,16);
	printf("TrackingAreaCode:%d\n", TrackingAreaCode);
	pos += 16;
	
	//CellIdentity BIT STRING (SIZE (28))
	int 	CellIdentity = ExtraData(pos,28);
	printf("CellIdentity:%d\n", CellIdentity);
	pos += 28;
	
	int cellBarred	=	ExtraData(pos,1);//0表示可以接入，1表示不能接入
	printf("cellBarred:%d\n", cellBarred);
	pos += 1;					
	
	int intraFreqReselection=	ExtraData(pos,1);//0表示允许同频重选，1表示不允许
	printf("intraFreqReselection:%d\n", intraFreqReselection);
	pos += 1;						
	int csg_Indication	=	ExtraData(pos,1);//用于家庭基站对用户接入的控制。
	printf("csg_Indication:%d\n", csg_Indication);
	pos += 1;		

	//csg-Identity	BIT STRING (SIZE (27))	OPTIONAL
	if(option_level4==1)
	{//csg-Identity						CSG-Identity
		pos += 27;
	}

	//cellSelectionInfo 解译
	int option_level7 =  ExtraData(pos,1);
	//printf("option_level7:%d, pos:%d, bitSize:%d\n", option_level7, pos, 1);
	pos +=1;
	
	int QRxLevMin =  ExtraData(pos,6)-70;
	printf("Q-RxLevMin:%d\n", QRxLevMin);
	pos +=6;//Q-RxLevMin重选最小电平值INTEGER (-70..-22)
	
	if(option_level7 ==1)
	{
		int RxLevMinOffset = ExtraData(pos,3);
		printf("RxLevMinOffset:%d\n", RxLevMinOffset);
		pos +=3;//q-RxLevMinOffset INTEGER (1..8)
	}
	
	//SystemInformationBlockType1 op p-MAX
	if ((option_level3&0x04) == 4)
	{
		int pMAX = ExtraData(pos,6)-30;
		printf("pMAX:%d\n", pMAX);

		pos +=6;//p-MAX INTEGER (-30..33)
	}
	
	int freqBandIndicator = ExtraData(pos,6)+1;//1-64
	printf("freqBandIndicator:%d\n", freqBandIndicator);
	pos +=6;

	//处理schedulingInforList
	//SEQUENCE (SIZE (1..maxSI-Message)) OF SchedulingInfo
	//maxSI-Message	 INTEGER ::= 32	-- Maximum number of SI messages
	int SI_Message_num = ExtraData(pos,5)+1;
	printf("SI_Message_num:%d\n", SI_Message_num);
	pos +=5;
	
	int i;
	for( i = 0; i< SI_Message_num;i++)
	{
		//0-6
		int siPeriodicity = ExtraData(pos,3);
		printf("siPeriodicity:%d\n", siPeriodicity);
		pos +=3;		
		
		//maxSIB INTEGER ::= 32	-- Maximum number of SIBs
		info_sib[i][1]= ExtraData(pos,5);//取值意义见附件1
		printf("info_sib[%d][1]:%d\n",i, info_sib[i][1]);
		pos +=5;
		int j;
		for( j = 0; j < info_sib[i][1];j++)
		{
			int SIBType = ExtraData(pos,5);
			printf("SIBType:%d\n", SIBType);
			pos +=5;
		}

	}
	
	//读取TDD配置信息
	if ((option_level3&0x02) == 2)
	{
	//	printf("\nTDD config\n");
		int subframeAssignment=ExtraData(pos,3);////用于指示上下行子帧的配置,取值意义见附件1
		printf("subframeAssignment:%d\n", subframeAssignment);
		pos +=3;

		int	specialSubframePatternst=ExtraData(pos,4);//特殊自帧配比,取值意义见附件1
		printf("specialSubframePatternst:%d\n", specialSubframePatternst);
		pos +=4;
	//	printf("TDD config End\n\n");
	}
	
	//32
	int si_WindowLength = si_ms_time[ExtraData(pos,3)];////用于指示上下行子帧的配置,取值意义见附件1
	printf("si_WindowLength:%d\n", si_WindowLength);
	pos +=3;

	int systemInfoValueTag =ExtraData(pos,5);//			INTEGER (0..31),
	printf("systemInfoValueTag:%d\n", systemInfoValueTag);
	pos +=5;
	
	printf("---pos:%d---\n",pos);
	
	int SystemInformationBlockType1_v890OP =ExtraData(pos,1);
	printf("SystemInformationBlockType1_v890OP:%d\n", SystemInformationBlockType1_v890OP);
	pos+=1;
	
	//nonCriticalExtension SystemInformationBlockType1-v890-IEs
	if ((option_level3&0x01) == 1)
	{
		//nonCriticalExtensionOP
		int nonCriticalExtensionOP =ExtraData(pos,2);
		printf("nonCriticalExtensionOP:%d\n", nonCriticalExtensionOP);
		pos +=2;
		
		//lateNonCriticalExtension OCTET STRING (CONTAINING SystemInformationBlockType1-v8h0-IEs)
		if ((nonCriticalExtensionOP&0x02) == 0)
		{
			//...
			int maxMulBandNu =ExtraData(pos,3)+1;
			printf("maxMulBandNu:%d\n", maxMulBandNu);
			pos +=3;
			pos +=2; //跳过2bit；不明字段
			
			int k=0;
			for(k=0;k<maxMulBandNu;k++)
			{
				int FreqBandIndicator =ExtraData(pos,6)+1;
				printf("FreqBandIndicator:%d\n", FreqBandIndicator);
				pos +=6;
				
			}
					
			int lastNoCritialExtension[4];
			for(k=0;k<4;k++)
			{
				lastNoCritialExtension[k] =ExtraData(pos,4);
				printf("lastNoCritialExtension[%d]:%d\n", k,lastNoCritialExtension[k]);
				pos +=4;
			}				
		}
		
	}	
	return 0;	
}


int ExtraData(int bit_pos, int bitsize)
{
	//只对小于32bit的数据进行截取
	int jieguo = 0;	
	jieguo = ((data_p[(int)((bit_pos)/8)]&mask[(int)((bit_pos)%8)])>0?1:0);
	if(bitsize>1)
	{
		int i;
		for( i = 1; i<bitsize;i++)
		{
		  	jieguo *=2;
			jieguo += ((data_p[(int)((bit_pos+i)/8)]&mask[(int)((bit_pos+i)%8)])>0?1:0);
		}
	}
	return jieguo;
}


