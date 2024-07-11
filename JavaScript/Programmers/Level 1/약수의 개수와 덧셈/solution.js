const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let left = null;
let right = null;

const getDivisorsCount = (num) => {
    let rootNum = Math.pow(num, 0.5);
    let res = 0;
    for (let i = 1; i < rootNum; i++) {
        if (num % i === 0) res++;
    }

    // 약수 대칭수인 경우 +1 더함
    return res * 2 + (Math.trunc(rootNum) === rootNum ? 1 : 0);
}

const solution = (left, right) => {
    let ans = 0;
    for (let i = left; i <= right; i++) {
        if (getDivisorsCount(i) % 2 === 0) {
            ans += i;
        }
        else {
            ans -= i;
        }
    }

    return ans;
}

rl.on('line', (line) => {
    [left, right] = line.split(' ').map(e => +e);
    rl.close();
}).on('close', () => {
    const res = solution(left, right);
    console.log(res);
    process.exit();
});