

#include "PinNames.h"
#include "TCPSocket.h"
#include "Thread.h"
#include "mbed.h"
#include <cstdint>
#include <stdio.h>	//printf
#include <string.h>	//strlen
#include <string>
#include <sys/socket.h>	//socket
#include <arpa/inet.h>	//inet_addr
#include <vector>
#include "DigitalOut.h"
#include "hcsr04.h"
#include "mbed_wait_api.h"
#include "http_request.h"
#include "MFRC522.h"
#include "Dht11.h"
#include <cstdio>
#include "string"
#include "SPI.h"

WiFiInterface *wifi;

Serial pc(SERIAL_TX, SERIAL_RX);// отладка на пк
DigitalOut myled(LED1);// светиод на плате, для индикации аутентификации 
HCSR04 sensor(D9, D10); // датчик расстояния

MFRC522    RfChip   (PC_3, PC_2, PB_13, D14, D15);// nfc датчик
Dht11 cala(A0);// датчик температуры/влажности
SPI spi(D11, D12, D13);// первый дисплей
DigitalOut cs(D7);// первый дисплей
DigitalOut cs2(A1);// второй дисплей
SPI spi2(PC_12, PC_11, PC_10);// второй дисплей

void show_temp(string val)// вывод температуры на дисплей
{
    cs = 1;
    cs = 0;
    spi.format(8);
    spi.frequency(1000000);
    /*while (val.size() < 4) {
    temp.insert()
    }*/
    spi.write(129);
    spi.write(129);
    spi.write(129);
    spi.write(129);
 
    for (int i = 0; i < val.length(); i++) {
 

    switch (val[i]) {
    case '0':{
        spi.write(129);
        break;
    }
    case '1':{
        spi.write(243);
        break;
    }
    case '2':{
        spi.write(73);
        break;
    }
    case '3':{
        spi.write(97);
        break;
    }
    case '4':{
        spi.write(51);
        break;
    }
    case '5':{
        spi.write(37);
        break;
    }
    case '6':{
        spi.write(5);
        break;
    }
    case '7':{
        spi.write(241);
        break;
    }
    case '8':{
        spi.write(1);
        break;
    }
    case '9':{
        spi.write(33);
        break;
    }

    }
    }    
    spi.write(57);
    spi.write(141);
    cs = 1;
}

void show_helt(string val)// вывод влажности на дисплей
{
    cs2 = 1;
    cs2 = 0;
    spi2.format(8);
    spi2.frequency(1000000);
    /*while (val.size() < 4) {
    temp.insert()
    }*/
    spi2.write(129);
    spi2.write(129);
    spi2.write(129);
    spi2.write(129);
 
    for (int i = 0; i < val.length(); i++) {
 

    switch (val[i]) {
    case '0':{
        spi2.write(129);
        break;
    }
    case '1':{
        spi2.write(243);
        break;
    }
    case '2':{
        spi2.write(73);
        break;
    }
    case '3':{
        spi2.write(97);
        break;
    }
    case '4':{
        spi2.write(51);
        break;
    }
    case '5':{
        spi2.write(37);
        break;
    }
    case '6':{
        spi2.write(5);
        break;
    }
    case '7':{
        spi2.write(241);
        break;
    }
    case '8':{
        spi2.write(1);
        break;
    }
    case '9':{
        spi2.write(33);
        break;
    }

    }
    }    
    spi2.write(57);
    spi2.write(71);
    cs2 = 1;
}

void calla(string val)// функция вывода числовой строки на дисплей один
{    
    cs = 1;
    cs = 0;
    string stro = "";
    /*while (val.size() < 4) {
    temp.insert()
    }*/
    while (val.size() > 0) {
        stro += val.back();
        val.pop_back();
    }
	while (stro.length() != 4)
	{
		stro += '0';
	}
 
    for (int i = 4; i > -1; i--) {
 
    spi.format(8);
    spi.frequency(1000000);
    switch (stro[i]) {
    case '0':{
        spi.write(129);
        break;
    }
    case '1':{
        spi.write(243);
        break;
    }
    case '2':{
        spi.write(73);
        break;
    }
    case '3':{
        spi.write(97);
        break;
    }
    case '4':{
        spi.write(51);
        break;
    }
    case '5':{
        spi.write(37);
        break;
    }
    case '6':{
        spi.write(5);
        break;
    }
    case '7':{
        spi.write(241);
        break;
    }
    case '8':{
        spi.write(1);
        break;
    }
    case '9':{
        spi.write(33);
        break;
    }
    }
    }    
    cs = 1;
}
void calla_alt(string val)// функция вывода числовой строки на дисплей два
{    
    cs2 = 1;
    cs2 = 0;
    string stro = "";
    /*while (val.size() < 4) {
    temp.insert()
    }*/
    while (val.size() > 0) {
        stro += val.back();
        val.pop_back();
    }
	while (stro.length() != 4)
	{
		stro += '0';
	}
 
    for (int i = 4; i > -1; i--) {
 
    spi2.format(8);
    spi2.frequency(1000000);
    switch (stro[i]) {
    case '0':{
        spi2.write(129);
        break;
    }
    case '1':{
        spi2.write(243);
        break;
    }
    case '2':{
        spi2.write(73);
        break;
    }
    case '3':{
        spi2.write(97);
        break;
    }
    case '4':{
        spi2.write(51);
        break;
    }
    case '5':{
        spi2.write(37);
        break;
    }
    case '6':{
        spi2.write(5);
        break;
    }
    case '7':{
        spi2.write(241);
        break;
    }
    case '8':{
        spi2.write(1);
        break;
    }
    case '9':{
        spi2.write(33);
        break;
    }
    }
    }    
    cs2 = 1;
}


Thread thread;// поток для времени

int tima = 0;
bool check_time_val = false;// разр. переменная для считывания времени 

void show_time()// подсчет времени
{
   while (1) { 
            if (check_time_val)
        {
            wait_us(125000);
            tima++;
        }
        else {
            tima = 0;  
        }  
    }

    

}


string dump_response(HttpResponse* res) {// дешифратор http запроса
    printf("Status: %d - %s\n", res->get_status_code(), res->get_status_message().c_str());
 
    printf("Headers:\n");
    for (size_t ix = 0; ix < res->get_headers_length(); ix++) {
        printf("\t%s: %s\n", res->get_headers_fields()[ix]->c_str(), res->get_headers_values()[ix]->c_str());
    }
    printf("\nBody (%d bytes):\n\n%s\n", res->get_body_length(), res->get_body_as_string().c_str());
    std::string body = res->get_body_as_string().c_str();
    return body;
}
 
//------------------------------------переменные для работы сети------------------------------
int remaining;
int rcount;
char *p;
char *buffer = new char[256];
//------------------------------------
 
 void sendData(vector<string> data, TCPSocket* socketa)// отправка post запроса с json телом из 2 переменных
 {
        HttpRequest* get_req = new HttpRequest(socketa, HTTP_POST, "http://192.168.1.72/check/");
 
        get_req->set_header("Content-Type", "application/json");
        string body = "{\"" + data[0] + "\":\"" +data[1] + "\",\"" + data[2] + "\":\"" +data[3] + "\"}";

        HttpResponse* post_res = get_req->send(body.c_str(), body.length());
        if (!post_res) {
            printf("HttpRequest failed (error code %d)\n", get_req->get_error());
        }
 
        printf("\n----- HTTP POST response -----\n");
        string dataRet = dump_response(post_res);
 
        delete get_req;
        
 }
 
int getTrain(vector<string> data, TCPSocket* socketa)// отправка get запроса с json телом из 1 переменной
{// получает кол-во иттераций пользователя
        HttpRequest* get_req = new HttpRequest(socketa, HTTP_POST, "http://192.168.1.72/getTrain/");
 
        get_req->set_header("Content-Type", "application/json");
 
        string body = "{\"" + data[0] + "\":\"" +data[1] + "\"}";
 
        HttpResponse* post_res = get_req->send(body.c_str(), body.length());
        if (!post_res) {
            printf("HttpRequest failed (error code %d)\n", get_req->get_error());
        }
 
        printf("\n----- HTTP POST response -----\n");
        string dataRet = dump_response(post_res);
 
        delete get_req;
        return stoi(dataRet);
}
 

const char *sec2str(nsapi_security_t sec)// сетевая часть
{
    switch (sec) {
        case NSAPI_SECURITY_NONE:
            return "None";
        case NSAPI_SECURITY_WEP:
            return "WEP";
        case NSAPI_SECURITY_WPA:
            return "WPA";
        case NSAPI_SECURITY_WPA2:
            return "WPA2";
        case NSAPI_SECURITY_WPA_WPA2:
            return "WPA/WPA2";
        case NSAPI_SECURITY_UNKNOWN:
        default:
            return "Unknown";
    }
}

int scan_demo(WiFiInterface *wifi)// вывод доступных сетей
{
    WiFiAccessPoint *ap;

    printf("Scan:\n");

    int count = wifi->scan(NULL,0);

    if (count <= 0) {
        printf("scan() failed with return value: %d\n", count);
        return 0;
    }

    /* Limit number of network arbitrary to 15 */
    count = count < 15 ? count : 15;

    ap = new WiFiAccessPoint[count];
    count = wifi->scan(ap, count);

    if (count <= 0) {
        printf("scan() failed with return value: %d\n", count);
        return 0;
    }

    for (int i = 0; i < count; i++) {
        printf("Network: %s secured: %s BSSID: %hhX:%hhX:%hhX:%hhx:%hhx:%hhx RSSI: %hhd Ch: %hhd\n", ap[i].get_ssid(),
               sec2str(ap[i].get_security()), ap[i].get_bssid()[0], ap[i].get_bssid()[1], ap[i].get_bssid()[2],
               ap[i].get_bssid()[3], ap[i].get_bssid()[4], ap[i].get_bssid()[5], ap[i].get_rssi(), ap[i].get_channel());
    }
    printf("%d networks available.\n", count);

    delete[] ap;
    return count;
}


string card_data = "";

int main()
{
    //Init all chips and ethernet
    //-------------------------------------
    TCPSocket* socketa = new TCPSocket();
    RfChip.PCD_Init();
    wifi = WiFiInterface::get_default_instance();
    //-------------------------------------

    //starting wifi
    //--------------------------------
    if (!wifi) {
        printf("ERROR: No WiFiInterface found.\n");
        return -1;
    }
    //conect to wifi net by pass and name in mbed_app.json
    //--------------------------------
    printf("\nConnecting to %s...\n", MBED_CONF_APP_WIFI_SSID);
    int ret = wifi->connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2);
    if (ret != 0) {
        printf("\nConnection error: %d\n", ret);
        return -1;
    }
    // show ip add in net
    printf("Success\n\n");
    printf("MAC: %s\n", wifi->get_mac_address());
    printf("IP: %s\n", wifi->get_ip_address());
    printf("Netmask: %s\n", wifi->get_netmask());
    printf("Gateway: %s\n", wifi->get_gateway());
    printf("RSSI: %d\n\n", wifi->get_rssi());
    nsapi_error_t open_result = socketa->open(wifi);
    printf("\nDone\n");
    //--------------------------------

    //main cycle
    //--------------------------------
    thread.start(show_time);// start time thread
    while (1) {
        
        while (1)// while no card readed be in cycle
        {
        if(RfChip.PICC_IsNewCardPresent())
        {
            RfChip.PICC_ReadCardSerial();
            break;// else break them
        }
        else if(RfChip.PICC_ReadCardSerial()) 
        {
            break;// else break them
        }
            cala.read();// show temp while no card
            show_temp(to_string(cala.getCelsius()));
            show_helt(to_string(cala.getHumidity()));
        }
        // if card has been readed, clear displays
        calla(to_string(0000));
        calla_alt(to_string(0000));
        //----------------output card data------------------
        printf("Card Reader 1: ");
        for (uint8_t i = 0; i < RfChip.uid.size; i++) {
            card_data += to_string(RfChip.uid.uidByte[i]) + ' ';// card unique number
        }
        for (uint8_t i = 0; i < RfChip.uid.size; i++) {
            printf(" %X", card_data[i]);
        }
        //-----------------------------------------
        printf("\n\r");
        
               std::vector<std::string> card_id, card_id_for_train {};// main data vector, that contains id and time
        card_id.push_back("id");
        card_id.push_back(card_data); 
        
        card_id_for_train.push_back("id");
        card_id_for_train.push_back(card_data); 

        nsapi_error_t connect_result = socketa->connect("192.168.1.72", 5000);
        
        //init var
        //----------------------------
        int time_alt = 0;    
        int itterations = getTrain(card_id_for_train, socketa);;
        pc.printf("%i", itterations);
        int current = 0;// current number of iterations
        bool checker = false, checker_check = false;// checker - checks that a projectile for training has been lifted
        // checker_check - checks that a projectile for training has been lowered
        check_time_val = true;// access to read time from thread
        //----------------------------
        while (current != 2*itterations) { 
        calla(to_string(current/2));// show current number of iterations
        calla_alt(to_string(tima/8));// show current time
        long distance = sensor.distance();// read data from sensor
        //pc.printf("distanza  %d  \n",distance);
        wait_us(125000);// с этим лучше опрос датчика расстояния
        //time_alt++;
            if (checker && checker_check)
            {
                current++;
                checker = false;           
                checker_check = false;
            }
            else {
            if (distance > 50)
            {
                checker = true;
            }
            if (distance < 5) {
                checker_check = true;
            }
            printf("\n");
            }

        }
        printf("train stop");
        connect_result = socketa->connect("192.168.1.72", 5000);
        // pack all data about train
        card_id.push_back("time");
        card_id.push_back(to_string(tima/8));
        sendData(card_id, socketa);// send them
        card_data = "";// erase card data
        check_time_val = false;// stop read time from thread
        time_alt = 0;
        
    }
    //--------------------------------

}