#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// This user program will:
// Accept command-line arguments: strace [args...]
// Fork a child process to run the specified command
// Enable tracing for the child process
// Wait for child completion
// This user program should:
// Validate command-line arguments (at least 2 arguments required)
// Use fork() to create child process
// In child: exec() the target program with its arguments
// In parent: call trace() on child PID, then wait() for completion

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(2, "Usage: strace [command] [args...]\n");
        return 1;
    }

    int pid = fork();
    if (pid < 0) {
        fprintf(2, "strace: fork failed\n");
        return 1;
    }

    if (pid == 0) {
        // Child process
        exec(argv[1], &argv[1]);
        fprintf(2, "strace: exec failed\n");
        return 1;
    } else {
        // Parent process
        trace(pid);  // Enable tracing for the child process
        wait(0);     // Wait for child to complete
    }

    return 0;
}