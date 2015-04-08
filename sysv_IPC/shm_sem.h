#ifndef SHM_SEM_H
#define SHM_SEM_H

int createshm( char * pathname, int proj_id, size_t size);
int sem_delete (int semid);
int sem_v (int semid, int index);
int sem_p(int semid, int index);
int opensem(const char * pathname, int proj_id);
int createsem (const char * pathname,  int proj_id,  int members,  int init_val);

#define SHM_SIZE 1024

#endif

