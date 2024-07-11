const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

// dp 이용한 풀이
const solution = (N) => {
    let dp = Array(N + 1).fill(Math.min());
    // dp 초기값 설정
    dp[3] = 1;
    dp[5] = 1;

    for (let i = 5; i <= N; i++) {
        dp[i] = Math.min(dp[i], Math.min(dp[i - 5] + 1, dp[i - 3] + 1));
    }

    return dp[N] === Math.min() ? -1 : dp[N];
}

let N = null;

rl.on('line', (line) => {
    if (!N) {
        N = +line;
    }
    rl.close();
}).on('close', () => {
    const res = solution(N);
    console.log(res);
    process.exit();
});