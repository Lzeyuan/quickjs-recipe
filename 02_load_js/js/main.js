// 使用 ES 模块语法导入
import { formatGreeting, getCurrentTime, toUpperCase, toLowerCase, APP_NAME } from './utils.js';
import math, { add, multiply, factorial } from './math.js';

console.log(`=== ${APP_NAME} ===`);
console.log("");

console.log("--- 工具函数测试 ---");
const name = "ES Module";
console.log(formatGreeting(name));
console.log(`大写: ${toUpperCase(name)}`);
console.log(`小写: ${toLowerCase(name)}`);
console.log(`当前时间: ${getCurrentTime()}`);
console.log("");

console.log("--- 数学函数测试 ---");
console.log(`10 + 20 = ${add(10, 20)}`);
console.log(`7 × 8 = ${multiply(7, 8)}`);
console.log(`5! = ${factorial(5)}`);
console.log("");

console.log("--- 使用默认导入 ---");
console.log(`100 ÷ 4 = ${math.divide(100, 4)}`);
console.log(`2^10 = ${math.power(2, 10)}`);
console.log(`50 - 25 = ${math.subtract(50, 25)}`);
console.log("");

console.log("--- 综合测试 ---");
const a = 12;
const b = 7;
const sum = add(a, b);
const product = multiply(a, b);
console.log(`数字: a=${a}, b=${b}`);
console.log(`和: ${sum}, 积: ${product}`);
console.log(`"sum" 大写: ${toUpperCase("sum")}`);

console.log("");
console.log("=== ES Module Demo 运行完成 ===");