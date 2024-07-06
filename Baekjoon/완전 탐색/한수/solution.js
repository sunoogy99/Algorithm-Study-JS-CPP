const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let N = null;

const solution = (N) => {
    const checkNum = (num) => {
        let numArray = (num + "").split('').map(e => +e);
        
        // 한 자리 수는 등차수열로 판별함
        if (numArray.length === 1) return true;
        
        // 등차수열 공식 : a + di
        let a = numArray[0];
        let d = numArray[1] - a;

        for (let i = 1; i < numArray.length; i++) {
            // 등차수열 공식이 깨지는 지점에서 해당 수가 한수가 아님을 반환
            if (numArray[i] !== a + d * i) return false;
        }

        // 모든 경우를 통과하면 한수로 판별
        return true;
    }

    let ans = 0;
    for (let i = 1; i <= N; i++) {
        if (checkNum(i)) {
            ans++;
        }
    }

    return ans;
}

rl.on('line', (line) => {
    N = +line;
    rl.close();
}).on('close', () => {
    const res = solution(N);
    console.log(res);
    process.exit();
});