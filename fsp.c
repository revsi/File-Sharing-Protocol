// Assignment - 2
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
int closingTime;
int Cpid;
int pipeFD[2];
tempo=20;
int *ptr;
void udp_Client( int clientPort)
{
    int connectFlag, bytes_recieved,addr_len;  
    char data_Send [1024],data_Receive[1024];
    char regex[100];
    char fileName[100];
    struct hostent *host;
    struct sockaddr_in server_addr;  
    host= (struct hostent *) gethostbyname((char *)"127.0.0.1");
    if ((connectFlag = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
	perror("Socket");
	fprintf(stderr,"fck\n");
	exit(1);
    }
    server_addr.sin_family = AF_INET;     
    server_addr.sin_port = htons(clientPort);   
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    addr_len = sizeof(struct sockaddr);
    char *result;
    char copy[1024];
    while(1)
    {
	gets(data_Send); 
Todo :		
	strcpy(copy,data_Send);
	result = strtok (copy," ");
	if(result!=NULL)
	{
	    if(strcmp(result,"FileHash")==0)
	    {
		result = strtok (NULL, " ");
		if(result !=NULL)
		{
		    if(strcmp(result,"Verify")==0)
		    {
			result = strtok (NULL, " ");
			if(result!=NULL)
			{
			    strcpy(data_Send,"FV");
			    strcat(data_Send,result);
			    printf("data_Send : %s\n",data_Send);        
			    sendto(connectFlag, data_Send, strlen(data_Send), 0,
				    (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
			    while(1)
			    {
				bytes_recieved=recvfrom(connectFlag,data_Receive,1024,0,
					(struct sockaddr *)&server_addr, &addr_len);
				data_Receive[bytes_recieved] = '\0';
				if(strcmp(data_Receive,"End Of File") == 0)break;
				fwrite(data_Receive,1,bytes_recieved,stdout);
			    }
			    printf("\nout now\n");
			    continue;
			}
		    }
		    else if(strcmp(result,"CheckAll")==0)
		    {
			strcpy(data_Send,"FC");
			sendto(connectFlag, data_Send, strlen(data_Send), 0,
				(struct sockaddr *)&server_addr, sizeof(struct sockaddr));
			while(1)
			{
			    bytes_recieved=recvfrom(connectFlag,data_Receive,1024,0,
				    (struct sockaddr *)&server_addr, &addr_len);
			    data_Receive[bytes_recieved] = '\0';
			    if(strcmp(data_Receive,"End Of File") == 0)break;
			    fwrite(data_Receive,1,bytes_recieved,stdout);
			}
			printf("\nout now\n");
			continue;
		    }
		}
		else printf("Error in FileHash\n");
	    }
	    else if(strcmp(result,"IndexGet")==0)	
	    {
		printf ("%s\n",result);
		result = strtok (NULL, " ");
		if(result!=NULL)
		{
		    if(strcmp(result,"ShortList")==0)
		    {
			result = strtok (NULL, " ");
			if(result!=NULL)
			{
			    strcpy(data_Send,"IS");	    	    
			    strcat(data_Send,result);
			    result = strtok (NULL, " ");
			    if(result!=NULL)
			    {
				strcat(data_Send," ");
				strcat(data_Send,result);
				printf("data_Send : %s\n",data_Send);	
				sendto(connectFlag, data_Send, strlen(data_Send), 0,
					(struct sockaddr *)&server_addr, sizeof(struct sockaddr));
				while(1)
				{
				    bytes_recieved=recvfrom(connectFlag,data_Receive,1024,0,
					    (struct sockaddr *)&server_addr, &addr_len);
				    data_Receive[bytes_recieved] = '\0';
				    if(strcmp(data_Receive,"End Of File") == 0)break;
				    fwrite(data_Receive,1,bytes_recieved,stdout);
				}
				printf("\nout now\n");
				continue;
			    }
			}		
		    }
		    if(strcmp(result,"Regex")==0)
		    {
			result = strtok (NULL, " ");
			if(result!=NULL)
			{
			    strcpy(data_Send,"IR");
			    strcat(data_Send,result);
			    printf("data_Send : %s\n",data_Send);
			    sendto(connectFlag, data_Send, strlen(data_Send), 0,
				    (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
			    while(1)
			    {
				bytes_recieved=recvfrom(connectFlag,data_Receive,1024,0,
					(struct sockaddr *)&server_addr, &addr_len);
				data_Receive[bytes_recieved] = '\0';
				if(strcmp(data_Receive,"End Of File") == 0)break;
				fwrite(data_Receive,1,bytes_recieved,stdout);
			    }
			    printf("\nout now\n");
			    continue;
			}
			else
			{    
			    printf("no filename given\n");
			}
		    }
		    else if(strcmp(result,"LongList")==0)
		    {
			strcpy(data_Send,"IL");
			printf("------SENDING IL\n");
			sendto(connectFlag, data_Send, strlen(data_Send), 0,
				(struct sockaddr *)&server_addr, sizeof(server_addr)); 
			printf("------ready to receive file\n");
			while(1)
			{
			    bytes_recieved=recvfrom(connectFlag,data_Receive,1024,0,
				    (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
			    data_Receive[bytes_recieved] = '\0';
			    if(strcmp(data_Receive,"End Of File") == 0)break;
			    fwrite(data_Receive,1,bytes_recieved,stdout);
			}
			printf("\nout now\n");
			continue;
		    }
		}		
	    }
	    else if(strcmp(result,"Upload") == 0)
	    {
		result = strtok (NULL, " ");
		char arr[100];
		strcpy(arr,result);
		printf("opening %s\n",arr);
		strcpy(data_Send,"U ");
		strcat(data_Send,result);
		sendto(connectFlag, data_Send, 1024, 0,
			(struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	    }
	    else if(strcmp(result,"Download") == 0)
	    {
		result = strtok (NULL, " ");
		if(result!=NULL)
		{
		    strcpy(data_Send,"D ");
		    strcat(data_Send,result);		    
		    sendto(connectFlag, data_Send, 1024, 0,
			    (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
		    printf("printing %s\n",result);
		    FILE *fp1 = fopen(result,"wb");
		    memset(data_Receive,0,1024);
		    while(1)
		    {
			bytes_recieved=recvfrom(connectFlag,data_Receive,1024,0,
				(struct sockaddr *)&server_addr, &addr_len);
			data_Receive[bytes_recieved] = '\0';
			printf("got %s number %d-----\n",data_Receive,bytes_recieved);
			if(strcmp(data_Receive,"End Of File")==0)
			{
			    break;
			}	
			fwrite(data_Receive, 1,bytes_recieved, fp1);
		    }
		    printf("File closed\n");
		    fclose(fp1);
		}

		else printf("Wrong use of download");

	    }
	    else if(strcmp(result,"Allow") == 0)
	    {	

		close(pipeFD[1]);
		int nbytes = read(pipeFD[0],fileName,sizeof(fileName));
		strcpy(data_Send,"Download ");		
		strcat(data_Send,fileName);
		goto Todo;
	    }
	    else if(strcmp(result,"Stop") == 0)
	    {
		printf("Process stopped\n");
	    }
	    else{
		if ((strcmp(data_Send , "q") == 0 || strcmp(data_Send , "Q") == 0) || closingTime ==1)
		{
		    if(closingTime)printf("bbye\n");
		    sendto(connectFlag, data_Send, strlen(data_Send), 0,
			    (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) ;
		    fflush(stdout);
		    close(connectFlag);
		    exit(0);
		    break;
		}
		else
		    sendto(connectFlag, data_Send, strlen(data_Send), 0,
			    (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	    }
	}
    }
    return;
}

int toDownload(char * str)
{
    if(strlen(str)>2 && str[0]=='D' && str[1]==' ')
	return 1;
    return 0;
}

void client( int clientPort)
{
    int connectFlag, bytes_recieved;  
    char dataSend [1024],dataReceived[1024];
    char regex[100];
    char fileName[100];
    struct hostent *host;
    struct sockaddr_in server_addr;  
    host = gethostbyname("127.0.0.1");
    if ((connectFlag = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
	perror("Socket");
	fprintf(stderr,"fck\n");
	exit(1);
    }
    server_addr.sin_family = AF_INET;     
    server_addr.sin_port = htons(clientPort);      
    server_addr.sin_addr = *((struct in_addr *)host->h_addr);
    bzero(&(server_addr.sin_zero),8);
    while (connect(connectFlag, (struct sockaddr *)&server_addr,sizeof(struct sockaddr)) == -1) ;
    char *result;
    char copy[1024];
    while(1)
    {
	gets(dataSend);
Todo :		
	strcpy(copy,dataSend);
	result = strtok (copy," ");
	if(result!=NULL)
	{
	    if(strcmp(result,"FileHash")==0) // FileHash Verify or FileHash CheckAll
	    {
		result = strtok (NULL, " ");
		if(result !=NULL)
		{
		    if(strcmp(result,"Verify")==0)
		    {
			result = strtok (NULL, " ");
			if(result!=NULL)
			{
			    strcpy(dataSend,"FV");
			    strcat(dataSend,result);
			    send(connectFlag, dataSend,strlen(dataSend), 0);
			    while(1)
			    {
				bytes_recieved=recv(connectFlag,dataReceived,1024,0);
				dataReceived[bytes_recieved] = '\0';
				if(strcmp(dataReceived,"End Of File") == 0)break;
				fwrite(dataReceived,1,bytes_recieved,stdout);

			    }
			    continue;
			}
		    }
		    else if(strcmp(result,"CheckAll")==0)
		    {
			strcpy(dataSend,"FC");
			send(connectFlag, dataSend,strlen(dataSend), 0);
			while(1)
			{
			    bytes_recieved=recv(connectFlag,dataReceived,1024,0);
			    dataReceived[bytes_recieved] = '\0';
			    if(strcmp(dataReceived,"End Of File") == 0)break;
			    fwrite(dataReceived,1,bytes_recieved,stdout);
			}
			continue;
		    }
		}
		else printf("wrong usage of FileHash\n");
	    }
	    else if(strcmp(result,"IndexGet")==0)	
	    {
		printf ("%s\n",result);
		result = strtok (NULL, " ");
		if(result!=NULL)
		{
		    if(strcmp(result,"ShortList")==0)
		    {
			result = strtok (NULL, " ");
			if(result!=NULL)
			{
			    strcpy(dataSend,"IS");
			    strcat(dataSend,result);
			    result = strtok (NULL, " ");
			    if(result!=NULL)
			    {
				strcat(dataSend," ");
				strcat(dataSend,result);
				send(connectFlag, dataSend,strlen(dataSend), 0);
				
				while(1)
				{
				    bytes_recieved=recv(connectFlag,dataReceived,1024,0);
				    dataReceived[bytes_recieved] = '\0';
				    if(strcmp(dataReceived,"End Of File") == 0)break;
				    fwrite(dataReceived,1,bytes_recieved,stdout);
				}
				printf("\nout now\n");
				continue;
			    }
			}
			else printf("Wrong Usage. Please Type \"IndexGet ShortList <filename>\"	\n");	
		    }
		    if(strcmp(result,"Regex")==0)
		    {
			result = strtok (NULL, " ");
			if(result!=NULL)
			{
			    strcpy(dataSend,"IR");
			    strcat(dataSend,result);
			    printf("dataSend : %s\n",dataSend);
			    send(connectFlag, dataSend,strlen(dataSend), 0);
			    while(1)
			    {
				bytes_recieved=recv(connectFlag,dataReceived,1024,0);
				dataReceived[bytes_recieved] = '\0';
				if(strcmp(dataReceived,"End Of File") == 0)break;
				fwrite(dataReceived,1,bytes_recieved,stdout);		
			    }
			    continue;
			}
			else
			{
			    printf("Regular Expression not Given, please try again\n");
			}
		    }
		    else if(strcmp(result,"LongList")==0)
		    {
			strcpy(dataSend,"IL");
			send(connectFlag, dataSend,strlen(dataSend), 0); 
			while(1)
			{
			    bytes_recieved=recv(connectFlag,dataReceived,1024,0);
			    dataReceived[bytes_recieved] = '\0';
			    if(strcmp(dataReceived,"End Of File") == 0)break;
			    fwrite(dataReceived,1,bytes_recieved,stdout);
			}
			continue;
		    }
		}
	    }
	    else if(strcmp(result,"Upload") == 0)
	    { 
		result = strtok (NULL, " ");
		char arr[100];
		strcpy(arr,result);
		printf("Waiting for permission to Upload %s\n",arr);	
		strcpy(dataSend,"U ");
		strcat(dataSend,result);
		write(connectFlag,dataSend,1024);
	    }
	    else if(strcmp(result,"Download") == 0)
	    {
		result = strtok (NULL, " ");
		if(result!=NULL)
		{
resend:			strcpy(dataSend,"D ");
			strcat(dataSend,result);
			write(connectFlag,dataSend,1024);
			FILE *fp1 = fopen(result,"w");

			memset(dataReceived,0,1024);
			while(1)
			{
			    bytes_recieved=read(connectFlag,dataReceived,1024);
			    if(strcmp(dataReceived,"End Of File")==0)
			    {
				break;
			    }	
			    fwrite(dataReceived, 1,bytes_recieved, fp1);
			}
			fclose(fp1);
			bytes_recieved=read(connectFlag,dataReceived,1024);
			char dt[1024];
			strcpy(dt,dataReceived);
			char * hsh = strtok(dt," ");
			if(hsh == NULL) 
			    hsh = strtok(NULL," ");	
			if(strcmp(hsh,result) == 0)
			{
			    hsh = strtok(NULL," ");
			    char fname[100];
			    strcpy(fname,result);
			    char packet[1024];
			    char cmd[1000],temp[100];
			    int stlen,ii;
			    strcpy(cmd,"md5sum ");
			    strcat(cmd,fname);
			    strcat(cmd," | awk '{print $1}'> t1");
			    system(cmd);
			    FILE *f1= fopen("t1","r");
			    fgets( packet, 100, f1 );
			    stlen=strlen(packet);
			    packet[stlen-1]='\0';
			    fclose(f1);
			    strcpy(cmd,"rm t1");
			    system(cmd);
			    if(strcmp(packet,hsh) == 0 ) 
				printf(" TRANSFER COMPLETE\n");
			    else
			    {
				printf("ERROR md5 shows error, will RE_REQUEST FILE\n") ;
				goto resend;
			    }		
			}
			else printf("ERROR unknown as file names dont match\n");
		}

		else
		    printf("Error in download");

	    }
	    else if(strcmp(result,"Allow") == 0)
	    {	

		close(pipeFD[1]);
		int nbytes = read(pipeFD[0],fileName,sizeof(fileName));
		strcpy(dataSend,"Download ");
		strcat(dataSend,fileName);
		goto Todo;
	    }
	    else if(strcmp(result,"Stop") == 0)
	    {
		printf("Process stopped\n");
	    }
	    else{
		if ((strcmp(dataSend , "q") == 0 || strcmp(dataSend , "Q") == 0) || closingTime ==1)
		{
		    if(closingTime)printf("bbye\n");
		    send(connectFlag, dataSend,strlen(dataSend), 0); 
		    
		    fflush(stdout);
		    close(connectFlag);
		    
		    kill(Cpid, SIGTERM);
		    exit(0);
		    break;
		}
		else
		    send(connectFlag, dataSend,strlen(dataSend), 0);  
	    }
	}
    }
    return;
}
void tcp_Server(int serverPort)
{

    char command[1024];
    char lower[100],upper[100],cpy[1000];
    int sock, connectFlag, true = 1,bytes_recieved;  
    char dataSend [1024],dataReceived[1024],copy[1024];       
    char regex[100];
    struct sockaddr_in server_addr,client_addr;    
    int size_in;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
	perror("Socket");
	exit(1);
    }
    server_addr.sin_family = AF_INET;         
    server_addr.sin_port = htons(serverPort);     
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    bzero(&(server_addr.sin_zero),8); 
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))
	    == -1) {
	perror("Unable to bind");
	exit(1);
    }
    if (listen(sock, 5) == -1) {
	perror("Listen");
	exit(1);
    }
    printf("\nTCP Server Waiting for client on port %d\n",serverPort);
    fflush(stdout);
    size_in = sizeof(struct sockaddr_in);
    connectFlag = accept(sock, (struct sockaddr *)&client_addr,&size_in);
    printf("\n I got a connection from (%s , %d)",
	    inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
    char * result;
    fflush(stdout);
    int cntr=0;
    char buff[1000];
    FILE *fpr;
    FILE *filePointer2;
    int place=0;
    while (1)
    {
	bytes_recieved=recv(connectFlag,dataReceived,1024,0);
	dataReceived[bytes_recieved] = '\0';
	if (strcmp(dataReceived , "q") == 0 || strcmp(dataReceived , "Q") == 0)
	{	printf("have to close\n");
	    closingTime = 1; 
	    close(connectFlag);
	    break;
	}
	else if(dataReceived[0]=='F' && dataReceived[1]=='C')
	{
	    system("find . -type f -exec sh -c 'printf \"%s %s \n\" \"$(ls -l --time-style=+%Y%m%d%H%M%S $1 )\" \"$(md5sum $1 | cut -d\" \" -f1)\"' '' '{}' '{}' \\; | awk '{print $7, $6, $8}' > checkall");
	    FILE *fp = fopen("checkall","r");
	    if(fp == NULL)
	    {
		printf("wrong file\n");
		continue;
	    }
	    memset(dataSend,0,1024);
	    int byte_R,sentN;
	    while(!feof(fp))
	    {	
		byte_R = fread(dataSend,1,1024,fp);
		dataSend[byte_R] = '\0';
		sentN =  write(connectFlag,dataSend,1024);
	    }
	    memset(dataSend,0,1024);
	    char end[]= "End Of File";
	    strcpy(dataSend,end);
	    write(connectFlag,dataSend,1024);
	    fclose(fp);
	    continue;
	}
	else if(dataReceived[0]=='F' && dataReceived[1]=='V')
	{
	    strncpy(regex,(char*)dataReceived+2,100);
	    printf("Verifying %s\n",regex);
	    strcpy(command,"openssl md5 ");
	    strcat(command,regex);
	    strcat(command," | cut -d\" \" -f2 > md5");
	    system(command);
	    strcpy(command,"date -r ./");
	    strcat(command,regex);
	    strcat(command," +%Y%m%d%H%M%S > date");
	    system(command);
	    strcpy(command,"paste md5 date > verify");
	    system(command);
	    strcpy(command,"rm md5 date");
	    system(command);
	    FILE *fp = fopen("verify","r");
	    if(fp == NULL)
	    {
		printf("wrong file\n");
		continue;
	    }
	    memset(dataSend,0,1024);
	    int byte_R,sentN;
	    while(!feof(fp))
	    {
		byte_R = fread(dataSend,1,1024,fp);
		dataSend[byte_R] = '\0';
		sentN =  write(connectFlag,dataSend,1024);
	    }
	    memset(dataSend,0,1024);
	    char end[]= "End Of File";
	    strcpy(dataSend,end);
	    write(connectFlag,dataSend,1024);
	    fclose(fp);
	    continue;
	}
	else if(dataReceived[0]=='I' && dataReceived[1]=='L')
	{
	    system("find . -printf '%p %TY%Tm%Td%TH%Tm%Tm %k \n' > il");
	    FILE *fp = fopen("il","r");
	    if(fp == NULL)
	    {
		printf("wrong file\n");
		continue;
	    }
	    memset(dataSend,0,1024);
	    int byte_R,sentN;
	    while(!feof(fp))
	    {	
		byte_R = fread(dataSend,1,1024,fp);
		dataSend[byte_R] = '\0';
		sentN =  write(connectFlag,dataSend,1024);
		printf("%s",dataSend);
		printf("read %d sent %d--------\n",sentN,byte_R);
	    }
	    printf("End file\n");
	    memset(dataSend,0,1024);
	    char end[]= "End Of File";
	    strcpy(dataSend,end);
	    write(connectFlag,dataSend,1024);
	    fclose(fp);			
	    printf("dataReceived after longlist : %s \n",dataReceived);
	    continue;
	}
	else if(dataReceived[0] == 'I' && dataReceived[1]=='S')
	{
	    printf("Identified ID\n");
	    strncpy(regex,(char*)dataReceived+2,100);		
	    printf("Timestamps are is %s\n",regex);
	    result = strtok (regex," ");
	    strcpy(lower,result);
	    result = strtok (NULL, " ");
	    strcpy(upper,result);
	    system("ls -l --time-style=+%Y%m%d%H%M%S -t > ls");
	    fpr = fopen( "ls", "r" );
	    filePointer2 = fopen( "is", "w" );
	    while ( fgets( buff, 1000, fpr ) != NULL )
	    {	
		if(cntr!=0 && cntr!=1)
		{
		    printf("%d hahaha    %s",cntr,buff);
		    strcpy(cpy,buff);
		    place=0;
		    result = strtok (buff," ");
		    while (result != NULL)
		    {
			if(place==5)
			{
			    printf("%s\n", result);
			    if(strcmp(result,lower)>0 && strcmp(result,upper)<0)
			    {
				printf("printing\n");
				fprintf(filePointer2,"%s",cpy);
			    }
			}
			place++;
			result = strtok (NULL," ");
		    }
		}
		cntr++;
	    }
	    fclose( fpr );
	    fclose( filePointer2 );
	    FILE *fp = fopen("is","r");
	    if(fp == NULL)
	    {
		printf("wrong file\n");
		continue;
	    }
	    memset(dataSend,0,1024);
	    int byte_R,sentN;
	    while(!feof(fp))
	    {	
		byte_R = fread(dataSend,1,1024,fp);
		dataSend[byte_R] = '\0';
		sentN =  write(connectFlag,dataSend,1024);
		printf("%s",dataSend);
		printf("read %d sent %d--------\n",sentN,byte_R);
	    }
	    memset(dataSend,0,1024);
	    char end[]= "End Of File";
	    strcpy(dataSend,end);
	    write(connectFlag,dataSend,1024);
	    fclose(fp);
	    continue;	
	}
	else if(dataReceived[0]=='I' && dataReceived[1]=='R')
	{
	    strncpy(regex,(char*)dataReceived+2,100);
	    strcpy(command,"find . -name \"");
	    strcat(command,regex);
	    strcat(command,"\" > ir");
	    system(command);
	    FILE *fp = fopen("ir","r");
	    if(fp == NULL)
	    {
		printf("wrong file\n");
		continue;
	    }
	    memset(dataSend,0,1024);
	    int byte_R,sentN;
	    while(!feof(fp))
	    {	
		byte_R = fread(dataSend,1,1024,fp);
		dataSend[byte_R] = '\0';
		sentN =  write(connectFlag,dataSend,1024);
		printf("%s",dataSend);
		printf("read %d sent %d--------\n",sentN,byte_R);
	    }
	    printf("End file\n");
	    memset(dataSend,0,1024);
	    char end[]= "End Of File";
	    strcpy(dataSend,end);
	    write(connectFlag,dataSend,1024);
	    fclose(fp);
	    continue;
	}
	else if(strlen(dataReceived)>2 && dataReceived[0]=='U' && dataReceived[1]==' ')
	{
	    char arr[100];
	    strncpy(arr,(char*)dataReceived+2,100);
	    FILE *fp = fopen(arr,"r");
	    free(fp);
	    printf("Someone wants to Upload File : %s\n Type \"Allow\" to let them; \"Stop\" to prevent them\n",arr);
	    close(pipeFD[0]);
	    write(pipeFD[1],arr,strlen(arr)+1);		

	}
	else if(strlen(dataReceived)>2 && dataReceived[0]=='D' && dataReceived[1]==' ')
	{
	    char arr[100];
	    strcpy(arr,dataReceived+2);
	    printf("Sending %s\n",arr);
	    FILE *fp = fopen(arr,"r");
	    if(fp == NULL)
	    {
		printf("wrong file\n");
		continue;
	    }
	    memset(dataSend,0,1024);
	    int byte_R,sentN;
	    while(!feof(fp))
	    {	
		byte_R = fread(dataSend,1,1024,fp);
		sentN =  write(connectFlag,dataSend,byte_R);

	    }
	    memset(dataSend,0,1024);
	    char end[]= "End Of File";
	    strcpy(dataSend,end);
	    write(connectFlag,dataSend,1024);
	    fclose(fp);
	    char fname[100];
	    strcpy(fname,arr);
	    char packet[1024];
	    char cmd[1000],temp[100];
	    int stlen,ii;
	    strcpy(cmd,"md5sum ");
	    strcat(cmd,fname);
	    strcat(cmd," | awk '{print $2, $1}'> t1");
	    system(cmd);
	    strcpy(cmd,"stat -c%s ");
	    strcat(cmd,fname);
	    strcat(cmd," > t2");
	    system(cmd);
	    strcpy(cmd,"paste t1 t2 | awk '{print $1, $2, $3}' > md5");
	    system(cmd);
	    strcpy(cmd,"rm t1 t2");
	    system(cmd);
	    FILE *f1= fopen("md5","r");
	    fgets( packet, 100, f1 );
	    stlen=strlen(packet);
	    packet[stlen-1]='\0';
	    printf("length of packet now is %d\n",strlen(packet));
	    printf("packet header : %s\n",packet);
	    fclose(f1);
	    strcpy(cmd,"rm md5");
	    system(cmd);
	    memset(dataSend,0,1024);
	    strcpy(dataSend,packet);
	    write(connectFlag,dataSend,1024);
	}
	else
	{
	    printf("%s\n" , dataReceived);
	    fflush(stdout);
	}
    }
    close(sock);
}
void udp_Server(int serverPort)
{
    int sock, connectFlag, true = 1,bytes_recieved,addr_len;  
    char data_Send [1024],data_Receive[1024],copy[1024];       
    char regex[100];
    struct sockaddr_in server_addr,client_addr;    
    int size_in;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
	perror("Socket");
	exit(1);
    }		
    server_addr.sin_family = AF_INET;         
    server_addr.sin_port = htons(serverPort);     
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))
	    == -1)
    {
	perror("Unable to bind");
	exit(1);
    }
    printf("till here\n");
    addr_len = sizeof(struct sockaddr);
    printf("\nUDPServer Waiting for client on port 5000");
    fflush(stdout);
    char * result;
    fflush(stdout);
    char command[1024];
    char lower[100],upper[100],cpy[1000];
    int cntr=0;
    char buff[1000];
    FILE *fpr;
    FILE *filePointer2;
    int place=0;
    while (1)
    {
	bytes_recieved=recvfrom(sock,data_Receive,1024,0,
		(struct sockaddr *)&client_addr, &addr_len);
	data_Receive[bytes_recieved] = '\0';
	if (strcmp(data_Receive , "q") == 0 || strcmp(data_Receive , "Q") == 0)
	{	printf("have to close\n");
	    closingTime = 1;
	    close(connectFlag);
	    break;
	}
	else if(data_Receive[0]=='F' && data_Receive[1]=='C')
	{
	    system("find . -type f -exec sh -c 'printf \"%s %s \n\" \"$(ls -l --time-style=+%Y%m%d%H%M%S $1 )\" \"$(md5sum $1 | cut -d\" \" -f1)\"' '' '{}' '{}' \\; | awk '{print $7, $6, $8}' > checkall");
	    FILE *fp = fopen("checkall","r");
	    if(fp == NULL)
	    {
		printf("wrong file\n");
		continue;
	    }
	    memset(data_Send,0,1024);
	    int byte_R,sentN;
	    while(!feof(fp))
	    {
		byte_R = fread(data_Send,1,1024,fp);
		data_Send[byte_R] = '\0';
		sentN =  sendto(sock, data_Send, 1024, 0,
			(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
		printf("%s",data_Send);
		printf("read %d sent %d--------\n",sentN,byte_R);
	    }
	    printf("End file\n");
	    memset(data_Send,0,1024);
	    char end[]= "End Of File";
	    strcpy(data_Send,end);
	    sendto(sock, data_Send, 1024, 0,
		    (struct sockaddr *)&client_addr, sizeof(struct sockaddr));
	    fclose(fp);
	    printf("data_Receive after check all : %s \n",data_Receive);
	    continue;
	}
	else if(data_Receive[0]=='F' && data_Receive[1]=='V')
	{
	    printf("Identified FV\n");
	    strncpy(regex,(char*)data_Receive+2,100);
	    printf("Filename is %s\n",regex);
	    strcpy(command,"openssl md5 ");
	    strcat(command,regex);
	    strcat(command," | cut -d\" \" -f2 > md5");
	    system(command);
	    strcpy(command,"date -r ./");
	    strcat(command,regex);
	    strcat(command," +%Y%m%d%H%M%S > date");
	    system(command);
	    strcpy(command,"paste md5 date > verify");
	    system(command);
	    strcpy(command,"rm md5 date");
	    system(command);
	    FILE *fp = fopen("verify","r");
	    if(fp == NULL)
	    {
		printf("wrong file\n");
		continue;
	    }
	    memset(data_Send,0,1024);
	    int byte_R,sentN;
	    while(!feof(fp))
	    {	
		byte_R = fread(data_Send,1,1024,fp);
		data_Send[byte_R] = '\0';
		sentN =  sendto(sock, data_Send, 1024, 0,
			(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
		printf("%s",data_Send);
		printf("read %d sent %d--------\n",sentN,byte_R);
	    }
	    printf("End file\n");
	    memset(data_Send,0,1024);
	    char end[]= "End Of File";
	    strcpy(data_Send,end);
	    sendto(sock, data_Send, 1024, 0,
		    (struct sockaddr *)&client_addr, sizeof(struct sockaddr));
	    fclose(fp);

	    printf("data_Receive after verify : %s \n",data_Receive);
	    continue;
	}
	else if(data_Receive[0]=='I' && data_Receive[1]=='L')
	{
	    printf("IL RECEIVED\n");
	    system("find . -printf '%p %TY%Tm%Td%TH%Tm%Tm %k \n' > il");
	    FILE *fp = fopen("il","r");
	    if(fp == NULL)
	    {
		printf("wrong file\n");
		continue;
	    }
	    memset(data_Send,0,1024);
	    int byte_R,sentN;
	    while(!feof(fp))
	    {	
		byte_R = fread(data_Send,1,1024,fp);
		data_Send[byte_R] = '\0';
		sentN =  sendto(sock, data_Send, 1024, 0,
			(struct sockaddr *)&client_addr, sizeof(server_addr));
		printf("%s",data_Send);
		printf("read %d sent %d--------\n",sentN,byte_R);
	    }
	    printf("End file\n");
	    memset(data_Send,0,1024);
	    char end[]= "End Of File";
	    strcpy(data_Send,end);
	    sendto(sock, data_Send, 1024, 0,
		    (struct sockaddr *)&client_addr, sizeof(server_addr));
	    fclose(fp);
	    continue;
	}
	else if(data_Receive[0] == 'I' && data_Receive[1]=='S')
	{
	    printf("Identified IR\n");
	    strncpy(regex,(char*)data_Receive+2,100);
	    printf("Timestamps are %s\n",regex);
	    result = strtok (regex," ");
	    strcpy(lower,result);
	    result = strtok (NULL, " ");
	    strcpy(upper,result);
	    system("ls -l --time-style=+%Y%m%d%H%M%S -t > ls");
	    fpr = fopen( "ls", "r" );
	    filePointer2 = fopen( "is", "w" );
	    while ( fgets( buff, 1000, fpr ) != NULL )
	    {	
		if(cntr!=0 && cntr!=1)
		{
		    printf("%d hahaha    %s",cntr,buff);
		    strcpy(cpy,buff);
		    place=0;
		    result = strtok (buff," ");
		    while (result != NULL)
		    {
			if(place==5)
			{
			    printf("%s\n", result);
			    if(strcmp(result,lower)>0 && strcmp(result,upper)<0)
			    {
				printf("printing\n");
				fprintf(filePointer2,"%s",cpy);
			    }
			}
			place++;
			result = strtok (NULL," ");
		    }
		}
		cntr++;
	    }
	    fclose( fpr );
	    fclose( filePointer2 );
	    FILE *fp = fopen("is","r");
	    if(fp == NULL)
	    {
		printf("wrong file\n");
		continue;
	    }
	    memset(data_Send,0,1024);
	    int byte_R,sentN;
	    while(!feof(fp))
	    {
		byte_R = fread(data_Send,1,1024,fp);
		data_Send[byte_R] = '\0';
		sentN =  sendto(sock, data_Send, 1024, 0,
			(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
		printf("%s",data_Send);
		printf("read %d sent %d--------\n",sentN,byte_R);
	    }
	    printf("End file\n");
	    memset(data_Send,0,1024);
	    char end[]= "End Of File";
	    strcpy(data_Send,end);
	    sendto(sock, data_Send, 1024, 0,
		    (struct sockaddr *)&client_addr, sizeof(struct sockaddr));
	    fclose(fp);
	    printf("data_Receive after regex : %s \n",data_Receive);
	    continue;
	}
	else if(data_Receive[0]=='I' && data_Receive[1]=='R')
	{
	    printf("Identified IR\n");
	    strncpy(regex,(char*)data_Receive+2,100);
	    printf("Regex is %s\n",regex);
	    strcpy(command,"find . -name \"");
	    strcat(command,regex);
	    strcat(command,"\" > ir");
	    system(command);
	    FILE *fp = fopen("ir","r");
	    if(fp == NULL)
	    {
		printf("Error File Name\n");
		continue;
	    }
	    memset(data_Send,0,1024);
	    int byte_R,sentN;
	    while(!feof(fp))
	    {	
		byte_R = fread(data_Send,1,1024,fp);
		data_Send[byte_R] = '\0';
		sentN =  sendto(sock, data_Send, 1024, 0,
			(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
		printf("%s",data_Send);
		printf("read %d sent %d--------\n",sentN,byte_R);
	    }
	    printf("End file\n");
	    memset(data_Send,0,1024);
	    char end[]= "End Of File";
	    strcpy(data_Send,end);
	    sendto(sock, data_Send, 1024, 0,
		    (struct sockaddr *)&client_addr, sizeof(struct sockaddr));
	    fclose(fp);
	    printf("data_Receive after regex : %s \n",data_Receive);
	    continue;
	}
	else if(strlen(data_Receive)>2 && data_Receive[0]=='U' && data_Receive[1]==' ')
	{
	    char arr[100];
	    strncpy(arr,(char*)data_Receive+2,100);
	    printf("Someone wants to Upload File : %s\n Type \"Allow\" to let them; \"Stop\" to prevent them\n",arr);
	    close(pipeFD[0]);
	    write(pipeFD[1],arr,strlen(arr)+1);		
	}
	else if(strlen(data_Receive)>2 && data_Receive[0]=='D' && data_Receive[1]==' ')
	{
	    char arr[100];
	    strcpy(arr,data_Receive+2);
	    printf("opening %s\n",arr);
	    FILE *fp = fopen(arr,"r");
	    if(fp == NULL)
	    {
		printf("wrong file\n");
		continue;
	    }
	    memset(data_Send,0,1024);
	    int byte_R,sentN;
	    while(!feof(fp))
	    {
		byte_R = fread(data_Send,1,1024,fp);
		data_Send[byte_R] = '\0';
		sentN =  sendto(sock, data_Send, byte_R, 0,
			(struct sockaddr *)&client_addr, sizeof(struct sockaddr));
		printf("%s",data_Send);
		printf("read %d sent %d--------\n",sentN,byte_R);
	    }
	    printf("End file\n");
	    memset(data_Send,0,1024);
	    char end[]= "End Of File";
	    strcpy(data_Send,end);
	    sendto(sock, data_Send, 1024, 0,
		    (struct sockaddr *)&client_addr, sizeof(struct sockaddr));
	    fclose(fp);
	    
	}
	else
	{
	    printf("%s\n" , data_Receive);
	    fflush(stdout);
	}
    }
    close(sock);
}
int main()
{
    int pid;
    int serverPort,choice=0;
    printf("####		File Transfer Protocol - Assignment 2		####\n\n\n\n");
    printf("enter server port\n");
    scanf("%d",&serverPort);
    printf("enter 0 for tcp mode and 1 for udp mode\n");
    scanf("%d",&choice);
    closingTime = 0;
    pipe(pipeFD);
    Cpid = getpid();
    pid = fork();
    if(!pid)
    {
	int clientPort;
	scanf("%d",&clientPort);
	if(choice==0)
	    client(clientPort);
	else
	    udp_Client(clientPort);
    }
    else
    {		
	if(choice==0)
	    tcp_Server(serverPort);
	else
	    udp_Server(serverPort);
    }
    return 0;
}
