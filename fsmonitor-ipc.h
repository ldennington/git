#ifndef FSMONITOR_IPC_H
#define FSMONITOR_IPC_H

int fsmonitor_ipc__is_supported(void);

#ifdef HAVE_FSMONITOR_DAEMON_BACKEND
#include "run-command.h"
#include "simple-ipc.h"

/*
 * Returns the pathname to the IPC named pipe or Unix domain socket
 * where a `git-fsmonitor--daemon` process will listen.  This is a
 * per-worktree value.
 */
const char *fsmonitor_ipc__get_path(void);

/*
 * Try to determine whether there is a `git-fsmonitor--daemon` process
 * listening on the IPC pipe/socket.
 */
enum ipc_active_state fsmonitor_ipc__get_state(void);

/*
 * Connect to a `git-fsmonitor--daemon` process via simple-ipc
 * and ask for the set of changed files since the given token.
 *
 * This DOES NOT use the hook interface.
 *
 * Spawn a daemon process in the background if necessary.
 */
int fsmonitor_ipc__send_query(const char *since_token,
			      struct strbuf *answer);

/*
 * Connect to a `git-fsmonitor--daemon` process via simple-ipc and
 * send a command verb.  If no daemon is available, we DO NOT try to
 * start one.
 */
int fsmonitor_ipc__send_command(const char *command,
				struct strbuf *answer);

/*
 * Spawn a new long-running `git-fsmonitor--daemon` process in the
 * background.
 *
 * The daemon may or may not be ready yet when we return, so our
 * caller may need to spin until the daemon is ready.
 */
int fsmonitor_ipc__spawn_daemon(void);

#endif /* HAVE_FSMONITOR_DAEMON_BACKEND */
#endif /* FSMONITOR_IPC_H */