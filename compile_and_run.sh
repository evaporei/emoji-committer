gcc src/main.c src/cli.c src/failure.c -o emoji-committer -I/usr/local/Cellar/openssl/1.0.2s/include -L/usr/local/Cellar/openssl/1.0.2s/ -lssl -lcrypto && ./emoji-committer "$@"
