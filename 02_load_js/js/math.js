// 数学函数模块
export function add(a, b) {
    return a + b;
}

export function subtract(a, b) {
    return a - b;
}

export function multiply(a, b) {
    return a * b;
}

export function divide(a, b) {
    if (b === 0) {
        console.log("错误: 除数不能为0");
        return null;
    }
    return a / b;
}

export function power(base, exponent) {
    let result = 1;
    for (let i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

export function factorial(n) {
    if (n < 0) return null;
    if (n === 0 || n === 1) return 1;
    let result = 1;
    for (let i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// 默认导出
export default {
    add,
    subtract,
    multiply,
    divide,
    power,
    factorial
};