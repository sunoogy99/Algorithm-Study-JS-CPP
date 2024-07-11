const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let T = null;
let N = null;
let count = 0;

const solution = (N) => {
    const dp = Array(10).fill(0);
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 4;

    for (let i = 4; i <= 10; i++) {
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
    }

    return dp[N];
}

rl.on('line', (line) => {
    if (!T) {
        T = +line;
    } else {
        N = +line;
        const res = solution(N);
        console.log(res);
        count++;
    }

    if (count === T) {
        rl.close();
    }
}).on('close', () => {
    process.exit();
});