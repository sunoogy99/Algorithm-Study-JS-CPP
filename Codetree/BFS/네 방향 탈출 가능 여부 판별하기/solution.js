/*
    뱀이 있는 경우 : 0
    뱀이 없는 경우 : 1

    뱀한테 물리지 않고 탈출할 수 있는 경우 ? 1 : 0 출력

    BFS 유형 -> DFS로도 풀 수 있을 듯
*/

let N = null;
let M = null;
let countN = 0;

let graph = [];
const dx = [-1, 0, 1, 0];
const dy = [0, 1, 0, -1];

const solutionByBFS = (graph, visited) => {
    
}

const solutionByDFS = (graph, visited) => {
    const inRange = (x, y) => {
        return x >= 0 && x < N && y >= 0 && y < M;
    }

    const canGo = (x, y) => {
        if (!inRange(x, y)) return false;
        else if (visited[x][y] || !graph[x][y]) return false;
        else return true;
    }

    const dfs = (x, y) => {
        visited[x][y] = true;

        for (let i = 0; i < 4; i++) {
            let newX = x + dx[i];
            let newY = y + dy[i];

            if (canGo(newX, newY)) {
                dfs(newX, newY);
            }
        }
    }

    dfs(0, 0);

    if (visited[N - 1][M - 1]) {
        console.log(1);
    }
    else {
        console.log(0);
    }
}

const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

rl.on('line', (line) => {
    if (!N && !M) {
        [N, M] = line.split(' ').map(e => +e);
    }
    else {
        graph.push(line.split(' ').map(e => +e));
        countN++;
    }

    if (countN === N) {
        rl.close();
    }
}).on('close', () => {
    let visited = Array.from(Array(N), () => Array(M).fill(false));
    // solutionByDFS(graph, visited);
    solutionByBFS(graph, visited);
    process.exit();
});