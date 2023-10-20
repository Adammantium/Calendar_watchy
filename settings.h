/* Arduino IDE Tool Settings:
Board: "Watchy"
Upload Speed: "921600"
CPU Frequency: "240MHz (WiFi/BT)"
Flash Frequency: "80MHz"
Flash Mode: "QIO"
Flash Size: "4MB (32Mb)"
Partition Scheme: "HUGE APP (3MB No OTA/1MB Spiffs)"
Core Debug Level: "None"
PSRAM: "Diabled"
Arduino Runs On: "Core 1"
Events Runs On: "Core 1"
Port: "/dev/ttyUSB0"
 */

#ifndef SETTINGS_H
#define SETTINGS_H

/*Time Zone Information
  List of US Time Zones: EST:-5, CST:-6, MST:-7, PST:-8, AKST:-9, AHST:-10
  List of US Daylight Savings Time Zones: EDT:-4, CDT:-5, MDT:-6, PDT:-7, AKDT:-8, AHDT:-9
*/

//Weather Settings
#define CITY_ID "5128581" //New York City https://openweathermap.org/current#cityid
#define OPENWEATHERMAP_APIKEY "none" //use your own API key :)
#define OPENWEATHERMAP_URL "http://api.openweathermap.org/data/2.5/weather?id=" //open weather api
#define TEMP_UNIT "imperial" //metric = Celsius , imperial = Fahrenheit
#define TEMP_LANG "en"
#define WEATHER_UPDATE_INTERVAL 99 //must be greater than 5, measured in minutes
#define PING 10 //see if network is available
//NTP Settings
#define NTP_SERVER "pool.ntp.org"
#define GMT_OFFSET_SEC 3600 * -5 //New York is UTC -5 EST, -4 EDT, will be overwritten by weather data, based on CITY_ID, unless OPENWEATHERMAP_APIKEY is not valid.
#define DST_OFFSET_SEC 3600

watchySettings settings{
    CITY_ID,
    OPENWEATHERMAP_APIKEY,
    OPENWEATHERMAP_URL,
    TEMP_UNIT,
    TEMP_LANG,
    WEATHER_UPDATE_INTERVAL,
    NTP_SERVER,
    GMT_OFFSET_SEC,
    DST_OFFSET_SEC
};

#endif
