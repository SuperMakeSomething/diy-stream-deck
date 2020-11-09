/* DIY Stream Deck LCD Screen Code (DIY Stream Deck - Super Make Something Episode 22)
 * by: Alex - Super Make Something
 * date: November 8th, 2020
 * license: Creative Commons - Attribution - Non-Commercial.  More information available at: http://creativecommons.org/licenses/by-nc/3.0/
 */

#include "SD.h"
#include <SPI.h>
#include <LCDWIKI_GUI.h> //Core graphics library
#include <LCDWIKI_KBV.h> //Hardware-specific library

//Initialize my_lcd object
LCDWIKI_KBV my_lcd(ILI9486,A3,A2,A1,A0,A4); //model,cs,cd,wr,rd,reset

#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define PIXEL_NUMBER  1 //(my_lcd.Get_Display_Width()/4)
#define FILE_NUMBER 7
#define FILE_NAME_SIZE_MAX 20

int LOADED = 0;
int imageSize = 120;
int gridSpacing = 62;

int inputPin = A7;
int pageFlag = 0;
int pageFlagCurrent = 3;

uint32_t bmp_offset = 0;
uint16_t s_width = my_lcd.Get_Display_Width();  
uint16_t s_height = my_lcd.Get_Display_Height();
//int16_t PIXEL_NUMBER;

char file_name[FILE_NUMBER][FILE_NAME_SIZE_MAX]; // char arrays that define filenames
char file_name2[FILE_NUMBER][FILE_NAME_SIZE_MAX];

uint16_t read_16(File fp)
{
    uint8_t low;
    uint16_t high;
    low = fp.read();
    high = fp.read();
    return (high<<8)|low;
}

uint32_t read_32(File fp)
{
    uint16_t low;
    uint32_t high;
    low = read_16(fp);
    high = read_16(fp);
    return (high<<8)|low;   
}
 
bool analysis_bpm_header(File fp)
{
    if(read_16(fp) != 0x4D42)
    {
      return false;  
    }
    //get bpm size
    read_32(fp);
    //get creator information
    read_32(fp);
    //get offset information
    bmp_offset = read_32(fp);
    //get DIB infomation
    read_32(fp);
    //get width and heigh information
    uint32_t bpm_width = read_32(fp);
    uint32_t bpm_heigh = read_32(fp);
    read_16(fp);
    return true;
}

void errorCheck(File bmp_file)
{
   Serial.println("Error checking: ");
   if(!bmp_file)
       {
            my_lcd.Set_Text_Back_colour(BLUE);
            my_lcd.Set_Text_colour(WHITE);    
            my_lcd.Set_Text_Size(1);
            my_lcd.Print_String("didnt find BMPimage!",0,10);
            while(1);
        }
        if(!analysis_bpm_header(bmp_file))
        {  
            my_lcd.Set_Text_Back_colour(BLUE);
            my_lcd.Set_Text_colour(WHITE);    
            my_lcd.Set_Text_Size(1);
            my_lcd.Print_String("bad bmp picture!",0,0);
            return;
        }
   Serial.println("No error: ");
}


void draw_bmp_picture(File fp)
{
  uint16_t i,j,k,l,m=0;
  uint8_t bpm_data[PIXEL_NUMBER*3] = {0};
  uint16_t bpm_color[PIXEL_NUMBER];
  fp.seek(bmp_offset);
  for(i = 0; i<s_height; i++)
  {
    for(j = 0;j<s_width/PIXEL_NUMBER;j++)
    {
      m = 0;
      fp.read(bpm_data,PIXEL_NUMBER*3);
      for(k = 0;k<PIXEL_NUMBER;k++)
      {
        bpm_color[k]= my_lcd.Color_To_565(bpm_data[m+2], bpm_data[m+1], bpm_data[m+0]); //change to 565
        m +=3;
      }
      for(l = 0;l<PIXEL_NUMBER;l++)
      {
        my_lcd.Set_Draw_color(bpm_color[l]);
        my_lcd.Draw_Pixel(j*PIXEL_NUMBER+l,(s_height-1)-i);
      }    
     }
   }    
}


void draw_icon(File bmp_file, int xLoc, int yLoc)
{
  uint16_t i,j,k,l,m = 0;
  uint8_t bpm_data[PIXEL_NUMBER*3] = {0};
  uint16_t bpm_color[PIXEL_NUMBER];
  bmp_file.seek(bmp_offset);
  for(i = xLoc; i<xLoc+imageSize; i++)
  {
    for(j = yLoc; j<(yLoc+imageSize); j++)
    {
      m = 0;
      bmp_file.read(bpm_data,PIXEL_NUMBER*3);
      
      bpm_color[0]= my_lcd.Color_To_565(bpm_data[2], bpm_data[1], bpm_data[0]); //change to 565

      my_lcd.Draw_Pixe(j,(s_height)-i,bpm_color[0]);
     }
   }
  bmp_file.close();     
}

void setup() 
{
  Serial.begin(9600);
  my_lcd.Init_LCD();
  Serial.println(my_lcd.Read_ID(), HEX);
  my_lcd.Fill_Screen(BLACK);

  strcpy(file_name[0],"splash.bmp"); //Define filenames on SD Card - page 1
  strcpy(file_name[1],"01.bmp");
  strcpy(file_name[2],"02.bmp");
  strcpy(file_name[3],"03.bmp");
  strcpy(file_name[4],"04.bmp");
  strcpy(file_name[5],"05.bmp");
  strcpy(file_name[6],"06.bmp");
  
  strcpy(file_name2[0],"splash.bmp"); //Define filenames on SD Card - page 2
  strcpy(file_name2[1],"07.bmp");
  strcpy(file_name2[2],"08.bmp");
  strcpy(file_name2[3],"09.bmp");
  strcpy(file_name2[4],"10.bmp");
  strcpy(file_name2[5],"11.bmp");
  strcpy(file_name2[6],"12.bmp");
  
  //Init SD_Card
  pinMode(10, OUTPUT);
  delay(100);
  
  if (!SD.begin(SS)) //SD Card Initialization Error
  {
    my_lcd.Set_Text_Back_colour(BLUE);
    my_lcd.Set_Text_colour(WHITE);    
    my_lcd.Set_Text_Size(1);
    my_lcd.Print_String("SD Card Init fail!",0,0);
  }
  else
  {
    /*
    //Display splash screen
    File bmp_file;
    bmp_file = SD.open(file_name[0]);
    errorCheck(bmp_file);
    draw_bmp_picture(bmp_file);
    bmp_file.close();
    delay(1000); // Display splash screen for 10 seconds
    */
  }
}

void loop() 
{
    
    int i = 0;
    File bmp_file;
    int xLoc[] = {0, gridSpacing+imageSize, 2*(gridSpacing+imageSize), 0, gridSpacing+imageSize, 2*(gridSpacing+imageSize)};
    int yLoc[] = {0, 0, 0, 62+imageSize, 62+imageSize, 62+imageSize};
    
    while(1)
    {
      int currentVal = analogRead(inputPin);
      //Serial.println("Data Loaded!");
      Serial.println(currentVal);
      if (currentVal<512) // Add additional if statements for more pages
      {
        pageFlag=1;
        if (pageFlag!=pageFlagCurrent)
        {
          for (i = 1; i<FILE_NUMBER; i++)
          {
            bmp_file = SD.open(file_name[i]);
            //Serial.print(file_name[1]);
            errorCheck(bmp_file);
            draw_icon(bmp_file, xLoc[i-1], yLoc[i-1]);
          }
          pageFlagCurrent=pageFlag;
        }
      }
      else
      {
        pageFlag=2;
        if (pageFlag!=pageFlagCurrent)
        {
          for (i = 1; i<FILE_NUMBER; i++)
          {
            bmp_file = SD.open(file_name2[i]);
            //Serial.print(file_name[1]);
            errorCheck(bmp_file);
            draw_icon(bmp_file, xLoc[i-1], yLoc[i-1]);
          }
          pageFlagCurrent=pageFlag;
        }
      }
    }
}
