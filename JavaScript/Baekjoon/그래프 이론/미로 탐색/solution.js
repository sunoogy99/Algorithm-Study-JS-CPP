const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let N = null;
let M = null;
let count = 0;

let graph = [];

const solution = (N, M, graph) => {
    // 해당 지점까지 이동한 최소 횟수 기록
    let minCountPath = Array.from(Array(N), () => Array(M).fill(Math.min())); // Math.min() : 양의 무한대
    let visited = Array.from(Array(N), () => Array(M).fill(false));
    let dx = [-1, 0, 1, 0];
    let dy = [0, 1, 0, -1];

    const inRange = (x, y) => {
        return x >= 0 && x < N && y >= 0 && y < M;
    }

    const canGo = (x, y) => {
        if (!inRange(x, y)) return false;
        else if (visited[x][y] || !graph[x][y]) return false;
        else return true;
    }

    const bfs = (x, y) => {
        let queue = [];
        queue.push([x, y]);
        visited[x][y] = true;
        minCountPath[x][y] = 1; // 시작점에서 시작점까지는 1칸

        while (queue.length !== 0) {
            let [curX, curY] = queue.shift();

            for (let i = 0; i < 4; i++) {
                let newX = curX + dx[i];
                let newY = curY + dy[i];

                if (canGo(newX, newY)) {
                    queue.push([newX, newY]);
                    visited[newX][newY] = true;
                    minCountPath[newX][newY] = Math.min(minCountPath[curX][curY] + 1, minCountPath[newX][newY]);
                }
            }
        }
    }

    // 1, 1 출발이지만 0-based로 구현하여 0, 0에서 시작
    bfs(0, 0);
    return minCountPath[N - 1][M - 1];
}

rl.on('line', (line) => {
    if (!N && !M) {
        [N, M] = line.split(' ').map(e => +e);
    }
    else {
        graph.push(line.split('').map(e => +e));
        count++;
    }
    
    if (count === N) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(N, M, graph);
    console.log(res);
    process.exit();
});