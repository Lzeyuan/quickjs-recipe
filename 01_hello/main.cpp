#include <quickjs.h>
#include <stdio.h>
#include <string.h>

int main() {
  // 1. 创建运行时和上下文
  JSRuntime *rt = JS_NewRuntime();
  JSContext *ctx = JS_NewContext(rt);

  // 2. 要执行的 JavaScript 代码（可任意修改）
  const char *js_code = R"JS(
function greet(name) {
    return `Hello, ${name}!`;
}
greet('QuickJS-ng') + ' Result: ' + (100 + 23)
)JS";

  // 3. 执行 JS 代码
  JSValue result =
      JS_Eval(ctx, js_code, strlen(js_code), "<input>", JS_EVAL_TYPE_GLOBAL);

  // 4. 处理执行结果
  if (JS_IsException(result)) {
    // 捕获异常并打印
    JSValue exception = JS_GetException(ctx);
    JSValue str_ex = JS_ToString(ctx, exception);
    const char *err_msg = JS_ToCString(ctx, str_ex);
    printf("JavaScript 异常: %s\n", err_msg);
    JS_FreeCString(ctx, err_msg);
    JS_FreeValue(ctx, str_ex);
    JS_FreeValue(ctx, exception);
  }

  // 将 JS 返回值转换为字符串并输出
  JSValue str_result = JS_ToString(ctx, result);
  const char *cstr = JS_ToCString(ctx, str_result);
  printf("JS 输出: %s\n", cstr);
  JS_FreeCString(ctx, cstr);
  JS_FreeValue(ctx, str_result);

  // 5. 释放资源
  JS_FreeValue(ctx, result);
  JS_FreeContext(ctx);
  JS_FreeRuntime(rt);
  return 0;
}