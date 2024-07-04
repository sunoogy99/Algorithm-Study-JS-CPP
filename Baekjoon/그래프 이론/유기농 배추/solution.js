const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let T = null;
let M = null;
let N = null;
let K = null;

let countT = 0;
let countK = 0;
let digPoint = [];

const solution = (M, N, digPoint) => {
    let visited = Array.from(Array(N), () => Array(M).fill(false));
    let graph = Array.from(Array(N), () => Array(M).fill(0));

    digPoint.map(pos => {
        // 입력 받을 때 y, x로 받아서 이렇게 받은 다음 그래프에는 x, y로 넣어줌
        let [y, x] = pos;
        graph[x][y] = 1;
    });

    const dx = [-1, 0, 1, 0];
    const dy = [0, 1, 0, -1];

    // x, y가 올바른 범위에 해당되는지 검사
    const inRange = (x, y) => x >= 0 && x < N && y >= 0 && y < M;

    // 배추가 심어진 지점, 방문하지 않은 지점인지 검사
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

    let needBug = 0;

    // 모든 지점에서 DFS 수행. dfs 함수가 나온 지점이 하나의 그룹이 됨
    // 하나의 그룹 = 지렁이 한 마리 필요
    for (let i = 0; i < N; i++) {
        for (let j = 0; j < M; j++) {
            if (canGo(i, j)) {
                dfs(i, j);
                needBug++;
            }
        }
    }

    return needBug;
}

rl.on('line', (line) => {
    if (!T) {
        T = +line;
    } else if (!M && !N && !K) {
        [M, N, K] = line.split(' ').map(e => +e);
    } else {
        digPoint.push(line.split(' ').map(e => +e));
        countK++;
    }

    if (countK === K) {
        const res = solution(M, N, digPoint);
        console.log(res);
        M = null;
        N = null;
        K = null;
        digPoint = [];
        countK = 0;
        countT++;
    }

    if (countT === T) {
        rl.close();
    }
}).on('close', () => {
    process.exit();
});