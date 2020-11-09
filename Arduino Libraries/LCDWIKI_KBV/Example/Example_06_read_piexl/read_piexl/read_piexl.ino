// IMPORTANT: LCDWIKI_KBV LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.

//This program is a demo of how to read color value from GRAM.

//Set the pins to the correct ones for your development shield or breakout board.
//when using the BREAKOUT BOARD only and using these 8 data lines to the LCD,
//pin usage as follow:
//             CS  CD  WR  RD  RST  D0  D1  D2  D3  D4  D5  D6  D7
//Arduino Uno  A3  A2  A1  A0  A4   8   9   2   3   4   5   6   7
//Arduino Mega A3  A2  A1  A0  A4   8   9   2   3   4   5   6   7

//the 16bit mode only use in Mega.you must modify the mode in the file of lcd_mode.h
//when using the BREAKOUT BOARD only and using these 16 data lines to the LCD,
//pin usage as follow:
//             CS  CD  WR  RD  RST  D0  D1  D2  D3  D4  D5  D6  D7  D8  D9  D10  D11  D12  D13  D14  D15 
//Arduino Mega 40  38  39  44  41   37  36  35  34  33  32  31  30  22  23  24   25   26   27   28   29

//Remember to set the pins to suit your display module!

#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library

//the definiens of 8bit mode as follow:
//if the IC model is known or the modules is unreadable,you can use this constructed function
//LCDWIKI_KBV my_lcd(ILI9341,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV my_lcd(ILI9325,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV my_lcd(ILI9328,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV my_lcd(HX8357D,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV my_lcd(HX8347G,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV my_lcd(HX8347I,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV my_lcd(ILI9486,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV my_lcd(ST7735S,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset

//if the IC model is not known and the modules is readable,you can use this constructed function
//LCDWIKI_KBV my_lcd(240,320,A3,A2,A1,A0,A4);//width,height,cs,cd,wr,rd,reset 
//LCDWIKI_KBV my_lcd(320,480,A3,A2,A1,A0,A4);//width,height,cs,cd,wr,rd,reset

//the definiens of 16bit mode as follow:
//if the IC model is known or the modules is unreadable,you can use this constructed function
//LCDWIKI_KBV my_lcd(ILI9341,40,38,39,44,41); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV my_lcd(ILI9325,40,38,39,44,41); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV my_lcd(ILI9328,40,38,39,44,41); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV my_lcd(HX8357D,40,38,39,44,41); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV my_lcd(HX8347G,40,38,39,44,41); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV my_lcd(HX8347I,40,38,39,44,41); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV my_lcd(ILI9486,40,38,39,44,41); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV mylcd(ILI9488,40,38,39,44,41); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV mylcd(ILI9481,40,38,39,44,41); //model,cs,cd,wr,rd,reset
//LCDWIKI_KBV my_lcd(ST7735S,40,38,39,44,41); //model,cs,cd,wr,rd,reset

//if the IC model is not known and the modules is readable,you can use this constructed function
//LCDWIKI_KBV my_lcd(240,320,40,38,39,44,41);//width,height,cs,cd,wr,rd,reset for
//LCDWIKI_KBV my_lcd(320,480,40,38,39,44,41);//width,height,cs,cd,wr,rd,reset

#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

void color_dump(uint16_t x,uint16_t y)
{
    uint8_t buf[30] = {0},pbuf[10] = {0};
    uint8_t wd = (my_lcd.Get_Display_Width() - 9 * 6)/ (5 * 6);
    uint8_t hi = (my_lcd.Get_Display_Height() / 8) - 1;
    uint16_t pixel = 0;
    //set white
    my_lcd.Set_Text_colour(WHITE);
    //set text size 1
    my_lcd.Set_Text_Size(1);
    for(int j = 0;j< hi;j++)
    {
      sprintf(buf,"%3d,%3d:",x,y+j);
      my_lcd.Print_String(buf, 0, 8*(j+1)*my_lcd.Get_Text_Size());
      for(int i=0;i<wd;i++)
      {          
//          my_lcd.Print_String(buf, 0, line+8);
        //read pixel
          pixel = my_lcd.Read_Pixel(x+i,y+j);

        // if white set green
          if(WHITE == pixel)
          {
             my_lcd.Set_Text_colour(GREEN); 
           }
           sprintf(pbuf,"%04X ",pixel); 
           my_lcd.Print_String(pbuf,(strlen(buf)+strlen(pbuf)*i)*6*my_lcd.Get_Text_Size(),8*(j+1)*my_lcd.Get_Text_Size());
        //set white
           my_lcd.Set_Text_colour(WHITE);
        } 
     }
}   

uint8_t aspect;
char *aspectname[] = {"PORTRAIT", "LANDSCAPE", "PORTRAIT_REV", "LANDSCAPE_REV"};
uint16_t colors[] = {BLACK, BLUE};

void setup()
{
  my_lcd.Init_LCD();
//my_lcd.Set_Text_Back_colour(BLACK);
}

void loop() 
{
  uint16_t iter, color;
    char buf[80];
    aspect = (aspect + 1) & 3;
    my_lcd.Set_Rotation(aspect);
 //color_dump(36,0);
 
    for (iter = 0; iter < sizeof(colors) / sizeof(uint16_t); iter++) 
    {
        color = colors[iter];
        my_lcd.Fill_Screen(color);
        my_lcd.Set_Text_Back_colour(color);
        my_lcd.Set_Text_colour(WHITE);
        my_lcd.Set_Text_Size(1);
     sprintf(buf, " ID=0x%04X Background=%04X %s", my_lcd.Read_ID(), color, aspectname[aspect]);
      my_lcd.Print_String(buf,0,0);
        color_dump(36,0);
        delay(3000);
       
    } 

}
