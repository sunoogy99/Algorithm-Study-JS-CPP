// 뱀이 있는 경우, 0
// 뱀이 없는 경우, 1


let N = null;
let M = null;
let countN = 0;
let data = [];

const dx = [0, 1];
const dy = [1, 0];

const solution = (data, visited) => {
    function inRange(x, y) {
        return x >= 0 && x < N && y >= 0 && y < M;
    }

    function canGo(x, y) {
        // 범위 밖으로 가는 경우
        if (!inRange(x, y)) {
            return false;
        }
        // 방문했거나 뱀이 존재하는 경우
        else if (visited[x][y] || !data[x][y]) {
            return false;
        }
        else {
            return true;
        }
    }

    const dfs = (x, y) => {
        // dfs 방문 체크를 먼저 해야 함 
        visited[x][y] = true;

        for (let i = 0; i < 2; i++) {
            let newX = x + dx[i];
            let newY = y + dy[i];

            if (canGo(newX, newY)) {
                dfs(newX, newY);
                // 여기서 dfs 호출 후 방문 체크하게 되면 시간 초과 발생할 수 있음
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
    // N, M이 null인 경우
    if (!N && !M) {
        [N, M] = line.split(' ').map(e => +e);
    }
    else {
        data.push(line.split(' ').map(e => +e));
        countN++;
    }

    if (countN === N) {
        rl.close();
    }
});

rl.on('close', () => {
    // solution 실행
    let visited = Array.from(Array(N), () => Array(M).fill(false));
    solution(data, visited);
    process.exit();
});