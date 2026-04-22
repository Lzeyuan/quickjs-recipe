#include "quickjs-libc.h" // 提供 js_std_* 等辅助函数
#include "quickjs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static JSModuleDef *js_module_loader(JSContext *ctx, const char *module_name,
                                     void *opaque) {
  size_t buf_len;
  uint8_t *buf;
  char *filename = NULL;
  JSValue val;
  JSModuleDef *m;

  // 1. 构建文件路径
  if (module_name[0] == '.' || module_name[0] == '/') {
    filename = strdup(module_name);
  } else {
    filename = (char *)malloc(strlen(module_name) + 4);
    strcpy(filename, module_name);
    strcat(filename, ".js");
  }

  // 2. 读取文件内容
  buf = js_load_file(ctx, &buf_len, filename);
  if (!buf) {
    JS_ThrowReferenceError(ctx, "could not load module '%s'", module_name);
    free(filename);
    return NULL;
  }

  // 3. 编译模块（关键：必须使用 JS_EVAL_TYPE_MODULE）
  val = JS_Eval(ctx, (char *)buf, buf_len, filename,
                JS_EVAL_TYPE_MODULE | JS_EVAL_FLAG_COMPILE_ONLY);
  js_free(ctx, buf);
  free(filename);

  // 4. 检查编译异常
  if (JS_IsException(val)) {
    js_std_dump_error(ctx);
    return NULL;
  }

  // 5. 确保返回值是模块类型
  if (JS_VALUE_GET_TAG(val) != JS_TAG_MODULE) {
    JS_FreeValue(ctx, val);
    JS_ThrowTypeError(ctx, "module '%s' did not evaluate to a module",
                      module_name);
    return NULL;
  }

  // 6. 提取模块指针（不要释放 val！）
  m = (JSModuleDef *)JS_VALUE_GET_PTR(val);
  return m;
}

int main(int argc, char *argv[]) {
  JSRuntime *rt;
  JSContext *ctx;
  JSValue result;
  const char *main_module = "./main.js"; // 主模块路径
  size_t main_len;
  uint8_t *main_buf;

  // 1. 创建运行时和上下文
  rt = JS_NewRuntime();
  if (!rt) {
    fprintf(stderr, "Failed to create runtime\n");
    return 1;
  }
  ctx = JS_NewContext(rt);
  if (!ctx) {
    fprintf(stderr, "Failed to create context\n");
    JS_FreeRuntime(rt);
    return 1;
  }

  js_std_init_handlers(rt);
  js_std_add_helpers(ctx, argc, argv);

  // 3. 注册自定义模块加载器
  JS_SetModuleLoaderFunc(rt, NULL, js_module_loader, NULL);

  // 4. 读取主模块文件
  main_buf = js_load_file(ctx, &main_len, main_module);
  if (!main_buf) {
    fprintf(stderr, "Failed to load main module: %s\n", main_module);
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);
    return 1;
  }

  // 5. 以模块方式执行主模块
  result = JS_Eval(ctx, (char *)main_buf, main_len, main_module,
                   JS_EVAL_TYPE_MODULE);
  js_free(ctx, main_buf);

  if (JS_IsException(result)) {
    js_std_dump_error(ctx);
    JS_FreeValue(ctx, result);
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);
    return 1;
  }

  // 6. 释放资源
  JS_FreeValue(ctx, result);
  JS_FreeContext(ctx);
  JS_FreeRuntime(rt);
  return 0;
}