//	Port B	-	APB base: 0x4000.5000
//						AHB base: 0x4005.9000
#include "XAAR128.h"

#define GPIO_PORTB_DATA_R				(*((volatile unsigned long *)0x400053FC))	//Data Register 									offset 0x000, Type RW, 	reset 0x0000.0000, Available btis 7:0	-- Only accessable at ADDR[9:2] aka 0x03FC
#define GPIO_PORTB_DIR_R				(*((volatile unsigned long *)0x40005400))	//Direction Register							offset 0x400,	Type RW, 	reset 0x0000.0000, Available bits 7:0
#define GPIO_PORTB_IS_R					(*((volatile unsigned long *)0x40005404))	//Interrupt Sense									offset 0x404, Type RW, 	reset 0x0000.0000, Available bits 7:0
#define GPIO_PORTB_IBE_R				(*((volatile unsigned long *)0x40005408))	//Interrupt Both Edges						offset 0x408, Type RW, 	reset 0x0000.0000, Available bits 7:0
#define GPIO_PORTB_IEV_R				(*((volatile unsigned long *)0x4000540C))	//Interrupt Event									offset 0x40C, Type RW, 	reset 0x0000.0000, Available bits 7:0
#define GPIO_PORTB_IM_R					(*((volatile unsigned long *)0x40005410))	//Interrupt Mask									offset 0x410, Type RW, 	reset 0x0000.0000, Available bits 7:0
#define GPIO_PORTB_RIS_R				(*((volatile unsigned long *)0x40005414))	//Raw Interrupt Status						offset 0x414, Type RO, 	reset 0x0000.0000, Available bits 7:0
#define GPIO_PORTB_MIS_R				(*((volatile unsigned long *)0x40005418)) //Masked Interrupt Status					offset 0x418, Type RO, 	reset 0x0000.0000, Available bits 7:0
#define GPIO_PORTB_ICR_R				(*((volatile unsigned long *)0x4000541C)) //Interrupt Clear									offset 0x41C, Type W1C, reset 0x0000.0000, Available bits 7:0
#define GPIO_PORTB_AFSEL_R			(*((volatile unsigned long *)0x40005420))	//Alternate Function Select				offset 0x420, Type RW, 	reset 0x0000.0000, Available bits 7:0
#define GPIO_PORTB_DR2R_R				(*((volatile unsigned long *)0x40005500))	//2-mA Drive Select								offset 0x500, Type RW, 	reset 0x0000.00FF, Available bits 7:0
#define GPIO_PORTB_DR4R_R				(*((volatile unsigned long *)0x40005504))	//4-mA Drive Select								offset 0x504, Type RW, 	reset 0x0000.0000, Available bits 7:0
#define GPIO_PORTB_DR8R_R				(*((volatile unsigned long *)0x40005508))	//8-mA Drive Select								offset 0x508, Type RW, 	reset 0x0000.0000, Available bits 7:0
#define GPIO_PORTB_ODR_R				(*((volatile unsigned long *)0x4000550C))	//Open Drain Select								offset 0x50C, Type RW, 	reset 0x0000.0000, Available bits 7:0
#define GPIO_PORTB_PUR_R				(*((volatile unsigned long *)0x40005510))	//Pull-Up Select									offset 0x510, Type RW, 	reset 0x0000.0000, Available bits 7:0
#define GPIO_PORTB_PDR_R				(*((volatile unsigned long *)0x40005514))	//Pull-Down Select								offset 0x514, Type RW, 	reset 0x0000.0000, Available bits 7:0
#define GPIO_PORTB_SLR_R				(*((volatile unsigned long *)0x40005518)) //Slew Rate Control Select				offset 0x518, Type RW,	reset 0x0000.0000, Available bits 7:0
#define GPIO_PORTB_DEN_R				(*((volatile unsigned long *)0x4000551C))	//Digital Enbale									offset 0x51C, Type RW,	reset 0x0000.0000, Available bits 7:0
#define GPIO_PORTB_LOCK_R				(*((volatile unsigned long *)0x40005520))	//Lock														offset 0x520, Type RW, 	reset 0x0000.0001, Availabel bits 31:0
#define GPIO_PORTB_CR_R					(*((volatile unsigned long *)0x40005524))	//Commit													offset 0x524, Type - ,	reset -					 , Available bits 7:0
#define GPIO_PORTB_AMSEL_R			(*((volatile unsigned long *)0x40005528)) //Analog Mode Select							offset 0x528, Type RW,	reset 0x0000.0000, Available bits 7:0
#define GPIO_PORTB_PCTL_R				(*((volatile unsigned long *)0x4000552C))	//Port Control										offset 0x52C, Type RW,	reset -					 , Available bits 31:0
#define GPIO_PORTB_ADCCTL_R			(*((volatile unsigned long *)0x40005530)) //ADC Control											offset 0x530, Type RW,	reset 0x0000.0000, Available bits 7:0
#define GPIO_PORTB_DMACTL_R			(*((volatile unsigned long *)0x40005534)) //DMA Control											offset 0x524, Type RW, 	reset 0x0000.0000, Available bits 7:0


#define SYSCTL_SSI2_CR0_R				(*((volatile unsigned long *)0x4000A000))
#define SYSCTL_SSI2_CR1_R				(*((volatile unsigned long *)0x4000A004))
#define SYSCTL_SSI2_DR_R				(*((volatile unsigned long *)0x4000A008))
#define SYSCTL_SSI2_SR_R				(*((volatile unsigned long *)0x4000A00C))
#define SYSCTL_SSI2_CCR_R				(*((volatile unsigned long *)0x4000AFC8))
#define SYSCTL_SSI2_CPSR_R			(*((volatile unsigned long *)0x4000A010))


#define SYSCTL_RCGC0_R					(*((volatile unsigned long *)0x400FE000))
#define SYSCTL_RCC_R						(*((volatile unsigned long *)0x400FE060))
#define SYSCTL_RCGC1_R          (*((volatile unsigned long *)0x400FE104))
#define SYSCTL_RCGC2_R					(*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGCGPIO_R				(*((volatile unsigned long *)0x400FE608))
#define SYSCTL_RCGCSSI_R				(*((volatile unsigned long *)0x400FE61C))

void XAAR128_Init(void){
	//****PORT CONFIGURATION****
	//	1.	Enable the SSI module using the RCGCSSI register
	SYSCTL_RCGCSSI_R |= (1<<2);
	//	2.	Enable the clock to the appropriate GPIO module cia the RCGCGPIO register
	SYSCTL_RCGCGPIO_R |= (1<<1);
	//	3.	Set the GPIO AFSEL bits for the appropriate pins
	GPIO_PORTB_AFSEL_R |= (1<<4)|(1<<5)|(1<<6)|(1<<7);
	//	4.	Configure the PMCn fields in the GPIOPCTL register to assign the SSI signals to the appropriate pins
	GPIO_PORTB_PCTL_R |=	(2<<16)|(2<<20)|(2<<24)|(2<<28);
	//	5.	Program the GPIODEN register to enbale the pin's digital function
	//		-	In addtion, the drive strength, drain select and pull-up/pull down functions must be configured
	GPIO_PORTB_DEN_R |= (1<<4)|(1<<5)|(1<<6)|(1<<7);
	GPIO_PORTB_PDR_R |= (1<<4)|(1<<5)|(1<<6)|(1<<7);

	//****MODE CONFIGURATION****
	//	1.	Ensure that the SSE bit in the SSICR1 register is clear before making any configuration changes
	SYSCTL_SSI2_CR1_R &= (0<<1);
	//	2.	Select the whether the SSI is a master or slave
	SYSCTL_SSI2_CR1_R = 0x00000000;
	//	3.	Configure the SSI clock source by writing to the SSICC register
	SYSCTL_SSI2_CCR_R = 0x0;
	//	4.	Configure the clock prescale divisor by writing the SSICPSR register
	SYSCTL_SSI2_CPSR_R = 0x02;
	//	5.	Write the SSICR0 register with the following configuration
	//		-	Serial clock rate (SCR)
	//		-	Desire clock phase/polarity (SPH and SPO)
	//		-	The protocol mode (FRF)
	//		-	The data size (DSS)
	SYSCTL_SSI2_CR0_R |= 0x13C7;
	//	6.	Enable the SSI by setting the SSE bit in the SSICR1 register
	SYSCTL_SSI2_CR1_R |= (1<<1);

	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4);
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

	GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5);
	GPIOPadConfigSet(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4,GPIO_PIN_4);
	GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_5,GPIO_PIN_5);
}

uint8_t ON = 1;
uint8_t OFF = 0;

//*******POWER UP sequence*******
//	delay between steps >= 100ms
//		VDD		VPPH		VPPL		nRESET
//	1.	OFF		OFF			OFF			ACTIVE
//	2.	ON		OFF			OFF			ACTIVE
//	3.	ON		ON			ON			ACTIVE
//	4.	ON		ON			ON			INACTIVE
void Xaar128_PowerUp(void){
	//	step 1

	//	nRESET ACTIVE;
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
	SysCtlDelay(1500000);
	//	step 2
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
	SysCtlDelay(1500000);
	//	step 3
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
	SysCtlDelay(1500000);
	//	step 4
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
	SysCtlDelay(2000);
}

//*******POWER DOWN sequence*******
//	delay between steps >= 100ms
//			VDD		VPPH		VPPL		nRESET
//	1.	ON		ON			ON			INACTIVE
//	2.	ON		ON			ON			ACTIVE
//	3.	ON		OFF			OFF			ACTIVE
//	4.	OFF		OFF			OFF			ACTIVE
void Xaar128_PowerDown(void){
	//	step 1
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
	SysCtlDelay(2000);
	//	step 3
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
	SysCtlDelay(2000);
	//	step 4
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
	SysCtlDelay(2000);
}

void XAAR128_DATA_Write(uint8_t data){
	SYSCTL_SSI2_DR_R = data;
	while((SYSCTL_SSI2_SR_R&0x01)==0){};
}

void XAAR128_Fire(void){
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0);
	SysCtlDelay(300);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);
}

