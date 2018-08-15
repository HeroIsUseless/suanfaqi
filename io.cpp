#include  <msp430xG43x.h>

void WriteSegment_256 (char index,char *value,char size);
char ReadSegment_256(char index);

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop watchdog timer
  FCTL2 = FWKEY + FSSEL0 + FN0;             // MCLK/2 for Flash Timing Generator

  char str1[3]={0xAA,0xBB,0xCC};

  WriteSegment_256(0,str1,3);

  for(char i=0;i<255;i++)
    _NOP();

  char str2[3]={0xBB,0xAA,0xCC};
  WriteSegment_256(0,str2,3);

}

#define SegmentStart 0x01000  //Segment = 0x01000~0x010FF  �൱�ڵ�ַһ��Ķ���
#define SegmentSize 255 //SegmentA + SegmentB = 256

//*********************************************************
//��ȡƬ�ڴ洢������
//*********************************************************
char ReadSegment_256(char index)
{
  char *flash_ptr = ((char *) SegmentStart) + index;  //��ȫ�����ڴ��е��ַ������ˣ��ӿ�ͷ��ʼ���ƶ��˼����ַ�
  return *flash_ptr;  //�����Ƿ���һ��ָ�룬��ʽ��Ҫ�Լ��ƶ���һ���ֽھ͹���
}

// *****************************************************
//������д�����ݵ�Ƭ��FLASH��������ȫ��������д��
//����index:���������λ��
//����value:�����ָ��
//����size:����Ĵ�С
// *****************************************************
void WriteSegment_256 (char index,char *value,char size)  //���Ҳ֪��զ����
{
  char buffer[SegmentSize],i=0;
  char *flash_ptr = (char *) SegmentStart;  //Ҳ�Ǵ��ʼ���

  //�ȶ�ȡԭFLASH����
  for(i=0;i<SegmentSize;i++)  //һ����256���ֽ�
    buffer[i]=ReadSegment_256(i);

  //����FLASH������
  FCTL1 = FWKEY + ERASE;                    // Set Erase bit
  FCTL3 = FWKEY;                            // Clear Lock bit
  *flash_ptr = 0;                           // Dummy write to erase Flash segment

  //���������鶼д��FLASH
  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

  for(i=0;i<size;i++)//�޸�ԭ����
    buffer[index+i]=value[i];
  for(i=0; i<SegmentSize; i++)//д�����ݵ�FLASH
    *(flash_ptr++) = buffer[i];  //Ҳ��һ����ȫд��ȥ

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}
