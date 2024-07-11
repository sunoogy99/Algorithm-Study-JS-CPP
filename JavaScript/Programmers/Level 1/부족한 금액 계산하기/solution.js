const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let price = null;
let money = null;
let count = null;

const solution = (price, money, count) => {
    let cost = 0;

    for (let i = 1; i <= count; i++) {
        cost += price * i;
    }

    return money - cost > 0 ? 0 : cost - money;
    // 등차수열 합 공식 적용 : a * (1 + 2 + 3 + ... N) = a * (N * (N + 1) / 2)
}

rl.on('line', (line) => {
    [price, money, count] = line.split(' ').map(e => +e);
    rl.close();
}).on('close', () => {
    const res = solution(price, money, count);
    console.log(res);
    process.exit();
});