
#include "header_files.h"

struct 
{
    char IDc[100];
    char IDtgs[100];
}
c_to_as;

struct ticket_tgs
{
    char IDc[100];
    char ADc[100];
    char IDtgs[100];
    char TS1[100];
    char lt1[100];
};


struct
{
    char IDc[100];
    char IDv[100];
    struct ticket_tgs t_tgs;
}
c_to_tgs;


struct ticket_v
{
    char IDc[100];
    char ADc[100];
    char IDv[100];
    char TS2[100];
    char lt2[100];
};


struct
{
    char IDc[100];
    struct ticket_v t_v;
}
c_to_v;


int main()
{
    char buffer[100];
    char IDc[] = "ID of client";
    char IDtgs[] = "ID of tgs";
    char IDv[] = "ID of v";
    char Kc[] = "c_as key";
    int Kc_len = strlen(Kc);
   
    
    int sfd_as , sfd_tgs , sfd_v;
    struct sockaddr_in addr_as , addr_tgs , addr_v;


    sfd_as = socket(AF_INET , SOCK_STREAM , 0);
    
    if(sfd_as < 0)
    {
        printf("Error in creating sfd_as socket\n");
        fflush(stdout);
    }

    bzero((char*)&addr_as , sizeof(addr_as));

    addr_as.sin_family = AF_INET;
    addr_as.sin_addr.s_addr = INADDR_ANY ;
    addr_as.sin_port = htons(2000);


    if(connect(sfd_as , (struct sockaddr *) &addr_as , sizeof(addr_as)) < 0)
    {
        printf("Error in connect with as");
        fflush(stdout);
    }
    
    else
    {
        printf("\nsuccessfully connected with as\n");
    }

    
    strcpy(c_to_as.IDc , IDc);
    strcpy(c_to_as.IDtgs , IDtgs);
    write(sfd_as , &c_to_as , sizeof(c_to_as));

    struct ticket_tgs t_tgs;
    read(sfd_as , &t_tgs , sizeof(t_tgs));

    rc4(t_tgs.IDc , Kc , Kc_len);
    rc4(t_tgs.ADc , Kc , Kc_len);
    rc4(t_tgs.IDtgs , Kc , Kc_len);
    rc4(t_tgs.TS1 , Kc , Kc_len);
    rc4(t_tgs.lt1 , Kc , Kc_len);

    

    sfd_tgs = socket(AF_INET , SOCK_STREAM , 0);
    
    if(sfd_tgs < 0)
    {
        printf("Error in creating sfd_tgs socket\n");
        fflush(stdout);   
    }

    bzero((char*)&addr_tgs , sizeof(addr_tgs));

    addr_tgs.sin_family = AF_INET;
    addr_tgs.sin_addr.s_addr = INADDR_ANY ;
    addr_tgs.sin_port = htons(3000);


    if(connect(sfd_tgs , (struct sockaddr *) &addr_tgs , sizeof(addr_tgs)) < 0)
    {
        printf("Error in connect with tgs");
        fflush(stdout);
    }
    
    else
    {
        printf("\nsuccessfully connected with tgs\n");
    }


    strcpy(c_to_tgs.IDc , IDc);
    strcpy(c_to_tgs.IDv , IDv);
    strcpy(c_to_tgs.t_tgs.IDc , t_tgs.IDc);
    strcpy(c_to_tgs.t_tgs.ADc , t_tgs.ADc);
    strcpy(c_to_tgs.t_tgs.IDtgs , t_tgs.IDtgs);
    strcpy(c_to_tgs.t_tgs.TS1 , t_tgs.TS1);
    strcpy(c_to_tgs.t_tgs.lt1 , t_tgs.lt1);

    write(sfd_tgs , &c_to_tgs , sizeof(c_to_tgs));

    struct ticket_v t_v;
    read(sfd_tgs , &t_v , sizeof(t_v));



    sfd_v = socket(AF_INET , SOCK_STREAM , 0);
    
    if(sfd_v < 0)
    {
        printf("Error in creating sfd_v socket\n");
        fflush(stdout);   
    }

    
    bzero((char*)&addr_v , sizeof(addr_v));

    addr_v.sin_family = AF_INET;
    addr_v.sin_addr.s_addr = INADDR_ANY ;
    addr_v.sin_port = htons(4000);

    

    if(connect(sfd_v , (struct sockaddr *) &addr_v , sizeof(addr_v)) < 0)
    {
        printf("Error in connect with v");
        perror("connect v");
        fflush(stdout);
    }
    
    else
    {
        printf("\nsuccessfully connected with v\n");
    }


    strcpy(c_to_v.IDc , IDc);
    strcpy(c_to_v.t_v.IDc , t_v.IDc);
    strcpy(c_to_v.t_v.ADc , t_v.ADc);
    strcpy(c_to_v.t_v.IDv , t_v.IDv);
    strcpy(c_to_v.t_v.TS2 , t_v.TS2);
    strcpy(c_to_v.t_v.lt2 , t_v.lt2);
    
    write(sfd_v , &c_to_v , sizeof(c_to_v));    
    

    read(sfd_v , buffer , 100);
    printf("\nmessage from the server\n%s\n" , buffer);
    while(1);
}

