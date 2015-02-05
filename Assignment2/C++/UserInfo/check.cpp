//IMPORTANT: the logic is NOT complete, the program works only once and
disconnects or freeze
//One needs to modify or rewrite the program so it is fully functional
for LIST and RETR
//Please refer to the sockets material and examples
//(compare this code with serv1.c and client.c codes)
//
//To connect use an FTP client. The port is 1221. To connect locally
issue the following command:
//#ftp 127.0.0.1 1221
//
// The server will have to:
//1 - accept LIST, CWD and PUT commands issued by the client.
//2 - The client should be an actual FTP application available in the
OS.
//3 - If the client type 'ls' or 'dir' it issues LIST. The content of
the directory is then shown on screen.
// The role of the server is just to send the contents via sockets.
//Includes
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<string.h>
#include<unistd.h>
#include<errno.h>
//Defines
#define WSVERS MAKEWORD(2,0)
WSADATA wsadata;
#define STKSIZE 16536

char sbuffer[80],rbuffer[80];//send and receive buffers
int n,bytes;//counters
SOCKET ns,ns_data;//sockets, ns is a new socket (on 1221) and ns_data
is a new socket for data (1220)
struct sockaddr_in remoteaddr, remoteaddr_data;
int active=0;
//MAIN
main(int argc, char *argv[]) {
struct sockaddr_in localaddr;//local address structure
struct sockaddr_in local_data_addr;//local address struct for data
connection
struct sockaddr_in local_data_addr_act;//local address for active
connection
SOCKET s,s_data,s_data_act;//welcome socket, welcome socket for data
connection and socket for active connection
int addrlen;//address lenght variable

if (WSAStartup(WSVERS, &wsadata) != 0) {
WSACleanup();
printf("WSAStartup failed\n");
}

memset(&localaddr,0,sizeof(localaddr));//clear localaddr
memset(&local_data_addr,0,sizeof(local_data_addr)) ;//clear
local_data_addr
memset(&local_data_addr_act,0,sizeof(local_data_ad dr_act));
//SOCKETS (notice that there are two welcome sockets, one for control,
one for data
s = socket(AF_INET, SOCK_STREAM, 0);
s_data = socket(AF_INET, SOCK_STREAM, 0);
s_data_act = socket(AF_INET, SOCK_STREAM, 0);
//include other errors here
if (s < 0) {
printf("socket failed\n");
}

localaddr.sin_family = AF_INET;
local_data_addr.sin_family = AF_INET;
if (argc == 2) localaddr.sin_port = htons((u_short)atoi(argv[1]));
else localaddr.sin_port = htons(1221);

localaddr.sin_addr.s_addr = INADDR_ANY;
local_data_addr.sin_port = htons(1220);
local_data_addr.sin_addr.s_addr = INADDR_ANY;
//BIND (bind uses ports 1221 and 1220 by default)
if (bind(s,(struct sockaddr *)(&localaddr),sizeof(localaddr)) < 0) {
printf("Bind failed!\n");
}
if (bind(s_data,(struct sockaddr
*)(&local_data_addr),sizeof(local_data_addr)) < 0) {
printf("Bind failed!\n");
}
//LISTEN
listen(s,5);
listen(s_data,5);
//INFINITE LOOP
while (1) {
addrlen = sizeof(remoteaddr);
//ACCEPT main connection (control connection)
ns = accept(s,(struct sockaddr *)(&remoteaddr),&addrlen);
printf("connected to %s\n",inet_ntoa(remoteaddr.sin_addr));
//Respond with welcome message, FTP client requires those
sprintf(sbuffer,"200 Welcome \r\n");
bytes = send(ns, sbuffer, strlen(sbuffer), 0);
sprintf(sbuffer,"530 Log in \r\n");
bytes = send(ns, sbuffer, strlen(sbuffer), 0);
sprintf(sbuffer,"530 Log in \r\n");
bytes = send(ns, sbuffer, strlen(sbuffer), 0);
//INFINITE LOOP
while (1) {
n = 0;
while (1) {
//RECEIVE
bytes = recv(ns, &rbuffer[n], 1, 0);
if ((bytes < 0) || (bytes == 0)) break;
if (rbuffer[n] == '\n') { /*end on LF*/
rbuffer[n] = '\0';
break;
}
if (rbuffer[n] != '\r') n++; /*ignore CR's*/
}
if ((bytes < 0) || (bytes == 0)) break;
printf("#The Server receives:# '%s' from client \n", rbuffer);
//STARTS INTERPRETATION OF THE FTP COMMANDS HERE
//Perhaps use "case" or "if/else" for this part
//It is a good idea to 'trap' any mistaken or non-implemented command
returning "500 Syntax error" code
//
//USER
if (strncmp(rbuffer,"USER",4)==0) {
printf("Logging in \n");
sprintf(sbuffer,"331 Password required (anything will do really...
:-) \r\n");
bytes = send(ns, sbuffer, strlen(sbuffer), 0);
}
//PASS
if (strncmp(rbuffer,"PASS",4)==0) {
printf("Typing password (anything will do... \n");
sprintf(sbuffer, "230 Public logging in ok, type your email for
password \r\n");
//sprintf(sbuffer, "230 Public logging in ok, type your email for
password \r\n");
bytes = send(ns, sbuffer, strlen(sbuffer), 0);
}
//SYST
if (strncmp(rbuffer,"SYST",4)==0) {
printf("Information about the system \n");
sprintf(sbuffer, "257 A very naive FTP system... \r\n");
bytes = send(ns, sbuffer, strlen(sbuffer), 0);
}
//PASV
if (strncmp(rbuffer,"PASV",4)==0) {
printf("Passive mode \n");
//change the IP address here if you want to connect from a remote
machine
//227 has a strange format, for IP 127.0.0.1 and port 1220 this is
it...)
sprintf(sbuffer, "227 Passive Mode
(%d,%d,%d,%d,%d,%d)\r\n",127,0,0,1,(1220>>8),(1220 & 0x00FF));
bytes = send(ns, sbuffer, strlen(sbuffer), 0);
//open a new connection on port 1220
ns_data = accept(s_data,(struct sockaddr
*)(&remoteaddr_data),&addrlen);
printf("connected to %s\n",inet_ntoa(remoteaddr.sin_addr));
}
//PORT (this indicates that the client want to make an active
connection)
if (strncmp(rbuffer,"PORT",4)==0) {
//local variables
unsigned char act_port[2];
int act_ip[4], port_dec;
char ip_decimal[40];
printf("Active mode, the client is listening \n");
active=1;//flag for active connection
sscanf(rbuffer, "PORT %d,%d,%d,%d,%d,%d",

&act_ip[0],&act_ip[1],&act_ip[2],&act_ip[3],&act_port[0],&act_port[1]);
local_data_addr_act.sin_family=AF_INET;//local_data_addr_act
sprintf(ip_decimal, "%d.%d.%d.%d", act_ip[0], act_ip[1],
act_ip[2],act_ip[3]);
printf("IP is %s\n",ip_decimal);
local_data_addr_act.sin_addr.s_addr=inet_addr(ip_d ecimal);
port_dec=act_port[0];
port_dec=port_dec << 8;
port_dec=port_dec+act_port[1];
printf("port %d\n",port_dec);
local_data_addr_act.sin_port=htons(port_dec);
if (connect(s_data_act, (struct sockaddr *)&local_data_addr_act,
(int) sizeof(struct sockaddr)) != 0){
printf("trying connection in %s
%d\n",inet_ntoa(local_data_addr_act.sin_addr),ntoh s(local_data_addr_act.sin_port));
sprintf(sbuffer, "425 Something is wrong, can't start active
connection... \r\n");
bytes = send(ns, sbuffer, strlen(sbuffer), 0);
close(s_data_act);
}
else {
sprintf(sbuffer, "200 Ok\r\n");
bytes = send(ns, sbuffer, strlen(sbuffer), 0);
printf("Connected to client\n");
}
}
//LIST (modified so it can use either passive or active connection)
if (strncmp(rbuffer,"LIST",4)==0) {
printf("Equivalent to dir \n");
system("ls > tmp.txt");
FILE *fin=fopen("tmp.txt","r");
sprintf(sbuffer,"125 Transfering... \r\n");
bytes = send(ns, sbuffer, strlen(sbuffer), 0);
char temp_buffer[80];
while (!feof(fin)){
fgets(temp_buffer,78,fin);
sprintf(sbuffer,"%s ",temp_buffer);
if (!active) send(ns_data, sbuffer, strlen(sbuffer), 0);
else send(s_data_act, sbuffer, strlen(sbuffer), 0);
}
fclose(fin);
//sprintf(sbuffer,"\r\n",temp_buffer);
//send(ns_data, sbuffer, strlen(sbuffer), 0);
sprintf(sbuffer,"250 File transfer completed... \r\n");
bytes = send(ns, sbuffer, strlen(sbuffer), 0);
if (!active) close(ns_data);
else close(s_data_act);
sprintf(sbuffer,"226 Close the data connection... \r\n");
bytes = send(ns, sbuffer, strlen(sbuffer), 0);
//	system("del tmp.txt");
}
//QUIT
if (strncmp(rbuffer,"QUIT",3)==0) {
printf("quit \n");
sprintf(sbuffer, "221 Bye bye ... \r\n");
bytes = send(ns, sbuffer, strlen(sbuffer), 0);
close(ns);
printf("disconnected from %s\n",inet_ntoa(remoteaddr.sin_addr));
return;
}
}
//CLOSE CONTROL SOCKET
close(ns);
printf("disconnected from %s\n",inet_ntoa(remoteaddr.sin_addr));
}
//CLOSE WELCOME SOCKET
close(s);
return 0;
}
