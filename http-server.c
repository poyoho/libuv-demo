#include <uv.h>

static uv_loop_t* loop;
static uv_tcp_t server;
static uv_buf_t res = uv_buf_init("Hello World\n", 12);

void on_new_connection(uv_stream_t* server, int status) {
  if (status < 0) {
    fprintf(stderr, "New connection error: %s\n", uv_strerror(status));
    return;
  }

  uv_tcp_t* client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
  uv_tcp_init(loop, client);

  if (uv_accept(server, (uv_stream_t*) client) == 0) {
    uv_write_t* req = (uv_write_t*) malloc(sizeof(uv_write_t));
    uv_write(req, (uv_stream_t*) client, &res, 1, NULL);
  } else {
    uv_close((uv_handle_t*) client, NULL);
  }
}

int main() {
  loop = uv_default_loop();

  uv_tcp_init(loop, &server);

  struct sockaddr_in addr;
  uv_ip4_addr("0.0.0.0", 8080, &addr);

  uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
  int r = uv_listen((uv_stream_t*) &server, 128, on_new_connection);

  if (r) {
    fprintf(stderr, "Listen error: %s\n", uv_strerror(r));
    return 1;
  }

  return uv_run(loop, UV_RUN_DEFAULT);
}
