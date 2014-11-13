
#ifndef netinet/pvd.h

typedef pvd_index_t size_t;

#define PVDIDX_UNSPEC (pvd_index_t)0


pvd_index_t getpvd_index();
// Sets the PVD to be used for this process.
int setpvdidx(pvd_index_t);

pvd_index_t pthread_getpvd_index();
// Set the PVD to be used for this thread.
int pthread_setpvd_index(pvd_index_t);

// C.f. if_nameindex()
struct pvd_if_indices {
  pvd_index_t pvd_index;
  unsigned int if_index;
};

cmsg
sockopt
getaddrinfo
getnameinfo

accept/recvfrom/sendto/... and what do about IP addresses and pvdid_t's.
