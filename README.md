Multiple Provisioning Domain (MPVD) Requirements for an Application Layer API

# Requirements

1. It MUST be possible for an application to learn all PvDs currently available for its use.

  Obviously policy injection here for the End System (restricting which PvDs can be viewed, and used, by which applications).

  It SHOULD be possible to restrict the returned set of PvDs to meet some requested criteria.

  It SHOULD be possible for an application to receive notifications about changes to a specific PvD, as well as the set of all PvDs (meeting some requested criteria).

  Implementations MAY return PvD handles, used by other API methods to query for specific information rather than the entirety of information in a PvD.

2. All programming interfaces with an implementation that might make use of information that could be found in a PvD MUST support having an explicit PvD specified by the application.

  MAY be explicit (extra argument), could be environment, per-thread setting, etc.

  The implementation MUST scope all network configuration information related operations to the specified PvD.

3. An API SHOULD include a method for an application to obtain any specific information element from a specified PvD.

  Implementation MAY restrict certain information elements (apply policy restrictions), e.g. to preserve privacy, while still allowing operations to be performed by the End System on behalf of the application using this information.

4. An API SHOULD include PvD specific directives that address the most common use cases and help minimize application changes.

  E.g.: allow an application to request the End System always use whichever PvD it determines to be most appropriate for the application at any given time.

# Implementation Guidance
