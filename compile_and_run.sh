gcc src/main.c src/cli.c src/failure.c -o emoji-committer -lssl -lcrypto && ./emoji-committer "$@"
