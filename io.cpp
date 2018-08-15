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

#define SegmentStart 0x01000  //Segment = 0x01000~0x010FF  相当于地址一类的东西
#define SegmentSize 255 //SegmentA + SegmentB = 256

//*********************************************************
//读取片内存储的数据
//*********************************************************
char ReadSegment_256(char index)
{
  char *flash_ptr = ((char *) SegmentStart) + index;  //完全看作内存中的字符本身了，从开头开始，移动了几个字符
  return *flash_ptr;  //仅仅是返回一个指针，格式需要自己制定，一个字节就够了
}

// *****************************************************
//把数组写入数据到片内FLASH，必须先全部擦除再写入
//参数index:保存数组的位置
//参数value:数组的指针
//参数size:数组的大小
// *****************************************************
void WriteSegment_256 (char index,char *value,char size)  //大概也知道咋用了
{
  char buffer[SegmentSize],i=0;
  char *flash_ptr = (char *) SegmentStart;  //也是从最开始算的

  //先读取原FLASH数组
  for(i=0;i<SegmentSize;i++)  //一共就256个字节
    buffer[i]=ReadSegment_256(i);

  //擦除FLASH，必须
  FCTL1 = FWKEY + ERASE;                    // Set Erase bit
  FCTL3 = FWKEY;                            // Clear Lock bit
  *flash_ptr = 0;                           // Dummy write to erase Flash segment

  //把整个数组都写入FLASH
  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

  for(i=0;i<size;i++)//修改原数组
    buffer[index+i]=value[i];
  for(i=0; i<SegmentSize; i++)//写入数据到FLASH
    *(flash_ptr++) = buffer[i];  //也是一股脑全写进去

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
}
