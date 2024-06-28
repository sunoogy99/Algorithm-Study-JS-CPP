// 문제 https://www.codetree.ai/missions/2/problems/places-can-go/description

// 이동할 수 있는 곳 -> 0
// 이동할 수 없는 곳 -> 1

class Queue {
    constructor() {
        this._arr = [];
    }

    enqueue(item) {
        this._arr.push(item);
    }

    dequeue() {
        return this._arr.shift();
    }

    isEmpty() {
        return this._arr.length === 0 ? true : false;
    }
}

let N = null;
let k = null;
let countN = 0;
let countK = 0;

let dx = [-1, 0, 1, 0];
let dy = [0, 1, 0, -1];

let graph = [];
let start = [];

const solution = (graph, visited, start) => {
    const inRange = (x, y) => {
        return x >= 0 && x < N && y >= 0 && y < N;
    }

    const canGo = (x, y) => {
        if (!inRange(x, y)) return false;
        else if (visited[x][y] || graph[x][y]) return false;
        else return true;
    }

    for (let [x, y] of start) {
        const queue = new Queue();

        // 0-base graph이므로 좌표에서 1씩 빼주기
        queue.enqueue([x - 1, y - 1]);
        visited[x - 1][y - 1] = true;

        while (!queue.isEmpty()) {
            let [curX, curY] = queue.dequeue();

            for (let i = 0; i < 4; i++) {
                let newX = curX + dx[i];
                let newY = curY + dy[i];

                if (canGo(newX, newY)) {
                    queue.enqueue([newX, newY]);
                    visited[newX][newY] = true;
                }
            }
        }
    }

    // 방문한 노드의 개수를 세서 저장하는 과정
    let res = visited.reduce((prev, curr) => prev + curr.filter(e => e).length, 0);
    console.log(res);
}

const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

rl.on('line', (line) => {
    if (!N && !k) {
        [N, k] = line.split(' ').map(e => +e);
    }
    else if (countN < N) {
        graph.push(line.split(' ').map(e => +e));
        countN++;
    }
    else {
        start.push(line.split(' ').map(e => +e));
        countK++;
    }

    if (countK === k) {
        rl.close();
    }
}).on('close', () => {
    let visited = Array.from(Array(N), () => Array(N).fill(false));
    solution(graph, visited, start);
    process.exit();
});