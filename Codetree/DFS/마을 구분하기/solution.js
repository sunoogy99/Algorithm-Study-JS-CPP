// 벽이 있는 경우, 0
// 사람이 있는 경우, 1

// 출력 데이터
// 마을의 수
// 마을당 사람 수 오름차순으로

let N = null;
let count = 0;
let graph = [];

let dx = [-1, 0, 1, 0];
let dy = [0, 1, 0, -1];

let townPerCount = [];

const solution = (graph, visited) => {
    // 마을 사람 수 저장하는 임시 변수
    let tempPerson = 0;
    
    function inRange(x, y) {
        return x >= 0 && x < N && y >= 0 && y < N;
    }

    function canGo(x, y) {
        if (!inRange(x, y)) return false;
        else if (visited[x][y] || !graph[x][y]) return false;
        else return true;
    }
    
    function dfs(x, y) {
        visited[x][y] = true;
        tempPerson++;

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
                townPerCount.push(tempPerson);
                tempPerson = 0;
            }
        }
    }

    console.log(townPerCount.length);
    townPerCount.sort((a, b) => a - b).map(e => console.log(e));
}

const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

rl.on('line', (line) => {
    if (!N) {
        N = +line;
    }
    else {
        graph.push(line.split(' ').map(e => +e));
        count++;
    }

    if (count === N) {
        rl.close();
    }
}).on('close', () => {
    let visited = Array.from(Array(N), () => Array(N).fill(false));
    solution(graph, visited);
    process.exit();
});