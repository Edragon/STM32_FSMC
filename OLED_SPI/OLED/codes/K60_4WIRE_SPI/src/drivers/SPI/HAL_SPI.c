/*

 *
 * �ļ���: HAL_SPI.c
 * ��;: SPI�ײ�ģ����غ���
 * ����޸�����: 20120321
 *
 */
#include"HAL_SPI.h"

/*
//SPIģ���жϷ�����
#undef  VECTOR_042
#define VECTOR_042 LPLD_SPI_Isr
#undef  VECTOR_043
#define VECTOR_043 LPLD_SPI_Isr
#undef  VECTOR_044
#define VECTOR_044 LPLD_SPI_Isr
//���º�����LPLD_Kinetis�ײ���������޸�
extern void LPLD_SPI_Isr(void);
*/

//SPIӳ���ַ����
volatile SPI_MemMapPtr SPIx_Ptr[3] = {SPI0_BASE_PTR, 
                                      SPI1_BASE_PTR, 
                                      SPI2_BASE_PTR};

/*
 * SPI_Init
 * SPI��ʼ������
 * 
 * ����:
 *    spix--ѡ��SPIͨ��
 *      |__SPI0     PORTA15 SCK 
 *                  PORTA16 SOUT (serial OUT)
 *                  PORTA17 SIN  (serial IN)
 *      |__SPI1     PORTB11 SCK 
 *                  PORTB16 SOUT (serial OUT)
 *                  PORTB17 SIN  (serial IN)
 *      |__SPI2     PORTD12 SCK      
 *                  PORTD13 SOUT (serial OUT)
 *                  PORTD14 SIN  (serial IN)
 *    sck_div--SCK SCK��Ƶϵ��
 *      ��SCK��ʱ��ԴΪϵͳʱ��fSYS 
 *      SCKƵ�ʣ�F_SCK = (fSYS/PBR) x [(1+DBR)/BR]
 *      �ڳ�ʼ�������н�DBR = 1��PBR = 2 
 *      ������� F_SCK = fSYS/BR
 *      BR = SPI_SCK_DIV_x
 *      |__SPI_SCK_DIV_2      -2��Ƶ
 *      |__SPI_SCK_DIV_4      -4��Ƶ
 *      |__SPI_SCK_DIV_6      -6��Ƶ
 *      |__SPI_SCK_DIV_8      -8��Ƶ
 *      |__SPI_SCK_DIV_16     -16��Ƶ
 *      |__SPI_SCK_DIV_32     -32��Ƶ
 *      ......
 *      |__SPI_SCK_DIV_8192   -8192��Ƶ
 *      |__SPI_SCK_DIV_16384  -16384��Ƶ
 *      |__SPI_SCK_DIV_32768  -32768��Ƶ
 *
 *    pcs_num--PCS�˿ڵ�����
 *      ��� spix = SPI0
 *      |__1--PCS0 PORTA14
 *      |__2--PCS0 PORTA14
 *            PCS1 PORTC3
 *      |__3--PCS0 PORTA14
 *            PCS1 PORTC3
 *            PCS2 PORTC2
 *      |__4--PCS0 PORTA14
 *            PCS1 PORTC3
 *            PCS2 PORTC2
 *            PCS3 PORTC1
 *      |__5--PCS0 PORTA14
 *            PCS1 PORTC3
 *            PCS2 PORTC2
 *            PCS3 PORTC1
 *            PCS4 PORTC0
 *      |__6--PCS0 PORTA14
 *            PCS1 PORTC3
 *            PCS2 PORTC2
 *            PCS3 PORTC1
 *            PCS4 PORTC0
 *            PCS5 PORTB23
 *      ��� spix = SPI1
 *      |__1--PCS0 PORTB10
 *      |__2--PCS0 PORTB10
 *            PCS1 PORTB9
 *      |__3--PCS0 PORTB10
 *            PCS1 PORTB9
 *            PCS2 PORTE5
 *      |__4--PCS0 PORTB10
 *            PCS1 PORTB9
 *            PCS2 PORTE5
 *            PCS3 PORTE6
 *      ��� spix = SPI2
 *      |__1--PCS0 PORTD11
 *      |__2--PCS0 PORTD11
 *            PCS1 PORTD15
 * ���:
 *    0����ʼ������
 *    1����ʼ���ɹ�
 */

uint8 SPI_Init(SPIx spix,uint8 sck_div,uint8 pcs_num)
{
      
     
  
  //��ʼ��SPI����OLED��ʾ���������ߵ�SPI������ʽ������Ҫ��ʼ��CS��RST��DC����
  
      gpio_init  (PORTC,8,GPO,HIGH); //��ʼ��OLED-CS����
  
      gpio_init  (PORTC,9,GPO,HIGH); //��ʼ��OLED-RST����
      
      gpio_init  (PORTC,10,GPO,HIGH); //��ʼ��OLED-D/C����
  
      SPI_MemMapPtr spi = SPIx_Ptr[spix];
   
      //ѡ��SPIģ��ʱ��
      
      SIM_SCGC6 |= SIM_SCGC6_DSPI0_MASK;  
      //����SPI0�ӿ�
       
      PORTC_PCR5 = 0 | PORT_PCR_MUX(2) | PORT_PCR_DSE_MASK;//SCK
      PORTC_PCR6 = 0 | PORT_PCR_MUX(2) | PORT_PCR_DSE_MASK;//SOUT
      PORTC_PCR7 = 0 | PORT_PCR_MUX(2);                    //SIN
     
     //�жϵ�ǰʹ�õ�PCS�ĸ���  
      
      
  //����SPI MCR�Ĵ���
  SPI_MCR_REG(spi) = 0 & (~SPI_MCR_MDIS_MASK) //ʹ��SPIʱ��
                    |SPI_MCR_HALT_MASK        //��SPI����ֹͣģʽ
                    |SPI_MCR_MSTR_MASK        //����SPIΪ����ģʽ
                    
                    //|SPI_MCR_PCSIS_MASK       //PCSΪ�ߵ�ƽ����SPI��������ʱ��
                    |SPI_MCR_CLR_TXF_MASK     //����Ҫ���MDIS�����TXF_MASK��RXF_MASK
                    |SPI_MCR_CLR_RXF_MASK  
                    |SPI_MCR_DIS_TXF_MASK     //Ȼ���ٽ�ֹTXD��RXD FIFO ģʽ ����SPI���ó�����ģʽ
                    |SPI_MCR_DIS_RXF_MASK; 
  
  //����SPI CTAR�Ĵ���
  SPI_CTAR_REG(spi,0) = 0 | SPI_CTAR_DBR_MASK  //����DBR = 1
                    |SPI_CTAR_PBR(0)           //����PBR = 2,������������ռ�ձ�Ϊ50%
                    |SPI_CTAR_FMSZ(7)          //����һ֡Ϊ8λ��һ���ֽ�����
                    &~(SPI_CTAR_LSBFE_MASK);   //��λ��ǰ����
                                               //���ʱSCKΪ��
  //==================���� Spi ʱ��======================
  //����SCK��Ƶ��
  //F_SCK = (fSYS/PBR) x [(1+DBR)/BR]
  //����DBR = 1��PBR = 2 ������� F_SCK = fSYS/BR
  
  SPI_CTAR_REG(spi,0) |=SPI_CTAR_BR(sck_div);
  
  //����PCS to SCK����ʱ
  //tCSC = (1/fSYS) x PCSSCK x CSSCK
  //tCSC = 1/150,000,000 x PCSSCK x CSSCK
  //SPI_CTAR_REG(spi,0) |=SPI_CTAR_PCSSCK(1); // Prescaler value is 3.
  //SPI_CTAR_REG(spi,0) |=SPI_CTAR_CSSCK(1);  // Delay Scaler Value is 4.
  
  //���� PCS ���� to ϵһ��֡��ʼ��ʱ
  //tDT = (1/fSYS) x PDT x DT
  //SPI_CTAR_REG(spi,0) |=SPI_CTAR_DT(1);
  //SPI_CTAR_REG(spi,0) |=SPI_CTAR_PDT(1);
  
  //Config the Delay of the last edge of SCK and the negation of PCS
  //tASC = (1/fSYS) x PASC x ASC
  //SPI_CTAR_REG(spi,0) |=SPI_CTAR_PASC(1);
  //SPI_CTAR_REG(spi,0) |=SPI_CTAR_ASC(1);
  //===============���� Spi ʱ�����====================== 
  
  SPI_SR_REG(spi) =  SPI_SR_RFDF_MASK   //���״̬��ʶ
                    |SPI_SR_RFOF_MASK
                    |SPI_SR_TFFF_MASK
                    |SPI_SR_TFUF_MASK
                    |SPI_SR_TCF_MASK
                    |SPI_SR_EOQF_MASK;
  
  SPI_MCR_REG(spi) &=~SPI_MCR_HALT_MASK; //�˳��ȴ�ģʽ,SPI��ʼ����
  
  return 1;
}



/*
 * SPI_Master_WriteRead
 * K60����SPI��ӻ�д���ݣ�����ȡ�ӻ�����
 * 
 * ����:
 *    spix--SPIѡ��
 *      |__SPI0       -ѡ��SPI0ģ��
 *      |__SPI1       -ѡ��SPI1ģ��
 *      |__SPI2       -ѡ��SPI2ģ��
 *    data--Ҫ��������
 *      |__��λΪһ���ֽڣ�8λ
 *    pcsx--CSƬѡ�˿ں�
 *      |__SPI_PCS0       -0��Ƭѡ(SPI0��SPI1��SPI2����)
 *      |__SPI_PCS1       -1��Ƭѡ(SPI0��SPI1��SPI2����)
 *      |__SPI_PCS2       -2��Ƭѡ(SPI0��SPI1����)
 *      |__SPI_PCS3       -3��Ƭѡ(SPI0��SPI1����)
 *      |__SPI_PCS4       -4��Ƭѡ(SPI0����)
 *      |__SPI_PCS5       -5��Ƭѡ(SPI0����)
 *    pcs_state--һ֡���ݴ�����ɺ�CS��״̬
 *      |__SPI_PCS_ASSERTED -����Ƭѡ��Ч
 *      |__SPI_PCS_INACTIVE -Ƭѡ��Ч
 * ���:
 *    8λ�Ķ�ȡ�ӻ�������
 */

uint8 SPI_Master_WriteRead(SPIx spix,uint8 data,uint8 pcsx,uint8 pcs_state)
{
  uint8 temp;
  SPI_MemMapPtr spi = SPIx_Ptr[spix];
  
  //����pcs_stateѡ��Ƭѡ�Ƿ���Ч
  SPI_PUSHR_REG(spi) = (((uint32_t)(((uint32_t)(pcs_state))<<SPI_PUSHR_CONT_SHIFT))&SPI_PUSHR_CONT_MASK)
               |SPI_PUSHR_CTAS(0)
               |SPI_PUSHR_PCS(pcsx)
               |data;                 
  
  while(!(SPI_SR_REG(spi) & SPI_SR_TCF_MASK));
  SPI_SR_REG(spi) |= SPI_SR_TCF_MASK ;               //������ͻ����־λ
  
  //ʹ���ջ�����Ϊ��
  while((SPI_SR_REG(spi) & SPI_SR_RFDF_MASK) == 0){}; //RX FIFO δ���յ�������һֱ�ȴ�
  temp = (uint8)(SPI_POPR_REG(spi) & 0xff);           //������32λ��ʽ����POPR�У�ת����ʽ 
  SPI_SR_REG(spi) |= SPI_SR_RFDF_MASK;                //�����־λ
  return temp;
  
}


/*
 * SPI_Master_Read
 * K60������ȡ�ӻ�����
 * 
 * ����:
 *    spix--SPIѡ��
 *      |__SPI0       -ѡ��SPI0ģ��
 *      |__SPI1       -ѡ��SPI1ģ��
 *      |__SPI2       -ѡ��SPI2ģ��
 * ���:
 *    8λ�Ķ�ȡ�ӻ�������
 */
uint8 SPI_Master_Read(SPIx spix)
{
  uint8 temp;
  SPI_MemMapPtr spi = SPIx_Ptr[spix];

  while(!(SPI_SR_REG(spi) & SPI_SR_RFDF_MASK)); //=1 RIFO is not empty
  temp=(uint8)SPI_POPR_REG(spi);
  SPI_SR_REG(spi) |=SPI_SR_RFDF_MASK;

  return temp;
}
/*
 * SPI_Master_Write
 * K60����SPI��ӻ�д����
 * 
 * ����:
 *    spix--SPIѡ��
 *      |__SPI0       -ѡ��SPI0ģ��
 *      |__SPI1       -ѡ��SPI1ģ��
 *      |__SPI2       -ѡ��SPI2ģ��
 *    data--Ҫ��������
 *      |__��λΪһ���ֽڣ�8λ
 *    pcsx--CSƬѡ�˿ں�
 *      |__SPI_PCS0       -0��Ƭѡ(SPI0��SPI1��SPI2����)
 *      |__SPI_PCS1       -1��Ƭѡ(SPI0��SPI1��SPI2����)
 *      |__SPI_PCS2       -2��Ƭѡ(SPI0��SPI1����)
 *      |__SPI_PCS3       -3��Ƭѡ(SPI0��SPI1����)
 *      |__SPI_PCS4       -4��Ƭѡ(SPI0����)
 *      |__SPI_PCS5       -5��Ƭѡ(SPI0����)
 *    pcs_state--һ֡���ݴ�����ɺ�CS��״̬
 *      |__SPI_PCS_ASSERTED -����Ƭѡ��Ч
 *      |__SPI_PCS_INACTIVE -Ƭѡ��Ч
 */
void SPI_Master_Write(SPIx spix,uint8 data,uint8 pcsx,uint8 pcs_state)
{  
  SPI_MemMapPtr spi = SPIx_Ptr[spix];

  //����pcs_stateѡ��Ƭѡ�Ƿ���Ч
  SPI_PUSHR_REG(spi) = (((uint32_t)(((uint32_t)(pcs_state))<<SPI_PUSHR_CONT_SHIFT))&SPI_PUSHR_CONT_MASK)
               |SPI_PUSHR_CTAS(0)
               |SPI_PUSHR_PCS(pcsx)
               |data; 

  while(!(SPI_SR_REG(spi) & SPI_SR_TCF_MASK));
  SPI_SR_REG(spi) |= SPI_SR_TCF_MASK ;            //������ͻ����־λ
}



