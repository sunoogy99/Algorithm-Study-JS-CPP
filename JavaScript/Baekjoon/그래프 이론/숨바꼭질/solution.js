const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
});

let N = null;
let K = null;

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

    enqueue(data) {
        const newNode = new Node(data);
        if (this.isEmpty()) this.front = newNode;
        else this.rear.next = newNode;

        this.rear = newNode;
    }

    dequeue() {
        if (this.isEmpty()) return;
        this.front = this.front.next;
        if (!this.front) this.rear = null;
    }

    isEmpty() {
        return this.front === null && this.rear === null;
    }

    peekFront() {
        if (this.isEmpty()) return -1;
        return this.front.data;
    }
}

const solution = (N, K) => {
    // K의 2배까지 범위가 최대이나 10만을 넘겨서는 안 됨
    let limit = 100001;
    let visitedCount = Array(limit).fill(Math.min());
    const inRange = (v) => v >= 0 && v <= limit;

    const queue = new Queue();
    queue.enqueue(N);
    visitedCount[N] = 0;

    // BFS 풀이 및 Queue dequeue 연산 O(1)으로 구현
    // shift로 구현하면 시간 초과 발생할 것 같음
    while (!queue.isEmpty()) {
        let v = queue.peekFront();
        queue.dequeue();
        let vc = visitedCount[v];

        if (inRange(v + 1)) {
            if (visitedCount[v] + 1 < visitedCount[v + 1]) {
                visitedCount[v + 1] = vc + 1;
                queue.enqueue(v + 1);
            }
        }

        if (inRange(v - 1)) {
            if (visitedCount[v] + 1 < visitedCount[v - 1]) {
                visitedCount[v - 1] = vc + 1;
                queue.enqueue(v - 1);
            }
        }

        if (inRange(v * 2)) {
            if (visitedCount[v] + 1 < visitedCount[v * 2]) {
                visitedCount[v * 2] = vc + 1;
                queue.enqueue(v * 2);
            }
        }
    }

    return visitedCount[K];
}

rl.on('line', (line) => {
    [N, K] = line.split(' ').map(e => +e);
    rl.close();
}).on('close', () => {
    const res = solution(N, K);
    console.log(res);
    process.exit();
});