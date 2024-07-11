// DFS/BFS
const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let n = null;
let computers = [];
let count = 0;

const solution = (n, computers) => {
    let visited = Array(n).fill(false);
    let networks = 0;

    const dfs = (num) => {
        visited[num] = true;

        for (let i = 0; i < n; i++) {
            // 같은 노드 x && 방문 x && 네트워크 연결 o
            if (i != num && !visited[i] && computers[num][i]) {
                dfs(i);
            }
        }
    }

    for (let i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
            networks++;
        }
    }

    return networks;
}

rl.on('line', (line) => {
    if (!n) {
        n = +line;
    } else {
        computers.push(line.split(' ').map(e => +e));
        count++;
    }

    if (count === n) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(n, computers);
    console.log(res);
    process.exit();
});