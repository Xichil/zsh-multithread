#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

int main(int argc, char * argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " 'bash_command'\n";
    return 1;
  }

  // Construct the command string
  std::string command("/usr/bin/zsh -c \"");
  for (int i = 1; i < argc; ++i) {
    command += " ";
    // Escape double quotes in each argument
    for (int j = 0; j < strlen(argv[i]); ++j) {
      if (argv[i][j] == '\"') {
        command += "\\\"";
      } else {
        command += argv[i][j];
      }
    }
  }
  command += " > /dev/null 2>&1\" &"; // Redirect stdout and stderr to /dev/null

  // Fork a new process
  pid_t pid = fork();

  if (pid == -1) {
    // Error forking
    std::cerr << "Error forking a new process.\n";
    return 1;
  } else if (pid == 0) {
    // Child process
    // Execute the command in the background using system()
    int result = system(command.c_str());
    if (result == -1) {
      std::cerr << "Error executing the command.\n";
      return 1;
    }
    return 0;
  } else {
    // Parent process
    std::cout << "Started process with PID: " << pid << "\n";
    std::cout << "CMD: " << command << std::endl;
  }

  return 0;
}
