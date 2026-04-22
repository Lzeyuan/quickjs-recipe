// 工具函数模块
export function formatGreeting(name) {
    return `Hello, ${name}!`;
}

export function getCurrentTime() {
    const now = new Date();
    return `${now.getHours()}:${now.getMinutes()}:${now.getSeconds()}`;
}

export function toUpperCase(str) {
    return str.toUpperCase();
}

export function toLowerCase(str) {
    return str.toLowerCase();
}

export const APP_NAME = "QuickJS-ng Demo";