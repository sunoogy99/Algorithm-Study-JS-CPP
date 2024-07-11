// 최대공약수 - GCD로 구하기
// 최소공배수 - 두 수의 곱 / GCD

const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let n = null;
let m = null;

function gcd(a, b) {
    if (a > b) [a, b] = [b, a];

    if (b % a === 0) return a;
    else return gcd(b % a, a);
}

const solution = (n, m) => {
    const GCD = gcd(n, m);
    const LCM = n * m / GCD;
    return [GCD, LCM];
}

rl.on('line', (line) => {
    [n, m] = line.split(' ').map(e => +e);
    rl.close();
}).on('close', () => {
    const res = solution(n, m);
    console.log(res);
    process.exit();
});