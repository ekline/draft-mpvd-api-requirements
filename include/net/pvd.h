
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
// be recycled to refer to a different PVD, but may or may not be
// reused later to refer to the same PVD when re{attaching,connection,associating}
// at some point in the future.
typedef pvd_index_t unsigned int;

// The value PVD_INDEX_UNSPEC is used to indicate that no specific
// PVD is specified but that the operating system should select the
// the current "default" PVD at the time of invocation of any specific
// PVD-aware function call.
//
// The definition of "default" is implementation dependent, and may freely
// change between PVD-aware function invocations over the lifetime of a
// process.
//
// NOTE: PVD_INDEX_UNSPEC specifically DOES NOT mean "all PVDs".  It
// refers to only one PVD at a time, whatever the implementation defines
// as an appropriate default.
#define PVD_INDEX_UNSPEC (pvd_index_t)0

// Retrieve the current "default" PVD.  If the return type is
// PVD_INDEX_UNSPEC there is no PVD accessible to this process at this
// time.
pvd_index_t pvd_current_default_index();
// Same as above, but operates at a per-thread level.
pvd_index_t pvd_thread_current_default_index();

// Get/Set the default PVD to be used for this process in the absence
// of explicitly specified PVD indices.
pvd_index_t pvd_get_index();
int pvd_set_index(pvd_index_t);  // 0 or -1 && errno = EFOO

// Same as above, but operates at a per-thread level.
pvd_index_t pvd_thread_get_index();
int pvd_thread_set_index(pvd_index_t);  // 0 or -1 && errno = EFOO

// Any function that is not easily extended to support a pvd_index_t
// argument, but for which the underlying operating system understands
// the process-global or per-thread pvd_index can be wrapped to create
// a PVD-aware variant like so:
//
// return_type pvd_functioname(pvd_index_t pvdix, regular arguments...) {
//     pvd_index_t saved = pvd_get_index();  // or pvd_thread_get_index()
//     if (pvd_set_index(pvdix) != 0) {
//         // handle error
//         return error_indicator_value;
//     }
//     return_type result = functionname(regular arguments...);
//     pvd_set_index(saved);  // Should error-check
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
