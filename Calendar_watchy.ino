/*
Calendar
Version 1.1.0
https://github.com/uCBill/Calendar
Calendar watchface by Bill Eichner
*/

#include <Watchy.h> //include the Watchy library
#include "calendar_img.h"
#include "Teko_Regular12pt7b.h"
#include "Teko_Regular8pt7b.h"
#include "settings.h"

class WatchFace : public Watchy { //inherit and extend Watchy class
	using Watchy::Watchy;
	public:
		void drawWatchFace() { //override this method to customize how the watch face looks
			
			int16_t  x1, y1;
			uint16_t w, h;
			String textstring;
			int frame;
			int mth;
			int yr;
			int days;
			int wkday;
			int x;
			int y;
			bool light = true; // left this here if someone wanted to tweak for dark

			//resets step counter at midnight everyday
			if(currentTime.Hour == 00 && currentTime.Minute == 00) {
				sensor.resetStepCounter();
			}

		
			// draw background
			display.fillScreen(light ? GxEPD_WHITE : GxEPD_BLACK);
			display.drawBitmap(0,0, calendar_grid, 200, 200, light ? GxEPD_BLACK : GxEPD_WHITE);
			display.setTextColor(light ? GxEPD_BLACK : GxEPD_WHITE);
			display.setTextWrap(false);
			
			
			uint8_t y_offset = 80;
			tmElements_t elem = currentTime;
			for(uint8_t day = 1; day <= 32; day++) { // Loop through all possible 31 days
				// Set day and recalculate date to check the month
				elem.Day = day;
				time_t base = makeTime(elem);
				tm* time = localtime(&base);
				
				if(time->tm_mon != elem.Month - 1) break; // Check if the day is still in the current month, otherwise abort
				
				uint8_t x = 1 + (200 / 7) * time->tm_wday + (200 / 14);
				if(y_offset > 200) {
					// If the day is off the calendar, we remove the last row elements that are affected and put both dates in the same field
					display.setFont(&Teko_Regular8pt7b);
					display.fillRect(x - 15, y_offset - 47, 23, 23, light ? GxEPD_WHITE : GxEPD_BLACK);
					
					drawCentreString(String(day - 7), x - 6, y_offset - 38);
					drawCentreString(String(day), x + 4, y_offset - 26);
					display.drawLine(x + 10, y_offset - 47, x - 13, y_offset - 24, light ? GxEPD_BLACK : GxEPD_WHITE);
				}else{
					// Just draw the day number in the corresponding field
					drawCentreString(String(day), x, y_offset);
				}
					
				// If its the current day, draw the border around it
				if(currentTime.Day == day) {
					display.drawBitmap(x - 18, y_offset - 24 - (y_offset > 200 ? 28 : 0), block34x34, 35, 34, light ? GxEPD_BLACK : GxEPD_WHITE);
				}
				
				// if its a saturday, we need to go to the next round
				if(time->tm_wday == 6) y_offset += 28;
			}
			
			display.setFont(&Teko_Regular12pt7b);
			
			// draw Calendar
			mth = currentTime.Month;
			yr = currentTime.Year + 1970;
			display.setFont(&Teko_Regular12pt7b);
			textstring = monthStr(currentTime.Month);
			textstring.toUpperCase();
			textstring += " ";
			textstring += currentTime.Day;
			textstring += ", ";
			textstring += currentTime.Year + 1970;
			
			display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
			display.setCursor(100-w/2, 38); // date position
			display.print(textstring);
			// END draw Calendar
		
	/*      //draw day hightlight image
				x = 27;//Sun:x=-1, Mon:x=27, Tue:x=55, Thu:x=112, Fri:x=140, Sat:x=168
				y = 140;//R1:y=56, R2:y=84, R3:y=112, R4:y=140, R5:y=168
				display.drawBitmap(x,y, block34x34, 35, 34, GxEPD_BLACK);
				x = 83;//Wed:x=83
				y = 140;//R1:y=56, R2:y=84, R3:y=112, R4:y=140, R5:y=168
				display.drawBitmap(x,y, block35x34, 35, 34, GxEPD_BLACK);
				//END highlight calendar day
	*/      
			// draw time
			display.setFont(&Teko_Regular12pt7b);
			int displayHour;
			if (currentTime.Hour > 12) {
				textstring = ((currentTime.Hour+11)%12)+1;
			} else if (currentTime.Hour < 1) {
				textstring = 12;
			} else {
				textstring = currentTime.Hour;
			}
			textstring += ":";
			if (currentTime.Minute < 10) {
				textstring += "0";
			} else {
				textstring += "";
			}
			textstring += currentTime.Minute;
			//This option displays am or pm to 12 hour clock
			if (currentTime.Hour >= 12) {
				textstring += "PM";
			} else {
				textstring += "AM";
			}
			
			display.setCursor(5, 19);
			display.print(textstring);
			//END time

			//  Draw Battery Percent
			display.setFont(&Teko_Regular12pt7b);
			int8_t batteryLevel = 0;
			float VBAT = getBatteryVoltage();

			if(VBAT >= 4.2){
				batteryLevel = 100.0;
			}
			else if (VBAT >= 3.3) {
				batteryLevel = 100.0*(VBAT-3.3)/0.9;
			}
			textstring = "BAT:";
			textstring += batteryLevel;
			textstring += "%";
			display.getTextBounds(textstring, 0, 0, &x1, &y1, &w, &h);
			display.setCursor(195-w, 19);
			display.print(textstring);
			//  END OF Draw Battery

		}
	
	private:
		void drawCentreString(String str, int x, int y) {
			int16_t x1, y1;
			uint16_t w, h;
			
			display.setTextWrap(false);
			display.getTextBounds(str, x, y, &x1, &y1, &w, &h); //calc width of new string
			display.setCursor(x - w / 2, y);
			
			display.print(str);
		}
};

WatchFace m(settings); //instantiate your watchface

void setup() {
	m.init(); //call init in setup
}

void loop() {
	// this should never run, Watchy deep sleeps after init();
}
