const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let N = null; // 정점 개수
let E = null; // 간선 개수
let countE = 0;
let connectionInfo = [];

const solution = (N, E, connectionInfo) => {
    let graph = {};

    // Linked List 기반 (Map 방식) graph 설정 작업
    connectionInfo.forEach((info) => {
        let [s, e] = info;
        
        if (graph[s] === undefined) {
            graph[s] = [e];
        } else {
            graph[s].push(e);
        }

        if (graph[e] === undefined) {
            graph[e] = [s];
        } else {
            graph[e].push(s);
        }
    });

    let visited = Array(N + 1).fill(false);
    let virusCount = 0;

    // 컴퓨터가 어디까지 연결되어 있는지 확인 -> DFS 적합
    const dfs = (v) => {
        visited[v] = true;

        // 1번 컴퓨터를 통해 바이러스 걸린 컴퓨터의 수를 구하는 것이므로
        // 정점 1번인 경우에는 숫자를 세지 않는다.
        if (v !== 1) {
            virusCount++;
        }

        // 연결된 정점이 존재하지 않을 수도 있음..!!!
        if (graph[v] === undefined) return;
        for (let i = 0; i < graph[v].length; i++) {
            let newV = graph[v][i];
            if (!visited[newV]) {
                dfs(newV);
            }
        }
    }

    dfs(1);
    
    return virusCount;
}

rl.on('line', (line) => {
    if (!N) {
        N = +line;
    } else if (!E) {
        E = +line;
    } else if (countE < E) {
        connectionInfo.push(line.split(' ').map(e => +e));
        countE++;
    }

    if (countE === E) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(N, E, connectionInfo);
    console.log(res);
    process.exit();
});