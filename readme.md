#微型拉伸试验机的自动控制器项目日志
###9月14日
实现PWM输出控制电机转速 ESCON
###9月21日
添加应用级代码 Tensile
###11月10日
添加ADS1255驱动。
###11月20日
####AD1255 REGISTER MAP####
**STATUS : STATUS REGISTER (ADDRESS 00h)**

| BIT7 | BIT6 | BIT5 | BIT4 | BIT3  | BIT2 | BIT1  | BIT0 |
| ---- | ---- | ---- | ---- | ----- | ---- | ----- | ---- |
| ID   | ID   | ID   | ID   | ORDER | ACAL | BUFEN | DRDY |

Bits 7-4 **ID3, ID2, ID1**, ID0 Factory Programmed Identification Bits (Read Only)

Bit 3 **ORDER**: Data Output Bit Order
&emsp; 0 = Most Significant Bit First (default)
&emsp; 1 = Least Significant Bit First
&emsp; Input data is always shifted in most significant byte and bit first. Output data is always shifted out most significant byte first. The ORDER bit only controls the bit order of the output data within the byte.

Bit 2 **ACAL**: Auto-Calibration
&emsp; 0 = Auto-Calibration Disabled (default)
&emsp; 1 = Auto-Calibration Enabled
&emsp; When Auto-Calibration is enabled, self-calibration begins at the completion of the WREG command that changes the PGA (bits 0-2 of ADCON register), DR (bits 7-0 in the DRATE register) or BUFEN (bit 1 in the STATUS register)

Bit 1 **BUFEN**: Analog Input Buffer Enable
&emsp; 0 = Buffer Disabled (default)
&emsp; 1 = Buffer Enabled

Bit 0 **DRDY**: Data Ready (Read Only)
&emsp; This bit duplicates the state of the DRDY pin

**MUX : Input Multiplexer Control Register (Address 01h)**

| BIT7  | BIT6  | BIT5  | BIT4  | BIT3  | BIT2  | BIT1  | BIT0  |
| ----- | ----- | ----- | ----- | ----- | ----- | ----- | ----- |
| PSEL3 | PSEL2 | PSEL1 | PSEL0 | NSEL3 | NSEL2 | NSEL1 | NSEL0 |
Bits 7-4 **PSEL3, PSEL2, PSEL1, PSEL0**: Positive Input Channel (AINP) Select
&emsp; 0000 = AIN0 (default)
&emsp; 0001 = AIN1
&emsp; 0010 = AIN2 (ADS1256 only)
&emsp; 0011 = AIN3 (ADS1256 only)
&emsp; 0100 = AIN4 (ADS1256 only)
&emsp; 0101 = AIN5 (ADS1256 only)
&emsp; 0110 = AIN6 (ADS1256 only)
&emsp; 0111 = AIN7 (ADS1256 only)
&emsp; 1xxx = AINCOM (when PSEL3 = 1, PSEL2, PSEL1, PSEL0 are “don’t care”)
&emsp; _NOTE: When using an ADS1255 make sure to only select the available inputs._
Bits 3-0 **NSEL3, NSEL2, NSEL1, NSEL0**: Negative Input Channel (AINN)Select
&emsp; 0000 = AIN0
&emsp; 0001 = AIN1 (default)
&emsp; 0010 = AIN2 (ADS1256 only)
&emsp; 0011 = AIN3 (ADS1256 only)
&emsp; 0100 = AIN4 (ADS1256 only)
&emsp; 0101 = AIN5 (ADS1256 only)
&emsp; 0110 = AIN6 (ADS1256 only)
&emsp; 0111 = AIN7 (ADS1256 only)
&emsp; 1xxx = AINCOM (when NSEL3 = 1, NSEL2, NSEL1, NSEL0 are “don’t care”)

**ADCON: A/D Control Register (Address 02h)**

| BIT7 | BIT6 | BIT5 | BIT4  | BIT3  | BIT2 | BIT1 | BIT0 |
| ---- | ---- | ---- | ----- | ----- | ---- | ---- | ---- |
| 0    | CLK1 | CLK0 | SDCS1 | SDCS0 | PGA2 | PGA1 | PGA0 |
Bit 7 Reserved, always 0 (Read Only)

Bits 6-5 **CLK1, CLK0**: D0/CLKOUT Clock Out Rate Setting
&emsp; 00 = Clock Out OFF
&emsp; 01 = Clock Out Frequency = fCLKIN (default)
&emsp; 10 = Clock Out Frequency = fCLKIN/2
&emsp; 11 = Clock Out Frequency = fCLKIN/4
&emsp; When not using CLKOUT, it is recommended that it be turned off. These bits can only be reset using the RESET pin.

Bits 4-2 **SDCS1, SCDS0**: Sensor Detect Current Sources
&emsp; 00 = Sensor Detect OFF (default)
&emsp; 01 = Sensor Detect Current = 0.5μA
&emsp; 10 = Sensor Detect Current = 2μA
&emsp; 11 = Sensor Detect Current = 10μA
&emsp; The Sensor Detect Current Sources can be activated to verify the integrity of an external sensor supplying a signal to the
&emsp; ADS1255/6. A shorted sensor produces a very small signal while an open-circuit sensor produces a very large signal.

Bits 2-0 **PGA2, PGA1, PGA0**: Programmable Gain Amplifier Setting
&emsp; 000 = 1 (default)
&emsp; 001 = 2
&emsp; 010 = 4
&emsp; 011 = 8
&emsp; 100 = 16
&emsp; 101 = 32
&emsp; 110 = 64
&emsp; 111 = 64

**DRATE: A/D Data Rate (Address 03h)**

| BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0 |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| DR7  | DR6  | DR5  | DR4  | DR3  | DR2  | DR1  | DR0  |

&emsp;The 16 valid Data Rate settings are shown below. Make sure to select a valid setting as the invalid settings may produce unpredictable results.
Bits 7-0 **DR[7: 0]**: Data Rate Setting(1)
&emsp; 11110000 = 30,000SPS (default)
&emsp; 11100000 = 15,000SPS
&emsp; 11010000 = 7,500SPS
&emsp; 11000000 = 3,750SPS
&emsp; 10110000 = 2,000SPS
&emsp; 10100001 = 1,000SPS
&emsp; 10010010 = 500SPS
&emsp; 10000010 = 100SPS
&emsp; 01110010 = 60SPS
&emsp; 01100011 = 50SPS
&emsp; 01010011 = 30SPS
&emsp; 01000011 = 25SPS
&emsp; 00110011 = 15SPS
&emsp; 00100011 = 10SPS
&emsp; 00010011 = 5SPS
&emsp; 00000011 = 2.5SPS
> for fCLKIN = 7.68MHz. Data rates scale linearly with fCLKIN

**I/O: GPIO Control Register (Address 04H)**

| BIT7 | BIT6 | BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0 |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| DIR3 | DIR2 | DIR1 | DIR0 | DIO3 | DIO2 | DIO1 | DIO0 |

&emsp; The states of these bits control the operation of the general-purpose digital I/O pins. The ADS1256 has 4 I/O pins: D3, D2, D1, and D0/CLKOUT. The ADS1255 has two digital I/O pins: D1 and D0/CLKOUT. When using an ADS1255, the register bits DIR3, DIR2, DIO3, and DIO2 can be read from and written to but have no effect.
Bit 7 **DIR3**, Digital I/O Direction for Digital I/O Pin D3 (used on ADS1256 only)
&emsp; 0 = D3 is an output
&emsp; 1 = D3 is an input (default)
Bit 6 **DIR2**, Digital I/O Direction for Digital I/O Pin D2 (used on ADS1256 only)
&emsp; 0 = D2 is an output
&emsp; 1 = D2 is an input (default)
Bit 5 **DIR1**, Digital I/O Direction for Digital I/O Pin D1
&emsp; 0 = D1 is an output
&emsp;  = D1 is an input (default)
Bit 4 **DIR0**, Digital I/O Direction for Digital I/O Pin D0/CLKOUT
&emsp; 0 = D0/CLKOUT is an output (default)
&emsp; 1 = D0/CLKOUT is an input
Bits 3-0 **DI0[3:0]**: Status of Digital I/O Pins D3, D2, D1, D0/CLKOUT
&emsp; Reading these bits will show the state of the corresponding digital I/O pin, whether if the pin is configured as an input or output by DIR3-DIR0. When the digital I/O pin is configured as an output by the DIR bit, writing to the corresponding DIO bit will set the output state. When the digital I/O pin is configured as an input by the DIR bit, writing to the corresponding DIO bit will have no effect. When DO/CLKOUT is configured as an output and CLKOUT is enabled (using CLK1, CLK0 bits in the ADCON register), writing to DIO0 will have no effect.
###12月4日
添加了拉伸实验机的速度控制代码，重构了拉伸试验机的结构体，ADS1255可以读出数据。
###1月11日
重构了BSP的初始化代码，并将全部头文件包含代码放入sys.h文件