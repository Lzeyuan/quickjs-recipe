// main.js
import { sayHello, add } from './utils.js';

const message = sayHello('QuickJS');
console.log(message);          // 输出: Hello, QuickJS!

const sum = add(10, 32);
console.log('10 + 32 =', sum); // 输出: 10 + 32 = 42