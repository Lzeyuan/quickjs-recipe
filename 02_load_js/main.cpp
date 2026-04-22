#include <quickjs-libc.h>
#include <quickjs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 读取整个文件内容，返回字符串（调用者需 free）
char *read_file(const char *filename) {
  FILE *f = fopen(filename, "rb");
  if (!f) {
    fprintf(stderr, "无法打开文件: %s\n", filename);
    return NULL;
  }

  fseek(f, 0, SEEK_END);
  long size = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *buffer = (char *)malloc(size + 1);
  if (!buffer) {
    fclose(f);
    fprintf(stderr, "内存分配失败\n");
    return NULL;
  }

  size_t read_size = fread(buffer, 1, size, f);
  buffer[read_size] = '\0';
  fclose(f);
  return buffer;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "用法: %s <JavaScript文件路径>\n", argv[0]);
    return 1;
  }

  const char *js_path = argv[1];
  char *js_code = read_file(js_path);
  if (!js_code) {
    return 1;
  }

  // 创建运行时和上下文
  JSRuntime *rt = JS_NewRuntime();
  if (!rt) {
    fprintf(stderr, "无法创建 JSRuntime\n");
    free(js_code);
    return 1;
  }

  JSContext *ctx = JS_NewContext(rt);
  if (!ctx) {
    fprintf(stderr, "无法创建 JSContext\n");
    JS_FreeRuntime(rt);
    free(js_code);
    return 1;
  }

  // 初始化 libc 处理程序（启用 console.log、std 等）
  js_std_init_handlers(rt);
  js_std_add_helpers(ctx, argc, argv); // 注意：需要 ctx，稍后会移动位置

  // 执行 JS 代码
  JSValue result =
      JS_Eval(ctx, js_code, strlen(js_code), js_path, JS_EVAL_TYPE_GLOBAL);
  free(js_code); // 不再需要原始代码

  // 处理执行结果
  if (JS_IsException(result)) {
    JSValue exception = JS_GetException(ctx);
    JSValue str_ex = JS_ToString(ctx, exception);
    const char *err_msg = JS_ToCString(ctx, str_ex);
    fprintf(stderr, "JavaScript 异常: %s\n", err_msg);
    JS_FreeCString(ctx, err_msg);
    JS_FreeValue(ctx, str_ex);
    JS_FreeValue(ctx, exception);
    JS_FreeValue(ctx, result);
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);
    return 1;
  }

  // 将结果转为字符串并输出
  JSValue str_result = JS_ToString(ctx, result);
  const char *cstr = JS_ToCString(ctx, str_result);
  if (cstr) {
    printf("JS 输出: %s\n", cstr);
    JS_FreeCString(ctx, cstr);
  } else {
    fprintf(stderr, "无法将结果转换为字符串\n");
  }

  // 释放资源
  JS_FreeValue(ctx, str_result);
  JS_FreeValue(ctx, result);
  JS_FreeContext(ctx);
  JS_FreeRuntime(rt);

  return 0;
}