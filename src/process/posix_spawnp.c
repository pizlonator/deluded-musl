#include <spawn.h>
#include <unistd.h>
#include <pizlonated_musl_syscalls.h>

int posix_spawnp(pid_t *restrict res, const char *restrict file,
	const posix_spawn_file_actions_t *fa,
	const posix_spawnattr_t *restrict attr,
	char *const argv[restrict], char *const envp[restrict])
{
    return zsys_posix_spawnp(res, file, fa, attr, argv, envp);
}
