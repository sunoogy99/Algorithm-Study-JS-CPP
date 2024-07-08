const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let n = null;
let m = null;
let count = 0;

let graph =  [];

class Node {
    constructor(data) {
        this.data = data;
        this.next = null;
    }
}

class Queue {
    constructor() {
        this.front = null;
        this.rear = null;
    }

    isEmpty() {
        return this.front === null && this.rear === null;
    }

    enqueue(item) {
        const newNode = new Node(item);
        if (this.isEmpty()) this.front = newNode;
        else this.rear.next = newNode;
        this.rear = newNode;
    }

    dequeue() {
        if (this.isEmpty()) return;
        let peekNode = this.front.data;
        this.front = this.front.next;
        // 노드가 1개만 존재한 경우, Queue를 빈 큐로 설정
        if (!this.front) this.rear = null;
        return peekNode;
    }
}

const solution = (n, m, graph) => {
    let visited = Array.from(Array(n), () => Array(m).fill(false));
    let dx = [-1, 0, 1, 0];
    let dy = [0, 1, 0, -1];

    const inRange = (x, y) => x >= 0 && x < n && y >= 0 && y < m;
    const canGo = (x, y) => {
        if (!inRange(x, y)) return false;
        else if (visited[x][y] || !graph[x][y]) return false;
        else return true;
    }

    // 입력 범위가 500, 500이므로 shift 기반 Queue로 구현해도 통과할 것 같음
    // 입력 받은 x, y 지점으로부터 bfs 탐색 시작
    const bfs = (x, y) => {
        const queue = new Queue();
        queue.enqueue([x, y]);
        visited[x][y] = true;
        let area = 1; // 탐색 가능한 지점부터 넓이를 반영

        while (!queue.isEmpty()) {
            let [curX, curY] = queue.dequeue();

            for (let i = 0; i < 4; i++) {
                let newX = curX + dx[i];
                let newY = curY + dy[i];

                if (canGo(newX, newY)) {
                    queue.enqueue([newX, newY]);
                    visited[newX][newY] = true;
                    area++;
                }
            }
        }

        return area;
    }

    let maxArea = 0;
    let pictures = 0;
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < m; j++) {
            if (canGo(i, j)) {
                let curArea = bfs(i, j);
                maxArea = Math.max(maxArea, curArea);
                pictures++;
            }
        }
    }

    return pictures + '\n' + maxArea;
}

rl.on('line', (line) => {
    if (!n && !m) {
        [n, m] = line.split(' ').map(e => +e);
    } else {
        graph.push(line.split(' ').map(e => +e));
        count++;
    }

    if (count === n) {
        rl.close();
    }
}).on('close', () => {
    const res = solution(n, m, graph);
    console.log(res);
    process.exit();
});