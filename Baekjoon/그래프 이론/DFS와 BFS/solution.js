const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let N = null;
let M = null;
let V = null;
let countM = 0;
let connectionInfo = [];

const solution = (N, M, V, connectionInfo) => {
    let visited = Array(N + 1).fill(false);
    let graph = Array.from(Array(N + 1), () => Array(N + 1).fill(0));

    let dfsRes = '';
    let bfsRes = '';

    const graphSetting = (connectionInfo) => {
        for (let i = 0; i < connectionInfo.length; i++) {
            let [s, e] = connectionInfo[i];
            graph[s][e] = 1;
            graph[e][s] = 1;
        }
    }

    const initialVisited = (visited) => {
        for (let i = 0; i < N + 1; i++) {
            visited[i] = false;
        }
    }

    const dfs = (v) => {
        visited[v] = true;
        dfsRes += v + ' ';

        for (let i = 1; i <= N; i++) {
            if (i !== v && !visited[i] && graph[v][i]) {
                dfs(i);
            }
        }
    }

    const bfs = (v) => {
        // enqueue => push로 구현
        // dequeue => shift로 구현
        let queue = [];
        queue.push(v);
        visited[v] = true;

        while (queue.length !== 0) {
            let cur = queue.shift();
            bfsRes += cur + ' ';

            for (let i = 1; i <= N; i++) {
                if (i !== cur && !visited[i] && graph[cur][i]) {
                    queue.push(i);
                    visited[i] = true;
                }
            }
        }
    }

    graphSetting(connectionInfo);
    dfs(V);
    initialVisited(visited);
    bfs(V);
    return dfsRes + '\n' + bfsRes;
}

rl.on('line', (line) => {
    if (!N && !M && !V) {
        [N, M, V] = line.split(' ').map(e => +e);
    }
    else {
        connectionInfo.push(line.split(' ').map(e => +e));
        countM++;
    }

    if (countM === M) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(N, M, V, connectionInfo);
    console.log(res);
    process.exit();
});