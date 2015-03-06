
// what about new errno's? EINVAL, EOPNOTSUPP seem mostly fine...maybe.

#ifndef netinet/pvd.h

// Not guaranteed to be stable across across associations to a PVD.
//
// The same PVD may have different pvd_index_t's if, for example,
// when reattaching later to the same PVD (returning home in the
// evening), the same PVD may be assigned a different pvd_index_t.
//
// The pvd_index_t must remain valid until a disconnection or
// disassociation event occurs, after which the pvd_index_t MUST NOT
// be recycled to refer to a different PVD so long as there remain
// any identifiable references to it (e.g. a process or thread still
// has this PVD index set as its default).
//
// Applications explicitly specifying PVD indices to PVD-aware
// functions are not readily identifiable (indeed an application
// could progressively walk the PVD index space attempting various
// function calls without ever having received any indication from
// the system that a given index was valid).  In order to account for
// this, PVD indices SHOULD NOT be recycled, to the extent possible.
// One acceptable implementation approach is to assign every new PVD
// context a strictly monotically increasing index, such that any
// specific index is not reused until the unsigned integer space has
// been completely exhausted, before restarting again from 1. 
typedef unsigned int pvd_index_t;

// The value PVD_INDEX_INVALID is used to indicate no specific PVD.
//
// Depending on the context it may indicate that the system does not
// implement support for the Provisioning Domain API, an error, or
// a signal to "clear" previous PVD index state.
#define PVD_INDEX_INVALID ((pvd_index_t)0)

// PVD_INDEX_UNSPEC is define to be identically valued to
// PVD_INDEX_INVALID, but is provided for use where readability is
// improved (i.e. when PVD_INDEX_INVALID may be returned, but there
// is no error condition being signalled by this return value).
#define PVD_INDEX_UNSPEC PVD_INDEX_INVALID

// Retrieve the current "default" PVD.  If the return type is
// PVD_INDEX_INVALID there may be no PVD accessible to this process
// at this time or no system support for this API.
//
// These values are used by PVD-aware function calls when a PVD index
// is not explicitly specified.
pvd_index_t pvd_system_default();

// Same as above, but operates at a per-process level.  If no
// process-specific default has been set this MUST return the value
// of a call to pvd_current_system_default().
pvd_index_t pvd_process_default();

// Same as above, but operates at a per-thread level.  If no
// thread-specific default has been set this MUST return the value
// of a call to pvd_current_process_default().
pvd_index_t pvd_thread_default();

int pvd_set_system_default(pvd_index_t);  // 0 or -1 && errno = EFOO
int pvd_set_process_default(pvd_index_t);  // 0 or -1 && errno = EFOO
int pvd_set_thread_default(pvd_index_t);  // 0 or -1 && errno = EFOO

// Any function that is not easily extended to support a pvd_index_t
// argument, but for which the underlying operating system understands
// the process-global or per-thread pvd_index can be wrapped to create
// a PVD-aware variant like so:
//
// return_type pvd_functioname(pvd_index_t pvdix, regular arguments...) {
//     pvd_index_t saved = pvd_thread_default();
//     if (pvd_set_thread_default(pvdix) != 0) {
//         // handle error
//         return error_indicator_value;
//     }
//     return_type result = functionname(regular arguments...);
//     pvd_set_thread_default(saved);  // Should error-check
//     return result;
// }

#if 0
Things thare are missing include:

    - should there be a PVD index defined for "node-local"?
      Regardless, need text about what PVD loopback is in or why it's
      in every PVD or...


    - methods to get attributes of a PVD, like whether it
      is comprised of a mobile link versus wifi/ethernet, whether there
      is some metering/charging associated with traffic sent/received via
      this PVD or not, etc.


    - method to get a list of all current PVDs.


    - method to map pvd_index_t's to if_index.

// C.f. if_nameindex()
struct pvd_if_indices {
  pvd_index_t pvd_index;
  unsigned int if_index;
};
#endif
