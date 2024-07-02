const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let n = null;

const solution = (n) => {
    // 수학) 약수는 대칭적이다.
    // 예를 들면, 30의 약수 : 1, 2, 3, 5, 6, 10, 15, 30 을 보면
    // 1과 30, 2와 15, 3과 10, ... 서로 대칭되는 약수를 곱하면 30이 되는 것을 알 수 있다.
    // 따라서 약수를 구할 때 1 ~ 30까지 나누어 떨어지는 수를 찾을 필요 없이
    // 제곱근까지만 찾아 구하면 된다. (제곱근은 대칭점에 해당한다.)
    // 1 2 3 4 6 9 12 18 36
    let divisors = new Set(); // divisor : 약수, 중복 제거를 위해 Set 사용

    for (let i = 0; i <= Math.pow(n, 0.5); i++) {
        if (n % i === 0) {
            divisors.add(i);
            divisors.add(n / i);
        }
    }

    return Array.from(divisors).reduce((prev, curr) => prev + curr, 0);
}

rl.on('line', (line) => {
    n = +line;
    rl.close();
}).on('close', () => {
    const res = solution(n);
    console.log(res);
    process.exit();
});