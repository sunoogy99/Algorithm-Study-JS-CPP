// programmers 방식이랑 별개로 결과만 나오게 진행함

const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let n = null;
let m = null;

const solution = (n, m) => {
    let ans = '';
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            ans += '*';
        }
        
        if (i < m - 1) ans += '\n';
    }

    return ans;
}

rl.on('line', (line) => {
    [n, m] = line.split(' ').map(e => +e);
    rl.close();
}).on('close', () => {
    const res = solution(n, m);
    console.log(res);
    process.exit();
});