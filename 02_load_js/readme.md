# 要求
- nodejs
- pnpm
- esbuild

```
# 安装
pnpm install

# 打包
pnpm esbuild js/main.js --bundle --format=iife --outfile=generate/generate.js --minify

# 运行
out/build/debug/main_app generate/generate.js
```