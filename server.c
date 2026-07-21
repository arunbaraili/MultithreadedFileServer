/*

The program server will act as a database that reads, and let use interact with the server and 
lets users make requests listen in the client section. 

*/


#include "csapp.h"
#include <pthread.h>

void handle_client(int connfd); 
 
void *thread(void *vargp) {
     
    int connfd = *((int *)vargp);
     
    free(vargp);
     
    handle_client(connfd); 
    Close(connfd); 
    return NULL; 
}

int main (int argc, char **argv) {
     
    int listenfd; 
    socklen_t clientlen;
    struct sockaddr_storage clientaddr; 
     
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]); 
        exit(1);
    }

    listenfd = Open_listenfd(argv[1]); 
     
    while (1) {
        clientlen = sizeof(clientaddr);
        int *connfdp = Malloc(sizeof(int));
        *connfdp = Accept(listenfd, (SA *)&clientaddr, &clientlen);
         
        pthread_t tid; 
        Pthread_create(&tid, NULL, thread, connfdp); 
        Pthread_detach(tid);
    }
}
 
void handle_client(int connfd) {
    char buf[MAXLINE]; 
    rio_t rio; 
    Rio_readinitb(&rio, connfd); 
     
    while (Rio_readlineb(&rio, buf, MAXLINE) >0) {
         
        if(strncmp(buf, "Upload", 6) ==0) {
            char filename[100]; 
            int filesize; 

            sscanf(buf, "Upload %s %d", filename, &filesize); 
            filename[strcspn(filename, "\r\n")] = 0; 
             
            char filebuf[MAXBUF];
            int remaining = filesize; 

            char *base = strrchr(filename, '/'); 
            base = base ? base +1: filename; 

            int fd = Open(base, O_CREAT | O_WRONLY | O_TRUNC, 0644); 
             
            while (remaining > 0) {
                int toread = remaining < MAXBUF ? remaining : MAXBUF; 
                int n = Rio_readnb(&rio, filebuf, toread); 

                Write(fd, filebuf, n); 
                remaining -= n; 
            }

            Close(fd); 
        }
         
        else if (strncmp(buf, "Download", 8) == 0) {
            char filename[100]; 
            sscanf(buf, "Download %s", filename); 
            filename[strcspn(filename, "\r\n")] = 0; 

            int fd = open(filename, O_RDONLY, 0); 
             
            if (fd < 0) {
                Rio_writen(connfd, "Error\n", 6); 
                continue; 
            }
            struct stat st; 
            fstat(fd, &st); 

            char header[MAXLINE]; 
            sprintf(header, "OK %ld\n", st.st_size); 
            Rio_writen(connfd, header, strlen(header)); 

            char filebuf[MAXBUF]; 
            int n; 
             
            while ((n = read(fd, filebuf, MAXBUF)) > 0) {
                Rio_writen(connfd, filebuf, n); 
            }
            close(fd); 
        }
         
        else if (strncmp(buf, "List", 4) == 0) {
            DIR *dir = opendir("."); 
            struct dirent *entry; 

            char response[MAXBUF] = ""; 
             
            while ((entry = readdir(dir)) != NULL) {
                strcat(response, entry->d_name); 
                strcat(response, "\n"); 
            }

            Rio_writen(connfd, response, strlen(response)); 
            closedir(dir); 
        }
         
        else if (strncmp(buf, "Delete", 6) == 0) {
            char filename[100]; 
            sscanf(buf, "Delete %s", filename); 
            filename[strcspn(filename, "\r\n")] = 0; 
             
            if (remove(filename)==0) {
                Rio_writen(connfd, "Deleted\n", 8);
            } else {
                Rio_writen(connfd, "Error deleting file\n", strlen("Error deleting file\n")); 
            }
        }
         
        else if (strncmp(buf, "Quit", 4) ==0) {
            break; 
        }
    }
}