#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/bio.h>
#include "cli.h"
#include "failure.h"

void http_request(const char* host, const char* path, const char* method) {
  const char* space = " ";
  const char* line_break = "\r\n";
  const char* host_prefix = "Host:";
  const char* http_name = "HTTP/1.1";
  const char* user_agent = "User-Agent: Awesome-Octocat-App";
  const char* connection = "Connection: close";
  int message_len =
    strlen(method) + strlen(space) + strlen(path) + strlen(space) + strlen(http_name) + strlen(line_break) +
    strlen(host_prefix) + strlen(space) + strlen(host) + strlen(line_break) +
    strlen(user_agent) + strlen(line_break) +
    strlen(connection) + strlen(line_break) +
    strlen(line_break);

  char message[message_len];

  sprintf(message, "%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s",
      method, space, path, space, http_name, line_break,
      host_prefix, space, host, line_break,
      user_agent, line_break,
      connection, line_break,
      line_break);

  SSL_library_init();

  SSL_CTX* ssl_context = SSL_CTX_new(SSLv23_client_method());

  if (ssl_context == NULL) {
    exit_with_message("Error creating SSL context");
  }

  BIO* ssl_bio = BIO_new_ssl_connect(ssl_context);

  const char* PORT = "443";
  char hostname[strlen(host) + strlen(PORT)];
  const char* colon = ":";

  sprintf(hostname, "%s%s%s", host, colon, PORT);

  BIO_set_conn_hostname(ssl_bio, hostname);

  if (BIO_do_connect(ssl_bio) <= 0) {
    exit_with_message("Failed to connect to BIO");
  }

  if (BIO_write(ssl_bio, message, message_len) <= 0) {
    exit_with_message("Failed to write bytes");
  }

  int size;
  char buf[1024];

  printf("RESPONSE: \n");

  for (;;) {
    size = BIO_read(ssl_bio, buf, 1023);

    if (size <= 0) {
      break;
    }

    buf[size] = 0;

    printf("%s", buf);
  }

  BIO_free_all(ssl_bio);
  SSL_CTX_free(ssl_context);
}

bool is_github_username_valid(const char* username) {
  int MAXIMUM_GITHUB_USERNAME_SIZE = 39; /* info taken from Google */
  int username_len = strlen(username);

  if (username_len <= 0 || username_len > MAXIMUM_GITHUB_USERNAME_SIZE) {
    return false;
  }

  return true;
}

void get_github_user_repositories(const char* username) {
  const char* host = "api.github.com";

  const char* users_path = "/users";
  const char* slash = "/";
  const char* repos_path = "/repos";
  int path_len = strlen(users_path) + strlen(slash) + strlen(username) + strlen(repos_path);

  printf("path_len %d\n", path_len);
  
  char path[path_len];
  strcat(path, users_path);
  strcat(path, slash);
  strcat(path, username);
  strcat(path, repos_path);

  /* path[path_len] = '\0'; #<{(| truncate rest of string |)}># */

  http_request(host, path, "GET");
}


int main(int argc, const char** args) {
  if (!is_cli_args_size_valid(argc)) {
    exit_with_message("emoji-committer expects exactly one argument, the Github username");
  }

  const char* github_username = get_github_username(args);

  if (!is_github_username_valid(github_username)) {
    exit_with_message("Github username should be lower than 0 and higher than 39");
  }

  printf("github_username: %s\n", github_username);

  get_github_user_repositories(github_username);
}
