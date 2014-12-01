
#include <net/pvd.h>

/*
 * getsockopt()/setsockopt()
 *
 * The header file <sys/socket.h> SHALL define SO_PVDINDEX in supporting
 * implementations, for use with getsockopt/setsockopt and the SOL_SOCKET
 * level.  The option_value shall be understood to be a pointer to a
 * pvd_index_t and the option_len is required to be sizeof(pvd_index_t).
 *
 * Setting the SO_PVDINDEX option constrains all operations on the
 * specified socket to function only within the specified PVD currently
 * described by pvd_index_t.  If the pvd_index_t argument has the value
 * PVD_INDEX_UNSPEC then the operating-system policy-defined default is
 * to be used (see <net/pvd.h>).
 */
#define SO_PVDINDEX  some_implementation_specific_value


/*
 * recvmsg()/sendmsg()
 *
 * The same SO_PVDINDEX defined above shall be used as the cmsg_type in
 * conjunction with the SOL_SOCKET cmsg_level to specify struct cmsghdr
 * entries for use with recvmsg() and sendmsg().  These have the same
 * effect described above though applicability is limited to the immediate
 * sendmsg()/recvmsg() invocaton and not for the lifetime the socket file
 * descriptor.
 *
 * In certain situations it may be difficult or impossible for an operating
 * system to determing the correct pvd_index_t for incoming messages (e.g.
 * when there are multiple provisioning domains in a single interface and
 * the system is unable to determine which PVD should be associated with
 * the source of the message.  In such cases, the value returned in the
 * cmsg_data field MAY be PVD_INDEX_UNSPEC. This is not an error, but
 * rather an underspecified situation.
 */


/*
 * accept()
 *
 * If a listening socket is associated with a single PVD, e.g. via a prior
 * call to pvd_set_index() or setsockopt(SOL_SOCKET, SO_PVDINDEX, ...) then
 * traffic arriving from other provisioning domains MUST NOT cause a new
 * connection.
 *
 * Furthermore, whether or not a listening socket has a specified PVD, the 
 * specified PVD MUST be set for the accept()ed file descriptor.  Note that
 * in certain situations (e.g. listening socket using PVD_INDEX_UNPSEC and
 * multiple PVDs on a single interface with insufficient data to map
 * incoming traffic to specific PVDs), the specified PVD MAY be
 * PVD_INDEX_UNSPEC.  This is not an error, but rather an underspecified
 * situation.
 *
 * More broadly, operating systems SHOULD, wherever possible, implement
 * this style of incoming specified pvd_index_t reflection for other protocols
 * with similar accept()-style semantics.
 */
