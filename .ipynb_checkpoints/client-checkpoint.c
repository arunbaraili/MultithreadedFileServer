/*

The client program lets the client connect to the server and upload, download, list, delete
files from the server. 
05/5/2026

*/

#include "csapp.h"
 
int main(int argc, char **argv) {
    int clientfd; 
    char *host, *port; 
    char buf[MAXLINE]; 
     
    if (argc != 3) {
        printf("Usage: %s <host> <port>\n", argv[0]);
        exit(1);
    }

    host = argv[1]; 
    port = argv[2]; 
     
    while (1) {
        printf("\n(1) Upload File\n"); 
        printf("(2) Download File\n");
        printf("(3) List Files\n");
        printf("(4) Delete File\n");
        printf("(5) Quit\n");
        printf("Select option: ");

        int choice; 
        scanf("%d", &choice); 
        char response[MAXLINE]; 
        clientfd = Open_clientfd(host, port); 
         
        if (choice ==5) {
            sprintf(buf, "Quit\n");
            Rio_writen(clientfd, buf, strlen(buf)); 
            Close(clientfd); 
            break; 
        }
         
        if (choice ==1) {
            char filename[100]; 
            printf("Enter filename: "); 
            scanf("%s", filename);
             
            FILE *fp = fopen(filename, "rb"); 
             
            if(!fp) {
                printf("File not found.\n"); 
                Close(clientfd);
                continue; 
            }
             
            fseek(fp, 0, SEEK_END); 
            int filesize = ftell(fp); 
            rewind(fp); 
             
            sprintf(buf, "Upload %s %d\n", filename, filesize); 
            Rio_writen(clientfd, buf, strlen(buf)); 
             
            char filebuf[MAXBUF]; 
            int n; 
             
            while ((n = fread(filebuf, 1, MAXBUF, fp))> 0) {
                Rio_writen(clientfd, filebuf, n); 
            }

            fclose(fp); 
            printf("Upload completed.\n"); 
        }
         
        else if (choice ==2) {
            char filename[100]; 
            printf("Enter filename: "); 
            scanf("%s", filename); 
             
            sprintf(buf, "Download %s\n", filename); 
            Rio_writen(clientfd, buf, strlen(buf)); 
             
            rio_t rio; 
            Rio_readinitb(&rio, clientfd);

            char response[MAXLINE]; 
            Rio_readlineb(&rio, response, MAXLINE); 

            int filesize; 
             
            if (sscanf(response, "OK %d", &filesize)==1) {
                FILE * fp = fopen(filename, "wb"); 

                char filebuf[MAXBUF]; 
                int remaining = filesize; 
                 
                while (remaining > 0) {
                    int toread = remaining < MAXBUF ? remaining : MAXBUF;
                    int n = Rio_readnb(&rio, filebuf, toread); 

                    fwrite(filebuf, 1, n, fp); 
                    remaining -= n; 
                }

                fclose(fp); 
                printf("Download completed.\n"); 
            } else {
                printf("The file was not found.\n"); 
            }
        }
         
        else if (choice ==3) {
            sprintf(buf, "List\n"); 
            Rio_writen(clientfd, buf, strlen(buf)); 

             
            char response[MAXBUF]; 
            int n = read(clientfd, response, MAXBUF); 
            response[n] = '\0'; 

            printf("\nFiles on server: \n%s\n", response); 
        }
         
        else if(choice == 4) {
            char filename[100]; 
            printf("Enter filename: "); 
            scanf("%s", filename); 

             
            sprintf(buf, "Delete %s\n", filename); 
            Rio_writen(clientfd, buf, strlen(buf)); 
             
            char response[MAXLINE]; 
            int n = read(clientfd, response, MAXLINE); 
            response[n] = '\0'; 
            
            printf("%s\n", response); 
        }

        Close(clientfd); 
    }

    return 0; 
}