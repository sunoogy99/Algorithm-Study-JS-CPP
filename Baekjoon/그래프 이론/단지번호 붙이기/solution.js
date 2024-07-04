const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let N = null;
let count = 0;
let graph = [];

const solution = (N, graph) => {
    let visited = Array.from(Array(N), () => Array(N).fill(false));

    const inRange = (x, y) => x >= 0 && x < N && y >= 0 && y < N;

    const canGo = (x, y) => {
        if (!inRange(x, y)) return false;
        else if (visited[x][y] || !graph[x][y]) return false;
        else return true;
    }

    let dx = [-1, 0, 1, 0];
    let dy = [0, 1, 0, -1];
    let townCountList = [];
    let townCount = 0;

    const dfs = (x, y) => {
        visited[x][y] = true;
        townCount++;

        for (let i = 0; i < 4; i++) {
            let newX = x + dx[i];
            let newY = y + dy[i];

            if (canGo(newX, newY)) {
                dfs(newX, newY);
            }
        }
    }


    for (let i = 0; i < N; i++) {
        for (let j = 0; j < N; j++) {
            if (canGo(i, j)) {
                dfs(i, j);
                townCountList.push(townCount);
                townCount = 0;
            }
        }
    }

    return townCountList.length + '\n' + townCountList.sort((a, b) => a - b).join('\n');
}

rl.on('line', (line) => {
    if (!N) {
        N = +line;
    } else {
        graph.push(line.split('').map(e => +e));
        count++;
    }

    if (count === N) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(N, graph);
    console.log(res);
    process.exit();
});