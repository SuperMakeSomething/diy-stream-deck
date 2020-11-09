// Lcdwiki GUI library with init code from Rossum
// MIT license

#ifndef _LCDWIKI_KBV_H_
#define _LCDWIKI_KBV_H_

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#ifdef __AVR__
#include <avr/pgmspace.h>
#elif defined(ESP8266)
 #include <pgmspace.h>
#else
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#define pgm_read_word(addr) (*(const unsigned short *)(addr))
#endif
#include "LCDWIKI_GUI.h"

// LCD controller chip identifiers
#define ID_932X    0
#define ID_7575    1
#define ID_9341    2
#define ID_HX8357D    3
#define ID_4535    4
#define ID_9486    5
#define ID_7735    6
#define ID_9488    7
#define ID_9481    8
#define ID_UNKNOWN 0xFF

//LCD controller chip mode identifiers
#define ILI9325 0
#define ILI9328 1
#define ILI9341 2
#define HX8357D 3
#define HX8347G 4
#define HX8347I 5
#define ILI9486 6
#define ST7735S 7
#define ILI9488 8
#define ILI9481 9

//if using the lcd breakout board,comment out this next line.
//if using the lcd shield,leave the line enable: 

//#define USE_ADAFRUIT_SHIELD_PIN 1


typedef struct _lcd_info
{
	uint16_t lcd_id;
	int16_t lcd_wid;
	int16_t lcd_heg;
}lcd_info;

class LCDWIKI_KBV:public LCDWIKI_GUI
{
	public:
	LCDWIKI_KBV(uint16_t model,uint8_t cs, uint8_t cd, uint8_t wr, uint8_t rd, uint8_t reset);
	LCDWIKI_KBV(int16_t wid,int16_t heg,uint8_t cs, uint8_t cd, uint8_t wr, uint8_t rd, uint8_t reset);
	void Init_LCD(void);
	void reset(void);
	void start(uint16_t ID);
	void Draw_Pixe(int16_t x, int16_t y, uint16_t color);
	void Write_Cmd(uint16_t cmd);
	void Write_Data(uint16_t data);
	void Write_Cmd_Data(uint16_t cmd, uint16_t data);
	void init_table8(const void *table, int16_t size);
	void init_table16(const void *table, int16_t size);
	void Push_Command(uint16_t cmd, uint8_t *block, int8_t N);
	uint16_t Color_To_565(uint8_t r, uint8_t g, uint8_t b);
	uint16_t Read_ID(void);
	void Fill_Rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
	void Set_Rotation(uint8_t r); 
	uint8_t Get_Rotation(void) const;
	void Invert_Display(boolean i);
	uint16_t Read_Reg(uint16_t reg, int8_t index);
	int16_t Read_GRAM(int16_t x, int16_t y, uint16_t *block, int16_t w, int16_t h);
	void Set_Addr_Window(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
	void Push_Any_Color(uint16_t * block, int16_t n, bool first, uint8_t flags);
	void Push_Any_Color(uint8_t * block, int16_t n, bool first, uint8_t flags);
    void Vert_Scroll(int16_t top, int16_t scrollines, int16_t offset);
	int16_t Get_Height(void) const;
  	int16_t Get_Width(void) const;
	void Set_LR(void);

	protected:
    uint16_t WIDTH,HEIGHT,width, height, rotation,lcd_driver,lcd_model;
	private:
	uint16_t XC,YC,CC,RC,SC1,SC2,MD,VL,R24BIT;

	 #ifndef USE_ADAFRUIT_SHIELD_PIN
			
		  #ifdef __AVR__
				volatile uint8_t *csPort	, *cdPort	 , *wrPort	  , *rdPort;
				uint8_t 		  csPinSet	,  cdPinSet  ,	wrPinSet  ,  rdPinSet  ,
								  csPinUnset,  cdPinUnset,	wrPinUnset,  rdPinUnset,
								  _reset;
		  #endif
		  #if defined(__SAM3X8E__)
				Pio *csPort    , *cdPort	, *wrPort	 , *rdPort;
				uint32_t		  csPinSet	,  cdPinSet  ,	wrPinSet  ,  rdPinSet  ,
								  csPinUnset,  cdPinUnset,	wrPinUnset,  rdPinUnset,
								  _reset;
		  #endif
			  
	 #endif
};
#endif
