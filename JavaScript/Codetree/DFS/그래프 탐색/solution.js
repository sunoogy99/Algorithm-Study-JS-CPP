const solution = (N, data) => {
    // 여기서 dfs 수행
    // 2차원 배열 생성
    let graph = Array.from(Array(N + 1), () => Array(N + 1).fill(0));
    let visited = Array(N + 1).fill(false);
    
    for (let i = 0; i < data.length; i++) {
        let [x, y] = data[i];
        graph[x][y] = 1;
        graph[y][x] = 1;
    }

    const dfs = (vertex) => {
        for (let i = 1; i <= N; i++) {
            if (graph[vertex][i] && !visited[i]) {
                visited[i] = true;
                dfs(i);
                visitCount++;
            }
        }
    }

    visited[1] = true;
    dfs(1);
    console.log(visitCount);
}

const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let N = null;
let M = null;
let countM = 0;
let data = [];
let visitCount = 0;

rl.on('line', (line) => {
    // 여기에 입력 부분 작성
    if (!N && !M) {
        // 구조 분해 할당
        [N, M] = line.split(' ').map(e => +e);
    }
    else {
        data.push(line.split(' ').map(e => +e));
        countM++;
    }
    
    if (countM === M) {
        rl.close();
    }
}).on('close', () => {
    // 여기에 실행할 로직 작성
    solution(N, data);
    process.exit();
});