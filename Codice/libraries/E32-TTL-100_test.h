/**
 * E32-TTL-100 Transceiver Interface
 *
 * @author Bob Chen (bob-0505@gotmail.com)
 * @date 1 November 2017
 * https://github.com/Bob0505/E32-TTL-100
 *
 * Definizione strutture per setup parametri del tranceiver
 */
 
 // SPED byte setup values +
 enum UART_MODE
{
  UART_MODE_8N1 = 0x00,       // no   parity bit one stop  default
  UART_MODE_8O1 = 0x01,       // odd  parity bit one stop
  UART_MODE_8E1 = 0x02        // even parity bit one stop
}
enum UART_BPS
{
  UART_BPS_1200 = 0x00,
  UART_BPS_2400 = 0x01,
  UART_BPS_4800 = 0x02,
  UART_BPS_9600 = 0x03,             // default
  UART_BPS_19200 = 0x04,
  UART_BPS_38400 = 0x05,
  UART_BPS_57600 = 0x06,
  UART_BPS_115200 = 0x07
};
enum AIR_BPS
{
  AIR_BPS_300    = 0x00,
  AIR_BPS_1200   = 0x01,
  AIR_BPS_2400   = 0x02,            // default
  AIR_BPS_4800   = 0x03,
  AIR_BPS_96000  = 0x04,
  AIR_BPS_19200  = 0x05
};
 // SPED byte setup values -
 
 // Channel number setting: 410~441MHz : 410M + CHAN*1M +
enum AIR_CHAN_TYPE
{
  AIR_CHAN_410M = 0x00,             // first
  AIR_CHAN_411M = 0x01,
  AIR_CHAN_412M = 0x02,
  AIR_CHAN_413M = 0x03,
  AIR_CHAN_414M = 0x04,
  AIR_CHAN_415M = 0x05,
  AIR_CHAN_420M = 0x0A,
  AIR_CHAN_421M = 0x0B,
  AIR_CHAN_422M = 0x0C,
  AIR_CHAN_425M = 0x0F,
  AIR_CHAN_426M = 0x10,
  AIR_CHAN_433M = 0x17,             // default
  AIR_CHAN_441M = 0x1F              // last
};
 // Channel number setting: 410~441MHz : 410M + CHAN*1M -
 
 //OPTION +
#define TRSM_TT_MODE		0x00	// Transparent Transmission
#define TRSM_FP_MODE		0x01	// Fixed-point transmission mode

#define OD_DRIVE_MODE		0x00    // TXD and AUX open-collector outputs, RXD open-collector input
#define PP_DRIVE_MODE		0x01    // TXD and AUX push pull aoutput, RXD pull-up input  - default

enum WEAK_UP_TIME_TYPE
{
  WEAK_UP_TIME_250  = 0x00,
  WEAK_UP_TIME_1000 = 0x03,
  WEAK_UP_TIME_2000 = 0x07
};

#define DISABLE_FEC			0x00
#define ENABLE_FEC			0x01

//Transmit power
enum TSMT_PWR_TYPE
{
  TSMT_PWR_30DB = 0x00,
  TSMT_PWR_27DB = 0x01,
  TSMT_PWR_24DB = 0x02,
  TSMT_PWR_21DB = 0x03
};
//OPTION -

#pragma pack(push, 1)             // exact fit - no padding
struct SPEDstruct {
  uint8_t air_bps : 3;            //bit 0-2
  uint8_t uart_bps: 3;            //bit 3-5
  uint8_t uart_fmt: 2;            //bit 6-7
};

struct OPTIONstruct {
  uint8_t tsmt_pwr    : 2;        //bit 0-1
  uint8_t enFWC       : 1;        //bit 2
  uint8_t wakeup_time : 3;        //bit 3-5
  uint8_t drive_mode  : 1;        //bit 6
  uint8_t trsm_mode   : 1;        //bit 7
};

struct CFGstruct {
  uint8_t HEAD;
  uint8_t ADDH;
  uint8_t ADDL;
  struct SPEDstruct   SPED_bits;
  uint8_t CHAN;
  struct OPTIONstruct OPTION_bits;
};

struct MVerstruct {
  uint8_t HEAD;
  uint8_t Model;
  uint8_t Version;
  uint8_t features;
};
#pragma pack(pop)

