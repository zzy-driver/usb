/******************************************************************
   ������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
			
        ��ӭ�����ҵ�USBר����http://group.ednchina.com/93/
        ��ӭ�����ҵ�blog��   http://www.ednchina.com/blog/computer00
                             http://computer00.21ic.org

UsbCore.c file

���ߣ�����ȦȦ
��������: 2008.06.29
�޸�����: 2009.03.14
�汾��V1.1
��Ȩ���У�����ؾ���
Copyright(C) ����ȦȦ 2008-2018
All rights reserved            
*******************************************************************/

#include <AT91SAM7S64.H>
#include "config.h"
#include "AT91SAMxUSB.h"
#include "uart.h"
#include "usbcore.h"
#include "led.h"
#include "SCSI.h"

uint8 Buffer[16];  //���˵�0�õĻ�����
uint8 CBW[31];  //����CBW�õĻ�����
uint8 CSW[13];  //����CSW�õĻ�����

//��������߼���Ԫ����ʵ������һ���߼���Ԫ������ֵΪ0��
//�����ڶԺ����������У��������߼���Ԫ�ֶΣ������
//�������0�ĳ�1�������������߼���Ԫ���Ӷ���ʾ�������
//��ȫһ���Ĵ��̡��ĳ�n���ͻ���ʾn+1�������ȫһ���Ĵ��̡�
//��������16���߼���Ԫ��n=15����
const uint8 MaxLun[1]={0};

//����Ľ׶Σ�������(COMMAND_STAGE)������(DATA_STAGE)��״̬(STATUS_STAGE)������
uint8 TransportStage;

//USB�豸����ĸ��ֶ�
uint8  bmRequestType;
uint8  bRequest;
uint16 wValue;
uint16 wIndex;
uint16 wLength;
//��ǰ�������ݵ�λ��
uint8 * pSendData;
//��Ҫ�������ݵĳ���
uint16 SendLength;
//�Ƿ���Ҫ����0���ݰ��ı�־����USB���ƴ�������ݹ����У�
//�����ص����ݰ��ֽ�������������ʱ������Ϊ���ݹ��̽�����
//��������ֽ�����ʵ����Ҫ���ص��ֽ���������ʵ�ʷ��ص��ֽ�
//���ָպ��Ƕ˵�0��С��������ʱ������Ҫ����һ��0���ȵ����ݰ�
//���������ݹ��̡������������һ����־������������Ƿ���Ҫ����
//һ��0���ȵ����ݰ���
uint8 NeedZeroPacket;

//��ǰ������ֵ��ֻ�������÷�0���ú�
uint8 ConfigValue;

//�˵�1�����Ƿ�æ�ı�־������������������ʱ���ñ�־Ϊ�档
//���������п���ʱ���ñ�־Ϊ�١�
uint8 Ep1InIsBusy;

//�˵�3�����Ƿ�æ�ı�־������������������ʱ���ñ�־Ϊ�档
//���������п���ʱ���ñ�־Ϊ�١�
uint8 Ep3InIsBusy;

//�����˶��ٴα���ļ�����
uint32 Count=0;

//USB�豸�������Ķ���
const uint8 DeviceDescriptor[0x12]=  //�豸������Ϊ18�ֽ�
{
//bLength�ֶΡ��豸�������ĳ���Ϊ18(0x12)�ֽ�
 0x12,
 
//bDescriptorType�ֶΡ��豸�������ı��Ϊ0x01
 0x01,
 
//bcdUSB�ֶΡ��������ð汾ΪUSB1.1����0x0110��
//������С�˽ṹ�����Ե��ֽ����ȣ���0x10��0x01��
 0x10,
 0x01,
 
//bDeviceClass�ֶΡ����ǲ����豸�������ж����豸�࣬
//���ڽӿ��������ж����豸�࣬���Ը��ֶε�ֵΪ0��
 0x00,
 
//bDeviceSubClass�ֶΡ�bDeviceClass�ֶ�Ϊ0ʱ�����ֶ�ҲΪ0��
 0x00,
 
//bDeviceProtocol�ֶΡ�bDeviceClass�ֶ�Ϊ0ʱ�����ֶ�ҲΪ0��
 0x00,
 
//bMaxPacketSize0�ֶΡ�AT91SAM7S64�Ķ˵�0��С��16�ֽڡ�
 0x08,
 
//idVender�ֶΡ�����ID�ţ���������ȡ0x8888������ʵ���á�
//ʵ�ʲ�Ʒ�������ʹ�ó���ID�ţ������USBЭ�����볧��ID�š�
//ע��С��ģʽ�����ֽ����ȡ�
 0x88,
 0x88,
 
//idProduct�ֶΡ���ƷID�ţ������ǵڰ˸�ʵ�飬��������ȡ0x2108��
//ע��С��ģʽ�����ֽ�Ӧ����ǰ��
 0x08,
 0x21,
 
//bcdDevice�ֶΡ��豸�汾�ţ�ȡ1.0�棬��0x0100��
//С��ģʽ�����ֽ����ȡ�
 0x00,
 0x01,
 
//iManufacturer�ֶΡ������ַ���������ֵ��Ϊ�˷������͹�����
//�ַ��������ʹ�1��ʼ�ɡ�
 0x01,

//iProduct�ֶΡ���Ʒ�ַ���������ֵ���ո�����1�������ȡ2�ɡ�
//ע���ַ�������ֵ��Ҫʹ����ͬ��ֵ��
 0x02,
 
//iSerialNumber�ֶΡ��豸�����к��ַ�������ֵ��
//����ȡ3�Ϳ����ˡ�
 0x03,

//bNumConfigurations�ֶΡ����豸�����е���������
//����ֻ��Ҫһ�����þ����ˣ���˸�ֵ����Ϊ1��
 0x01
};
//////////////////////////�豸���������//////////////////////////////

//USB�������������ϵĶ���
//�����������ܳ���Ϊ9+9+7+7�ֽ�
const uint8 ConfigurationDescriptor[9+9+7+7]=
{
 /***************����������***********************/
 //bLength�ֶΡ������������ĳ���Ϊ9�ֽڡ�
 0x09,
 
 //bDescriptorType�ֶΡ��������������Ϊ0x02��
 0x02,
 
 //wTotalLength�ֶΡ��������������ϵ��ܳ��ȣ�
 //���������������������ӿ��������������������˵��������ȡ�
 sizeof(ConfigurationDescriptor)&0xFF, //���ֽ�
 (sizeof(ConfigurationDescriptor)>>8)&0xFF, //���ֽ�
 
 //bNumInterfaces�ֶΡ������ð����Ľӿ�������1���ӿڡ�
 0x01,
 
 //bConfiguration�ֶΡ������õ�ֵΪ1��
 0x01,
 
 //iConfigurationz�ֶΣ������õ��ַ�������������û�У�Ϊ0��
 0x00,
 
 //bmAttributes�ֶΣ����豸�����ԡ��������ǵİ��������߹���ģ�
 //�������ǲ���ʵ��Զ�̻��ѵĹ��ܣ����Ը��ֶε�ֵΪ0x80��
 0x80,
 
 //bMaxPower�ֶΣ����豸��Ҫ�������������������ǵİ���
 //��Ҫ�ĵ�������100mA�����������������Ϊ100mA������ÿ��λ
 //����Ϊ2mA��������������Ϊ50(0x32)��
 0x32,
 
 /*****************�ӿ�������*******************/
 //bLength�ֶΡ��ӿ��������ĳ���Ϊ9�ֽڡ�
 0x09,
 
 //bDescriptorType�ֶΡ��ӿ��������ı��Ϊ0x04��
 0x04,
 
 //bInterfaceNumber�ֶΡ��ýӿڵı�ţ���һ���ӿڣ����Ϊ0��
 0x00,
 
 //bAlternateSetting�ֶΡ��ýӿڵı��ñ�ţ�Ϊ0��
 0x00,
 
 //bNumEndpoints�ֶΡ���0�˵����Ŀ���ýӿ���2�������˵�
 0x02,
 
 //bInterfaceClass�ֶΡ��ýӿ���ʹ�õ��ࡣ�������洢�豸�ӿ���Ĵ���Ϊ0x08��
 0x08,
 
 //bInterfaceSubClass�ֶΡ��ýӿ���ʹ�õ����ࡣSCSI͸��������������Ϊ0x06��
 0x06,
 
 //bInterfaceProtocol�ֶΡ�Э��Ϊ���������䣬����Ϊ0x50��
 0x50,
 
 //iConfiguration�ֶΡ��ýӿڵ��ַ�������ֵ������û�У�Ϊ0��
 0x00,
 
 /*************��׼������������˵�������****************/
 //bLength�ֶΡ��˵�����������Ϊ7�ֽڡ�
 0x07,
 
 //bDescriptorType�ֶΡ��˵����������Ϊ0x05��
 0x05,
 
 //bEndpointAddress�ֶΡ��˵�ĵ�ַ������ʹ������˵�1��
 //D7λ��ʾ���ݷ�������˵�D7Ϊ1����������˵�1�ĵ�ַΪ0x81��
 0x81,
 
 //bmAttributes�ֶΡ�D1~D0Ϊ�˵㴫������ѡ��
 //�ö˵�Ϊ���˵㡣�����˵�ı��Ϊ2������λ����Ϊ0��
 0x02,
 
 //wMaxPacketSize�ֶΡ��ö˵�����������˵�1��������Ϊ64�ֽڡ�
 //ע����ֽ����ȡ�
 0x40,
 0x00,
 
 //bInterval�ֶΡ��˵��ѯ��ʱ�䣬�˴������塣
 0x00,
 
 /*************��׼������������˵�������****************/
 //bLength�ֶΡ��˵�����������Ϊ7�ֽڡ�
 0x07,
 
 //bDescriptorType�ֶΡ��˵����������Ϊ0x05��
 0x05,
 
 //bEndpointAddress�ֶΡ��˵�ĵ�ַ������ʹ������˵�2��
 //D7λ��ʾ���ݷ�������˵�D7Ϊ0����������˵�2�ĵ�ַΪ0x02��
 0x02,
 
 //bmAttributes�ֶΡ�D1~D0Ϊ�˵㴫������ѡ��
 //�ö˵�Ϊ���˵㡣�����˵�ı��Ϊ2������λ����Ϊ0��
 0x02,
 
 //wMaxPacketSize�ֶΡ��ö˵�����������˵�2��������Ϊ16�ֽڡ�
 //ע����ֽ����ȡ�
 0x40,
 0x00,
 
 //bInterval�ֶΡ��˵��ѯ��ʱ�䣬�˴������塣
 0x00
};
////////////////////////�����������������//////////////////////////

/************************����ID�Ķ���********************/
const uint8 LanguageId[4]=
{
 0x04, //���������ĳ���
 0x03, //�ַ���������
 //0x0409Ϊ��ʽӢ���ID
 0x09,
 0x04
};
////////////////////////����ID���//////////////////////////////////

/**************************************************/
/*********        ��ת���������         **********/
/********* Http://computer00.21ic.org    **********/
/*********        ����: ����ȦȦ         **********/
/*********         ��ӭ���ʹ��          **********/
/*********    ��Ȩ���У�������д������   **********/
/**************************************************/

//http://computer00.21ic.org/user1/2198/archives/2007/42769.html
//�ַ���������ȦȦ��USBר�� Http://group.ednchina.com/93/����Unicode����
//8λС�˸�ʽ
const uint8 ManufacturerStringDescriptor[82]={
 82,         //���������ĳ���Ϊ82�ֽ�
 0x03,       //�ַ��������������ͱ���Ϊ0x03
 0x35, 0x75, //��
 0x11, 0x81, //��
 0x08, 0x57, //Ȧ
 0x08, 0x57, //Ȧ
 0x84, 0x76, //��
 0x55, 0x00, //U
 0x53, 0x00, //S
 0x42, 0x00, //B
 0x13, 0x4e, //ר
 0x3a, 0x53, //��
 0x20, 0x00, // 
 0x48, 0x00, //H
 0x74, 0x00, //t
 0x74, 0x00, //t
 0x70, 0x00, //p
 0x3a, 0x00, //:
 0x2f, 0x00, ///
 0x2f, 0x00, ///
 0x67, 0x00, //g
 0x72, 0x00, //r
 0x6f, 0x00, //o
 0x75, 0x00, //u
 0x70, 0x00, //p
 0x2e, 0x00, //.
 0x65, 0x00, //e
 0x64, 0x00, //d
 0x6e, 0x00, //n
 0x63, 0x00, //c
 0x68, 0x00, //h
 0x69, 0x00, //i
 0x6e, 0x00, //n
 0x61, 0x00, //a
 0x2e, 0x00, //.
 0x63, 0x00, //c
 0x6f, 0x00, //o
 0x6d, 0x00, //m
 0x2f, 0x00, ///
 0x39, 0x00, //9
 0x33, 0x00, //3
 0x2f, 0x00  ///
};
/////////////////////////�����ַ�������/////////////////////////////

//�ַ�����21IC DIY U��ѧϰ�� ֮ ��U�̡���Unicode���롱��Unicode����
//8λС�˸�ʽ
const uint8 ProductStringDescriptor[42]={
 42,         //���������ĳ���Ϊ42�ֽ�
 0x03,       //�ַ��������������ͱ���Ϊ0x03
 0x32, 0x00, //2
 0x31, 0x00, //1
 0x49, 0x00, //I
 0x43, 0x00, //C
 0x20, 0x00, // 
 0x44, 0x00, //D
 0x49, 0x00, //I
 0x59, 0x00, //Y
 0x20, 0x00, // 
 0x55, 0x00, //U
 0xd8, 0x76, //��
 0x66, 0x5b, //ѧ
 0x60, 0x4e, //ϰ
 0x7f, 0x67, //��
 0x20, 0x00, // 
 0x4b, 0x4e, //֮
 0x20, 0x00, // 
 0x47, 0x50, //��
 0x55, 0x00, //U
 0xd8, 0x76  //��
};
////////////////////////��Ʒ�ַ�������////////////////////////////

//�ַ�����2009-03-16����Unicode����
//8λС�˸�ʽ
const uint8 SerialNumberStringDescriptor[22]={
22,         //���������ĳ���Ϊ22�ֽ�
0x03,       //�ַ��������������ͱ���Ϊ0x03
0x32, 0x00, //2
0x30, 0x00, //0
0x30, 0x00, //0
0x39, 0x00, //9
0x2d, 0x00, //-
0x30, 0x00, //0
0x33, 0x00, //3
0x2d, 0x00, //-
0x31, 0x00, //1
0x36, 0x00  //6
};
//////////////////////��Ʒ���к��ַ�������/////////////////////////

/********************************************************************
�������ܣ����߹����жϴ���������
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
void UsbBusSuspend(void)
{
#ifdef DEBUG0
 Prints("USB���߹���\r\n");
#endif
}
////////////////////////End of function//////////////////////////////

/********************************************************************
�������ܣ����߸�λ�жϴ���������
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
void UsbBusReset(void)
{
#ifdef DEBUG0
 Prints("USB���߸�λ��\r\n");
#endif
 UsbChipResetEndpoint(); //��λ�˵�
 ConfigValue=0; //����ֵ��ʼ��Ϊ0
 UsbChipSetConfig(0);  //����оƬ������ֵΪ0
 
 Ep1InIsBusy=0;  //��λ��˵�1���뻺�������С�
 Ep3InIsBusy=0;  //��λ��˵�3���뻺�������С�
}
////////////////////////End of function//////////////////////////////

/********************************************************************
�������ܣ�����pData��SendLength�����ݷ��͵��˵�0�ĺ�����
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
void UsbEp0SendData(void)
{
 //������д���˵���ȥ׼������
 //д֮ǰҪ���ж�һ����Ҫ���͵������Ƿ�ȶ˵�0
 //��󳤶ȴ���������˵��С����һ��ֻ�ܷ���
 //�����������ݡ��˵�0����������DeviceDescriptor[7]
 if(SendLength>DeviceDescriptor[7])
 {
  //���������ȷ���
  UsbChipWriteEndpointBuffer(0,DeviceDescriptor[7],pSendData);
  //���ͺ�ʣ���ֽ�������������
  SendLength-=DeviceDescriptor[7];
  //����һ�κ�ָ��λ��Ҫ����
  pSendData+= DeviceDescriptor[7];
 }
 else
 {
  if(SendLength!=0)
  {
   //����������������ֱ�ӷ���
   UsbChipWriteEndpointBuffer(0,SendLength,pSendData);
   //������Ϻ�SendLength���ȱ�Ϊ0
   SendLength=0;
  }
  else //���Ҫ���͵����ݰ�����Ϊ0
  {
   if(NeedZeroPacket==1) //�����Ҫ����0��������
   {
    UsbChipWriteEndpointBuffer(0,0,pSendData); //����0�������ݰ�
    NeedZeroPacket=0; //����Ҫ����0�������ݰ���־
   }
  }
 }
}
////////////////////////End of function//////////////////////////////

/********************************************************************
�������ܣ�USB�˵�0���ݹ������ݴ���������
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ú�����������0�˵���ƴ�������ݻ�״̬���̡�
********************************************************************/
void UsbEp0DataOut(void)
{
 UsbChipReadEndpointBuffer(0,16,Buffer);
 UsbChipClearBuffer(0);
}
////////////////////////End of function//////////////////////////////

/********************************************************************
�������ܣ��˵�0����жϴ���������
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
void UsbEp0Out(void)
{
 int32 L;
#ifdef DEBUG0
 Prints("USB�˵�0����жϡ�\r\n");
#endif
 //�ж��Ƿ��ǽ�����
 if(UsbChipIsSetup(0))
 {
  L=UsbChipReadEndpointBuffer(0,16,Buffer); //��������������
  UsbChipAcknowledgeSetup(0); //Ӧ������
  UsbChipClearBuffer(0);      //�建����
  if(L!=8) //����8�ֽڵı�׼����ֱ�ӷ���
   return;
  
  //������������豸����ĸ��ֶ���
  bmRequestType=Buffer[0];
  bRequest=Buffer[1];
  wValue=Buffer[2]+(((uint16)Buffer[3])<<8);
  wIndex=Buffer[4]+(((uint16)Buffer[5])<<8);
  wLength=Buffer[6]+(((uint16)Buffer[7])<<8);
  //����Ĵ����жϾ�������󣬲����ݲ�ͬ�����������ز���
  //���D7λΪ1����˵������������
  if((bmRequestType&0x80)==0x80)
  {
   //����bmRequestType��D6~5λɢת��D6~5λ��ʾ���������
   //0Ϊ��׼����1Ϊ������2Ϊ��������
   switch((bmRequestType>>5)&0x03)
   {
    case 0:  //��׼����
     #ifdef DEBUG0
      Prints("USB��׼��������");
     #endif
     //USBЭ�鶨���˼�����׼������������ʵ����Щ��׼���󼴿�
     //����Ĵ�����bRequest�У��Բ�ͬ������������ɢת
     //��ʵ�ϣ����ǻ���Ҫ�Խ����߽���ɢת����Ϊ��ͬ�����������
     //�ǲ�һ���ġ���������bmRequestType��D4~D0λ�ж��塣
     //��������Ϊ�˼򻯲�������Щ��ʡ���˶Խ����ߵ��жϡ�
     //�����ȡ������������ֻ����������������������
     switch(bRequest)
     {
      case GET_CONFIGURATION: //��ȡ����
       #ifdef DEBUG0
        Prints("��ȡ���á�\r\n");
       #endif
      break;
      
      case GET_DESCRIPTOR:  //��ȡ������
       #ifdef DEBUG0
        Prints("��ȡ����������");
       #endif
       //�����������ͽ���ɢת������ȫ���豸��
       //��׼����ֻ֧�ַ��͵��豸���豸�����á��ַ�������������
       switch((wValue>>8)&0xFF)
        {
         case DEVICE_DESCRIPTOR: //�豸������
          #ifdef DEBUG0
           Prints("�豸��������\r\n");
          #endif
          pSendData=(uint8)DeviceDescriptor;  //��Ҫ���͵�����
          //�ж�������ֽ����Ƿ��ʵ����Ҫ���͵��ֽ�����
          //������������豸��������������ݳ��Ⱦ���
          //DeviceDescriptor[0]���������ı�ʵ�ʵĳ���
          //��ôֻ����ʵ�ʳ��ȵ�����
          if(wLength>DeviceDescriptor[0])
          {
           SendLength=DeviceDescriptor[0];
           if(SendLength%DeviceDescriptor[7]==0) //���Ҹպ������������ݰ�ʱ
           {
            NeedZeroPacket=1; //��Ҫ����0���ȵ����ݰ�
           }
          }
          else
          {
           SendLength=wLength;
          }
          //������ͨ��EP0����
          UsbEp0SendData();
         break;
         
         case CONFIGURATION_DESCRIPTOR:  //����������
          #ifdef DEBUG0
           Prints("������������\r\n");
          #endif
          pSendData=(uint8 *)ConfigurationDescriptor; //��Ҫ���͵�����Ϊ����������
          //�ж�������ֽ����Ƿ��ʵ����Ҫ���͵��ֽ�����
          //������������������������ϣ�������ݳ��Ⱦ���
          //ConfigurationDescriptor[3]*256+ConfigurationDescriptor[2]��
          //�������ı�ʵ�ʵĳ�����ôֻ����ʵ�ʳ��ȵ�����
          SendLength=ConfigurationDescriptor[3];
          SendLength=SendLength*256+ConfigurationDescriptor[2];
          if(wLength>SendLength)
          {
           if(SendLength%DeviceDescriptor[7]==0) //���Ҹպ������������ݰ�ʱ
           {
            NeedZeroPacket=1; //��Ҫ����0���ȵ����ݰ�
           }
          }
          else
          {
           SendLength=wLength;
          }
          //������ͨ��EP0����
          UsbEp0SendData();
         break;
         
         case STRING_DESCRIPTOR:  //�ַ���������
          #ifdef DEBUG0
           Prints("�ַ���������");
          #endif
          switch(wValue&0xFF)  //����wValue�ĵ��ֽڣ�����ֵ��ɢת
          {
           case 0:  //��ȡ����ID
            #ifdef DEBUG0
             Prints("(����ID)��\r\n");
            #endif
            pSendData=(uint8 *)LanguageId;
            SendLength=LanguageId[0];
           break;
           
           case 1:  //�����ַ���������ֵΪ1����������Ϊ�����ַ���
           #ifdef DEBUG0
             Prints("(��������)��\r\n");
            #endif
            pSendData=(uint8 *)ManufacturerStringDescriptor;
            SendLength=ManufacturerStringDescriptor[0];
           break;
           
           case 2:  //��Ʒ�ַ���������ֵΪ2����������Ϊ��Ʒ�ַ���
           #ifdef DEBUG0
             Prints("(��Ʒ����)��\r\n");
            #endif
            pSendData=(uint8 *)ProductStringDescriptor;
            SendLength=ProductStringDescriptor[0];
           break;
           
           case 3:  //��Ʒ���кŵ�����ֵΪ3����������Ϊ���к�
           #ifdef DEBUG0
             Prints("(��Ʒ���к�)��\r\n");
            #endif
            pSendData=(uint8 *)SerialNumberStringDescriptor;
            SendLength=SerialNumberStringDescriptor[0];
           break;
           
           default :
            #ifdef DEBUG0
             Prints("(δ֪������ֵ)��\r\n");
            #endif
            //����δ֪����ֵ�����󣬷���һ��0���ȵİ�
            SendLength=0;
            NeedZeroPacket=1;
           break;
          }
          //�ж�������ֽ����Ƿ��ʵ����Ҫ���͵��ֽ�����
          //�������ı�ʵ�ʵĳ�����ôֻ����ʵ�ʳ��ȵ�����
          if(wLength>SendLength)
          {
           if(SendLength%DeviceDescriptor[7]==0) //���Ҹպ������������ݰ�ʱ
           {
            NeedZeroPacket=1; //��Ҫ����0���ȵ����ݰ�
           }
          }
          else
          {
           SendLength=wLength;
          }
          //������ͨ��EP0����
          UsbEp0SendData();         
         break;

         case REPORT_DESCRIPTOR:  //����������
          #ifdef DEBUG0
           Prints("������������\r\n");
          #endif
          pSendData=0; //��Ҫ���͵�����Ϊ����������
          SendLength=0; //��Ҫ���ص����ݳ���        
          //�ж�������ֽ����Ƿ��ʵ����Ҫ���͵��ֽ�����
          //�������ı�ʵ�ʵĳ�����ôֻ����ʵ�ʳ��ȵ�����
          if(wLength>SendLength)
          {
           if(SendLength%DeviceDescriptor[7]==0) //���Ҹպ������������ݰ�ʱ
           {
            NeedZeroPacket=1; //��Ҫ����0���ȵ����ݰ�
           }
          }
          else
          {
           SendLength=wLength;
          }
          //������ͨ��EP0����
          UsbEp0SendData();
         break;
                 
         default:  //����������
          #ifdef DEBUG0
           Prints("���������������������룺");
           PrintHex((wValue>>8)&0xFF);
           Prints("\r\n");
          #endif
         break;
        }
       break;
      
      case GET_INTERFACE: //��ȡ�ӿ�
       #ifdef DEBUG0
        Prints("��ȡ�ӿڡ�\r\n");
       #endif
      break;
      
      case GET_STATUS: //��ȡ״̬
       #ifdef DEBUG0
        Prints("��ȡ״̬��\r\n");
       #endif
      break;
      
      case SYNCH_FRAME: //ͬ��֡
       #ifdef DEBUG0
        Prints("ͬ��֡��\r\n");
       #endif
      break;
      
      default:  //δ����ı�׼����
       #ifdef DEBUG0
        Prints("����δ����ı�׼��������\r\n");
       #endif       
      break;
     }
    break;
    
    case 1:  //������
     #ifdef DEBUG0
      Prints("USB����������\r\n");
     #endif
     switch(bRequest)
     {
      case GET_MAX_LUN: //����ΪGET_MAX_LUN(0xFE)
       #ifdef DEBUG0
        Prints("��ȡ����߼���Ԫ��\r\n");
       #endif
       
       pSendData=(uint8 *)MaxLun; //Ҫ���ص�����λ��
       SendLength=1;     //����Ϊ1�ֽ�
       //�������ĳ��ȱ�ʵ�ʳ��ȶ̣�����������󳤶�
       if(wLength<SendLength) 
       {
        SendLength=wLength;
       }
       //������ͨ��EP0����
       UsbEp0SendData();
      break;
      
      default:
       #ifdef DEBUG0
        Prints("δ֪������\r\n");
       #endif
       SendLength=0;
       NeedZeroPacket=1;
      break;
     }
    //�ж�������ֽ����Ƿ��ʵ����Ҫ���͵��ֽ�����
    //�������ı�ʵ�ʵĳ�����ôֻ����ʵ�ʳ��ȵ�����
    if(wLength>SendLength)
    {
     if(SendLength%DeviceDescriptor[7]==0) //���Ҹպ������������ݰ�ʱ
     {
      NeedZeroPacket=1; //��Ҫ����0���ȵ����ݰ�
     }
    }
    else
    {
     SendLength=wLength;
    }
    //������ͨ��EP0����
    UsbEp0SendData();
    break;
    
    case 2:  //��������
     #ifdef DEBUG0
      Prints("USB������������\r\n");
     #endif
    break;
    
    default: //δ�������������ֻ��ʾһ��������Ϣ��
     #ifdef DEBUG0
      Prints("����δ�������������\r\n");
     #endif
    break;
   }
  }
  //����˵�����������
  else //if(bmRequestType&0x80==0x80)֮else
  {
   //����bmRequestType��D6~5λɢת��D6~5λ��ʾ���������
   //0Ϊ��׼����1Ϊ������2Ϊ��������
   switch((bmRequestType>>5)&0x03)
   {
    case 0:  //��׼����
     #ifdef DEBUG0
      Prints("USB��׼�������");
     #endif
     //USBЭ�鶨���˼�����׼�����������ʵ����Щ��׼���󼴿�
     //����Ĵ�����bRequest�У��Բ�ͬ������������ɢת
     switch(bRequest)
     {
      case CLEAR_FEATURE: //�������
       #ifdef DEBUG0
        Prints("������ԡ�\r\n");
       #endif
      break;
      
      case SET_ADDRESS:  //���õ�ַ
       #ifdef DEBUG0
        Prints("���õ�ַ����ַΪ��");
        PrintHex(wValue&0xFF); //��ʾ�����õĵ�ַ
        Prints("\r\n");
       #endif
       //���õ�ַû�����ݹ��̣�ֱ�ӽ��뵽״̬���̣�����һ��0���ȵ����ݰ�
       SendLength=0;
       NeedZeroPacket=1;
       //������ͨ��EP0����
       UsbEp0SendData();
       UsbChipWriteAddress(wValue&0xFF); //wValue�еĵ��ֽ������õĵ�ֵַ
      break;
      
      case SET_CONFIGURATION: //��������
       #ifdef DEBUG0
        Prints("�������á�\r\n");
       #endif
       //wValue�ĵ��ֽ�Ϊ���õ�ֵ�������ֵΪ��0������ʹ�ܷ�0�˵㡣        
       //���浱ǰ����ֵ
       ConfigValue=wValue&0xFF;
       //����оƬ��configֵ     
       UsbChipSetConfig(ConfigValue); 
         
       //ʹ�ܷ�0�˵㡣��0�˵�ֻ��������Ϊ��0�����ú����ʹ�ܡ�
       UsbChipSetEndpointEnable(ConfigValue);
      
       //����һ��0���ȵ�״̬���ݰ�
       SendLength=0;
       NeedZeroPacket=1;
       //������ͨ��EP0����
       UsbEp0SendData();
      break;
      
      case SET_DESCRIPTOR: //����������
       #ifdef DEBUG0
        Prints("������������\r\n");
       #endif
      break;
      
      case SET_FEATURE: //��������
       #ifdef DEBUG0
        Prints("�������ԡ�\r\n");
       #endif
      break;

      case SET_INTERFACE: //���ýӿ�
       #ifdef DEBUG0
        Prints("���ýӿڡ�\r\n");
       #endif
      break;      
      
      default:  //δ����ı�׼����
       #ifdef DEBUG0
        Prints("����δ����ı�׼�������\r\n");
        Prints("δ֪����\r\n");        
       #endif
        //ֻ��Ҫ����һ��0���ȵ����ݰ�����
        SendLength=0;
        NeedZeroPacket=1;
        //������ͨ��EP0����
        UsbEp0SendData();
      break;
     }
    break;
    
    case 1:  //������
     #ifdef DEBUG0
      Prints("USB���������");
     #endif
     switch(bRequest)
     {
      case MASS_STORAGE_RESET:
       #ifdef DEBUG0
        Prints("�������洢�豸��λ��\r\n");
       #endif
       
       //������������Ϊ����׶�(CBW)
       TransportStage=COMMAND_STAGE;
       //����һ��0���ȵ����ݰ�
       SendLength=0;
       NeedZeroPacket=1;
       //������ͨ��EP0����
       UsbEp0SendData();
      break;
      
      default:
       #ifdef DEBUG0
        Prints("δ֪����\r\n");
       #endif        
        //ֻ��Ҫ����һ��0���ȵ����ݰ�����
        SendLength=0;
        NeedZeroPacket=1;
        //������ͨ��EP0����
        UsbEp0SendData();
      break;
     }
    break;
    
    case 2:  //��������
     #ifdef DEBUG0
      Prints("USB�����������\r\n");
     #endif
    break;
    
    default: //δ�������������ֻ��ʾһ��������Ϣ��
     #ifdef DEBUG0
      Prints("����δ������������\r\n");
     #endif
    break;
   }
  }
 }
 //��ͨ�������
 else //�ж�setup��֮else
 {
  ClrCsr(0,1<<7);  //����DIRΪ0
  UsbEp0DataOut(); //������׼��������ݲ���
 }
}
////////////////////////End of function//////////////////////////////

/********************************************************************
�������ܣ��˵�0�����жϴ���������
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
void UsbEp0In(void)
{
#ifdef DEBUG0
 Prints("USB�˵�0�����жϡ�\r\n");
#endif
 //����˵�0����������жϱ�־λ
 ClrCsr(0,1<<0);
 
 //����ʣ����ֽ���
 UsbEp0SendData();
}
////////////////////////End of function//////////////////////////////

/********************************************************************
�������ܣ��˵�1�����жϴ���������
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
void UsbEp1In(void)
{
#ifdef DEBUG0
 Prints("USB�˵�1�����жϡ�\r\n");
#endif
 //����˵�1����������жϱ�־λ
 ClrCsr(1,1<<0);
 Ep1SendData();  //ͨ���˵�1��������
}
////////////////////////End of function//////////////////////////////

/********************************************************************
�������ܣ��˵�2����жϴ���������
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
void UsbEp2Out(void)
{
 uint8 Buf[64],Len;
 
#ifdef DEBUG0
 Prints("USB�˵�2����жϡ�\r\n");
#endif
 
 //����˵�2������жϱ�־λ
 //�޲���
 
 if(TransportStage==COMMAND_STAGE)
 {
  //�����ݶ��ص�CBW��������
  Len=UsbChipReadEndpointBuffer(2,sizeof(CBW),CBW);
  //����˵㻺����
  UsbChipClearBuffer(2);
  if(Len==31) //������յ������ݳ�����31�ֽڣ���˵����CBW
  {
   //���CBW��ǩ���Ƿ���ȷ��ǩ��Ϊ��USBC��
   if((CBW[0]=='U')&&(CBW[1]=='S')&&(CBW[2]=='B')&&(CBW[3]=='C'))
   {
    //CBWǩ����ȷ������SCSI����
    ProcScsiCommand();
   }
  }
 }
 else if(TransportStage==DATA_STAGE)
 {
  ProcScsiOutData(); //����SCSI�������
 }
 else
 {
  //��ȡ�˵�2�����ݡ�����ֵΪʵ�ʶ����������ֽ���
  Len=UsbChipReadEndpointBuffer(2,64,Buf);
  //����˵㻺����
  UsbChipClearBuffer(2);
 }
}
////////////////////////End of function//////////////////////////////

/********************************************************************
�������ܣ��˵�3�����жϴ���������
��ڲ������ޡ�
��    �أ��ޡ�
��    ע���ޡ�
********************************************************************/
void UsbEp3In(void)
{
#ifdef DEBUG0
 Prints("USB�˵�3�����жϡ�\r\n");
#endif
 //����˵�3����������жϱ�־λ
 ClrCsr(3,1<<0);
 //�˵�3���봦�ڿ���״̬
 Ep3InIsBusy=0;
}
////////////////////////End of function//////////////////////////////