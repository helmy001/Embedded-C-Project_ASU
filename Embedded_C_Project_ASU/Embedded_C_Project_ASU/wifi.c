/****************************************************
 *  Module :WiFi
 *
 *  File Name :wifi.c
 *
 *  Author: Helmy
 ****************************************************/
 
#include "wifi.h"


unsigned char Connection_ID='0';
unsigned char *button1="OFF";
unsigned char *button2="OFF";
unsigned char *Conditions="IOT Smart System";
#define Led1 2
#define Led2 3


void Wifi_Init(const unsigned char *ssid,const unsigned char* password)
{
	Uart_SendString("AT+RST\r\n\0");					 //Restart esp module
	_delay_ms(3500);
	LCD_displayCharacter('.');
	
	Uart_SendString("AT+UART_DEF=9600,8,1,0,0\r\n\0");
	_delay_ms(3500);
	LCD_displayCharacter('.');

	char AccessPoint[40];
	sprintf(AccessPoint,"AT+CWJAP=\"%s\",\"%s\"\r\n\0",ssid,password);    //send to esp the ssid and password of the access point 
	Uart_SendString(AccessPoint);
	_delay_ms(3500);
	LCD_displayCharacter('.');
	
	Uart_SendString("AT+CWMODE=1\r\n\0");
	_delay_ms(3500);
	LCD_displayCharacter('.');

	Uart_SendString("AT+CIPMUX=1\r\n\0");     // Enable multiple connections to multiple     
	_delay_ms(3500);
	LCD_displayCharacter('.');
	
	Uart_SendString("AT+CIPSERVER=1,80\r\n\0");  //Configure as server in Port 80
	_delay_ms(3500);
	LCD_displayCharacter('.');
	
}


void Get_Ip(unsigned char *ip){
	
	unsigned char ch,str[75];			
	
	unsigned char i=0;
	Uart_SendString("AT+CIFSR\r\n");				  //request the IP
	
	while (ch!='M')								     //keep receiving until the First Letter of Word "MAC"
	{
		ch=Uart_ReceiveByte();		
		str[i]=ch;
		i++;	
	}
	
	str[i]='\0';					
	
	unsigned char flag=0,j=0;
	for(int i=0;str[i]!='\0';i++)					//loop on the received string to extract the ip address of the server
	{
		
		if(flag==1)
		{
			ip[j]=str[i];
			j++;
		}
		
		if(str[i]=='\"')
		{
			flag++;
		}
	}
	
	ip[j-1]='\0';
	
 	LCD_clearScreen();				    	//Display the IP on the LCD Screen
 	LCD_DisplayString(ip);
    _delay_ms(1900);
}


unsigned char Get_Request_Details()				//Return the Connection Id
{
	
		
	unsigned char ch,str[20],i=0,flag=0;

	while(i<17)
	{
		ch=Uart_ReceiveByte();
		if(ch=='+')								//Wait until +IPD is Received
		{
			flag=1;
		}
		
		if(flag==1)
		{
			str[i]=ch;
			i++;
		}
	}
	
	if(flag==1)
	Connection_ID=str[5];			 //+IPD,ID     , str[5] has the connection id number
		
	str[i+1]='\0';
		
	unsigned char path;
	for(unsigned char j=5;str[j]!='\0';j++)			//Search for Word Get IN the Request to Get the required Path
	{
		if(str[j-2]=='G'&&str[j-1]=='E'&&str[j]=='T')
		{
			path=str[j+3];
			break;
		}
	}
		
	Control_Led(path);
		
	return Connection_ID;
	
}

void Website()
{
	
	unsigned char ID=Get_Request_Details();	

	
   	{		
		char *web_Page_Packet1="<!DOCTYPE html>\
		<html lang=\"en\"><head>\
		<meta charset=\"UTF-8\">\
		<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\
		<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\
		<meta http-equiv=\"refresh\" content=\"8; url=http://192.168.20.42:80\" />\
		<title>FCIS-CSYS-2023</title>\
		<link rel=\"stylesheet\" href=\"https://cdn.jsdelivr.net/gh/ziadbadwy/embded@latest/main.css\">\
		</head><body><section>\
		<p class=\"main-word\">%s</p>\
		<div class=\"btns\">\
		<p>System is Turned On</p>\
		<a href=\"/1\"><button id=\"on_btn\" class=\"btn b-1-on\">%s</button></a>\
		<a href=\"/2\"><button id=\"off_btn\" class=\"btn b-2-on\">%s</button></a>\
		</div></section></body></html>\0";
		
		
		char *Updated_web=malloc(GetLength(web_Page_Packet1)+2);				// replace the %s with the button text 
 		sprintf(Updated_web,web_Page_Packet1,Conditions,button1,button2);
		 
		 
		char Send_Command[45];
		sprintf(Send_Command,"AT+CIPSEND=%c,%d\r\n\0",ID,GetLength(Updated_web));
		Uart_SendString(Send_Command);
		_delay_ms(1000);
		Uart_SendString(Updated_web);
		_delay_ms(1000);
		
		free(Updated_web);
	}
	

	char Close_Command[40];
	sprintf(Close_Command,"AT+CIPCLOSE=%c\r\n\0",ID);
	Uart_SendString(Close_Command);
	_delay_ms(1000);
		
}

void Control_Led(unsigned char Pressed_button){
		
	if(Pressed_button=='1')
	{
		if(BIT_IS_SET(PORTB,Led1))
		{
			button1="OFF";
			CLEAR_BIT(PORTB,Led1);
		}else
		{
			button1="ON";
			SIT_BIT(PORTB,Led1);
		}
	}else if(Pressed_button=='2')
	{
		if(BIT_IS_SET(PORTB,Led2))
		{
			button2="OFF";
			CLEAR_BIT(PORTB,Led2);
		}else
		{
			button2="ON";
			SIT_BIT(PORTB,Led2);
		}
	}
	
	
	if(Adc_readChannel(0)>500)
	{
	Conditions="HIGH TEMP DETECTED";
	}else if(BIT_IS_SET(PIND,2))
	{
	Conditions="MOTION DETECTED";	
	}else{
	Conditions="IOT Smart System";
	}
	
	
	return;
}

unsigned short GetLength(unsigned char* str)
{
	unsigned short len=0;
	for(unsigned short i=0;str[i]!='\0';i++){
		len++;
	}
	return len;
	
}





