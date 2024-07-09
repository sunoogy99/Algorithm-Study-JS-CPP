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
        const peekNode = this.front.data;
        this.front = this.front.next;
        if (!this.front) this.rear = null;
        return peekNode;
    }
}

const solution = (N, K) => {
    let visitCount = Array.from(Array(100001), () => Math.min());

    const inRange = (num) => num >= 0 && num <= 100000;

    const queue = new Queue();
    queue.enqueue(N);
    visitCount[N] = 0;

    while (!queue.isEmpty()) {
        let curPos = queue.dequeue();

        if (inRange(curPos - 1) && visitCount[curPos] + 1 < visitCount[curPos - 1]) {
            visitCount[curPos - 1] = visitCount[curPos] + 1;
            queue.enqueue(curPos - 1);
        }

        if (inRange(curPos + 1) && visitCount[curPos] + 1 < visitCount[curPos + 1]) {
            visitCount[curPos + 1] = visitCount[curPos] + 1;
            queue.enqueue(curPos + 1);
        }

        // 2배 위치로 순간 이동하는 경우 0초 소요되므로 +1 부분 제거
        if (inRange(curPos * 2) && visitCount[curPos] < visitCount[curPos * 2]) {
            visitCount[curPos * 2] = visitCount[curPos];
            queue.enqueue(curPos * 2);
        }
    }

    return visitCount[K];
}

rl.on('line', (line) => {
    [N, K] = line.split(' ').map(e => +e);
    rl.close();
}).on('close', () => {
    const res = solution(N, K);
    console.log(res);
    process.exit();
});